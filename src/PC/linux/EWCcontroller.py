#/* ---------------------------------------------------------------------------
#** This software is in the public domain, furnished "as is", without technical
#** support, and with no warranty, express or implied, as to its usefulness for
#** any purpose.
#**
#**
#** -------------------------------------------------------------------------*/
#
#    Use Protocol 1 (PSP in keypad #1 mode) to simulate regular buttons. The analog stick also simulates key presses,
#    so you can use it in regular emulators, for example.should control the mouse.
#    Use Protocol 2 (PSP in keypad #2 mode) to make the L and R triggers work as the corresponding mouse buttons. The
#    analog stick should control the pointer. Press SELECT for velocity and release it for precision.
#
#    This class receives the string (something like 11001000100000100)
#    and simulate some key presses and mouse movements


from Xlib import display, X
from Xlib.protocol import event
from Xlib.ext import xtest
import os
import time

#Definitions

PROTOCOL_INDEX = 0
UP_INDEX = 1
DOWN_INDEX = 2
LEFT_INDEX = 3
RIGHT_INDEX = 4
SQUARE_INDEX = 5
CIRCLE_INDEX = 6
CROSS_INDEX = 7
TRIANGLE_INDEX = 8
LTRIGGER_INDEX = 9
RTRIGGER_INDEX = 10
START_INDEX = 11
DANALOG_INDEX = 12
UANALOG_INDEX = 13
RANALOG_INDEX = 14
LANALOG_INDEX = 15
SELECT_INDEX = 16

#Keycodes

K_UP = 111
K_DOWN = 116
K_LEFT = 113
K_RIGHT = 114
K_ENTER = 36
K_BACKSPACE = 22
K_A = 38
K_B = 56
K_C = 54
K_D = 40
K_E = 26
K_F = 41
K_G = 42
K_H = 43

#How much the pointer will run in each iteration - change it as your will
POINTER_STEP = 8

