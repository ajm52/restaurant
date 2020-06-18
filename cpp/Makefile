#Makefile for restaurant - C++ portion.
#Author: AJ McFarlane
#Created 1/22/20
#Last Modified 2/12/20


PROG := sim
CC := g++
ODIR := bin
SDIR := src
HPP_DIR := headers
MAIN_OBJ := main.o
MAIN := $(SDIR)/sim/main.cpp
PKG_DIRS := $(shell ls $(SDIR))
CXXFLAGS = -g -std=c++17 -Wall $(addprefix -I$(HPP_DIR)/,$(PKG_DIRS)) -I$(BOOST_ROOT)
FIND_SRC_FILES = $(wildcard $(SDIR)/$(pkg)/*.cpp) 
SRC_FILES = $(foreach pkg,$(PKG_DIRS),$(FIND_SRC_FILES)) 
OBJ_FILES = $(patsubst $(SDIR)/%,$(ODIR)/%,\
$(patsubst %.cpp,%.o,$(filter-out $(MAIN),$(SRC_FILES))))

vpath %.h $(addprefix $(SDIR)/,$(PKG_DIRS))
vpath %.cpp $(addprefix $(SDIR)/,$(PKG_DIRS)) 
vpath $(MAIN) $(addprefix $(SDIR)/,main)

# main target
#$(PROG) : all
$(PROG) : $(MAIN) $(OBJ_FILES)
	$(CC) $(CXXFLAGS) -o $(PROG) $(MAIN) $(OBJ_FILES)

# debugging
all : ; $(info $$PKG_DIRS is [${PKG_DIRS}])@echo Hello world

%.o : %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

 $(OBJ_FILES) : $(ODIR)/%.o : $(SDIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

# for whatever reason, clean is not being called...
# any ideas why???
.PHONY: clean

clean :
	@echo Build done! Cleaning object files...
	@rm -r $(ODIR)/*/*.o