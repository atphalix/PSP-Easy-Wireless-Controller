/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
**
** -------------------------------------------------------------------------*/

#include "classControle.h"
#include "classServidorUDP.h"
/*
#define _WIN32_WINNT 0x500
#include <windows.h>
#include <stdio.h>
#include "classServidorUDP.h"
#include "classControle.h"
*/


//using namespace std;

/*

        O objeto ServidorUDP recebe o comando e armazena o protocolo 
        em char ServidorUDP::protocolo[5] e o comando em char ServidorUDP::comando[5]

        O objeto Controle recede esses arumentos na função Controle::interpreta_comandos()
        e executa as operações.

*/


int main()
{
	ServidorUDP server;
	InfoCliente cliente;
	char buffer[BUFFERLEN];
	
    //KEYBDINPUT teclado;	
	
    Controle controle;
        
    while(1)
    {
            if(!server.recebe(buffer, &cliente))
            {
                //cout << buffer << cliente.ip;
                //cout << "NO MAIN: "<< server.protocolo << server.comando;
                //controle.interpreta_comandos(server.protocolo, server.comando);
                controle.interpreta_comandos2(server.comando);
                //cout << controle.errormsg;
            }
            Sleep(0);
      
    }
    
	return 0;
}



