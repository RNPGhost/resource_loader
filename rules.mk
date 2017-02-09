.PHONY: default
default: all

# Build with optimized configuration.
.PHONY: opt
opt: all

# Delete all generated files.
.PHONY: clean
clean:
	rm -rf bin obj

# Create the output (binary) directory.
bin:
	mkdir bin

# Create the intermediate (object) directory.
obj:
	mkdir obj

# Pattern rule for compiling a cc file into an o file.
obj/%.o: src/%.cc | obj
	${CXX} $< -c -o $@ ${CPPFLAGS} ${CXXFLAGS}

# Pattern rule for generating a binary.
bin/%: | bin
	${CXX} $^ -o $@ ${CPPFLAGS} ${CXXFLAGS} ${LDFLAGS}
