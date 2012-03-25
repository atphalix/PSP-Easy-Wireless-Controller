/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
**
** -------------------------------------------------------------------------*/

#include "classControle.h"

using namespace std;

HWND g_hWnd;


/*
                PROTOCOLOS
                            1 - tecl
                            2 - vlcp
                            3 - wina
                            4 - newc|pspp (nova conexao)             
*/

Controle::Controle()
{
                    //Começa com "null"
                    //sprintf(prot, "null");
                    
                    //Seto todos os botões como soltos
                    int i;
                    for(i=0; i<SIZEOFKEYBOARDMSG; i++) apertados[i] = false;
                    
                    //Inicia com protocolo do teclado - só pra não dar erro;
                    protocoloAtual = PROTOCOLO_TECLADO;
}


int Controle::interpreta_comandos(char protocolo[4], char comando[4])
{   
    /************** NOVA CONEXAO **************/
        //if(!strcmp(protocolo, "newc") && !strcmp(comando, "pspp")) printf("\nNova conexao - PSP!\n");
    
    /************* INPUTS DO TECLADO *****************/
        //else if(!strcmp(protocolo, TECLADO_PROTOCOLO)) manipula_teclado(comando);
                
    /************* VLC **************/
        //else if(!strcmp(protocolo, VLC_PROTOCOLO)) manipula_vlc(comando);
             
    /************* WINAMP ***********/
       //else if(!strcmp(protocolo, WINAMP_PROTOCOLO)) manipula_winamp(comando);
               
    return 0;
}


//BOOL CALLBACK FindVLC(HWND hWnd, LPARAM lParam) {
BOOL CALLBACK FindVLC(HWND hWnd, LPARAM lParam) {
	DWORD dwThreadId, dwProcessId;
	HINSTANCE hInstance;
	char String[255];
	HANDLE hProcess;
	char * found;
    if (!hWnd)
    	return TRUE;		// Not a window
    if (!::IsWindowVisible(hWnd))
    	return TRUE;		// Not visible
    if (!SendMessage(hWnd, WM_GETTEXT, sizeof(String), (LPARAM)String))
    	return TRUE;		// No window title
    
    hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
    dwThreadId = GetWindowThreadProcessId(hWnd, &dwProcessId);
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
    //cout << hWnd << ' ' << dwProcessId << '\t' << String << '\t';
    // GetModuleFileNameEx uses psapi, which works for NT only!
    found = strstr(String,"VLC");
    if(found) {
              //cout << "ACHEI VLC!!" << endl;
              g_hWnd = hWnd;
              return FALSE;
              }   
    CloseHandle(hProcess);
    return TRUE;
}


