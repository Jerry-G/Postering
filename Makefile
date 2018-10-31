CXX=g++
CFLAGS=-O2 -L/usr/X11R6/lib -lm -lpthread -lX11
OBJS=poster.o CImg.o
SRC_PATH=src/

all: CImg.o poster.o Poster

CImg.o: CImg.cpp
	$(CXX) -o $@ -c $^

poster.o: poster.cpp
	$(CXX) -o $@ -c $^

Poster: poster.cpp
	$(CXX) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(OBJS) Poster

