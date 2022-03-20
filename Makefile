#
# C compiler and flags
#
CC = clang
CFLAGS = -g -fPIC

#
# C++ compiler and flags
#
CXX = clang++
CXXFLAGS = -g -fPIC

# Linker flags
LDFLAGS = -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -Iinclude -lstdc++ -lsupc++

AR = ar
ARFLAGS = -crs

lupine_sourcedir := lib
lupine_objdir := obj
lupine_bindir := bin
lupine_includedir := include

# Source files
lupine_source_cxx := $(wildcard $(lupine_sourcedir)/*.cpp)
lupine_source_cc := $(wildcard $(lupine_sourcedir)/*.c)

# Object files
lupine_obj := $(subst $(lupine_sourcedir)/,$(lupine_objdir)/,$(addsuffix .o,$(basename $(lupine_source_cxx))) $(addsuffix .o,$(basename $(lupine_source_cc))))

# Include files
lupine_source_headers := $(shell find $(lupine_sourcedir)/ -type f -name '*.h') $(shell find $(lupine_sourcedir)/ -type f -name '*.hpp')
lupine_headers_inc := $(subst $(lupine_sourcedir)/,$(lupine_includedir)/,$(lupine_source_headers))

#
# Build library files
#
lupine_major := 0
lupine_minor := 0
lupine_dlname := lupine
lupine_version := $(lupine_major).$(lupine_minor)

lupine_libso := $(lupine_bindir)/lib$(lupine_dlname).so
lupine_libsom := $(lupine_libso).$(lupine_major)
lupine_libsov := $(lupine_libso).$(lupine_version)
lupine_liba := $(lupine_bindir)/lib$(lupine_dlname).a

lupine: $(lupine_libso) $(lupine_liba) lupine_include dirs

dirs:
	@mkdir -p $(lupine_sourcedir)
	@mkdir -p $(lupine_objdir)
	@mkdir -p $(lupine_bindir)
	@mkdir -p $(lupine_includedir)

lupine_include:
	@echo "Copying header files..."
	@cp -r $(lupine_sourcedir)/* $(lupine_includedir)/
	@find $(lupine_includedir) -type f -name \*.c | xargs rm -rf
	@find $(lupine_includedir) -type f -name \*.cpp | xargs rm -rf

$(lupine_libso): $(lupine_libsov)
	@echo "Building $@"
	@ln -sf $(lupine_libsov) $(lupine_libso)

$(lupine_libsov): $(lupine_obj)
	@echo "Building $@"
	@echo "  LD $@"
	@$(CC) $(CFLAGS) -shared -Wl,-soname,$(lupine_libsom) -o $@ $^

$(lupine_liba): $(lupine_obj)
	@echo "Building $@"
	@echo "  AR $@"
	@$(AR) $(ARFLAGS) $@ $^

$(lupine_objdir)/%.o: $(lupine_sourcedir)/%.cpp
	@echo "  CXX $^"
	@$(CXX) $(CXXFLAGS) -std=c++17 $^ -o $@ -c

$(lupine_objdir)/%.o: $(lupine_sourcedir)/%.c
	@echo "  CC $^"
	@$(CC) $(CFLAGS) -std=c17 $^ -o $@ -c

# END LIBRARY BUILD CODE

# Testing
test: lupine bin/app
	@echo "Running lupine test app..."
	@./bin/app


bin/app: $(wildcard src/*.cpp)
	@echo "Compiling lupine tester"
	@echo "  CXX $^"
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -I './include' -std=c++17 $^ $(shell readlink -f ./bin/liblupine.a) -o $@

targets:
	@echo "Avaliable targets:"
	@echo "lupine  | Build lupine as a static or shared library, use BUILD_STATIC=no BUILD_SHARED=no to disable as needed"
	@echo "test    | Build and run test file"
	@echo "clean   | Clean up built files"
	@echo "targets | Show avaliable targets"

clean:
	rm -rf ./bin/*
	rm -rf ./obj/*
	rm -rf ./include/*
