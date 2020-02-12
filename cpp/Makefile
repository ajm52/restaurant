#Makefile for restaurant - C++ portion.
#Author: AJ McFarlane
#Created 1/22/20
#Last Modified 2/12/20


PROG := sim
CC := g++
ODIR := bin
SDIR := src
MAIN_OBJ := main.o
MAIN := main.cpp
PKG_DIRS := $(shell ls $(SDIR))
CXXFLAGS = -v -std=c++11 -Wall $(addprefix -I$(SDIR)/,$(PKG_DIRS)) -I$(BOOST_ROOT)
FIND_SRC_FILES = $(wildcard $(SDIR)/$(pkg)/*.cpp) 
SRC_FILES = $(foreach pkg,$(PKG_DIRS),$(FIND_SRC_FILES)) 
OBJ_FILES = $(patsubst $(SDIR)/%,$(ODIR)/%,\
$(patsubst %.cpp,%.o,$(filter-out $(SDIR)/main/$(MAIN),$(SRC_FILES))))

vpath %.h $(addprefix $(SDIR)/,$(PKG_DIRS))
vpath %.cpp $(addprefix $(SDIR)/,$(PKG_DIRS)) 
vpath $(MAIN) $(addprefix $(SDIR)/,main)

# main target
#$(PROG) : all
$(PROG) : $(MAIN) $(OBJ_FILES) 
	$(CC) $(CXXFLAGS) -o $(PROG) $(SDIR)/main/$(MAIN) 

# debugging
all : ; $(info $$PKG_DIRS is [${PKG_DIRS}])@echo Hello world

%.o : %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(OBJ_FILES) : $(ODIR)/%.o : $(SDIR)/%.h
	$(CC) $(CXXFLAGS) -c $< -o $@

# for whatever reason, clean is not being called...
# any ideas why???
.PHONY: clean

clean :
	@echo Build done! Cleaning object files...
	@rm -r $(ODIR)/*/*.o