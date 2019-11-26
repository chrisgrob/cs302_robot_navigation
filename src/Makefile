EXECUTABLE_PATH=..
INCLUDE_PATH=../headers/include
OUT_PATH=../bin

CXX = g++

CFLAGS = -O3 -I$(INCLUDE_PATH) -I$(DEPENDENCY_PATH) -std=c++14
LFLAGS = 

TARGETS = main

all: $(TARGETS)

main: main.o test_struct.o

$(TARGETS):
	$(CXX) -o $(EXECUTABLE_PATH)/$@ $(^:%.o=$(OUT_PATH)/%.o)  $(LFLAGS)


%.o: %.cpp
	# $(CXX) -M $(CFLAGS) $< > $*.d
	# $(CXX) -c $(CFLAGS) $< -o $@
	$(CXX) -c $(CFLAGS) $< -o $(OUT_PATH)/$@

clean:
	rm -f *.o *.d


# pull in dependency info for *existing* .o files
# got this hint here: http://scottmcpeak.com/autodepend/autodepend.html
# except I'm using wildcard instead of a hard list of obj/d files.
# it's important for this to be after the first rule. Otherwise,
# make with no arguments will use one of these.
-include $(wildcard *.d)
