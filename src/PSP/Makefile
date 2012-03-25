TARGET = PSPEWC
OBJS = main.o util.o

INCDIR =
CFLAGS = -O0 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1

LIBDIR =

EXTRA_TARGETS = EBOOT.PBP

PSP_EBOOT_TITLE = PSPWiFiTerm
PSP_EBOOT_ICON = icon.png
PSP_EBOOT_PIC1 = wire.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
