#Makefile for restaurant test code - C++ portion.
#Author: AJ McFarlane
#Created 1/24/20
#Last Modified 2/3/20

PROG = main
CC = g++
CPPFLAGS = -Wall -I$(ODIR_TEST) -I$(SDIR_TEST) \
-I$(SDIR) -I$(ODIR) -I$(BOOST_ROOT)
ODIR_TEST = ./bin
SDIR_TEST = ./src
OUTDIR = ./execs
ODIR = ../sim/bin
SDIR = ../sim/src
TEST_EXEC_NAMES = $(notdir $(basename $(wildcard $(SDIR_TEST)/*.cpp)))

# default rule (main.cpp)
$(OUTDIR)/$(PROG) : $(SDIR_TEST)/main.cpp $(TEST_EXEC_NAMES)
	$(CC) $(CPPFLAGS) -o $@ $<

% : $(SDIR_TEST)/%.cpp
	$(CC) $(CPPFLAGS) -o $(OUTDIR)/$@ $<
