#ifndef RAKNETEXAMPLE_H
#define RAKNETEXAMPLE_H

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h" // getMessageIdentifier();
#include "reference.h"
#include "ustring.h"
#include "array.h"

class RakNetExample : public Reference
{
	OBJ_TYPE(RakNetExample, Reference);

	protected:
		// Specify the methods which can be called from a script within the
		// Godot engine.
		static void _bind_methods();

	public:
		RakNetExample();
		~RakNetExample();
		// Calls the Startup function of the rakPeer on the specified port.
		// The maximum number of allowed connections are hard coded, if you
		// want more than peer to peer connection, check the startup and listen
		// functions. For more information refer to the RakNet documentation.
		void startup(int = 0);
		// Calls the Shutdown function of the rakPeer, with 1 second block time.
		void shutdown();
		// Sets the number of the maximum incoming connections to 1.
		void listen();
		// Sends a connection request to the specified address. Takes the IP
		// as a Godot String.
		void connect(String, int);
		// Loops through the received packets, and returns an array of strings
		// which specify the identifier of each packet.
		// Since we are using the Godot's core classes, we can use this function
		// easily within a Godot script.
		Array receivePackets();

	private:
		RakNet::RakPeerInterface *rakPeer;
		RakNet::Packet *packet;
		// Returns a human readable message depending on the message identifier
		// of the received packet.
		String getMessageIdentifier(unsigned char);
};

#endif // RAKNETEXAMPLE_H
