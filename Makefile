CPP=g++
CPPFILES=main.cpp
OBJFILES=main.o
OUTFILE=ipmanage
CPPFLAGS=-Wall

all: $(OUTFILE)

$(OUTFILE): $(OBJFILES)
	$(CPP) $(CPPFLAGS) $(OBJFILES) -o $(OUTFILE)

$(%.o): $(%.cpp)
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm *.o
	rm $(OUTFILE)

install: all
	cp $(OUTFILE) ~/getcount
