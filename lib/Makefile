CXX=g++
CXXFLAGS=-g -O3 -Wall -shared -std=c++11 -fPIC
PYBIND=`python3 -m pybind11 --includes`
PYCONFIG=`python3-config --extension-suffix`

all: ../include/graph.hpp ggdGVC.cpp
	${CXX} $(CXXFLAGS) -I../include $(PYBIND) ggdGVC.cpp -o ggdGVC$(PYCONFIG)

clean:
	$(RM) -rf *.so
