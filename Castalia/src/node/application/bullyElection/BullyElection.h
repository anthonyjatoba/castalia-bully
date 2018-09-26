/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2011                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Dimosthenis Pediaditakis, Yuriy Tselishchev                  *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *
 ****************************************************************************/

#ifndef _BULLYELECTION_H_
#define _BULLYELECTION_H_

#include "VirtualApplication.h"
#include "BullyElectionPacket_m.h"

using namespace std;

enum BullyElectionTimers {
	HEARTBEAT = 1,
	CHECK = 2,
};

class BullyElection: public VirtualApplication {
 private:
	bool working;

	simtime_t lastHeartbeat;

 protected:
	void startup();
	void fromNetworkLayer(ApplicationPacket *, const char *, double, double);
	void sendHeartbeat();
	void timerFiredCallback(int);
};

#endif				// _BULLYELECTION_APPLICATIONMODULE_H_
