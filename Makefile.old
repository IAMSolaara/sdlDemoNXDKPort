CC := g++

CSWITCHES := 
CDSWITCHES := $(CSWITCHES) -g

CFLAGS := `pkg-config --cflags sdl2 SDL2_image SDL2_mixer`

CLIBS := `pkg-config --libs sdl2 SDL2_image SDL2_mixer`

TARGETS := main.cpp

default:	$(TARGETS)
	$(CC) $(CSWITCHES) $(CFLAGS) $(TARGETS) $(CLIBS)
debug:		$(TARGETS)
	$(CC) $(CDSWITCHES) $(CFLAGS) $(TARGETS) $(CLIBS)
custom:
	$(CC) $(CFLAGS) $(SRCARG) $(CLIBS)
