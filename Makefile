
test:
	g++ -c test.cpp -I /usr/local/include
	g++ test.o -o sfml-test -L /usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system
	export LD_LIBRARY_PATH=/usr/local/lib && ./sfml-test
