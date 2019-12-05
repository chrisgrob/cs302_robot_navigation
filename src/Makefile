EXECUTABLE_PATH=..
INCLUDE_PATH=../headers/include
OUT_PATH=../bin

CXX = g++

CFLAGS = -O3 -I$(INCLUDE_PATH) -I$(DEPENDENCY_PATH) -std=c++14
LFLAGS = 

TARGETS = main

all: $(TARGETS)

main: main.o occupancy_grid_map.o robot.o robot_utils.o project_utils.o cardinal_direction.o

$(TARGETS):
	$(CXX) -o $(EXECUTABLE_PATH)/$@ $(^:%.o=$(OUT_PATH)/%.o)  $(LFLAGS)


%.o: %.cpp
	# $(CXX) -M $(CFLAGS) $< > $*.d
	# $(CXX) -c $(CFLAGS) $< -o $@
	$(CXX) -c $(CFLAGS) $< -o $(OUT_PATH)/$@

clean:
	rm -f *.o *.d

