PSP Easy Wireless Controller - http://PSPEWC.blogspot.com

All the software which I have written are under public domain.

* The windows' server source is not yet translated. I'm sorry for that.

Version 1.1:

The best way to understand and reuse the code is taking a look at the python server in the folder PC/unix/. Or you can grab the raw data from the PSP (a 17 byte long string containing the buttons' statuses) using netcat:

$ netcat -l -u -p 30666

This will create a listening UDP socket on port 30666 and get the incoming data from PSP.


IMPORTANT:
 - You can reuse the PSP client in your C/C++/Java/PHP/etc application. All the PSP does here is sending a 17-char string to a UDP socket server running on the port 30666. That said, any datagram socket server should be able to manipulate this string on any way you want. For example, you can control, lets say, a Java game with your PSP. The data string is coded as follows:

#define INDEX_PROTOCOL 0
#define INDEX_UP 1
#define INDEX_DOWN 2
#define INDEX_LEFT 3
#define INDEX_RIGHT 4
#define INDEX_SQUARE 5
#define INDEX_BALL 6
#define INDEX_XIS 7
#define INDEX_TRIANGLE 8
#define INDEX_L 9
#define INDEX_R 10
#define INDEX_START 11
#define INDEX_ANALOG_DOWN 12
#define INDEX_ANALOG_UP 13
#define INDEX_ANALOG_RIGHT 14
#define INDEX_ANALOG_LEFT 15
#define INDEX_SELECT 16

The best way to understand this string is to run a UDP server on port 30666 (source for this server is in this folder, under the name udp_server.c and press the buttons. The string should contain 0s and 1s. Where the 1s represent the pressed buttons.
