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

#include "ValueReporting.h"

Define_Module(ValueReporting);

void ValueReporting::startup() {
	maxSampleInterval = ((double)par("maxSampleInterval")) / 1000.0;
	minSampleInterval = ((double)par("minSampleInterval")) / 1000.0;
	currSentSampleSN = 0;
	randomBackoffIntervalFraction = genk_dblrand(0);
	sentOnce = false;
//	setTimer(REQUEST_SAMPLE, maxSampleInterval * randomBackoffIntervalFraction);
	setTimer(HEARTBEAT, 10);
	//trace() << mobilityModule->getLocation().x << "," << mobilityModule->getLocation().y;
}

void ValueReporting::timerFiredCallback(int index) {
	switch (index) {
		case REQUEST_SAMPLE:{
			//requestSensorReading();
			//setTimer(REQUEST_SAMPLE, maxSampleInterval);
			break;
		}
		case HEARTBEAT:{
			setTimer(HEARTBEAT, 10);
			sendHeartbeat();
			//requestSensorReading();
			//setTimer(REQUEST_SAMPLE, maxSampleInterval);
			break;
		}
	}
}

void ValueReporting::fromNetworkLayer(ApplicationPacket * genericPacket,
		 const char *source, double rssi, double lqi) {
	//ValueReportingDataPacket *rcvPacket = check_and_cast<ValueReportingDataPacket*>(genericPacket);
	//ValueReportData theData = rcvPacket->getExtraData();

	//ApplicationPacket *rcvPacket = check_and_cast<ApplicationPacket*>(genericPacket);
	trace() << self << " received a package";
	//trace() << self << " knows " << rcvPacket->getData() << " is alive!";

	//if (isSink)
		//trace() << self << "received from: " << theData.nodeID << " \tvalue=" << rcvPacket->getData();

}

void ValueReporting::handleSensorReading(SensorReadingMessage * rcvReading) {
	// int sensIndex =  rcvReading->getSensorIndex();
	// string sensType(rcvReading->getSensorType());
	double sensValue = rcvReading->getSensedValue();

	// schedule the TX of the value
	trace() << self << " sensed = " << sensValue;

	ValueReportData tmpData;
	tmpData.nodeID = (unsigned short)self;
	tmpData.locX = mobilityModule->getLocation().x;
	tmpData.locY = mobilityModule->getLocation().y;

	ValueReportingDataPacket *packet2Net =
	    new ValueReportingDataPacket("Value reporting pck", APPLICATION_PACKET);
	packet2Net->setExtraData(tmpData);
	packet2Net->setData(sensValue);
	packet2Net->setSequenceNumber(currSentSampleSN);
	currSentSampleSN++;

	toNetworkLayer(packet2Net, SINK_NETWORK_ADDRESS);
	sentOnce = true;

}

void ValueReporting::sendHeartbeat() {
	working = rand() % 100 > 20 ? true : false;

	trace() << self << (working ? " tá massa" : " travou");
	//TODO TEM QUE AJEITAR!
	if (working){
		ApplicationPacket *packet2Net = new ApplicationPacket("Heartbeat", APPLICATION_PACKET);
		packet2Net->setData(self);
		packet2Net->setSequenceNumber(currSentSampleSN);
		currSentSampleSN++;
		//toNetworkLayer(packet2Net);
	} else {
		//faz nada
	}
}
