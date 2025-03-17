CFLAGS=-std=c++20 -Wall -O3 -g -Wextra -Wno-unused-parameter -I/usr/include/SDL2 -I/usr/include/SDL2 -lSDL2 -lSDL2_image -Wno-narrowing
CXXFLAGS=$(CFLAGS)
OBJECTS=main.o game.o maze.o perlin_noise.o raycaster.o window.o renderer.o surfaces.o path_finder.o
BINARIES=main

RGB_LIB_DISTRIBUTION=..
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
LDFLAGS+=-L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread -lSDL2 -lSDL2_image

all : $(BINARIES)

$(RGB_LIBRARY): FORCE
	$(MAKE) -C $(RGB_LIBDIR)

main : $(OBJECTS) $(RGB_LIBRARY)
	$(CXX) $^ -o $@ $(LDFLAGS)

# All the binaries that have the same name as the object file.q
% : %.o $(RGB_LIBRARY)
	$(CXX) $< -o $@ $(LDFLAGS)

%.o : %.cc
	$(CXX) -I$(RGB_INCDIR) $(CXXFLAGS) -c -o $@ $<

%.o : %.c
	$(CC) -I$(RGB_INCDIR) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(BINARIES)

run:
	sudo ./main

FORCE:
.PHONY: FORCE
