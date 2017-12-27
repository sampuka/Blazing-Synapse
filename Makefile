IDIR = include

SDIR = src
CC=g++
CFLAGS=-I$(IDIR) -g -Wall -std=c++11

ODIR=$(SDIR)/obj
LDIR =../lib

LIBS=-lm -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window 

_DEPS = HotSynapseGame.hpp GameScreen.hpp MatchScreen.hpp MatchMap.hpp MapTile.hpp EmptyTile.hpp WallTile.hpp SoldierTile.hpp OccupancyTile.hpp Soldier.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = HotSynapseGame.o MatchScreen.o MatchMap.o MapTile.o EmptyTile.o WallTile.o SoldierTile.o OccupancyTile.o Soldier.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

client: $(OBJ) BlazingSynapseClient.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

server: $(OBJ) BlazingSynapseServer.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/BlazingSynapseClient.o: $(SDIR)/BlazingSynapseClient.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/BlazingSynapseServer.o: $(SDIR)/BlazingSynapseServer.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ ircbutt $(IDIR)/*~
	rmdir $(ODIR)

$(shell mkdir -p $(ODIR))
