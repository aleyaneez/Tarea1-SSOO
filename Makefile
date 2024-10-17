CXX = g++
CXXFLAGS = -std=c++11 -pthread

all: CarreraAutos

CarreraAutos: CarreraAutos.cpp
	$(CXX) $(CXXFLAGS) -o CarreraAutos CarreraAutos.cpp

clean:
	rm -f CarreraAutos
