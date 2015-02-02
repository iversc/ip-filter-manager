CPP=g++

all: main

main: main.cpp
	$(CPP) main.cpp -o main

clean:
	rm main
