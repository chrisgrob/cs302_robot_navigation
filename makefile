
# for this makefile to work, you'll need these:
#
# sudo apt-get install libboost-all-dev
#

# Add .d to Make's recognized suffixes.
SUFFIXES += .d

CXX = g++

CFLAGS = -O3 -I. -std=c++14
LFLAGS = 

TARGETS = adj_lists

all: $(TARGETS)

adj_lists: adj_lists.o


$(TARGETS):
	$(CXX) -o $@ $^  $(LFLAGS)


%.o: %.cpp
	$(CXX) -M $(CFLAGS) $< > $*.d
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(TARGETS) *.d

test:
	./generate_random_pts_3d.pl 1000 > points1k.vtk
	./delaunay3d --filename points1k.vtk > delaunay3d1k.vtk
	./generate_random_pts_3d.pl 100000 > points100k.vtk
	./delaunay3d --filename points100k.vtk > delaunay3d100k.vtk


# pull in dependency info for *existing* .o files
# got this hint here: http://scottmcpeak.com/autodepend/autodepend.html
# except I'm using wildcard instead of a hard list of obj/d files.
# it's important for this to be after the first rule. Otherwise,
# make with no arguments will use one of these.
-include $(wildcard *.d)
