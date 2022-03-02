CPP=clang++
#CC=clang
SRC=./src

INCLUDES=-I$(SRC)/include

CPPFLAGS=-Wall -Wextra $(INCLUDES) -g3 -std=c++17
#CCFLAGS=-Wall -Wextra $(INCLUDES) -g3
LDFLAGS=


TARGET=nasha
BUILDDIR=bin

CPPSOURCES=$(shell find $(SRC) -name '*.cc')
OBJECTS = $(patsubst $(SRC)/%.cc, $(BUILDDIR)/%.o, $(CPPSOURCES))

#CSOURCES = $(shell find $(SRC) -name '*.c')
#OBJECTS += $(patsubst $(SRC)/%.c, $(BUILDDIR)/%.o, $(CSOURCES))


.PHONY: all build clean run dirs


all: build

build: dirs $(OBJECTS) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CPP) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRC)/%.cc
	$(CPP) $(CPPFLAGS) -c -o $@ $<

#$(BUILDDIR)/%.o: $(SRC)/%.c
#	$(CC) $(CCFLAGS) -c -o $@ $<


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

disa:
	objdump -Mintel,i386 -b binary -m i386 -D temp.out