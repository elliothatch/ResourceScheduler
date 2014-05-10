#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

CC = clang++
CFLAGS = -Wall -Wextra -pedantic -g -std=c++11
LFLAGS = 
RM = rm -f
MAIN = ResourceSimulation

CPPS := $(wildcard src/*.cpp)
OBJS := $(addprefix obj/,$(notdir $(CPPS:.cpp=.o)))

.PHONY: clean

all: $(MAIN)
	@echo Built $(MAIN).

$(MAIN): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *~ $(MAIN)

# DO NOT DELETE THIS LINE -- make depend needs it