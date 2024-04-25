clientName = Client
serverName = Server

flags = -Wall -O3
objects = $(patsubst %.cpp, %.o, $(wildcard utils/**/*.cpp))
objects += $(patsubst %.cpp, %.o, $(wildcard network/**/*.cpp))
libs = -lboost_program_options

.PHONY: all client server clean purge

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
	g++ -c client.cpp $(flags)

server.o: server.cpp
	g++ -c server.cpp $(flags)

%.o : %.cpp
	g++ -c $< -o $@ $(flags)

# ----------------------------------------------------------------------

clean:
	rm -f *.o utils/**/*.o network/**/*.o

purge:
	rm -f *.o utils/**/*.o network/**/*.o $(clientName) $(serverName)