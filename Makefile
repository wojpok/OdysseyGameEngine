example.out: main.o bin/odyssey.a
	g++ -lstdc++ main.o bin/odyssey.a -o example.out

main.o: main.cpp
	g++ -lstdc++ -Wall -Wextra -Werror -c -o main.o main.cpp
	
bin/odyssey.a: bin/main-module.o bin/time-module.o
	ar rsv bin/odyssey.a bin/main-module.o bin/time-module.o

bin/main-module.o: src/main-module/odyssey.h src/main-module/odyssey.cpp
	g++ -lstdc++ -c -o bin/main-module.o src/main-module/odyssey.cpp

bin/time-module.o: src/time-module/chrono.h src/time-module/chrono.cpp src/time-module/chronoCl.h
	g++ -lstdc++ -c -o bin/time-module.o src/time-module/chrono.cpp
