#include <stdio.h>
#include <enet/enet.h>

int main() {
	printf("Client!\n");

	// Setup ENet
	if (enet_initialize () != 0) {
		printf("Cannot initialize enet\n");
		return 1;
	}
	atexit(enet_deinitialize);

	// Setup client
	ENetHost *client;
	client = enet_host_create(NULL, 1, 2, 0, 0);
	if (client == NULL) {
		printf("Can't create client\n");
		return 1;
	}

	// Connect
	ENetAddress addr;
	ENetEvent event;
	ENetPeer *peer;

	enet_address_set_host(&addr, "localhost");
	addr.port = 5001;
	peer = enet_host_connect (client, &addr, 1, 0);
	if (peer == NULL) {
		printf("Can't create peer\n");
		return 1;
	}

	if (enet_host_service(client, &event, 2000) > 0 &&
			event.type == ENET_EVENT_TYPE_CONNECT) {
		printf("Connected to server\n");

		// Send a packet
		ENetPacket *pack = enet_packet_create("HELO", 5, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, pack);
		enet_host_flush(client);

		// Disconnect
		enet_peer_disconnect(peer, 0);
		enet_host_flush(client);

	} else {
		enet_peer_reset(peer);
		printf("Can't connect to server\n");
	}

	// Destroy client
	enet_host_destroy(client);
	return 0;
}

