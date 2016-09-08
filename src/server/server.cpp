#include <enet/enet.h>
#include <iostream>

#include "../core/network/protocol.h"


// ask at enet: 1) no need to destroy sent package?
//				2) can't remember right now

int main( int argc, char** argv )
{
	ENetAddress address;
	ENetHost* host;
	ENetEvent event;

	int last_player_id = 0 ;

	if( enet_initialize() != 0 )
	{
		std::cerr << "Couldn't initialize enet" << std::endl;
		exit(EXIT_FAILURE);
	}
	atexit(enet_deinitialize);

	//address.host = "127.0.0.1";
	enet_address_set_host(&address, "127.0.0.1");
	address.port = NetworkConfig::Port;

	host = enet_host_create( &address,	// the address to bind the server host to
							 32,		// allow up to 32 clients and/or outgoing connections
							 2,			// allow up to 2 channels to be used, 0 and 1
							 0,			// assume any amount of incoming bandwidth
							 0			// assume any amount of outgoing bandwidth
							 );

	if( host == nullptr )
	{
		std::cerr << "Error creating enet host" << std::endl;
		exit(EXIT_FAILURE);
	}

	while( true )
	{
		while( enet_host_service( host, &event, 5000 ) > 0 )
		{
			std::cout << "event!" << std::endl;
			switch( event.type )
			{
			case ENET_EVENT_TYPE_CONNECT:
				std::cout << "New connection from "
					<< event.peer->address.host << std::endl;
				break;

			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Msg: " << event.packet->data << std::endl;
				enet_host_broadcast(host, 0, event.packet);
				enet_host_flush(host);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << event.peer->data << " disconnected." << std::endl;
				event.peer->data = NULL;
				break;

			case ENET_EVENT_TYPE_NONE:
				std::cout << "none event" << std::endl;
				break;
			}
		}
	}

	enet_host_destroy(host);
	return 0;
}
