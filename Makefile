CXX ?= g++
OPT ?= -O2 -march=native -std=c++11
SDL_FLAGS := $(shell sdl2-config --cflags --libs) -lSDL2_image

all: encrypt decrypt

encrypt: encrypt.cc
	$(CXX) $(OPT) -o encrypt encrypt.cc $(SDL_FLAGS)

decrypt: decrypt.cc
	$(CXX) $(OPT) -o decrypt decrypt.cc $(SDL_FLAGS)

clean:
	rm encrypt decrypt
