server:
	g++ server.c -o server

client:
	g++ client.c -o client

clean:
	rm -f server client