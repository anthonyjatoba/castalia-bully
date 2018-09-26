#include "BullyElection.h"

Define_Module(BullyElection);

void BullyElection::startup() {
	setTimer(HEARTBEAT, 5);	//o sink começa a enviar o heartbeat após 5 segundos
	setTimer(CHECK, 10);		//após 10 segundos os nodes começam a checar
}

void BullyElection::timerFiredCallback(int index) {
		switch (index) {
		case HEARTBEAT:{
				sendHeartbeat();
				setTimer(HEARTBEAT, 5);
				break;
		}
		case CHECK: {
			if (!isLeader) {
				if (getClock() - lastHeartbeat > 5){		//se passou 5 segundos sem receber o heartbeat, detecta a falha
					trace() << self << " detectou a falha";
					//TODO ELEIÇÃO
					toNetworkLayer(createGenericDataPacket(self, 1), BROADCAST_NETWORK_ADDRESS);		//Envia seu id para a rede
					//newPacket->setData(data);
					//newPacket->setSequenceNumber(seqNum);
					//for (int i = self+1; i < netSize; i++){
						//toNetworkLayer(createGenericDataPacket(self, 1), i);
					//}
				}
				setTimer(CHECK, 5);
				break;
			}
		}
	}
}

void BullyElection::fromNetworkLayer(ApplicationPacket * genericPacket, const char *source, double rssi, double lqi) {
	if (isLeader){

	} else {
		ApplicationPacket *rcvPacket = check_and_cast<ApplicationPacket*>(genericPacket);
		trace() << self << " received a package from " << rcvPacket->getData();
		lastHeartbeat = getClock();
	}
}

void BullyElection::sendHeartbeat() {
	if (isLeader){
		if (working){
			working = rand() % 100 > 20 ? true : false;		//20% de chance de travar
		} else {
			working = rand() % 100 > 70 ? true : false;		//Um node travado tem 30% de chance de voltar a funcionar
		}

		trace() << "O lider" << (working ? " está funcionando normalmente" : " está travado");

		if (working) {
			toNetworkLayer(createGenericDataPacket(self, 1), BROADCAST_NETWORK_ADDRESS);		//Envia seu id para a rede
		} else {
			//faz nada
		}
	}
}
