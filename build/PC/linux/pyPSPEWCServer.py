#!/usr/bin/env python

#/* ---------------------------------------------------------------------------
#** This software is in the public domain, furnished "as is", without technical
#** support, and with no warranty, express or implied, as to its usefulness for
#** any purpose.
#**
#**
#** -------------------------------------------------------------------------*/
#
#    Use Protocol 1 (PSP in keypad #1 mode) to simulate regular buttons. The analog stick should control the mouse.
#    Use Protocol 2 (PSP in keypad #2 mode) to make the L and R triggers work as the corresponding mouse buttons.
#
#
#    This program will receive a string of keystates and simulate key presses and mouse events. 
#    This string is 17-char long and  contain '0's and '1's acording to that key state. This  
#    software was conceived as a port of the PSPEWC (http://PSPEWC.blogspot.com) server,  Anyway, 
#    which runs on Microsoft Windows systems.it can work with any other client that sends a similar
#    string at the port 30666 of this UDP socket.
#
#    Use Protocol 1 (PSP in keypad #1 mode) to simulate regular buttons. The analog stick also simulates key presses,
#    so you can use it in regular emulators, for example.should control the mouse.
#    Use Protocol 2 (PSP in keypad #2 mode) to make the L and R triggers work as the corresponding mouse buttons. The
#    analog stick should control the pointer. Press SELECT for velocity and release it for precision.

import EWCnetworking
import EWCcontroller

VERSION = '0.2'

srv = EWCnetworking.Server()
ctrl = EWCcontroller.Controller()

print 'Python PSPEWCServer version v{0} - running on IP: {1}'.format(VERSION, srv.localaddr)

while 1:
	srv.receive()
	ctrl.handle_string(srv.message)
