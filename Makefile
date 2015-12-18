CPP=clang++
CPPFILES=main.cpp CMenu.cpp
OBJFILES=main.o CMenu.o
OUTFILE=ipmanage
CPPFLAGS=-Wall -Wextra -g
INSTALLDIR=/usr/local/bin

all: $(OUTFILE)

$(OUTFILE): $(OBJFILES)
	$(CPP) $(CPPFLAGS) $(OBJFILES) -o $(OUTFILE)

$(%.o): $(%.cpp)
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	rm *.o
	rm $(OUTFILE)

install: all
	cp $(OUTFILE) $(INSTALLDIR)/$(OUTFILE)

uninstall:
	rm $(INSTALLDIR)/$(OUTFILE)
