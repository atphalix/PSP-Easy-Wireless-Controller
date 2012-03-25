PSP Easy Wireless Controller
============================
A zero-configuration PSP-as-wireless-joystick client/server. With PSPEWC, you should be able to use your PSP to simulate keypresses/mouse events as a physical keyboard would. It works on linux and windows.

All software written by myself are under public domain. the python XLib (which is include) is distributed under its own license.

![sample](http://4.bp.blogspot.com/-peRY7pFsDFM/ToTYNryPkfI/AAAAAAAAAAs/T53xKDE3O_E/s1600/IMG_0148.JPG)

A) For linux users
==================

How to use
-----------

1. Run the python server on your computer

		$ cd PC/linux/
		$ ./pyPSPEWCServer.py 
		Xlib.protocol.request.QueryExtension
		Python PSPEWCServer version v0.2 - running on IP: [Your IP address]


2. Put the build/PSP/GAME/PSPEasyWirelessController folder inside your GAME folder on your PSP
3. Start the PSPEWC homebrew on your PSP and set it up with the IP address shown on step 1
4. It should be working. To try out, try to press the buttons on your PSP and it should act like a normal keyboard

Description
------------

Since version 1.1 there is a python server which runs under unix systems. This server supports two operational modes:

1. Keypad #1 - This will simulate regular keyboard buttons presses.

2. Keypad #2 - This will simulate mouse events. The analog control the pointer position and the R and L triggers, the mouse buttons. The SELECT key will make the pointer triple it`s velocity.

B) For Windows users
====================

How to use
----------

1. Run the build/windows/PSPEWCServer.exe on your computer. It will act as a server.

2. Put the build/PSP/GAME/PSPEasyWirelessController folder inside your GAME folder on your PSP.

3. Start the PSPEWC homebrew on your PC and set it up with the IP address shown on the PSPEWCServer.exe.

4. It should be working. To try out, try to press the buttons on your PSP and it should act like a normal keyboard.


Description:
-----------

PSPEWC allows you to use your PSP as joysticks for your computer, as well to control VLC Media Player and Winamp. No pre-configuration is needed. All you have to do is run PSPEWC.exe on the computer (which will act as a server) and run the PSPEasyWirelessController homebrew on the PSP (which will be the client that will connect to the PC`s server). In other words, the PSPEWC will work in 4 ways (4 protocols):

1. Keypad #1 - This option will simulate keypresses on the computer. You can configure those keys on any game or emulator. This will make your PSP act as a joystick.

2. Keypad #2 - Same as #1, but will simulate different keypresses.

3. VLC Mode - This option simulates the key presses corresponding to the VLC`s shortcurts. The commands are:

 - X: play/pause;
 - O: stop;
 - Triangle: show progress;
 - Square: fullscreen On/Off;
 - L: go 10 seconds in the past;
 - R: go 10 seconds in the future;
 - UP: vol up;
 - DOWN: vol down;


4. Winamp Mode - This option calls the function SendMessage() to simulate WM_COMMANDs events. The comands are:

 - X: play;
 - O: pause/unpause;
 - Triangle: stop;
 - L: previous;
 - R: next;
 - UP: vol up;
 - DOWN: vol down;

