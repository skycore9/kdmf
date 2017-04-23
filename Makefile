.SUFFIXES: .o .cpp .h
CXX = g++-6
CFLAGS := -O3 -pthread -std=c++0x -march=native -funroll-loops -Wall -Wl,--no-as-needed
OBJ = mf.o convert.o train.o predict.o view.o

all: kdmf

%.o: src/%.cpp src/mf.h
	$(CXX) $(CFLAGS) $(DFLAG) -c -o $@ $<

kdmf: $(OBJ) src/main.cpp src/mf.h
	$(CXX) $(CFLAGS) -o kdmf $^

clean:
	rm -f $(OBJ) kdmf
