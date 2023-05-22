
EXENAME := _main.exe
PKGS=--static SDL2 SDL2_image SDL2_mixer SDL2_ttf freetype2 fontconfig
CFLAGS = -g -O0 -Wall -DUNICODE $(shell pkg-config --cflags $(PKGS)) -I. -fpermissive
LIBS = -static -municode -mwindows $(shell pkg-config --libs $(PKGS)) -lm

CSRCSCAN := $(wildcard ./**/*.cpp) $(wildcard *.cpp)
CSRCS := $(filter %.cpp,$(CSRCSCAN))
objects := $(patsubst %.cpp,obj/%.o,$(CSRCS))

OBJSCAN_PRE1 := $(wildcard ./obj/**/*.o) $(wildcard ./obj/*.o) $(wildcard ./obj/**/**/*.o)
OBJSCAN := $(EXENAME) $(OBJSCAN_PRE1)

all:	$(objects)
	g++ -o $(EXENAME) $(objects) $(LIBS) $(LIBS)
 
$(objects):	obj/%.o: %.cpp
	$(shell sh.exe -c "mkdir -p ./$(dir $@)")
	g++ -g -O0 -Wall $(CFLAGS) -c $< -o $@ 
  
clean:
	$(foreach objFile,$(OBJSCAN),$(shell sh.exe -c "rm $(objFile)"))
