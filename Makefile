CPP=g++
CPPFILES=main.cpp
OBJFILES=main.o
OUTFILE=ipmanage

all: $(OUTFILE)

$(OUTFILE): $(OBJFILES)
	$(CPP) $(OBJFILES) -o $(OUTFILE)

$(%.o): $(%.cpp)
	$(CPP) -c $< -o $@

clean:
	rm *.o
	rm $(OUTFILE)
