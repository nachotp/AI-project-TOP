# C++ Makefile Template
# Copyright (c) 2018 Ignacio Tampe
# Based on Manuel Weitzman Makefile: https://github.com/mudetz/rcvrp/blob/master/Makefile thanks! <3
# You may use/distribute this template under the terms of the MIT LICENSE

# HowTo:
#	Create a src/ dir for all .cpp files
#	Create a head/ dir for all .h files
#	In .cpp files import .h files as if they were in the same dir
#	You have available:
#		make			Compile binaries
#		make install		Install final exec to root folder
#		make uninstall		Remove final exec from root folder
#		make clean		Remove intermediate .o files
#		make distclean		Remove final executable
#		make cleanall		clean+distclean

# Final executable name
EXEC = top.exe

# Macros
BENCHMARK ?= 0

# Directories for sourcefiles, headers and object files
SRCDIR = src
HEADDIR = head
OBJDIR = obj

# Files will be detected automatically (they shall not be in subdirectories
# though)
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Compiler options
CXX = g++
CPPFLAGS = $(addprefix -I, $(HEADDIR)) -MMD -MP -lm
CFLAGS = -O2 -Wall -std=c++11 -D"BENCHMARK=${BENCHMARK}" -g
LDFLAGS =
LDLIBS =

# Utilities used for output and others
ECHO = echo
RM = rm -rf
MKDIR = mkdir
INSTALL = install
FIND = find
CP = cp

# Makefile rules
.PHONY: all
all: $(OBJDIR) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJDIR):
	@$(MKDIR) -p $@

.PHONY: install
install:
	$(INSTALL) $(EXEC) $(EXEC)

.PHONY: uninstall
uninstall:
	$(RM) $(EXEC)

.PHONY: cleanall
cleanall: clean distclean

.PHONY: clean
clean:
	$(FIND) . -iname '*.d'            -type f -delete
	$(FIND) . -iname '*.o'            -type f -delete
	$(FIND) . -iname '*.exe'          -type f -delete
	$(FIND) . -iname '*.out'          -type f -delete

.PHONY: distclean
distclean:
	$(RM) $(EXEC)

-include $(wildcard $(OBJDIR)/*.d)