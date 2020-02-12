#Makefile for restaurant test code - C++ portion.
#Author: AJ McFarlane
#Created 1/24/20
#Last Modified 2/3/20

PROG := main
CC := g++
SDIR := ../src
PKG_DIRS := $(shell ls $(SDIR))
CXXFLAGS = -v -Wall -std=c++11 -I$(SDIR_TEST) \
$(addprefix -I$(SDIR)/,$(PKG_DIRS)) -I$(BOOST_ROOT)
ODIR_TEST = ./bin
SDIR_TEST = ./src
OUTDIR = ./execs
ODIR = ../sim/bin

TEST_EXEC_NAMES = $(notdir $(basename $(wildcard $(SDIR_TEST)/*.cpp)))

# default rule (main.cpp)
$(OUTDIR)/$(PROG) : $(SDIR_TEST)/main.cpp $(TEST_EXEC_NAMES)
	$(CC) $(CXXFLAGS) -o $@ $<

% : $(SDIR_TEST)/%.cpp
	$(CC) $(CXXFLAGS) -o $(OUTDIR)/$@ $<
