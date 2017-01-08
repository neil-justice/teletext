CFLAGS = -Wall -Wextra -Wfloat-equal -pedantic -ansi -lm  `pkg-config sdl2 --cflags`
INCS = cell.h state.h display.h error.h base.h

SOURCES = display.c state.c error.c cell.c
TARGET = teletext
MAIN = teletext.c

TMAIN = test.c
TESTINCS = test.h
TTARGET = test

FONTTARGET = fontwriter

EXTINCS = extension/extension.h extension/extdisplay.h extension/logic.h extension/event.h extension/init.h extension/utility.h
EXTSOURCES = extension/extension.c extension/extdisplay.c extension/logic.c extension/event.c extension/init.c extension/utility.c
ETARGET = ext

LIBS = `pkg-config sdl2 --libs`
CC = gcc

all: $(MAIN) $(SOURCES) $(INCS)
	$(CC) $(MAIN) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

# Compiles the program in testing mode.  Normal functionality is not available
# from this executable.
test: $(TMAIN) $(SOURCES) $(INCS) $(TESTINCS)
	$(CC) -D TESTING $(TMAIN) $(SOURCES) -o $(TTARGET) $(CFLAGS) $(LIBS)

# Compiles the fontwriter program.  This standalone program generates sixel
# fonts.
fontwriter: $(FONTTARGET).c
	$(CC) $(FONTTARGET).c -o $(FONTTARGET) $(CFLAGS)

# Compiles the program with extension included.
ext: $(EXTSOURCES) $(SOURCES) $(EXTINCS) $(INCS)
	$(CC) $(EXTSOURCES) $(SOURCES) -o $(ETARGET) $(CFLAGS) $(LIBS)
