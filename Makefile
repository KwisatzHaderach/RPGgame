LOGIN=xmatyas3
CC=g++
CFLAGS=-std=c++11
FILES=Capsule.cpp City.cpp Finale.cpp GameEngine.cpp Hero.cpp\
	Inventory.cpp Item.cpp main.cpp NPC.cpp Person.cpp Place.cpp\
	BeginningPlace.cpp DeadEnd.cpp FinishingPlace.cpp variables.cpp
TOPACK=Makefile description *.cpp *.h CMakeLists.txt ZOO-game.vpp ZOO-game.pdf

all: ZOO-game

ZOO-game: $(FILES)
	$(CC) $(CFLAGS) -o $@ -lm $(FILES)

run:
	./ZOO-game

clean:
	rm -f *.o *.out ZOO-game

tar:
	tar -zcvf $(LOGIN).tar.gz $(TOPACK)

zip:
	zip $(LOGIN).zip $(TOPACK)
