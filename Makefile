CC := clang++
CXXFLAGS := -std=c++11 -O3

BIN := bin
SRC := src

HEADERS := $(wildcard $(SRC)/*.h)
SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp,$(BIN)/%.o,$(SOURCES))
TARGETS := $(BIN)/fft

all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $@ $^

$(BIN)/%.o: $(SRC)/%.cpp $(HEADERS)
	$(CC) $(CXXFLAGS) -c -o $@ $<
