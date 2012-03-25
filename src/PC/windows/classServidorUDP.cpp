/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
**
** -------------------------------------------------------------------------*/

#include "classServidorUDP.h"

using namespace std;

ServidorUDP::ServidorUDP()
{
                          
    cout << "PSP Easy Wireless Controller Server - v.1.2 - r4pha" << endl << endl;
    
    int nonblocking = 1;
	//Seta o tamanho do endereço
    int tamanho_endereco = sizeof(struct sockaddr_in);
    
    //Inicia  WSA
    WSAStartup(MAKEWORD(1,1),&wsa);
    
    //Comprimento do buffer a ser recebido
    bufferlen2 = 16; //Mudei
   
    //Armazenará informações do servidor
    struct hostent * host;

	//Cria o sock - UDP
	if ((socket_ouvidor = socket(AF_INET, SOCK_DGRAM, 0)) != INVALID_SOCKET)
	{
         //Limpa o endereco_servidor
    	memset(&endereco_servidor, 0, sizeof(endereco_servidor)); 
    	
    	//Seta os parâmetros do endereco_servidor
    	endereco_servidor.sin_family = AF_INET;
        endereco_servidor.sin_addr.S_un.S_addr = ADDR_ANY;
        endereco_servidor.sin_port = htons(PORTA);
     
       	//Abre a porta - binda
		if((bind(socket_ouvidor, (sockaddr *)&endereco_servidor, sizeof(endereco_servidor))) == 0)
        {
             //Seta o sock como non-blocking
             if(ioctlsocket(socket_ouvidor, FIONBIO, (u_long FAR*) &nonblocking) == 0)
             {
                 //Deu tudo certo
                 ioctlsocket(socket_ouvidor, FIONBIO, (u_long FAR*) &nonblocking);
                 
                 //Seta o nome do computador
                 gethostname(nome, sizeof(nome));
                 
                 //Seta o ip do servidor
                 host = gethostbyname(nome);
                 endereco_servidor.sin_addr.s_addr = *(u_long *)(host->h_addr_list[0]);
                 sprintf(ip, inet_ntoa(endereco_servidor.sin_addr));
    
                 cout << "Socket successfully created! Listening no ip: " << ip << " - port: "<< PORTA << endl << endl << "-------------------------------------------------------"  << endl << endl;
                 erro = false;
              }
              else escreve_erro("Error when setting socket to non-blocking.");          
                                               
        }
        else escreve_erro("Error on bind(). Maybe you already have a server running?");
     }
     else escreve_erro("Error creating the socket.");
}

int ServidorUDP::recebe(char texto[BUFFERLEN], struct InfoCliente * cliente)
{
     //Pega o tamanho da string ip da struct InfoCliente
     DWORD len = sizeof(cliente->ip);
     
     int tamanho_endereco2 = sizeof(struct sockaddr_in);
     
     int erro;
     
     memset(texto, 0, sizeof(texto));  
       
     //Caso recebeu algum byte
     if(recvfrom(socket_ouvidor, texto, BUFFERLEN, 0, (sockaddr *)&endereco_cliente, &tamanho_endereco2) > 0)
     {
        //cout << "Received: " << texto << " len: " << strlen(texto) <<  endl;
                                        
         //Se a string enviada é válida
         if(!manipula_string(texto))
         {
             //Modifica os valores da struct cliente
             WSAAddressToString((sockaddr *) &endereco_cliente, sizeof(endereco_cliente), 0, cliente->ip, &len);
             
             //Teste
             //cout << "Protocolo: " << protocolo << endl << "Comando: " << comando << endl << endl;
                                          
             return 0;                
         }
         //String inválida
         else
         {
             escreve_erro("Invalid string received.\n");
             return -1;
         }                                                            
     }
     //Não recebeu nada
     else
     {
          //teste
         //cout << texto;
         
         //cout << "   - erro: " << WSAGetLastError() << endl;

         //escreve_erro("Nao recebeu nada recvfrom");
         return -1;
     }
}

int ServidorUDP::manipula_string(char *string)
{
     //Test
     //cout << string << endl;

     if(strlen(string) <= BUFFERLEN)
     {
         strcpy(comando, string);         
     }
     else
     {
         escreve_erro("Unrecognized string received.");
         return -1;
     }
     
     return 0;
}

void ServidorUDP::escreve_erro(char texto_erro[256])
{
     sprintf(errormsg, texto_erro);
     erro = true;
     cout << errormsg;
}

ServidorUDP::~ServidorUDP()
{
     //freeaddrinfo(endereco_servidor);
     
     closesocket(socket_ouvidor);          
}
