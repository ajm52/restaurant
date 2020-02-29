#Makefile for restaurant test code - C++ portion.
#Author: AJ McFarlane
#Created 1/24/20
#Last Modified 2/28/20

PROG := main
CC := g++
SDIR := ../src
PKG_DIRS := $(shell ls $(SDIR))
CXXFLAGS = -g -v -Wall -std=c++11 -I$(SDIR_TEST) \
$(addprefix -I$(SDIR)/,$(PKG_DIRS)) -I$(BOOST_ROOT) \
-L$(BOOST_LIBS) -lboost_unit_test_framework
ODIR_TEST = ./bin
SDIR_TEST = ./src
OUTDIR = ./execs
ODIR = ../sim/bin

TEST_OBJS = $(patsubst $(SDIR_TEST)%,$(ODIR_TEST)%,$(patsubst %.cpp,%.o,$(wildcard $(SDIR_TEST)/*.cpp)))

$(OUTDIR)/$(PROG) : $(TEST_OBJS)  
	$(CC) $(CXXFLAGS) -o $@ $^

$(ODIR_TEST)/%.o : $(SDIR_TEST)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@
