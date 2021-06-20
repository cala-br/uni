ifdef test
SRC=test/*.cpp
OUTFILE=tests
else
SRC=src/*.cpp
OUTFILE=uni
endif


INCLUDE=include/

CXXFLAGS += -std=c++20
CXXFLAGS += -I$(INCLUDE)
CXXFLAGS += -o $(OUTFILE)

MAKEFLAGS += --silent


main: depend build clean
build: $(SRC)
	g++ $(CXXFLAGS) $^

depend:
	g++ -MM $(SRC) > deps


-include deps


run: main exec cleanall 
exec:
	./$(OUTFILE)


.PHONY: clean cleanall
clean:
	rm -rf *.o

cleanall: clean
	rm -rf $(OUTFILE) deps