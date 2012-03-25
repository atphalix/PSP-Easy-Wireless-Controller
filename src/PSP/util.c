/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** util.c
**
** -------------------------------------------------------------------------*/

#include "util.h"

//Default function
int exit_callback(int arg1, int arg2, void *common) {
  pspSdkInetTerm();
  sceKernelExitGame();
  return 0;
}

//Default function
int CallbackThread(SceSize args, void *argp) {
  int cbid;
  cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();
  return 0;
}

//Default function
int SetupCallbacks(void) {
  int thid = 0;
  thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
  if(thid >= 0) {
    sceKernelStartThread(thid, 0, 0);
  }
  return thid; 
}

//Init everything
int InitAll() {
	//Setups
	SetupCallbacks();

	//Init screen
	pspDebugScreenInit();

	//Load net modules
	if(sceUtilityLoadModule(PSP_MODULE_NET_COMMON) != 0) { printf("Failed on first module init!\n"); return -1; }
	if(sceUtilityLoadModule(PSP_MODULE_NET_INET) != 0) { printf("Failed on second module init!\n"); return -1; }

	//Init 
	if(pspSdkInetInit() != 0) { printf("Failed on third module init!\n"); return -1; }

	//g_status: 0 = not connected to AP and not sending
	g_status = 0;

	//Current protocol = 1
	g_currentProtocol = 1;

	return 0;
}

//Clear screen and set cursor to right position
void ClearScreen() {	
	//Clear
	pspDebugScreenClear();

	//Note: GU_ARGB(a,r,g,b)

	//Write header
	pspDebugScreenSetXY(0,0);
	pspDebugScreenSetTextColor(GU_ARGB(255,0,255,0));
	printf("PSP Easy Wireless Controller v%s", VERSION);

	//Brazil's flag -- Just a color example!
	/*
	pspDebugScreenSetTextColor(GU_ARGB(255,0,255,0)); //green
	printf(" [");
	pspDebugScreenSetTextColor(GU_ARGB(255,255,255,0)); //yellow
	printf("<");
	pspDebugScreenSetTextColor(GU_ARGB(255,0,0,255)); //bluw
	printf("o");
	pspDebugScreenSetTextColor(GU_ARGB(255,255,255,0)); //yellow
	printf(">");
	pspDebugScreenSetTextColor(GU_ARGB(255,0,255,0)); //green
	printf("]");
	*/

	//footer
	pspDebugScreenSetXY(0,31);
	pspDebugScreenSetTextColor(GU_ARGB(255,0,255,0));

	
	if(g_status >= 1) //Connected
	{		
		if(g_status == 2) //Sever's address is set
		{
			printf("MENU: Press Start+Select! | Current protocol: ");

			switch(g_currentProtocol)
			{
				case 1: printf("#1 - Keypad #1");
					break;
				case 2: printf("#2 - Keypad #2");
					break;
				case 3: printf("#3 - VLC");
					break;
				case 4: printf("#4 - Winamp");
					break;
				default: printf("#? (unrecognized)     ");
			}
		}
		
		printf("\n\nConnected! | PSP's IP: %s", g_pspIP);
		
		if(g_status == 2) printf(" | Server's IP: %s", g_serverIP);
	}
	else printf("\n\nNot connected!");

	//Reset
	pspDebugScreenSetTextColor(GU_ARGB(255,255,255,255));
	pspDebugScreenSetXY(0,3);
}

//Connect to the network (profile number (int) config) and sets
int ConnectToNetwork(int config, char *pspIp) {
   int err;
   int stateLast = -1;

   //Struct for info
   //SceNetApctlInfo * pInfo;

   //Uses profile (int)config
   err = sceNetApctlConnect(config);

   if (err != 0)
   {
      printf("Error while connecting to network: %08X\n", err);
      return 0;
   }

   printf("\n\nConnecting... (Profile #%d)\n", config);

   while (1)
   {
      int state;
      err = sceNetApctlGetState(&state);
      if (err != 0)
      {
         printf("Error while connecting to network: %x\n", err);
         break;
      }
      if (state > stateLast)
      {
         //printf("Connectiong, state %d of 4\n", state);
	 printf(".");
         stateLast = state;
      }
      if (state == 4)
         break;  // connected with static IP

      //Wait a little before polling again
      sceKernelDelayThread(50*1000); // 50ms
   }

   printf("Connected!\n");

   //Pega o IP (seta variável global ip_psp)
   sceNetApctlGetInfo(PSP_NET_APCTL_INFO_IP, pspIp);

   if(err != 0)
   {
      return -1;
   }

   //Set status to connected
   g_status = 1;

   return 0;
}

//Print avaliable connections on the screen
int ListConnections(int selected) {
	int n;

	//Number of connections
	int conn = 0;
	
	//Will hold the wlan names
	char ssid[64];

	printf("Connect to:\n\n");
	
	for(n = 1; n < 10; n++)
	{
		//If no connection available, jump to next iteration
		if (sceUtilityCheckNetParam(n) != 0) continue;

		//Get profile info
		sceUtilityGetNetParam(n, 1, ssid);

		//Print info
		printf("\n%d: SSID: %s",n, ssid);

		conn++;	
	}
	
	//If no connections available
	if(conn == 0) printf("There are no wireless set up wireless connections!");

	//Which one?
	printf("\n\n\n=> Selected: %d", selected);
	printf("\n\nUse Up/Down to select and press Start!");

	return conn;
}