int Controle::interpreta_comandos2(char string_recebida[SIZEOFKEYBOARDMSG])
{
       
        //If protocol = 1 -> Keypad #1
        if(string_recebida[INDICE_PROTOCOLO] == CHAR_PROTOCOLO_TECLADO)
        {
                    //Seta o protocolo
                    if(protocoloAtual != PROTOCOLO_TECLADO) protocoloAtual = PROTOCOLO_TECLADO;
                    
                    
                    //Quadrado
                    if(string_recebida[INDICE_QUADRADO] == '1') if(!apertados[INDICE_QUADRADO]) apertateste(TECLADO_0, INDICE_QUADRADO); else {} else soltateste(TECLADO_0, INDICE_QUADRADO);
                    //Triangulo
                    if(string_recebida[INDICE_TRIANGULO] == '1') if(!apertados[INDICE_TRIANGULO]) apertateste(TECLADO_1, INDICE_TRIANGULO); else {} else soltateste(TECLADO_1, INDICE_TRIANGULO);
                    //Bola
                    if(string_recebida[INDICE_BOLA] == '1') if(!apertados[INDICE_BOLA]) apertateste(TECLADO_2, INDICE_BOLA); else {} else soltateste(TECLADO_2, INDICE_BOLA);
                    //Xis
                    if(string_recebida[INDICE_XIS] == '1') if(!apertados[INDICE_XIS]) apertateste(TECLADO_3, INDICE_XIS); else {} else soltateste(TECLADO_3, INDICE_XIS);
                    //Cima
                    if(string_recebida[INDICE_UP] == '1') if(!apertados[INDICE_UP]) apertateste(TECLADO_CIMA, INDICE_UP); else {} else soltateste(TECLADO_CIMA, INDICE_UP);
                    //Baixo
                    if(string_recebida[INDICE_DOWN] == '1') if(!apertados[INDICE_DOWN]) apertateste(TECLADO_BAIXO, INDICE_DOWN); else {} else soltateste(TECLADO_BAIXO, INDICE_DOWN);
                    //Esquerda
                    if(string_recebida[INDICE_LEFT] == '1') if(!apertados[INDICE_LEFT]) apertateste(TECLADO_ESQUERDA, INDICE_LEFT); else {} else soltateste(TECLADO_ESQUERDA, INDICE_LEFT);
                    //Direita
                    if(string_recebida[INDICE_RIGHT] == '1') if(!apertados[INDICE_RIGHT]) apertateste(TECLADO_DIREITA, INDICE_RIGHT); else {} else soltateste(TECLADO_DIREITA, INDICE_RIGHT);
                    //L-Trigger
                    if(string_recebida[INDICE_L] == '1') if(!apertados[INDICE_L]) apertateste(TECLADO_4, INDICE_L); else {} else soltateste(TECLADO_4, INDICE_L);
                    //R-Trigger
                    if(string_recebida[INDICE_R] == '1') if(!apertados[INDICE_R]) apertateste(TECLADO_5, INDICE_R); else {} else soltateste(TECLADO_5, INDICE_R);
                    //Start
                    if(string_recebida[INDICE_START] == '1') if(!apertados[INDICE_START]) apertateste(TECLADO_ENTER, INDICE_START); else {} else soltateste(TECLADO_ENTER, INDICE_START);
                    //Select
                    if(string_recebida[INDICE_SELECT] == '1') if(!apertados[INDICE_SELECT]) apertateste(TECLADO_BACKSPACE, INDICE_SELECT); else {} else soltateste(TECLADO_BACKSPACE, INDICE_SELECT);
                    //Analog UP
                    if(string_recebida[INDICE_ANALOG_UP] == '1') if(!apertados[INDICE_ANALOG_UP]) apertateste(TECLADO_6, INDICE_ANALOG_UP); else {} else soltateste(TECLADO_6, INDICE_ANALOG_UP);
                    //Analog DOWN
                    if(string_recebida[INDICE_ANALOG_DOWN] == '1') if(!apertados[INDICE_ANALOG_DOWN]) apertateste(TECLADO_7, INDICE_ANALOG_DOWN); else {} else soltateste(TECLADO_7, INDICE_ANALOG_DOWN);
                    //Analog LEFT
                    if(string_recebida[INDICE_ANALOG_LEFT] == '1') if(!apertados[INDICE_ANALOG_LEFT]) apertateste(TECLADO_8, INDICE_ANALOG_LEFT); else {} else soltateste(TECLADO_8, INDICE_ANALOG_LEFT);
                    //Analog RIGHT
                    if(string_recebida[INDICE_ANALOG_RIGHT] == '1') if(!apertados[INDICE_ANALOG_RIGHT]) apertateste(TECLADO_9, INDICE_ANALOG_RIGHT); else {} else soltateste(TECLADO_9, INDICE_ANALOG_RIGHT);
        }
        
        
        //If protocol = 2 -> keypad #2
        else if(string_recebida[INDICE_PROTOCOLO] == CHAR_PROTOCOLO_TECLADO_2)
        {
                    //Seta o protocolo
                    if(protocoloAtual != PROTOCOLO_TECLADO_2) {
                                      protocoloAtual = PROTOCOLO_TECLADO_2;
                                      //cout << "Setting the protocol to: Keypad #2" << endl; //Isso vai dar pau! porque pode ter 2 players ao mesmo tempo!
                    }
                    
                    //Quadrado
                    if(string_recebida[INDICE_QUADRADO] == '1') if(!apertados[INDICE_QUADRADO]) apertateste(TECLADO2_0, INDICE_QUADRADO); else {} else soltateste(TECLADO2_0, INDICE_QUADRADO);
                    //Triangulo
                    if(string_recebida[INDICE_TRIANGULO] == '1') if(!apertados[INDICE_TRIANGULO]) apertateste(TECLADO2_1, INDICE_TRIANGULO); else {} else soltateste(TECLADO2_1, INDICE_TRIANGULO);
                    //Bola
                    if(string_recebida[INDICE_BOLA] == '1') if(!apertados[INDICE_BOLA]) apertateste(TECLADO2_2, INDICE_BOLA); else {} else soltateste(TECLADO2_2, INDICE_BOLA);
                    //Xis
                    if(string_recebida[INDICE_XIS] == '1') if(!apertados[INDICE_XIS]) apertateste(TECLADO2_3, INDICE_XIS); else {} else soltateste(TECLADO2_3, INDICE_XIS);
                    //Cima
                    if(string_recebida[INDICE_UP] == '1') if(!apertados[INDICE_UP]) apertateste(TECLADO2_CIMA, INDICE_UP); else {} else soltateste(TECLADO2_CIMA, INDICE_UP);
                    //Baixo
                    if(string_recebida[INDICE_DOWN] == '1') if(!apertados[INDICE_DOWN]) apertateste(TECLADO2_BAIXO, INDICE_DOWN); else {} else soltateste(TECLADO2_BAIXO, INDICE_DOWN);
                    //Esquerda
                    if(string_recebida[INDICE_LEFT] == '1') if(!apertados[INDICE_LEFT]) apertateste(TECLADO2_ESQUERDA, INDICE_LEFT); else {} else soltateste(TECLADO2_ESQUERDA, INDICE_LEFT);
                    //Direita
                    if(string_recebida[INDICE_RIGHT] == '1') if(!apertados[INDICE_RIGHT]) apertateste(TECLADO2_DIREITA, INDICE_RIGHT); else {} else soltateste(TECLADO2_DIREITA, INDICE_RIGHT);
                    //L-Trigger
                    if(string_recebida[INDICE_L] == '1') if(!apertados[INDICE_L]) apertateste(TECLADO2_4, INDICE_L); else {} else soltateste(TECLADO2_4, INDICE_L);
                    //R-Trigger
                    if(string_recebida[INDICE_R] == '1') if(!apertados[INDICE_R]) apertateste(TECLADO2_5, INDICE_R); else {} else soltateste(TECLADO2_5, INDICE_R);
                    //Start
                    if(string_recebida[INDICE_START] == '1') if(!apertados[INDICE_START]) apertateste(TECLADO2_ENTER, INDICE_START); else {} else soltateste(TECLADO2_ENTER, INDICE_START);
                    //Select
                    if(string_recebida[INDICE_SELECT] == '1') if(!apertados[INDICE_SELECT]) apertateste(TECLADO2_BACKSPACE, INDICE_SELECT); else {} else soltateste(TECLADO2_BACKSPACE, INDICE_SELECT);
                    //Analog UP
                    if(string_recebida[INDICE_ANALOG_UP] == '1') if(!apertados[INDICE_ANALOG_UP]) apertateste(TECLADO2_6, INDICE_ANALOG_UP); else {} else soltateste(TECLADO2_6, INDICE_ANALOG_UP);
                    //Analog DOWN
                    if(string_recebida[INDICE_ANALOG_DOWN] == '1') if(!apertados[INDICE_ANALOG_DOWN]) apertateste(TECLADO2_7, INDICE_ANALOG_DOWN); else {} else soltateste(TECLADO2_7, INDICE_ANALOG_DOWN);
                    //Analog LEFT
                    if(string_recebida[INDICE_ANALOG_LEFT] == '1') if(!apertados[INDICE_ANALOG_LEFT]) apertateste(TECLADO2_8, INDICE_ANALOG_LEFT); else {} else soltateste(TECLADO2_8, INDICE_ANALOG_LEFT);
                    //Analog RIGHT
                    if(string_recebida[INDICE_ANALOG_RIGHT] == '1') if(!apertados[INDICE_ANALOG_RIGHT]) apertateste(TECLADO2_9, INDICE_ANALOG_RIGHT); else {} else soltateste(TECLADO2_9, INDICE_ANALOG_RIGHT);
        }
        
        
        //If protocol = 3 -> VLC
        //Por enquanto é gambiarra - funciona com os atalhos do teclado (vide codes.h)
        else if(string_recebida[INDICE_PROTOCOLO] == '3')
        {
             //Seta o protocolo e procura a janela
             if(protocoloAtual != PROTOCOLO_VLC) {
                               cout << "Setting the protocol to: VLC;";
                               protocoloAtual = PROTOCOLO_VLC;
                               
                               //Tenta achar a janela do VLC - Essa função retorna false quando acha a janela.
                               if(EnumWindows(&FindVLC, NULL)) cout << " -> Could not find VLC's window.\n" << endl;
                               else {
                                    cout << " -> VLC window was found!\n" << endl;
                                    cout << "** Important: Make sure VLC's window is on top or in fullscreen! **\n\n" << endl;
                                    }
             }
                         
             //Xis - play/pause
             if(string_recebida[INDICE_XIS] == '1') if(!apertados[INDICE_XIS]) {
                                            apertateste(VLC_PLAY_KEY, INDICE_XIS);
                                            cout << "VLC::play/pause!" << endl; 
                                            } else {} else soltateste(VLC_PLAY_KEY, INDICE_XIS);
              
             //Bola - stop
             if(string_recebida[INDICE_BOLA] == '1') if(!apertados[INDICE_BOLA]){
                                              apertateste(VLC_STOP_KEY, INDICE_BOLA);
                                              cout << "VLC::stop!" << endl; 
                                              } else {} else soltateste(VLC_STOP_KEY, INDICE_BOLA);
             
             //Quadrado - fullscreen
             if(string_recebida[INDICE_QUADRADO] == '1') if(!apertados[INDICE_QUADRADO]){
                                                  apertateste(VLC_FULLSCREEN_KEY, INDICE_QUADRADO); 
                                                  cout << "VLC::fullscreen!" << endl; 
                                                  } else {} else soltateste(VLC_FULLSCREEN_KEY, INDICE_QUADRADO);
             
             //Triangulo - Mostra o tempo
             if(string_recebida[INDICE_TRIANGULO] == '1') if(!apertados[INDICE_TRIANGULO]){
                                                   apertateste(VLC_SHOW_TIME_KEY, INDICE_TRIANGULO); 
                                                   cout << "VLC::show progress!" << endl; 
                                                   } else {} else soltateste(VLC_SHOW_TIME_KEY, INDICE_TRIANGULO);
             
             //UP - aumenta o volume
             if(string_recebida[INDICE_UP] == '1') {
                                           if(!apertados[INDICE_UP]) {
                                                                     apertateste(VLC_NUM_LOCK, NULL); soltateste(VLC_NUM_LOCK, NULL); //Desliga num lock
                                                                     apertateste(VLC_CTRL_KEY, NULL); //CTRL
                                                                     apertateste(VLC_UP_VOL_NEED_PRE_CTRL, INDICE_UP); //Cima
                                                                     soltateste(VLC_CTRL_KEY, NULL);
                                                                     apertateste(VLC_NUM_LOCK, NULL); soltateste(VLC_NUM_LOCK, NULL); //liga num lock
                                                                     cout << "VLC::vol up!" << endl; 
                                           }
             } else soltateste(VLC_UP_VOL_NEED_PRE_CTRL, INDICE_UP);          
             
             //DOWN - diminui o volume
             if(string_recebida[INDICE_DOWN] == '1') {
                                           if(!apertados[INDICE_DOWN]) {
                                                                     apertateste(VLC_NUM_LOCK, NULL); soltateste(VLC_NUM_LOCK, NULL); //Desliga num lock
                                                                     apertateste(VLC_CTRL_KEY, NULL); //CTRL
                                                                     apertateste(VLC_DOWN_VOL_NEED_PRE_CTRL, INDICE_DOWN); //Cima
                                                                     soltateste(VLC_CTRL_KEY, NULL);
                                                                     apertateste(VLC_NUM_LOCK, NULL); soltateste(VLC_NUM_LOCK, NULL); //liga num lock
                                                                     cout << "VLC::vol down!" << endl; 
                                           }
             } else soltateste(VLC_UP_VOL_NEED_PRE_CTRL, INDICE_DOWN);
             
             //L - anda 10 seg pra trás
             if(string_recebida[INDICE_L] == '1') {
                                           if(!apertados[INDICE_L]) {
                                                                     apertateste(VLC_NUM_LOCK, NULL); soltateste(VLC_NUM_LOCK, NULL); //Desliga num lock
                                                                     apertateste(VLC_ALT_KEY, NULL); //CTRL
                                                                     apertateste(VLC_BACK_10_SEC_NEED_PRE_ALT, INDICE_L); //Cima
                                                                     soltateste(VLC_ALT_KEY, NULL);
                                                                     apertateste(VLC_NUM_LOCK, NULL); soltateste(VLC_NUM_LOCK, NULL); //liga num lock
                                                                     cout << "VLC::10sec back!" << endl; 
                                           }
             } else soltateste(VLC_UP_VOL_NEED_PRE_CTRL, INDICE_L);       
             
             //R - anda 10 seg pra trás
             if(string_recebida[INDICE_R] == '1') {
                                           if(!apertados[INDICE_R]) {
                                                                     apertateste(VLC_NUM_LOCK, NULL); soltateste(VLC_NUM_LOCK, NULL); //Desliga num lock
                                                                     apertateste(VLC_ALT_KEY, NULL); //CTRL
                                                                     apertateste(VLC_FORWARD_10_SEC_NEED_PRE_ALT, INDICE_R); //Cima
                                                                     soltateste(VLC_ALT_KEY, NULL);
                                                                     apertateste(VLC_NUM_LOCK, NULL); soltateste(VLC_NUM_LOCK, NULL); //liga num lock
                                                                     cout << "VLC::10sec forward!" << endl; 
                                           }
             } else soltateste(VLC_UP_VOL_NEED_PRE_CTRL, INDICE_R);          
             
        }
        
        
        
        //Proto = 4 - winamp
        else if(string_recebida[INDICE_PROTOCOLO] == CHAR_PROTOCOLO_WINAMP)
        {
             //Seta o protocolo e acha a janela
             if(protocoloAtual != PROTOCOLO_WINAMP) {
                               cout << "Setting the protocol to: Winamp;";
                               protocoloAtual = PROTOCOLO_WINAMP;
                               g_hWnd = FindWindow(WINAMP_WINDOW_NAME, NULL);
                               if(!g_hWnd) cout << " -> Winamp window was not found! Make sure Winamp is running!\n\n" << endl;
                               else cout << " -> Winamp window was found!\n\n" << endl; 
             }
             
             //XIS - PLAY
             if(string_recebida[INDICE_XIS] == '1') {
                                            if(!apertados[INDICE_XIS]) {
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_PLAY, 0);
                                                               apertados[INDICE_XIS] = true;
                                                               cout << "Winamp::play!" << endl;    
                                            }
              }
              else {
                  apertados[INDICE_XIS] = false;
             }
             
             //BOLA - PAUSE
             if(string_recebida[INDICE_BOLA] == '1') {
                                            if(!apertados[INDICE_BOLA]) {
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_PAUSE, 0);
                                                               apertados[INDICE_BOLA] = true;
                                                               cout << "Winamp::pause!" << endl;    
                                            }
              }
              else {
                  apertados[INDICE_BOLA] = false;
             }
             
             //TRIANGULO - STOP
             if(string_recebida[INDICE_TRIANGULO] == '1') {
                                            if(!apertados[INDICE_TRIANGULO]) {
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_STOP, 0);
                                                               apertados[INDICE_TRIANGULO] = true;
                                                               cout << "Winamp::stop!" << endl;    
                                            } 
              }
              else {
                  apertados[INDICE_TRIANGULO] = false;
             }
             
             
             //L-PREV
             if(string_recebida[INDICE_L] == '1') {
                                            if(!apertados[INDICE_L]) {
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_PREV, 0);
                                                               apertados[INDICE_L] = true;
                                                               cout << "Winamp::prev!" << endl;    
                                            } 
              }
              else {
                  apertados[INDICE_L] = false;
             }
             
             //R-NEXT
             if(string_recebida[INDICE_R] == '1') {
                                            if(!apertados[INDICE_R]) {
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_NEXT, 0);
                                                               apertados[INDICE_R] = true;
                                                               cout << "Winamp::next!" << endl;    
                                            } 
              }
              else {
                  apertados[INDICE_R] = false;
             }
             
             //UP-VOL UP
             if(string_recebida[INDICE_UP] == '1') {
                                            if(!apertados[INDICE_UP]) {
                                                               //Envia tres vezes pra diminuir razoavelmente
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_VOL_UP, 0);
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_VOL_UP, 0);
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_VOL_UP, 0);
                                                               apertados[INDICE_UP] = true;
                                                               cout << "Winamp::vol up!" << endl;    
                                            } 
              }
              else {
                  apertados[INDICE_UP] = false;
             }
             
             //DOWN-VOL UP
             if(string_recebida[INDICE_DOWN] == '1') {
                                            if(!apertados[INDICE_DOWN]) {
                                                               //Envia tres vezes pra diminuir razoavelmente
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_VOL_DOWN, 0);
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_VOL_DOWN, 0);
                                                               SendMessage(g_hWnd, WM_COMMAND, WINAMP_VOL_DOWN, 0);
                                                               apertados[INDICE_DOWN] = true;
                                                               cout << "Winamp::vol down!" << endl;    
                                            } 
              }
              else {
                  apertados[INDICE_DOWN] = false;
             } 
             
             
        }
        
}



