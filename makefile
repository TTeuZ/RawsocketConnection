clientName = Client
serverName = Server

flags = -Wall -O3
objects = $(patsubst %.cpp, %.o, $(wildcard src/**/*.cpp))
libs = -lboost_program_options

.PHONY: all client server clean

# ----------------------------------------------------------------------

all: $(clientName) $(serverName)

client: $(clientName)

server: $(serverName)

# ----------------------------------------------------------------------

$(clientName): client.o $(objects) 
	g++ -o $(clientName) client.o $(objects) $(flags) $(libs)

$(serverName): server.o $(objects)
	g++ -o $(serverName) server.o $(objects) $(flags) $(libs)

client.o: client.cpp
	g++ -c client.cpp $(flags) $(libs)

server.o: server.cpp
	g++ -c server.cpp $(flags) $(libs)

%.o : %.cpp
	g++ -c $< -o $@ $(flags) $(libs)

# ----------------------------------------------------------------------

clean:
	rm -f *.o src/**/*.o $(clientName) $(serverName)