//Returns select index
int ChooseConnection() {
	//Connection index
	int conn = 1;
	int n_conn;
	
	//Objeto para eventos dos botoes
	SceCtrlData ctrl;
	sceCtrlSetSamplingCycle(0); 
   	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

	//Show all connections, return the total number of available profiles
	n_conn = ListConnections(conn);

	//Loop para escolher
	while(1)
	{
		//Read buttons
		sceCtrlReadBufferPositive(&ctrl, 1);
		
		//Up
		if((ctrl.Buttons & PSP_CTRL_UP) && conn < n_conn) 
		{
			conn++;
			ClearScreen();
			ListConnections(conn);
		}
		
		//Down
		else if((ctrl.Buttons & PSP_CTRL_DOWN) && conn > 1) 
		{
			conn--;
			ClearScreen(); 
			ListConnections(conn);
		}
	
		//Start - end loop
		else if(ctrl.Buttons & PSP_CTRL_START) break;
	}
	return conn;
}

//Prints hex string - for debugging
void printHexString(void *buff) {
	int i;

	printf("Hex content on %p:\n", buff);
	
	for(i=0; *(char *)(buff + i*(sizeof(char))) != 0x00; i++) {
		printf("0x%02x ", *(unsigned char *)(buff+i*(sizeof(unsigned char))));
        }
	printf("\n");
}

//Get the first three digits from Server's ip - Assume they are the same as the PSP's IP
void GrabTempServerIP(char *beginning, int *lastDigit, char *pspIP)
{
	int nParts = 0;
	char *part;
	char editablePSPIP[16];
	char lastDigits[3];

	memset(beginning, 0, sizeof(beginning));

	//Copy so that the pspIP wont get messed up
	strcpy(editablePSPIP, pspIP);

	//Get first three digits	
	part = strtok(editablePSPIP, ".");

	while(nParts < 3) {
		//Concat
		strcat(beginning, part);
		
		//Put a '.'
		strcat(beginning, ".");

		nParts++;

		//Get next token
		part = strtok(NULL, ".");
  	}

	//Get last three digits
	strcpy(lastDigits, part);

	//Set last digits (int)
	*lastDigit = atoi(lastDigits);
}


//Chose Server's ip - write to char *g_serverIP
void ChooseServerIP(char *serverIP, char *pspIP) {
	char beginning[13]; //xxx.xxx.xxx. + '\0'
	int lastDigit;
	int done = 0;

	//Grab first 3 fields from Server's IP (assume they are the same as the PSP's ip and a close enough last digit
	GrabTempServerIP(beginning, &lastDigit, pspIP);

	//Button event structure
	SceCtrlData control;
	sceCtrlSetSamplingCycle(0); 
   	sceCtrlSetSamplingMode(PSP_CTRL_MODE_DIGITAL);

	ClearScreen(); 

	//Exibe o IP
	printf("Select the server's IP:\n\n %s<< %d >>\n\nPress Start to choose!\n", beginning, lastDigit);
	
	while(!done)
	{
		//Verifica os botoes
		sceCtrlReadBufferPositive(&control, 1);

			//Pra cima
			if(control.Buttons & PSP_CTRL_UP && lastDigit < 255) {
				lastDigit++;
				ClearScreen();  
				printf("Select the server's IP:\n\n %s<< %d >>\n\nPress Start to choose!\n", beginning, lastDigit);
				sprintf(serverIP,"%s%d", beginning, lastDigit);
				//Sleep so we count it as just one button press
				sleep(100000);
			}
		
			//Pra baixo
			else if((control.Buttons & PSP_CTRL_DOWN) && lastDigit > 0) {
				lastDigit--;
				ClearScreen(); 
				printf("Select the server's IP:\n\n %s<< %d >>\n\nPress Start to choose!\n", beginning, lastDigit);
				sprintf(serverIP,"%s%d", beginning, lastDigit);				
				//Sleep so we count it as just one button press
				sleep(100000);
			}
	
			//Start - End loop
			else if(control.Buttons & PSP_CTRL_START) {
				done = 1;
				sleep(1000000);
			} 
	}
	
	//Set status to connected and sending
	g_status = 2;
}

//Display usage information
int ShowInstructions() {
	//keypad #1
	if(g_currentProtocol == 1) printf("\nPSP in keypad #1 mode.");

	//kaypad #2
	else if(g_currentProtocol == 2) printf("\nPSP in keypad #2 mode.");

	//vlc
	else if(g_currentProtocol == 3) printf("\nPSP in VLC mode (Windows only):\n\n - X: play/pause;\n\n - O: stop;\n\n - Triangle: show progress;\n\n - Square: fullscreen On/Off;\n\n - L: go 10 seconds in the past;\n\n - R: go 10 seconds in the future;\n\n - UP: vol up; \n\n - DOWN: vol down;");

	//winamp
	else if(g_currentProtocol == 4) printf("\nPSP in Winamp mode (Windows only):\n\n - X: play;\n\n - O: pause/unpause;\n\n - Triangle: stop;\n\n - L: previous;\n\n - R: next;\n\n - UP: vol up; \n\n - DOWN: vol down;");

	return 0;
}