class Controller:
	#This list holds the state of all the buttons on the psp. They are 0 or 1
	keystates = ['0']*17 #why cant it start with self.?

	def __init__(self):
		self.disp = display.Display()
		self.scr = self.disp.screen()
		self.root = self.disp.screen().root

	def press_button(self, keycode):
		#Search for the focused window
		self.wnd = self.disp.get_input_focus().focus

		if (self.wnd) == None:
			print 'Error assigning the focused window! Existing...'
			os._exit(0)

		self.keyevtpress = event.KeyPress(
			type = X.KeyPress,
			display = self.disp, 
			detail = keycode,
			time = X.CurrentTime,
			root = self.root,
			window = self.wnd,
			child = X.NONE,
			root_x = 1,
			root_y = 1,
			event_x = 1,
			event_y = 1,
			state = 0,
			same_screen = 1,
		)
		self.disp.send_event(self.wnd, self.keyevtpress, propagate = True)
		self.disp.flush()

	def release_button(self, keycode):
		#Search for the focused window
		self.wnd = self.disp.get_input_focus().focus

		if (self.wnd) == None:
			print 'Error assigning the focused window! Existing...'
			os._exit(0)

		self.keyevtrelease = event.KeyRelease(
			type = X.KeyRelease,
			display = self.disp, 
			detail = keycode,
			time = X.CurrentTime,
			root = self.root,
			window = self.wnd,
			child = X.NONE,
			root_x = 1,
			root_y = 1,
			event_x = 1,
			event_y = 1,
			state = 0,
			same_screen = 1,
		)
		self.disp.send_event(self.wnd, self.keyevtrelease, propagate = True)
		self.disp.flush()

	def move_mouse(self, boolx, booly):
		self.disp.warp_pointer(boolx*POINTER_STEP, booly*POINTER_STEP)
		self.disp.flush()

	#I would like to get it working without the fake_input. The original code is commented at the end of the file.
	def click(self, button):
		xtest.fake_input(self.disp, X.ButtonPress, button)
		xtest.fake_input(self.disp, X.ButtonRelease, button)
		self.disp.flush()

	def handle_string(self, received_string):
		
		if len(received_string) != 17:
			print 'Unrecognized string received! Exiting...'
			os._exit(0)
	
		else:
			#Up
			if received_string[UP_INDEX] == '1':
				if self.keystates[UP_INDEX] == '0':
					self.press_button(K_UP)
					self.keystates[UP_INDEX] = '1'
			else:
				if self.keystates[UP_INDEX] == '1':
					self.release_button(K_UP)
					self.keystates[UP_INDEX] = '0'

			#Down
			if received_string[DOWN_INDEX] == '1':
				if self.keystates[DOWN_INDEX] == '0':
					self.press_button(K_DOWN)
					self.keystates[DOWN_INDEX] = '1'
			else:
				if self.keystates[DOWN_INDEX] == '1':
					self.release_button(K_DOWN)
					self.keystates[DOWN_INDEX] = '0'

			#Left
			if received_string[LEFT_INDEX] == '1':
				if self.keystates[LEFT_INDEX] == '0':
					self.press_button(K_LEFT)
					self.keystates[LEFT_INDEX] = '1'
			else:
				if self.keystates[LEFT_INDEX] == '1':
					self.release_button(K_LEFT)
					self.keystates[LEFT_INDEX] = '0'

			#Right
			if received_string[RIGHT_INDEX] == '1':
				if self.keystates[RIGHT_INDEX] == '0':
					self.press_button(K_RIGHT)
					self.keystates[RIGHT_INDEX] = '1'
			else:
				if self.keystates[RIGHT_INDEX] == '1':
					self.release_button(K_RIGHT)
					self.keystates[RIGHT_INDEX] = '0'

			#Cross
			if received_string[CROSS_INDEX] == '1':
				if self.keystates[CROSS_INDEX] == '0':
					self.press_button(K_A)
					self.keystates[CROSS_INDEX] = '1'
			else:
				if self.keystates[CROSS_INDEX] == '1':
					self.release_button(K_A)
					self.keystates[CROSS_INDEX] = '0'

			#Square
			if received_string[SQUARE_INDEX] == '1':
				if self.keystates[SQUARE_INDEX] == '0':
					self.press_button(K_B)
					self.keystates[SQUARE_INDEX] = '1'
			else:
				if self.keystates[SQUARE_INDEX] == '1':
					self.release_button(K_B)
					self.keystates[SQUARE_INDEX] = '0'

			#Triangle
			if received_string[TRIANGLE_INDEX] == '1':
				if self.keystates[TRIANGLE_INDEX] == '0':
					self.press_button(K_C)
					self.keystates[TRIANGLE_INDEX] = '1'
			else:
				if self.keystates[TRIANGLE_INDEX] == '1':
					self.release_button(K_C)
					self.keystates[TRIANGLE_INDEX] = '0'
				
			#Circle
			if received_string[CIRCLE_INDEX] == '1':
				if self.keystates[CIRCLE_INDEX] == '0':
					self.press_button(K_D)
					self.keystates[CIRCLE_INDEX] = '1'
			else:
				if self.keystates[CIRCLE_INDEX] == '1':
					self.release_button(K_D)
					self.keystates[CIRCLE_INDEX] = '0'

			#Start
			if received_string[START_INDEX] == '1':
				if self.keystates[START_INDEX] == '0':
					self.press_button(K_ENTER)
					self.keystates[START_INDEX] = '1'
			else:
				if self.keystates[START_INDEX] == '1':
					self.release_button(K_ENTER)
					self.keystates[START_INDEX] = '0'

			#The following buttons can behave in two ways:
			#If protocol = 1, they act like normal keyboard buttons
			#If protocol = 2, they perform mouse events

			#Protocol = 1
			if received_string[PROTOCOL_INDEX] == '1':
				
				#Up Analog
				if received_string[UANALOG_INDEX] == '1':
					if self.keystates[UANALOG_INDEX] == '0':
						self.press_button(K_E)
						self.keystates[UANALOG_INDEX] = '1'
				else:
					if self.keystates[UANALOG_INDEX] == '1':
						self.release_button(K_E)
						self.keystates[UANALOG_INDEX] = '0'

				#Down Analog
				if received_string[DANALOG_INDEX] == '1':
					if self.keystates[DANALOG_INDEX] == '0':
						self.press_button(K_F)
						self.keystates[DANALOG_INDEX] = '1'
				else:
					if self.keystates[DANALOG_INDEX] == '1':
						self.release_button(K_F)
						self.keystates[DANALOG_INDEX] = '0'

				#Left Analog
				if received_string[LANALOG_INDEX] == '1':
					if self.keystates[LANALOG_INDEX] == '0':
						self.press_button(K_G)
						self.keystates[LANALOG_INDEX] = '1'
				else:
					if self.keystates[LANALOG_INDEX] == '1':
						self.release_button(K_G)
						self.keystates[LANALOG_INDEX] = '0'

				#Right Analog
				if received_string[RANALOG_INDEX] == '1':
					if self.keystates[RANALOG_INDEX] == '0':
						self.press_button(K_H)
						self.keystates[RANALOG_INDEX] = '1'
				else:
					if self.keystates[RANALOG_INDEX] == '1':
						self.release_button(K_H)
						self.keystates[RANALOG_INDEX] = '0'
	
				#L-Trigger
				if received_string[LTRIGGER_INDEX] == '1':
					if self.keystates[LTRIGGER_INDEX] == '0':
						self.press_button(K_E)
						self.keystates[LTRIGGER_INDEX] = '1'
				else:
					if self.keystates[LTRIGGER_INDEX] == '1':
						self.release_button(K_E)
						self.keystates[LTRIGGER_INDEX] = '0'
	
				#R-Trigger (if protocol = 2, use as right mouse button)
				if received_string[RTRIGGER_INDEX] == '1':
					if self.keystates[RTRIGGER_INDEX] == '0':
						self.press_button(K_F)
						self.keystates[RTRIGGER_INDEX] = '1'
				else:
					if self.keystates[RTRIGGER_INDEX] == '1':
						self.release_button(K_F)
						self.keystates[RTRIGGER_INDEX] = '0'

				#Select - Simulate backspace when protocol = 1
				#Works as a speed-increaser to mouse velocity when protocol = 2.
				if received_string[SELECT_INDEX] == '1':
					if self.keystates[SELECT_INDEX] == '0':
						self.press_button(K_BACKSPACE)
						self.keystates[SELECT_INDEX] = '1'
				else:
					if self.keystates[SELECT_INDEX] == '1':
						self.release_button(K_BACKSPACE)
						self.keystates[SELECT_INDEX] = '0'

			#Protocol = 2
			elif received_string[PROTOCOL_INDEX] == '2':
				#Up Analog
				if received_string[UANALOG_INDEX] == '1':
						factor = 1
						if received_string[SELECT_INDEX] == '1': factor = 3
						self.move_mouse(0, -1*factor)

				#Down Analog
				if received_string[DANALOG_INDEX] == '1':
						factor = 1
						if received_string[SELECT_INDEX] == '1': factor = 3
						self.move_mouse(0, 1*factor)

				#Left Analog
				if received_string[LANALOG_INDEX] == '1':
						factor = 1
						if received_string[SELECT_INDEX] == '1': factor = 3
						self.move_mouse(-1*factor, 0)

				#Right Analog
				if received_string[RANALOG_INDEX] == '1':
						factor = 1
						if received_string[SELECT_INDEX] == '1': factor = 3
						self.move_mouse(1*factor, 0)
				
				#R-Trigger
				if received_string[RTRIGGER_INDEX] == '1':
						self.click(1) #right click

				#L-Trigger
				if received_string[LTRIGGER_INDEX] == '1':
						self.click(3) #left click

