example.out: main.o bin/odyssey.a
	g++ -lstdc++ main.o bin/odyssey.a -o example.out -lm -lGL -lGLU -lglut -lglfw -lGLEW

main.o: main.cpp
	g++ -lstdc++ -lglfw -Wall -Wextra -Werror -c -o main.o main.cpp 
	
bin/odyssey.a: bin/main-module.o bin/time-module.o bin/view-module.o
	ar rsv bin/odyssey.a bin/main-module.o bin/time-module.o bin/view-module.o

bin/main-module.o: src/main-module/odyssey.h src/main-module/odyssey.cpp
	g++ -lstdc++ -c -o bin/main-module.o src/main-module/odyssey.cpp

bin/time-module.o: src/time-module/chrono.h src/time-module/chrono.cpp src/time-module/chronoCl.h
	g++ -lstdc++ -c -o bin/time-module.o src/time-module/chrono.cpp

bin/view-module.o: src/view-module/opengl.cpp src/view-module/opengl.hpp src/view-module/view.h src/view-module/viewHidden.h src/view-module/classes.hpp src/view-module/frame.hpp src/view-module/loader.hpp 
	g++ -lstdc++ -c -o bin/view-module.o src/view-module/opengl.cpp -lm -lGL -lGLU -lglut -lglfw -lGLEW

clean:
	rm bin/*
	rm example.out
