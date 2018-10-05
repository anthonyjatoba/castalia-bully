#include "BullyElection.h"

Define_Module(BullyElection);

void BullyElection::startup() {
	working = true;
	sendLeader();									//o líder informa aos demais
	setTimer(SEND_HEARTBEAT, 5);	//o sink começa a enviar o heartbeat após 5 segundos
	setTimer(CHECK_LEADER, 10);		//após 10 segundos os nodes começam a checar
}

void BullyElection::timerFiredCallback(int index) {
	switch (index) {
		case SEND_HEARTBEAT: {
			sendHeartbeat();
			setTimer(SEND_HEARTBEAT, 5);
			break;
		}
		case CHECK_LEADER: {
			if (!isLeader && getClock() - lastHeartbeat > 5) {
					trace() << self << " detectou a falha do líder " << leaderID << "and is electioneering";
					if (!electioneering)
						callElection();
			}
			setTimer(CHECK_LEADER, 15);
			break;
		}
		case CHECK_ELECTION: {
			trace() << self << " vai verificar a eleição";
			trace() << "\telectioneering=" << electioneering << ", oks=" << oks;
			if (electioneering && oks == 0) {
					trace() << self << " não recebeu resposta e se declara líder";
					isLeader = true;
					sendLeader();
			}
			electioneering = false;
			oks = 0;
		}
			break;
	}
}

void BullyElection::fromNetworkLayer(ApplicationPacket * genericPacket, const char *source, double rssi, double lqi) {
	BullyElectionDataPacket	*rcvPacket = check_and_cast<BullyElectionDataPacket*>(genericPacket);
	BullyElectionData theData = rcvPacket->getExtraData();

		switch (theData.messageType) {
			case HEARTBEAT:
				trace() << self << " received a HB from " << theData.nodeID;
				lastHeartbeat = getClock();	//registra o instante do último HB
				break;
			case LEADER:
				trace() << self << " knows the leader " << theData.nodeID;
				leaderID = theData.nodeID;	// atualiza a variável de líder
				lastHeartbeat = getClock();	//registra o instante do último HB
				working = true;
				electioneering = false;
				isLeader = false;
				oks = 0;
				break;
			case ELECTION:
				if (working && !isLeader) {
					trace() << self << " received the election from " << theData.nodeID;
					sendOKAY(source);
					if (!electioneering)
						callElection();
				}
				break;
			case OKAY:
				trace() << self << " received an OK from " << theData.nodeID << " and is not electioneering anymore";
				//electioneering = false;
				oks++;
				break;
		}
}

void BullyElection::sendHeartbeat() {
	if (isLeader) {
		if (working) {
			working = rand() % 100 > 70 ? true : false;		//30% de chance de travar
		} else {
			working = rand() % 100 > 70 ? true : false;		//Um node travado tem 30% de chance de voltar a funcionar
		}

		trace() << "Leader" << (working ? " is working" : " has failed");

		// cria e envia o pacote de HB
		if (working) {
			BullyElectionData tmpData;
			tmpData.nodeID = (unsigned short)self;
			tmpData.messageType = HEARTBEAT;

			BullyElectionDataPacket *packet2Net = new BullyElectionDataPacket("Heartbeat pck", APPLICATION_PACKET);
			packet2Net->setExtraData(tmpData);

			toNetworkLayer(packet2Net, BROADCAST_NETWORK_ADDRESS);		//Envia seu id para a rede (tá errado o tipo da mensagem)
		}
	}
}

void BullyElection::sendLeader() {
	if (isLeader) {
		BullyElectionData tmpData;
		tmpData.nodeID = (unsigned short)self;
		tmpData.messageType = LEADER;

		BullyElectionDataPacket *packet2Net = new BullyElectionDataPacket("Leader pck", APPLICATION_PACKET);
		packet2Net->setExtraData(tmpData);

		toNetworkLayer(packet2Net, BROADCAST_NETWORK_ADDRESS);		//Envia seu id para a rede (tá errado o tipo da mensagem)
	}
}

void BullyElection::callElection() {
	electioneering = true;
	oks = 0;

	BullyElectionData tmpData;
	tmpData.nodeID = (unsigned short)self;
	tmpData.messageType = ELECTION;

	for (int i = self+1; i < numNodes; i++) {
		BullyElectionDataPacket *packet2Net = new BullyElectionDataPacket("Election pck", APPLICATION_PACKET);
		packet2Net->setExtraData(tmpData);

		string destString = to_string(i);
		char const *dest = destString.c_str();  //use char const* as target type

		toNetworkLayer(packet2Net, dest);		//Envia seu id para a rede (tá errado o tipo da mensagem)
	}
	setTimer(CHECK_ELECTION, 15);		//após 10 segundos os nodes começam a checar
}

void BullyElection::sendOKAY(const char *source) {
	BullyElectionData tmpData;
	tmpData.nodeID = (unsigned short)self;
	tmpData.messageType = OKAY;

	BullyElectionDataPacket *packet2Net = new BullyElectionDataPacket("okay pck", APPLICATION_PACKET);
	packet2Net->setExtraData(tmpData);

	toNetworkLayer(packet2Net, source);		//Envia seu id para a rede (tá errado o tipo da mensagem)
}
