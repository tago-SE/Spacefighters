#include <SDL.h>
#include <SDL_net.h>
#include <stdio.h>
#include <string.h>

#include "UDP.h"

int UDP(int ipNr)
{
	printf("UDP\n");


	IPaddress ip;
	UDPsocket server;
	UDPsocket client;
	UDPpacket *packets;
	UDPpacket *packetr;
	//write "127.0.0.1",1234 to connect to the server.cpp on your local machine

	server = SDLNet_UDP_Open(0); //kan va 1123 men b�r inte va de //send
	client = SDLNet_UDP_Open(1234);//recieve

	SDLNet_ResolveHost(&ip, ipNr, 1234);

	packets = SDLNet_AllocPacket(1024);
	packetr = SDLNet_AllocPacket(1024);


	//packet->address = ip;
	packets->data = "hej";
	while (1)
	{

		//printf("%c", packets->data);
		//detta skickar
		packets->address.host = ip.host;	/* Set the destination host */
		packets->address.port = ip.port;	/* And destination port */

		packets->len = strlen((char *)packets->data) + 1;

		SDLNet_UDP_Send(server, -1, packets); /* This sets the p->channel */
											  //detta �r alts� den som tar emot
		if (SDLNet_UDP_Recv(server, packetr))
		{
			printf("UDP Packet incoming\n");
			printf("\tChan:    %d\n", packetr->channel);
			printf("\tData:    %s\n", (char *)packetr->data);
			printf("\tLen:     %d\n", packetr->len);
			printf("\tMaxlen:  %d\n", packetr->maxlen);
			printf("\tStatus:  %d\n", packetr->status);
			printf("\tAddress: %x %x\n", packetr->address.host, packetr->address.port);
		}
	}




	SDLNet_UDP_Close(server);


	return 0;
}