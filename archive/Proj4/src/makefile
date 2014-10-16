# set the C compiler, for C++ use g++
# use this setting on most sane machines
CC = gcc

# use this line on the engin linux machines
# CC = gcc296

# set the path to the include directory
INCDIR =../include

# set the flags for the C and C++ compiler to give lots of warnings
CFLAGS = -I$(INCDIR) -O2 -Wall -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes -Wmissing-declarations
CPPFLAGS = $(CFLAGS)

# path to the object file directory
ODIR = obj

# path to the lib directory
LIBDIR =../lib

# path to the bin directory
BINDIR =../bin

# libraries to include
LIBS = -lm -limageIO
LFLAGS = -L$(LIBDIR)

# put all of the relevant include files here
_DEPS = ppmIO.h color.h fractals.h image.h primitives.h floodfill.h graphics.h

# convert them to point to the right place
DEPS = $(patsubst %,$(INCDIR)/%,$(_DEPS))

# put a list of the executables here
EXECUTABLES = 3d test4a test4b req1 req2 req3

# put a list of all the object files here for all executables (with .o endings)
_OBJ = 3d.o test4a.o test4b.o req1.o req2.o req3.o

# convert them to point to the right place
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# patterns for compiling source code
# $< is the file that caused the action to occur
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.C $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


all:
	for i in $(EXECUTABLES); do (make $$i) ; done


# put the specific executable rules here
ppmtest: $(ODIR)/ppmmain.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
lab1: $(ODIR)/lab1.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
alphablend: $(ODIR)/alphablend.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
imagetest: $(ODIR)/imagetest.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
mandeltest: $(ODIR)/mandeltest.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
testbench: $(ODIR)/testbench.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
test3a: $(ODIR)/test3a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
testEll: $(ODIR)/testEll.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
test3b: $(ODIR)/test3b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
test3c: $(ODIR)/test3c.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
threed: $(ODIR)/threed.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
3d: $(ODIR)/3d.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
test4a: $(ODIR)/test4a.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
test4aNoFill: $(ODIR)/test4aNoFill.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
test4b: $(ODIR)/test4b.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
req1: $(ODIR)/req1.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
req2: $(ODIR)/req2.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)
req3: $(ODIR)/req3.o
	$(CC) -o $(BINDIR)/$@ $^ $(LFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

