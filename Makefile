Debug:
	g++ -c src/*.cpp -std=c++14 -g -Wall -fopenmp -m64 -I include -I".\SDL2-w64\include"
	g++ *.o -o bin/main -L".\SDL2-w64\lib" -fopenmp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
	rm -f *.o
	start bin/main

clean:
	rm -f *.o