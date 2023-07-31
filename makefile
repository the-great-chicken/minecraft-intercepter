make build:
	g++ -o ./intercepter -I ./src/ ./src/*.cpp ./src/**/*.cpp
make clean:
	rm ./intercepter