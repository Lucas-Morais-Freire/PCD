COMP = nvcc
GXXFLAGS = -Wall -Wextra -g -fopenmp -v #-fno-lto # -O3
NVCCFLAGS = -g -G
GENCODE = arch=compute_86,code=sm_86
SRCS = src/ipsum.cpp src/lorem.cpp src/main.cpp
INCLUDE = ./include
TARGET = main

OBJS = $(patsubst %.cpp,%.o,$(SRCS))
DEPS = $(patsubst %.cpp,%.d,$(SRCS))
INCLUDE_FLAGS = $(patsubst %,-I%,$(INCLUDE))

ifeq ($(COMP), g++)

COMPILE = $(COMP) $(GXXFLAGS) -MMD -MP -MF $*.d -c $< -o $*.o $(INCLUDE_FLAGS)
LINK = $(COMP) $(GXXFLAGS) $^ -o $@

else ifeq ($(COMP), nvcc)

COMPILE = $(COMP) -gencode $(GENCODE) $(NVCCFLAGS) -c $< -o $*.o $(INCLUDE_FLAGS) -Xcompiler "$(GXXFLAGS) -MMD -MP -MF $*.d"
LINK = $(COMP) $^ -o $@ -Xcompiler "$(GXXFLAGS)"

endif

# test:
# 	@echo $(LINK)
# 	@echo $(COMPILE)

all: $(DEPS) $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(LINK)

%.o %.d: %.cpp
	$(COMPILE)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

run: $(TARGET)
	./$(TARGET)