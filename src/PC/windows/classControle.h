/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
**
** -------------------------------------------------------------------------*/

#ifndef _classControle_h_
#define _classControle_h_

#define _WIN32_WINNT 0x500
#include <windows.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "codes.h"


#define SIZEOFKEYBOARDMSG 30

using namespace std;

class Controle
{
      public:
          //Window Handler! - Deprecated! This is now a global var declared in classControle.cpp
          //HWND g_hWnd;
          
          //Estruturas para envio das teclas
          KEYBDINPUT teclado; 
	      INPUT input; 
	      WORD tecla; //É o char[] em WinAPI
	      bool virt; //A tecla é virtual ou nao?
	      bool apertou; //apertou = true; soltou = false;
	      
          bool apertados[SIZEOFKEYBOARDMSG];
          
          //Protocolo atual
          int protocoloAtual;
          
          
          char prot[4];
          char comd[4];
          
          char errormsg[256];
          bool error;
          
          Controle();
                    
          //BOOL CALLBACK FindVLC(HWND hWnd, LPARAM lParam);
          
          
          int interpreta_comandos(char protocolo[4], char comando[4]);
          int interpreta_comandos2(char teclado[SIZEOFKEYBOARDMSG]);
          
          int apertateste(WORD tecla, int indice_no_vetor);
          int soltateste(WORD tecla, int indice_no_vetor);
          
          int localiza_janela(char prot[4]);
                    
          
      private:
      
          int manipula_teclado(char comando[4]);
          int manipula_vlc(char comando[4]);
          int manipula_winamp(char comando[4]);
            
      
};

#endif
