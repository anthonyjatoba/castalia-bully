package node.application.bullyElection;

// The sensor node module. Connects to the wireless channel in order to communicate
// with other nodes. Connects to psysical processes so it can sample them.

simple BullyElection like node.application.iApplication {
 parameters:
 	string applicationID = default ("bullyElection");
	bool collectTraceInfo = default (true);
	int priority = default (1);
	int packetHeaderOverhead = default (8);	// in bytes
	int constantDataPayload = default (12);	// in bytes
	bool isSink = default (false);
  bool isLeader = default (false);
  int numNodes = default (1);
 gates:
 	output toCommunicationModule;
	output toSensorDeviceManager;
	input fromCommunicationModule;
	input fromSensorDeviceManager;
	input fromResourceManager;
}
