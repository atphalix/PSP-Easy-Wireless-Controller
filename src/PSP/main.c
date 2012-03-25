/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** main.c
** 
** -------------------------------------------------------------------------*/

#include "util.h"

PSP_MODULE_INFO(MODULE_NAME, 0x0, 0, 3);
PSP_HEAP_SIZE_KB(1024*16);

PSP_MAIN_THREAD_ATTR(0);
PSP_MAIN_THREAD_STACK_SIZE_KB(32);

//Main thread: UDP Client
int UDPClient() {
	int error, changeProtocol=0;
	int sock, flags;
   	struct sockaddr_in serverAddress; 
	char message[17];

	memset(message, 0, sizeof message);
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
   	serverAddress.sin_port = htons(PORT);

	//Set server's IP
  	sceNetInetInetAton(g_serverIP, &serverAddress.sin_addr);

	//sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	sock = sceNetInetSocket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0) {
		printf("Error on socket(). Exiting...\n");
		sleep(5*1000*1000);
		return 0;
	} else printf("Socket created.\n");

	//Non-blocking
	flags = fcntl(sock, F_GETFL, 0);
	fcntl(sock, F_SETFL, flags | O_NONBLOCK);

	//Connect UDP socket, just so we can use send instead of sendto
	error = sceNetInetConnect(sock, &serverAddress, sizeof serverAddress);
	if(sock < 0) {
		printf("Error on connect(). Exiting...\n");
		sleep(5*1000*1000);
		return 0;
	} else printf("Connected.\n");

	sleep(500*1000);

	printf("\n\nAll set! Sending data!\n\n");

	//Display usage info
 	ShowInstructions();

	//While connected
	while(g_status >= 1) {	
		//Grab keypresses. If the user want to change protocol, set changeProtocol to 1.
		error = GrabKeyboard(message, &changeProtocol); 
        
		if(error) {
			printf("Error while grabbing key presses. Exiting...\n");
			break;
		}

		//Send
		error = sceNetInetSend(sock, message, sizeof message, 0);
	
		//If not working, show just one messsage
		if(error <= 0) {
			ClearScreen();
			printf("Send() failed. Is the server on?\nSleeping two seconds and retrying...");
			sleep(2*1000*1000);
			ClearScreen();
			ShowInstructions();
		}
		
		//Avoid error 10035 (winsock) 
		sleep(4000); //4ms

		//Check connection. Useful to support HOLD.
		CheckConnection();

		//If user want to change protocol
		if(changeProtocol) {
			sleep(1000*300); 
			ChangeProtocol();
			changeProtocol = 0; 
		}
	}
	

	//Close connection
	close(sock);

	return 0;

}

//Start main thread: TCPServer();
int ClientThread(void)
{
	int thid = 0;
	thid = sceKernelCreateThread("ClientThread", UDPClient, 0x18, 0x100000, PSP_THREAD_ATTR_USER, 0);
  	if(thid >= 0) {
    		sceKernelStartThread(thid, 0, 0);
  	}
  	return thid;
}



int main(int argc, char **argv) 
{  
	SceUID thid;

	if(InitAll()) {
		printf("Error while initializating modules. Exiting...\n");
		sceKernelSleepThread();
	}

	ClearScreen();

	//Choose network
	g_connIndex = ChooseConnection();

	//Connect to network
	ConnectToNetwork(g_connIndex, g_pspIP);
	
	printf("Connected with ip: %s\n", g_pspIP);

	//Choose Server's IP
	ChooseServerIP(g_serverIP, g_pspIP);

	//Starts client thread, user mode
	thid = ClientThread();

	if(thid < 0)
	{
		printf("Failed to start main thread. Exiting...");
	   	sceKernelSleepThread();
	}

	sceKernelStartThread(thid, 0, NULL);

	sceKernelExitDeleteThread(0);

	return 0;
}
