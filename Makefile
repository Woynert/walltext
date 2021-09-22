
#create executable
output: ./main.cpp
	g++ -o ./build/exe ./main.cpp `pkg-config --cflags --libs gtk+-3.0`

#./build/main.o: main.cpp ./build/node_types.o
#	g++ -c main.cpp -o ./build/main.o

#./build/node_types.o: node_types.h
#	g++ -c node_types.h -o ./build/node_types.o

#./build/sqlite3.o: ./lib/sqlite3.c
#	gcc -O2 -c ./lib/sqlite3.c -o ./build/sqlite3.o

#delete build files
clean:
	rm ./build/exe

#compile and run
run: output
	./build/exe


