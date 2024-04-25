clientName = Client
serverName = Server

flags = -Wall -O3
objects = $(patsubst %.cpp, %.o, $(wildcard src/exceptions/**/*.cpp))
objects += $(patsubst %.cpp, %.o, $(wildcard src/network/**/*.cpp))
objects += $(patsubst %.cpp, %.o, $(wildcard src/utils/**/*.cpp))
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
	rm -f *.o src/exceptions/**/*.o src/network/**/*.o src/utils/**/*.o

purge:
	rm -f *.o src/exceptions/**/*.o src/network/**/*.o src/utils/**/*.o $(clientName) $(serverName)