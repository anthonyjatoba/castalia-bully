cplusplus {{
#include "ApplicationPacket_m.h"
}}

class ApplicationPacket;

enum MessageType {
    HEARTBEAT = 1;
    ELECTION = 2;
		OKAY = 3;
		LEADER = 4;
};

struct BullyElectionData {
  unsigned short nodeID;
	int messageType enum(MessageType);		//Tipo da mensagem
}

packet BullyElectionDataPacket extends ApplicationPacket {
	BullyElectionData extraData;
}
