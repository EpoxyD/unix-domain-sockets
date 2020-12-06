

all: client server

client: client.c
	mkdir -p build
	$(CC) -g $^ -o build/$@

server: server.c
	mkdir -p build
	$(CC) -g $^ -o build/$@

clean:
	rm -rf build/*

.phony: all clean