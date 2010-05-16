# A basic Makefile to compile for Gp2x/SDL 

OPEN2X = /opt/openwiz/toolchain

CC = $(OPEN2X)/bin/arm-openwiz-linux-gnu-gcc
CXX = $(OPEN2X)/bin/arm-openwiz-linux-gnu-g++
LD = $(CXX)
STRIP = $(OPEN2X)/bin/arm-openwiz-linux-gnu-strip

NAME=../warehouse_panic
TARGET= $(NAME).bin

DEFS = -DWIZ -DIS_LITTLE_ENDIAN -D_REENTRANT -DGP2X_ASM

INCS =  -I. -I$(OPEN2X)/include 
#-I$(OPEN2X)/include/SDL

LDFLAGS=$(CFLAGS) -L$(OPEN2X)/lib
LIBS = -Wl,-rpath,$(OPEN2X)/lib -lSDL -lSDL_image -lSDL_mixer -lpng -lm -lz -lpthread

OBJS = WCEngine/Application.o WCEngine/EventManager.o WCEngine/ResourceManager.o WCEngine/Image.o WCEngine/Animation.o WCEngine/Sound.o WCEngine/SoundBuffer.o WCEngine/Music.o WCEngine/RenderWindow.o WCEngine/Scene.o WCEngine/Sprite.o WCEngine/Timer.o WCEngine/Vector2f.o WCEngine/main.o Keyboard.o SceneCredits.o SceneGame.o SceneHighscore.o SceneHowToPlay.o SceneMenu.o Scenesplash.o Text.o

MYCC = $(CC) $(CFLAGS) $(INCS) $(DEFS)
MYCXX = $(CXX) $(CFLAGS) $(INCS) $(DEFS)

########################################################################

sdl: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)
	$(STRIP) $@

.c.o:
	$(MYCC) -c $< -o $@

.cpp.o:
	$(MYCXX) -c $< -o $@

clean:
	rm -f *.o *.gpe

