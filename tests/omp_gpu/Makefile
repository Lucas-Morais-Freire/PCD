COMP = g++
FLAGS = -Wall -Wextra -g -fopenmp # -O3
SRCS = ipsum.cpp lorem.cpp main.cpp
TARGET = main

OBJS = $(patsubst %.cpp,%.o,$(SRCS))
DEPS = $(patsubst %.cpp,%.d,$(SRCS))

all: $(DEPS) $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(COMP) $(FLAGS) $^ -o $@

%.o %.d: %.cpp
	$(COMP) $(FLAGS) -MMD -MP -MF $*.d -c $< -o $*.o

clean:
	rm -f $(OBJS) $(DEPS)