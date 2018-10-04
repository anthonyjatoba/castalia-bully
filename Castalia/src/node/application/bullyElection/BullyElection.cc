#include "BullyElection.h"

Define_Module(BullyElection);

void BullyElection::startup() {
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
					trace() << self << " detectou a falha do líder " << leaderID;
					callElection();
					//TODO ELEIÇÃO
				}
			setTimer(CHECK_LEADER, 5);
			break;
		}
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
				break;
			case ELECTION:
				if (working && self > theData.nodeID){
					trace() << self << " received the election from " << theData.nodeID;
					sendOKAY(source);
					callElection();
				}
				break;
			case OKAY:
				trace() << self << " received an OK from " << theData.nodeID;
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
			//tmpData.nodeID = (unsigned short)self;
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
	BullyElectionData tmpData;
	tmpData.nodeID = (unsigned short)self;
	tmpData.messageType = ELECTION;

	BullyElectionDataPacket *packet2Net = new BullyElectionDataPacket("Election pck", APPLICATION_PACKET);
	packet2Net->setExtraData(tmpData);

	toNetworkLayer(packet2Net, BROADCAST_NETWORK_ADDRESS);		//Envia seu id para a rede (tá errado o tipo da mensagem)
}

void BullyElection::sendOKAY(const char *source) {
	BullyElectionData tmpData;
	tmpData.nodeID = (unsigned short)self;
	tmpData.messageType = OKAY;

	BullyElectionDataPacket *packet2Net = new BullyElectionDataPacket("okay pck", APPLICATION_PACKET);
	packet2Net->setExtraData(tmpData);

	toNetworkLayer(packet2Net, source);		//Envia seu id para a rede (tá errado o tipo da mensagem)
}
