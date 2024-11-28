all: server client

server: 
# g++ -I../dependency server.cc -o server
# -lwsock32 [windows] 
	g++ -I../dependency server.cc -o server -lws2_32 -lmswsock
client:
# g++ -I../dependency client.cc -o client
# -lwsock32 [windows]
	g++ -I../dependency client.cc -o client -lws2_32 -lmswsock
