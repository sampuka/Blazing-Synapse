IDIR = include

SDIR = src
CC=g++
CFLAGS=-I$(IDIR) -g -Wall -std=c++11

ODIR=$(SDIR)/obj
LDIR =../lib

LIBS=-lm -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-network -pthread

_DEPS = BlazingSynapseClient.hpp BlazingSynapseServer.hpp GameScreen.hpp MainMenuScreen.hpp MatchScreen.hpp MatchMap.hpp sock.hpp #MapTile.hpp EmptyTile.hpp WallTile.hpp SoldierTile.hpp OccupancyTile.hpp Soldier.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = BlazingSynapseClient.o BlazingSynapseServer.o GameScreen.o MainMenuScreen.o MatchScreen.o MatchMap.o sock.o #MapTile.o EmptyTile.o WallTile.o SoldierTile.o OccupancyTile.o Soldier.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

client: $(OBJ) $(ODIR)/client.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

server: $(OBJ) $(ODIR)/server.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/client.o: $(SDIR)/client.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/server.o: $(SDIR)/server.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ $(IDIR)/*~ client server
	rmdir $(ODIR)

$(shell mkdir -p $(ODIR))
