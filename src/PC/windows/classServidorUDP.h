/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
**
** -------------------------------------------------------------------------*/

#ifndef _classServidorUDP_h_
#define _classServidorUDP_h_

#include <iostream>
#include <stdlib.h>
#include <winsock2.h>

/* A mensagem será enviada como:
     PROT|COMD         
*/


#define PORTA 30666
#define PORTA2 30667
#define BUFFERLEN 30

struct InfoCliente
{
       char nome[20];
       char ip[20];
};

class ServidorUDP
{
	public:
        WSADATA wsa;
		SOCKET socket_ouvidor;
		
		char ip[20];
		char nome[50];
		sockaddr_in endereco_servidor, endereco_cliente;
		int tamanho_endereco;
		
		char buffer[100];
		char bufferlen2;
		int tamanho_buffer;
		
		char protocolo[4+1];
		//char comando[4+1];
		char comando[BUFFERLEN];

        bool erro;
		char errormsg[256];

	ServidorUDP();
	
	~ServidorUDP();

    int recebe(char texto[BUFFERLEN], struct InfoCliente * cliente);
    
    int manipula_string(char string[BUFFERLEN]);
    
    void escreve_erro(char texto_erro[256]);

};


#endif
