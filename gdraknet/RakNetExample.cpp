#include "RakNetExample.h"

RakNetExample::RakNetExample()
{
	this->rakPeer = RakNet::RakPeerInterface::GetInstance();
}

RakNetExample::~RakNetExample()
{
	this->shutdown();
	RakNet::RakPeerInterface::DestroyInstance(this->rakPeer);
}

void RakNetExample::startup(int port_)
{
	RakNet::SocketDescriptor socketDescriptor(port_, 0);
	this->rakPeer->Startup(1, &socketDescriptor, 1);
}

void RakNetExample::shutdown()
{
	this->rakPeer->Shutdown(1000);
}

void RakNetExample::listen()
{
	this->rakPeer->SetMaximumIncomingConnections(1);
}

void RakNetExample::connect(String ip_, int port_)
{
	// Convert Godot String to Godot's CharString
	CharString csIp = ip_.ascii();
	// Use CharString's get_data() method to get a C-style string
	this->rakPeer->Connect(csIp.get_data(), port_, 0, 0);
}

Array RakNetExample::receivePackets()
{
	Array packets;

	// Even though we intend to call this function every frame, it is a good
	// practice to loop until there is no packet left to receive.
	// This would prevent the packets from buffering up in case more than one
	// packet is received per frame. You can check the RakNet documentation
	// for more information.
	for(this->packet = this->rakPeer->Receive();
		this->packet;
		this->rakPeer->DeallocatePacket(this->packet),
			this->packet = this->rakPeer->Receive())
	{
		// For now we are only interested in the first byte of the packet, which
		// is it's message identifier.
		String description = this->getMessageIdentifier(this->packet->data[0]);
		packets.push_back(description);
	}

	return packets;
}

String RakNetExample::getMessageIdentifier(unsigned char id_)
{
	String description;

	switch(id_)
	{
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			description = "Remote peer has disconnected";
			break;
		case ID_REMOTE_CONNECTION_LOST:
			description = "Remote peer has lost the connection";
			break;
		case ID_NEW_INCOMING_CONNECTION:
			description = "Remote peer has connected";
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			description = "Our connection reuqest has been accepted";
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			description = "Connection limit reached";
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			description = "Disconnected from a peer";
			break;
		case ID_CONNECTION_LOST:
			description = "Connection lost from a peer";
			break;
		default:
			description = "Received packet with unspecified identifier";
			break;
	}

	return description;
}

void RakNetExample::_bind_methods()
{
	ObjectTypeDB::bind_method("startup", &RakNetExample::startup);
	ObjectTypeDB::bind_method("shutdown", &RakNetExample::shutdown);
	ObjectTypeDB::bind_method("listen", &RakNetExample::listen);
	ObjectTypeDB::bind_method("connect", &RakNetExample::connect);
	ObjectTypeDB::bind_method("receive_packets",
								&RakNetExample::receivePackets);
}
