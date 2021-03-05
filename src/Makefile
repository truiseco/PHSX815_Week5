# C++ compiler
CXX = g++

# necessary compiler flags for using ROOT (root.cern.ch) - remove these if you're not using root
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTGLIBS     = $(shell root-config --glibs)

# ROOT shared library flags
GLIBS += $(filter-out -stdlib=libc++ -pthread , $(ROOTGLIBS))

# some compiler flags
CXXFLAGS = -std=c++17 -g -Wall
# ROOT flags
CXXFLAGS += -fPIC $(filter-out -stdlib=libc++ -pthread , $(ROOTCFLAGS))

# location of source code
SRCDIR = ./src/

#location of header files
#INCLUDEDIR = ./include/

#CXXFLAGS += -I$(INCLUDEDIR)

# location of object files (from compiled library files)
OUTOBJ = ./obj/

#CC_FILES := $(wildcard src/*.cpp)
#HH_FILES := $(wildcard include/*.h)
#OBJ_FILES := $(addprefix $(OUTOBJ),$(notdir $(CC_FILES:.cc=.o)))

# targets to make
all: SinSim.x

# recipe for building GeigerCounter.x
#GeigerCounter.x:  $(SRCDIR)GeigerCounter.cpp $(OBJ_FILES) $(HH_FILES)
#	$(CXX) $(CXXFLAGS) -o GeigerCounter.x $(OUTOBJ)/*.o $(GLIBS) $ $<
#	touch GeigerCounter.x

# recipe for building ExpHypoTest.x
#ExpHypoTest.x:  $(SRCDIR)ExpHypoTest.cpp $(OBJ_FILES) $(HH_FILES)
#	$(CXX) $(CXXFLAGS) -o ExpHypoTest.x $(OUTOBJ)/*.o $(GLIBS) $ $<
#	touch ExpHypoTest.x

SinSim.x: SinSim.o Random.o
	g++ $(CXXFLAGS) -g -Wall SinSim.o Random.o $(GLIBS) -o SinSim.x

SinSim.o: SinSim.cpp Random.h
	g++ $(CXXFLAGS) -g -Wall -c $(GLIBS) SinSim.cpp

Random.o: Random.h Random.cpp
	g++ -std=c++17 -g -Wall -c Random.cpp

#$(OUTOBJ)%.o: src/%.cpp include/%.h
#	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean-up target (make clean)
clean:
	rm -f *.x
	rm -rf *.dSYM
	rm -f *.o
