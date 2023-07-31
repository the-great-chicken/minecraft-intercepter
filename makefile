make build:
	g++ -o ./intercepter -I ./src/ ./src/*.cpp
make clean:
	rm ./intercepter