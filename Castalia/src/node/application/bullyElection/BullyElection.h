#ifndef _BULLYELECTION_H_
#define _BULLYELECTION_H_

#include "VirtualApplication.h"
#include "BullyElectionPacket_m.h"

using namespace std;

enum BullyElectionTimers {
	SEND_HEARTBEAT = 1,
	CHECK_LEADER = 2,
};

class BullyElection: public VirtualApplication {
 private:
	bool working;								//Indica se o nó está funcionando normalmente
	simtime_t lastHeartbeat;		//Timestamp do último heartbeat recebido
	int leaderID;

 protected:
	void startup();
	void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
	void sendHeartbeat();
	void sendLeader();
	void callElection();
	void sendOKAY(const char *source);
	void timerFiredCallback(int);
};

#endif				// _BULLYELECTION_APPLICATIONMODULE_H_
