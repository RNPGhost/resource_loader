include config.mk
include rules.mk

# Conventionally, "make all" builds everything a makefile knows how to build.
all: bin/resource_loader

# Specify the object files needed to generate the binary. These are always the
# same name as the cc files.
bin/resource_loader: $(patsubst src/%.cc, obj/%.o, $(wildcard src/*.cc))