int Controle::apertateste(WORD tecla, int indice_no_vetor)
{
    
    
    //Só vou tratar teclas virtuais
    teclado.wVk = 0; //tecla; é ignorado    
    teclado.wScan = MapVirtualKey(tecla, 0);
    
    //Tecla foi pressionada, e não solta
    teclado.dwFlags = KEYEVENTF_SCANCODE;
    
    if(indice_no_vetor) //Pode ser NULL
    apertados[indice_no_vetor] = true;    
    
    //Seta tudo padrão
	teclado.time = 0;
	teclado.dwExtraInfo = 0;

    //Define o tipo do input e a origem (struct KEYBDINPUT)
	input.type = INPUT_KEYBOARD;
	input.ki = teclado;
    
    //Executa
    SendInput(1, &input, sizeof(input));
    
    //cout << "OIII" << endl; //
    
    return 0;
    
}

int Controle::soltateste(WORD tecla, int indice_no_vetor)
{
    //Só vou tratar teclas virtuais
    teclado.wVk = 0;//tecla;  é ignorado
    teclado.wScan = MapVirtualKey(tecla, 0);
    
    //Tecla pressionada
    teclado.dwFlags =  KEYEVENTF_SCANCODE|KEYEVENTF_KEYUP;
    
    if(indice_no_vetor) //Pode ser NULL
    apertados[indice_no_vetor] = false;
    
    //Seta tudo padrão
	teclado.time = 0;
	teclado.dwExtraInfo = 0;

    //Define o tipo do input e a origem (struct KEYBDINPUT)
	input.type = INPUT_KEYBOARD;
	input.ki = teclado;
    
    //Executa
    SendInput(1, &input, sizeof(input));
    
    return 0;
    
}
/*
//Seta a janela para o hWnd e retorna 0 se a janela existe e -1 em caso de erro
int Controle::localiza_janela(char protocolo[4])
{
    //Se o protocolo é VLC
    if(!strcmp(protocolo, VLC_PROTOCOLO))
    {
         //Tenta localizar a janela
         if(hWnd = FindWindow(NULL, VLC_WINDOW_NAME))
         {
             strcpy(prot, protocolo);
             //printf("achei a janela");
             return 0;
         }
         else
         {
             sprintf(errormsg, "A janela nao esta aberta.");
             cout << errormsg << endl << endl;
             
             //WinAPI::shellExecute("C:\Arquivos de programas\VideoLAN\VLC\vlc.exe", NULL);
             //system("C:\\Arquivos\/ de programas\\VideoLAN\\VLC\\vlc.exe");
             //ShellExecute(GetDesktopWindow(), NULL, "C:\\Arquivos de programas\\VideoLAN\\VLC\\vlc.exe", NULL, NULL, SW_SHOWNORMAL);
             
             return -1;
         }           
                    
    }
    //Se o protocolo é winamp
    else if(!strcmp(protocolo, WINAMP_PROTOCOLO))
    {
         SendMessage(hWnd, WM_COMMAND, WINAMP_NEXT, 0);
         //Tenta localizar a janela
         if(hWnd = FindWindow(WINAMP_WINDOW_NAME, NULL))
         {
             strcpy(prot, protocolo);
             return 0;
         }
         else
         {
             sprintf(errormsg, "A janela nao esta aberta.");
             
             //WinAPI::shellExecute("C:\Arquivos de programas\VideoLAN\VLC\vlc.exe", NULL);
             //system("C:\\Arquivos\/ de programas\\VideoLAN\\VLC\\vlc.exe");
             //ShellExecute(GetDesktopWindow(), NULL, "C:\\Arquivos de programas\\VideoLAN\\VLC\\vlc.exe", NULL, NULL, SW_SHOWNORMAL);
             return -1;
         }           
                    
    }
    //Protocolo inválido
    else
    {
        sprintf(errormsg, "Protocolo invalido.");
        return -1;
    }
}


int Controle::manipula_teclado(char comando[4])
{
    
    
              //  Vai receber uma string do tipo ape* ou sol*
              //  tratar como apertado ou solto
    
    
    //EXIBE NA TELA = TESTE;
    //cout << comando << endl;
    
    //botoes apertados    
        if(!strcmp(comando, "apes")) { tecla = TECLADO_ENTER; virt = true; apertou = true; }
        else if(!strcmp(comando, "apec")) { tecla = TECLADO_CIMA; virt = true; apertou = true; }
        else if(!strcmp(comando, "apeb")) { tecla = TECLADO_BAIXO; virt = true; apertou = true; }
        else if(!strcmp(comando, "aped")) { tecla = TECLADO_DIREITA; virt = true; apertou = true; }
        else if(!strcmp(comando, "apee")) { tecla = TECLADO_ESQUERDA; virt = true; apertou = true; }
        else if(!strcmp(comando, "ape-")) { tecla = TECLADO_TAB; virt = true; apertou = true; }
        else if(!strcmp(comando, "ape_")) { tecla = TECLADO_BACKSPACE; virt = true; apertou = true; }
        else if(!strcmp(comando, "apeo")) { tecla = TECLADO_0; virt = true; apertou = true; }
        else if(!strcmp(comando, "apet")) { tecla = TECLADO_1; virt = true; apertou = true; }
        else if(!strcmp(comando, "apeq")) { tecla = TECLADO_2; virt = true; apertou = true; }
        else if(!strcmp(comando, "apex")) { tecla = TECLADO_3; virt = true; apertou = true; }
        else if(!strcmp(comando, "aper")) { tecla = TECLADO_4; virt = true; apertou = true; }
        else if(!strcmp(comando, "apel")) { tecla = TECLADO_5; virt = true; apertou = true; }
        
    //botoes soltos
    
        else if(!strcmp(comando, "sols")) { tecla = TECLADO_ENTER; virt = true; apertou = false; }
        else if(!strcmp(comando, "solc")) { tecla = TECLADO_CIMA; virt = true; apertou = false; }
        else if(!strcmp(comando, "solb")) { tecla = TECLADO_BAIXO; virt = true; apertou = false; }
        else if(!strcmp(comando, "sold")) { tecla = TECLADO_DIREITA; virt = true; apertou = false; }
        else if(!strcmp(comando, "sole")) { tecla = TECLADO_ESQUERDA; virt = true; apertou = false; }
        else if(!strcmp(comando, "sol-")) { tecla = TECLADO_TAB; virt = true; apertou = false; }
        else if(!strcmp(comando, "sol_")) { tecla = TECLADO_BACKSPACE; virt = true; apertou = false; }
        else if(!strcmp(comando, "solo")) { tecla = TECLADO_0; virt = true; apertou = false; }
        else if(!strcmp(comando, "solt")) { tecla = TECLADO_1; virt = true; apertou = false; }
        else if(!strcmp(comando, "solq")) { tecla = TECLADO_2; virt = true; apertou = false; }
        else if(!strcmp(comando, "solx")) { tecla = TECLADO_3; virt = true; apertou = false; }
        else if(!strcmp(comando, "solr")) { tecla = TECLADO_4; virt = true; apertou = false; }
        else if(!strcmp(comando, "soll")) { tecla = TECLADO_5; virt = true; apertou = false; }   
    
    //Se não foi um comando reconhecido
    else
    {
        //Eu sei que isso é feio...
        return 0;
    }
    
    //Se a tecla é virtual
    if(virt)
    {
        teclado.wVk = (WORD) tecla;    
        teclado.wScan = 0;
        
        //Foi pressionado?
	    if(apertou == true)
	               teclado.dwFlags = 0;
        //Tecla foi solta
        else
                   teclado.dwFlags = KEYEVENTF_KEYUP; 
    }
    //Não virtual
    else
    {
        teclado.wScan = (WORD) tecla;
	    teclado.wVk = 0;
	    
	    //Foi pressionado?
	    if(apertou == true)
	               teclado.dwFlags = KEYEVENTF_UNICODE;
        //Tecla foi solta
        else
                   teclado.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
    }

    //Seta tudo padrão
	teclado.time = 0;
	teclado.dwExtraInfo = 0;

    //Define o tipo do input e a origem (struct KEYBDINPUT)
	input.type = INPUT_KEYBOARD;
	input.ki = teclado;
    
    //Executa
    SendInput(1, &input, sizeof(input));
    
    return 0;
    
}

int Controle::manipula_winamp(char comando[4])
{
    //O protocolo anterior não era 'wina'
    if(strcmp(prot, WINAMP_PROTOCOLO))
    {
        //Seleciona a janela
        cout << "Alterando o modo para: Winamp;" << endl;      
        
        cout << "Localizando a janela..." << endl;
        
        //Localiza a janela - retorna 0 em sucesso e -1 em erro
        if(!localiza_janela(WINAMP_PROTOCOLO))
        {
             cout << "Janela '" << WINAMP_WINDOW_NAME << "' localizada!" << endl;
             
             //Altera o protocolo em uso
             sprintf(prot, WINAMP_PROTOCOLO);
        }
        //Janela não localizada
        else
        {
            //Muda o protocolo pra 'null' (default)
            sprintf(prot, "null");
            
            //Exibe erro
            cout << "Janela '" << WINAMP_WINDOW_NAME << "' nao localizada! :(" << endl;
            
            //erro
            return -1;
        }
        
    }
    //O protocolo já era wina
    else
    {
        //cout << "Ja foi selecionado";
    }
    
        //Se chegou até aqui é pq não teve problema
        if(!strcmp(comando, "play")) SendMessage(hWnd, WM_COMMAND, WINAMP_PLAY, 0);
        else if(!strcmp(comando, "paus")) SendMessage(hWnd, WM_COMMAND, WINAMP_PAUSE, 0);
        else if(!strcmp(comando, "stop")) SendMessage(hWnd, WM_COMMAND, WINAMP_STOP, 0);
        else if(!strcmp(comando, "prev")) SendMessage(hWnd, WM_COMMAND, WINAMP_PREV, 0);
        else if(!strcmp(comando, "next")) SendMessage(hWnd, WM_COMMAND, WINAMP_NEXT, 0);       
}

int Controle::manipula_vlc(char comando[4])
{
    //O protocolo anterior não era 'vlcp'
    if(strcmp(prot, VLC_PROTOCOLO))
    {
        //Seleciona a janela
        cout << "Alterando o modo para: VLC;" << endl;      
        
        cout << "Localizando a janela..." << endl;
        
        //Localiza a janela - retorna 0 em sucesso e -1 em erro
        if(!localiza_janela(VLC_PROTOCOLO))
        {
             cout << "Janela '" << VLC_WINDOW_NAME << "' localizada!" << endl;
             
             //Altera o protocolo em uso
             sprintf(prot, VLC_PROTOCOLO);
        }
        //Janela não localizada
        else
        {
            //Muda o protocolo pra 'null' (default)
            sprintf(prot, "null");
            
            //Exibe erro
            cout << "Janela '" << VLC_WINDOW_NAME << "' nao localizada! :(" << endl;
            
            //erro
            return -1;
        }
        
    }
    //O protocolo já era 'vlcp'
    else
    {
        //cout << "Ja foi selecionado";
    }
    
        //Se chegou até aqui é pq não teve problema
        if(!strcmp(comando, "play")) SendMessage(hWnd, WM_COMMAND, VLC_PLAY, 0);
        else if(!strcmp(comando, "paus")) SendMessage(hWnd, WM_COMMAND, VLC_PAUSE, 0);
        else if(!strcmp(comando, "stop")) SendMessage(hWnd, WM_COMMAND, VLC_STOP, 0);
        else if(!strcmp(comando, "prev")) SendMessage(hWnd, WM_COMMAND, VLC_PREV, 0);
        else if(!strcmp(comando, "next")) SendMessage(hWnd, WM_COMMAND, VLC_NEXT, 0);          
}
*/
