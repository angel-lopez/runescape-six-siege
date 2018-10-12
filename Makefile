game:
	g++ main.cpp -o game -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2 && ./game