CXX ?= g++
OPT ?= -O2 -march=native -std=c++11 -Wall
SDL_FLAGS := $(shell sdl2-config --cflags --libs) -lSDL2_image

all: encrypt decrypt keygen

encrypt: encrypt.cc
	$(CXX) $(OPT) -o encrypt encrypt.cc $(SDL_FLAGS)

decrypt: decrypt.cc
	$(CXX) $(OPT) -o decrypt decrypt.cc $(SDL_FLAGS)

keygen: keygen.cc
	$(CXX) $(OPT) -o keygen keygen.cc $(SDL_FLAGS)

clean:
	rm encrypt decrypt
