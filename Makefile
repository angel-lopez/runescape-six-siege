game:
	rm -f ./bin/game && g++ ./src/main.cpp -o ./bin/game -I/usr/local/include/SDL2 -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -std=gnu++11 && ./bin/game