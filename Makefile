CXX= g++
CXXFLAGS = -Wall -w -O -g `pkg-config gtkmm-2.4 --cflags`
LDFLAGS=`pkg-config gtkmm-2.4 --libs`
OBJS = subject.o model.o controller.o DeckGUI.o view.o main.o game.o Player.o Card.o Deck.o Table.o
EXEC = straights

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) $(LDFLAGS) -o $(EXEC)

clean:
	rm $(EXEC) $(OBJS)
