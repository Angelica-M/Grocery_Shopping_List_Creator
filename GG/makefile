CXXFLAGS += -std=c++11
GTKFLAGS = `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

ex: gg_main.o gg.o
	$(CXX) $(CXXFLAGS) -o gg gg_main.o gg.o $(GTKFLAGS)
gg_main.o: gg_main.cpp gg.h
	$(CXX) $(CXXFLAGS) -c gg_main.cpp $(GTKFLAGS)
gg.o: gg.h gg.cpp
	$(CXX) $(CXXFLAGS) -c gg.cpp $(GTKFLAGS)