//Grab key presses
int GrabKeyboard(char *keyboard, int *changeProtocol) {
	SceCtrlData control;
	sceCtrlSetSamplingCycle(0); 
   	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	//Protocol
	sprintf(keyboard, "%d", g_currentProtocol);

	//Read pressed buttons
	sceCtrlReadBufferPositive(&control, 1);
		
		//Verifica os botoes soltos	
		//2
		if(control.Buttons & PSP_CTRL_UP) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//3
		if(control.Buttons & PSP_CTRL_DOWN) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//4
		if(control.Buttons & PSP_CTRL_LEFT) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//5
		if(control.Buttons & PSP_CTRL_RIGHT) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//6
		if(control.Buttons & PSP_CTRL_SQUARE) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//7
		if(control.Buttons & PSP_CTRL_CIRCLE) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//8
		if(control.Buttons & PSP_CTRL_CROSS) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//9
		if(control.Buttons & PSP_CTRL_TRIANGLE) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//10
		if(control.Buttons & PSP_CTRL_LTRIGGER) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//11
		if(control.Buttons & PSP_CTRL_RTRIGGER) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//12
		if(control.Buttons & PSP_CTRL_START) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//13
		if(control.Ly > ANALOG_RANGE/2 + ANALOG_TOL) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//14
		if(control.Ly < ANALOG_RANGE/2 - ANALOG_TOL) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//15
		if(control.Lx > ANALOG_RANGE/2 + ANALOG_TOL) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//16
		if(control.Lx < ANALOG_RANGE/2 - ANALOG_TOL) strcat (keyboard, "1"); else strcat (keyboard, "0");
		//17
		if(control.Buttons & PSP_CTRL_SELECT) strcat(keyboard, "1"); else strcat (keyboard, "0");

		//To change protocol, press START + SELECT
		if((control.Buttons & PSP_CTRL_SELECT) && (control.Buttons & PSP_CTRL_START)) {
			*changeProtocol = 1;
		}

		return 0;
}

//Check whether we are connected or not. In case not, connect. Useful for HOLD support.
int CheckConnection() {
	int connState;

	//Pega o estado da conexao e retorna no ponteiro
	sceNetApctlGetState(&connState);

	if(connState == PSP_NET_APCTL_STATE_DISCONNECTED) {
		//Set status to disconnected
		g_status = 0;

		ClearScreen();
		printf("\nConnection dropped! Trying to reconnect...\n");
		//Connect to network
		ConnectToNetwork(g_connIndex, g_pspIP);

		//Check if we are reconnected
		sceNetApctlGetState(&connState);

		if(connState == PSP_NET_APCTL_STATE_DISCONNECTED) {
			return -1;
		}
		else 
		{
			//Connected and server's ip is set
			g_status = 2;
			
			ClearScreen();
			printf("Reconnected!");
			ShowInstructions();
			return 0;
		}
	}
	//We are already connected...
	else {
		return 0;
	}
}

//Change protocol
int ChangeProtocol() {
	int protocol = g_currentProtocol;
	SceCtrlData control;

	sceCtrlSetSamplingCycle(0); 
   	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	ClearScreen(); 

	//Usage
	printf("\nSelect: \n\n1)Use as keypad #1;\n2)Use as keypad #2;\n3)VLC (windows only);\n4)Winamp (windows only);\n\n=> Selected: '%d'\n\nPress Up/Down and Start to choose!",protocol);

	while(1) {
		//Read
		sceCtrlReadBufferPositive(&control, 1);
		
		if((control.Buttons & PSP_CTRL_UP) && (protocol < 4)) {
			protocol++;
			ClearScreen(); 
                   	//Usage
			printf("\nSelect: \n\n1)Use as keypad #1;\n2)Use as keypad #2;\n3)VLC (windows only);\n4)Winamp (windows only);\n\n=> Selected: '%d'\n\nPress Up/Down and Start to choose!",protocol);
			//Sleep so we count only once
			sleep(100000);
		}
		
		else if((control.Buttons & PSP_CTRL_DOWN) && (protocol > 1)) {
			protocol--;
			ClearScreen(); 
                   	//Usage
			printf("\nSelect: \n\n1)Use as keypad #1;\n2)Use as keypad #2;\n3)VLC (windows only);\n4)Winamp (windows only);\n\n=> Selected: '%d'\n\nPress Up/Down and Start to choose!",protocol);
			//Sleep so we count only once
			sleep(100000);
		}
	
		//Select - end loop
		else if(control.Buttons & PSP_CTRL_START)
			break;
	}
	
	sleep(100000);

	//Set new protocol
	g_currentProtocol = protocol;

	ClearScreen();

	ShowInstructions();

	return protocol;
}

