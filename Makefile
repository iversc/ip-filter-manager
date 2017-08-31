CXX=clang++
CPPFILES=main.cpp CMenu.cpp
OBJFILES=main.o CMenu.o
OUTFILE=ipmanage
CPPFLAGS=-Wall -Wextra -g
INSTALLDIR=/usr/local/bin

all: $(OUTFILE)

$(OUTFILE): $(OBJFILES)
	$(CXX) $(CPPFLAGS) $(OBJFILES) -o $(OUTFILE)

$(%.o): $(%.cpp)
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm *.o
	rm $(OUTFILE)

install: all
	cp $(OUTFILE) $(INSTALLDIR)/$(OUTFILE)

uninstall:
	rm $(INSTALLDIR)/$(OUTFILE)
