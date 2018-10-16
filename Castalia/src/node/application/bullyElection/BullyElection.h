#ifndef _BULLYELECTION_H_
#define _BULLYELECTION_H_

#include "VirtualApplication.h"
#include "BullyElectionPacket_m.h"

using namespace std;

enum BullyElectionTimers {
	SEND_HEARTBEAT = 1,
	CHECK_LEADER = 2,
	CHECK_ELECTION = 3,
	FAILURE = 4,
};

class BullyElection: public VirtualApplication {
 private:
	simtime_t lastHeartbeat;		// Timestamp do último heartbeat recebido
	int leaderID;								// Cada nó tem o ID do líder
	bool applying;							// Indica se o nó está participando de uma eleição
	int oks;										// Contador de OKs (ver algoritmo)

 protected:
	void startup();
	void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
	void sendHeartbeat();
	void sendLeader(unsigned short id);
	void callElection();
	void failureUtility();
	void sendOKAY(const char *dest);
	void timerFiredCallback(int);
};

#endif				// _BULLYELECTION_APPLICATIONMODULE_H_
