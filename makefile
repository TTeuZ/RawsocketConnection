clientName = Client
serverName = Server

flags = -Wall -O3
objects = $(patsubst %.cpp, %.o, $(wildcard src/**/*.cpp))

.PHONY: all client server clean

# ----------------------------------------------------------------------

all: $(clientName) $(serverName)

client: $(clientName)

server: $(serverName)

# ----------------------------------------------------------------------

$(clientName): client.o $(objects) 
	g++ -o $(clientName) client.o $(objects) $(flags)

$(serverName): server.o $(objects)
	g++ -o $(serverName) server.o $(objects) $(flags)

client.o: client.cpp
	g++ -c client.cpp $(flags)

server.o: server.cpp
	g++ -c server.cpp $(flags)

%.o : %.cpp
	g++ -c $< -o $@ $(flags)

# ----------------------------------------------------------------------

clean:
	rm -f *.o src/**/*.o $(clientName) $(serverName)