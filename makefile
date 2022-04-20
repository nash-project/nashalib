CPP=clang++
SRC=./src

INCLUDES=-I./include -I./seegul/include/

CPPFLAGS=-Wall -Wextra $(INCLUDES) -g3 -std=c++17
LDFLAGS=


TARGET=nashalib.a
BUILDDIR=bin

CPPSOURCES=$(shell find $(SRC) -name '*.cc')
OBJECTS = $(patsubst $(SRC)/%.cc, $(BUILDDIR)/%.o, $(CPPSOURCES))



.PHONY: all build clean run dirs


all: build

build: dirs $(OBJECTS) $(TARGET)

$(BUILDDIR)/%.o: $(SRC)/%.cc
	@echo "[$(CPP)]===>[$<]->[$@]"
	@$(CPP) $(CPPFLAGS) -c -o $@ $<


clean:
	-@rm -rf $(OBJECTS) $(TARGET) $(BUILDDIR) temp.out docs

dirs:
	@mkdir -p $(BUILDDIR)
	@cd $(SRC) \
	&& dirs=$$(find -type d) \
	&& cd ../$(BUILDDIR) \
	&& mkdir -p $$dirs


build-docs:
	doxygen

$(TARGET):
	@ar rcs $@  $(shell find $(BUILDDIR) -type f -name "*.o")