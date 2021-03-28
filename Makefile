# set non-optional compiler flags here
CXXFLAGS += -std=c++14
#CXXFLAGS += -Wall -Wextra -pedantic-errors

# find cpp files in subdirectories
SOURCES := $(shell find . -name '*.cpp')

# find header files (.h or .hpp)
HEADERS := $(shell find . \( -name "*.h" -o -name "*.hpp" \))

OUTPUT := UnixShell

# Everything depends on the output
all: $(OUTPUT)

# The output depends on sources and headers
$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(OUTPUT) $(SOURCES)
