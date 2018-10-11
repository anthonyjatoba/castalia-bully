#include "BullyElection.h"

Define_Module(BullyElection);

void BullyElection::startup() {
	setTimer(FAILURE, 5);
	setTimer(CHECK_LEADER, 10);		//após 10 segundos os nodes começam a checar o líder
	if (isLeader) {
		leaderID = self;
		sendLeader(self);							// o líder informa seu ID aos demais
		setTimer(SEND_HEARTBEAT, 5);	//o líder começa a enviar o heartbeat após 5 segundos
	}
}

void BullyElection::timerFiredCallback(int index) {
	switch (index) {
		case SEND_HEARTBEAT: {
			sendHeartbeat();
			lastHeartbeat = getClock();		// líder deve saber seu último HB
			setTimer(SEND_HEARTBEAT, 5);
			break;
		}
		case FAILURE: {	//periodicamente muda o estado do nó para falho ou não
			failureUtility();
			setTimer(FAILURE, 5);
			break;
		}
		case CHECK_LEADER: {
			if (getClock() - lastHeartbeat > 10) {
					trace() << self << " detected the failure from " << leaderID;
					callElection();
			} else {
				setTimer(CHECK_LEADER, 5);
			}
			break;
		}
		case CHECK_ELECTION: {
			if (oks == 0) {
					trace() << self << " declares itself leader";
					isLeader = true;
					leaderID = self;
					sendLeader(self);
					setTimer(SEND_HEARTBEAT, 0);	//o lider começa a enviar o heartbeat imediatamente
			}
			applying = false;
			oks = 0;
			cancelTimer(CHECK_ELECTION);
			break;
		}
	}
}

void BullyElection::fromNetworkLayer(ApplicationPacket * genericPacket, const char *source, double rssi, double lqi) {
	if (!working) return;
	BullyElectionDataPacket	*rcvPacket = check_and_cast<BullyElectionDataPacket*>(genericPacket);
	BullyElectionData theData = rcvPacket->getExtraData();

		switch (theData.messageType) {
			case HEARTBEAT:
				if (theData.nodeID == leaderID){
					trace() << self << " received a HB from " << theData.nodeID;
					lastHeartbeat = getClock();		//registra o instante do último HB
				}
				break;
			case LEADER:
				trace() << self << " knows the leader " << theData.nodeID;
				leaderID = theData.nodeID;		// atualiza a variável de líder
				isLeader = false;
				cancelTimer(SEND_HEARTBEAT);	// se o nó for líder, para de enviar o heartbeat
				lastHeartbeat = getClock();		// líder deve saber seu último HB
				setTimer(CHECK_LEADER, 5);
				break;
			case ELECTION:
				trace() << self << " received the election from " << theData.nodeID;
				sendOKAY(source);		//diz que está funcionando
				if (!applying)			// evita que um nó dispare mais de uma eleiçãos
					callElection();
				break;
			case OKAY:
				if (applying) {		//apenas nós participando de eleições reagem ao OK
					trace() << self << " received an OK from " << theData.nodeID << " and is not applying anymore";
					//applying = false;
					oks++;
				}
				break;
		}
}

void BullyElection::failureUtility() {
	//if (!isLeader) return;	//por enquanto apenas o líder falha

	int failureP = isLeader ? 80 : 95;
	int recoverP = 80;

	if (working) {
		if (rand() % 100 > failureP) {
			trace() << self << " has failed";
			working = false;
			cancelTimer(SEND_HEARTBEAT);
			cancelTimer(CHECK_LEADER);
			cancelTimer(CHECK_ELECTION);
			cancelTimer(FAILURE);
		}
	} else {
		if (rand() % 100 > recoverP) {
			trace() << self << " is working";
			working = true;
			setTimer(CHECK_LEADER, 0);
			setTimer(SEND_HEARTBEAT, 0);
			//setTimer(CHECK_ELECTION, 0);
			setTimer(FAILURE, 0);
		}
	}
}

void BullyElection::sendHeartbeat() {
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

void BullyElection::sendLeader(unsigned short id) {
		BullyElectionData tmpData;
		tmpData.nodeID = (unsigned short)id;
		tmpData.messageType = LEADER;

		BullyElectionDataPacket *packet2Net = new BullyElectionDataPacket("Leader pck", APPLICATION_PACKET);
		packet2Net->setExtraData(tmpData);

		toNetworkLayer(packet2Net, BROADCAST_NETWORK_ADDRESS);		//Envia seu id para a rede (tá errado o tipo da mensagem)
}

void BullyElection::callElection() {
	applying = true;
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
	setTimer(CHECK_ELECTION, 10);		//após 10 segundos os nodes começam a checar
}

void BullyElection::sendOKAY(const char *dest) {
	BullyElectionData tmpData;
	tmpData.nodeID = (unsigned short)self;
	tmpData.messageType = OKAY;

	BullyElectionDataPacket *packet2Net = new BullyElectionDataPacket("okay pck", APPLICATION_PACKET);
	packet2Net->setExtraData(tmpData);

	toNetworkLayer(packet2Net, dest);		//Envia seu id para a rede (tá errado o tipo da mensagem)
}
