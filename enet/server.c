#include <stdio.h>
#include <enet/enet.h>

static void service(ENetHost *host) {
	ENetEvent event;
	while (enet_host_service(host, &event, 1000) > 0) {
		switch (event.type) {

			case ENET_EVENT_TYPE_CONNECT:
				printf("A new client connected from %x:%u.\n",
						event.peer->address.host,
						event.peer->address.port);
				event.peer->data = "Client information";
				break;

			case ENET_EVENT_TYPE_RECEIVE:
				printf("Packet (%s) %u b\n",
						event.packet->data,
						event.packet->dataLength);
						//event.peer->data,
						//event.channelID);
				enet_packet_destroy(event.packet);
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconnected.\n", event.peer->data);
				event.peer->data = NULL;

			default :
				printf("Unknown event %d\n", event.type);
				break;
		}
	}
}

int main() {
	printf("Server!\n");

	// Setup ENet
	if (enet_initialize () != 0) {
		printf("Cannot initialize enet\n");
		return 1;
	}
	atexit(enet_deinitialize);

	// Setup server
	ENetAddress addr;
	ENetHost *server;
	addr.host = ENET_HOST_ANY;
	addr.port = 5001;
	server = enet_host_create(&addr, 4, 1, 0, 0);

	if (server == NULL) {
		printf("Cannot create server\n");
		return 1;
	}

	// Poll
	while (1) {
		service(server);
	}

	// Destroy server
	enet_host_destroy(server);
	return 0;
}

