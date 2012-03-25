/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
**
** -------------------------------------------------------------------------*/

#ifndef _codes_h_
#define _codes_h_
#include <windows.h>



/********************* PROTOCOLOS ******************/

#define CHAR_PROTOCOLO_TECLADO '1'
#define CHAR_PROTOCOLO_TECLADO_2 '2'
#define CHAR_PROTOCOLO_VLC '3'
#define CHAR_PROTOCOLO_WINAMP '4'

#define PROTOCOLO_TECLADO 1
#define PROTOCOLO_TECLADO_2 2
#define PROTOCOLO_VLC 3
#define PROTOCOLO_WINAMP 4

/******************** INPUTS DO TECLADO ************/

//Definições para teclado 1
#define TECLADO_ENTER VK_RETURN
#define TECLADO_TAB VK_TAB
#define TECLADO_BACKSPACE VK_BACK

#define TECLADO_DIREITA 0x41 //A
#define TECLADO_ESQUERDA 0x42 //B
#define TECLADO_BAIXO 0x43 
#define TECLADO_CIMA 0x44

#define TECLADO_0 0x45
#define TECLADO_1 0x46
#define TECLADO_2 0x47
#define TECLADO_3 0x48
#define TECLADO_4 0x49
#define TECLADO_5 0x4A
#define TECLADO_6 0x4B
#define TECLADO_7 0x4C
#define TECLADO_8 0x4D
#define TECLADO_9 0x4E
#define TECLADO_10 0x4F //O

//Definições para teclado 2
#define TECLADO2_ENTER 0x50 //P
#define TECLADO2_BACKSPACE 0x35 //Q

#define TECLADO2_DIREITA 0x51 //A
#define TECLADO2_ESQUERDA 0x52 //B
#define TECLADO2_BAIXO 0x53 
#define TECLADO2_CIMA 0x54

#define TECLADO2_0 0x55
#define TECLADO2_1 0x56
#define TECLADO2_2 0x57
#define TECLADO2_3 0x58
#define TECLADO2_4 0x59
#define TECLADO2_5 0x5A //Z

#define TECLADO2_6 0x30 //0
#define TECLADO2_7 0x31
#define TECLADO2_8 0x32
#define TECLADO2_9 0x33
#define TECLADO2_10 0x34 //4


/********************** VLC ***********************/
// X = play/pause
// BOLA = stop
// L = prev
// R = next
// START = fullscreen

//#define VLC_WINDOW_NAME "VLC media player"
/* NAO FUNCIONA MAIS :{
#define VLC_WINDOW_NAME "Reprodutor de mýdias VLC"
#define VLC_PLAY 6020
#define VLC_PAUSE 6020
#define VLC_STOP 6090
#define VLC_PREV 6021
#define VLC_NEXT 6022
#define VLC_FULLSCREEN 9002
*/

// O VLC vai funcionar através dos atalhos do teclado. Pros: Fácil; Contra: Janela tem que estar On top
/* Atalhos:
Space Play/Pause
s Stop
+ Play faster
- Play Slower
t Position
n Next Item
p Previous Item
f Fullscreen
m Mute
Shift+Rt Arrow Forward 3 seconds
Shift+Lt Arrow Backward 3 seconds
Alt+Rt Arrow Forward 10 seconds
Alt+Lt Arrow Backward 10 seconds
Ctrl+Up Arrow Volume up
Ctrl+Dn Arrow Volume down
*/       

#define VLC_PLAY_KEY VK_SPACE
#define VLC_STOP_KEY 0x53 //s
#define VLC_SHOW_TIME_KEY 0x54 //t
#define VLC_FULLSCREEN_KEY 0x46 //f
#define VLC_MUTE_KEY 0x4D //m
#define VLC_UP_VOL_NEED_PRE_CTRL 0x68 //Seta pra cima
#define VLC_DOWN_VOL_NEED_PRE_CTRL VK_DOWN //Seta pra baixo
#define VLC_BACK_10_SEC_NEED_PRE_ALT VK_LEFT //Seta esquerda
#define VLC_FORWARD_10_SEC_NEED_PRE_ALT VK_RIGHT //Seta esquerda

//CTRL
#define VLC_CTRL_KEY VK_CONTROL

//NUM LOCK
#define VLC_NUM_LOCK VK_NUMLOCK

//ALT
#define VLC_ALT_KEY 0x12

/********************** WINDOWS MEDIA PLAYER CLASSIC ****************************/


/********************* WINAMP **********************/
#define WINAMP_WINDOW_NAME "Winamp v1.x"
#define WINAMP_PLAY 40045
#define WINAMP_PAUSE 40046
#define WINAMP_STOP 40047
#define WINAMP_PREV 40044
#define WINAMP_NEXT 40048
#define WINAMP_VOL_UP 40058
#define WINAMP_VOL_DOWN 40059

/******************* INDICES DAS TECLAS ***************/
#define INDICE_PROTOCOLO 0

#define INDICE_NUMERO_CONTROLE "ISSO NAO E' MAIS USADO" //Deprecated! Duplicate INDICE_PROTOCOLO instead. I know...

#define INDICE_UP 1
#define INDICE_DOWN 2
#define INDICE_LEFT 3
#define INDICE_RIGHT 4

#define INDICE_QUADRADO 5
#define INDICE_BOLA 6
#define INDICE_XIS 7
#define INDICE_TRIANGULO 8

#define INDICE_L 9
#define INDICE_R 10
#define INDICE_START 11

#define INDICE_ANALOG_DOWN 12
#define INDICE_ANALOG_UP 13
#define INDICE_ANALOG_RIGHT 14
#define INDICE_ANALOG_LEFT 15

#define INDICE_SELECT 16


#endif
