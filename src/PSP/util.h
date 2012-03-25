/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** util.h
**
** -------------------------------------------------------------------------*/

#ifndef _util_h_
#define _util_h_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> //bzero

//PSP
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspsdk.h>
#include <pspctrl.h>
#include <psputility.h>

//PSP Net
#include <pspnet.h>
#include <pspnet_inet.h>
#include <pspnet_apctl.h>
#include <pspnet_resolver.h>

//C Net
#include <stdio.h>
#include <sys/socket.h> //socket, bind, listen, accept
#include <netinet/in.h> //struct
#include <arpa/inet.h> //htons
#include <sys/select.h> //select
#include <fcntl.h> //non-blocking flags

//PSP Display
#include <pspdisplay.h>
#include <pspgu.h>

#define MODULE_NAME "PSPWiFiTerm"
#define VERSION "1.2"

#define printf pspDebugScreenPrintf
#define sleep sceKernelDelayThread //1E-6s

#define PORT 30666

//Define analog range and tolerance
#define ANALOG_RANGE 256
#define ANALOG_TOL 75

//Globals
int g_status; //0 = not connected to AP, 1 = connected do AP, 2 = connected to AP and server's address is set
int g_currentProtocol;
int g_connIndex; //Profile number of access point
char g_pspIP[16], g_serverIP[16]; //xxx.xxx.xxx.xxx + '\0'

//Callbacks and mandatory default functions
int exit_callback(int arg1, int arg2, void *common);
int CallbackThread(SceSize args, void *argp);
int SetupCallbacks(void);

//Init everything
int InitAll();

//Clear screen and set input to right place
void ClearScreen();

//Connect to the network (profile number (int) config) and sets pspIp
int ConnectToNetwork(int config, char *pspIp);

//Print avaliable connections on the screen
int ListConnections(int selected);

//Choose connection - return selected index
int ChooseConnection();

//Prints HEX *buffer - for debugging
void printHexString(void *buff);

//Get the temporary server's IP, just to make input easier
//Assume that the three first digits are the same as the PSP's IP and the last ones are somewhat close. 
void GrabTempServerIP(char *beginning, int *lastDigit, char *pspIP);

//Make user choose server's ip - write it to char *serverIP
void ChooseServerIP(char *serverIP, char *pspIP);

//Display usage information
int ShowInstructions();

//Grab key presses - Set the string keyboard to contain the key status.
int GrabKeyboard(char *keyboard, int *changeProtocol);

//Check whether we are connected or not. In case not, connect. Useful for HOLD support.
int CheckConnection();

//Change protocol
int ChangeProtocol();

#endif