#Something that Ive got in the internet. Also did not work.
'''
	def press(self, x, y, button = 1):
		focus = self.disp.get_input_focus().focus
		rel = focus.translate_coords(root, x, y)
		button_list = [None, X.Button1, X.Button2, X.Button3]

		try:
		    mousePress = event.ButtonPress(
		        time=X.CurrentTime,
		        root=root,
		        window=focus,
		        same_screen=1,
		        child=X.NONE,
		        root_x=x,
		        root_y=y,
		        event_x=rel.x,
		        event_y=rel.y,
		        state=0,
		        detail=button_list[button]
		        )
		    focus.send_event(mousePress)

		except:
		    pass

		self.disp.sync()

	def release(self, x, y, button = 1):
		focus = self.disp.get_input_focus().focus
		rel = focus.translate_coords(root, x, y)
		button_list = [None, X.Button1, X.Button2, X.Button3]

		try:
		    mouseRealease = event.ButtonRelease(
		        time=X.CurrentTime,
		        root=root,
		        window=focus,
		        same_screen=1,
		        child=X.NONE,
		        root_x=x,
		        root_y=y,
		        event_x=rel.x,
		        event_y=rel.y,
		        state=1,
		        detail=button_list[button]
		        )
		    focus.send_event(mouseRealease)

		except:
		    pass

		self.disp.sync()

	def click(self, x, y, button = 1):
		print 'click'
		try:
		    self.press(x, y, button)
		    self.release(x, y, button)
		    # Using xlib-xtest fake input
		    root.warp_pointer(x, y) # I believe you where not setting the position
		    Xlib.ext.xtest.fake_input (self.disp, X.ButtonPress, 1) #Unix-xlib starts from 1
		except:
			print ''

		self.disp.sync()
'''

#My original code:
'''
	def click(self, button):
		#Search for the focused window
		self.wnd = self.disp.get_input_focus().focus

		if (self.wnd) == None:
			print 'Error assigning the focused window! Existing...'
			os._exit(0)
	
		self.evtclick = event.ButtonPress(
			type = X.ButtonPress,
			display = self.disp, 
			detail = button,
			time = X.CurrentTime,
			root = self.root,
			window = self.wnd,
			child = X.NONE,
			root_x = 200,
			root_y = 200,
			event_x = 200,
			event_y = 200,
			state = 0,
			same_screen = 1,
		)
		self.disp.send_event(self.wnd, self.evtclick)
		self.disp.flush()
'''
