COMP = g++
FLAGS = -Wall -Wextra -g -fopenmp # -O3
SRCS = src/ipsum.cpp src/lorem.cpp src/main.cpp
INCLUDE = ./include
TARGET = main

OBJS = $(patsubst %.cpp,%.o,$(SRCS))
DEPS = $(patsubst %.cpp,%.d,$(SRCS))
INCLUDE_FLAGS = $(patsubst %,-I%,$(INCLUDE))

all: $(DEPS) $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(COMP) $(FLAGS) $^ -o $@

%.o %.d: %.cpp
	$(COMP) $(FLAGS) -MMD -MP -MF $*.d -c $< -o $*.o $(INCLUDE_FLAGS)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

run: $(TARGET)
	./$(TARGET)