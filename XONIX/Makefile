
EXENAME := XONIX_msys2mingw.exe
PKGS=--static SDL2 SDL2_ttf SDL2_image freetype2
CFLAGS = -g -O0 -Wall $(shell pkg-config --cflags $(PKGS)) -I. -std=gnu++11
# -DUNICODE 
LIBS2 = -static  $(shell pkg-config --libs $(PKGS)) -lm
LIBS = $(shell echo $(LIBS2) | sed "s/ -mwindows//g")
# -municode -mwindows

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
#$(shell cmd.exe /c "echo $(CSRCS) > test.txt")
#	$(shell cmd.exe /c "echo $(OBJSCAN_PRE1) > test2.txt")
#	$(shell cmd.exe /c "echo $(OBJSCAN) > test3.txt")
	$(foreach objFile,$(OBJSCAN),$(shell sh.exe -c "rm $(objFile)"))
