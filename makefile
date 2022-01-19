CPP=clang++
SRC=./src

INCLUDES=-I./include

CPPFLAGS=-Wall -Wextra $(INCLUDES) -g3 -std=c++17
LDFLAGS=


TARGET=nasha
BUILDDIR=bin

CSOURCES=$(shell find $(SRC) -name '*.cc')
OBJECTS = $(patsubst $(SRC)/%.cc, $(BUILDDIR)/%.o, $(CSOURCES))

.PHONY: all build clean run dirs


all: build

build: dirs $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CPP) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS)  main.cc -o $(TARGET)

$(BUILDDIR)/%.o: $(SRC)/%.cc
	$(CPP) $(CPPFLAGS) -c -o $@ $<

clean:
	-@rm -rf $(OBJECTS) $(TARGET) $(BUILDDIR)

dirs:
	@mkdir -p $(BUILDDIR)
	@cd $(SRC) \
	&& dirs=$$(find -type d) \
	&& cd ../$(BUILDDIR) \
	&& mkdir -p $$dirs

run: build
	./$(TARGET)

d:
	objdump -D -Mintel,i386 -b binary -m i386 ./asm