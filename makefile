CCXX=g++
CXXFLAGS=-Iinclude -Isrc/hdr -Isrc
LDFLAGS=

BUILDDIR:=obj
SRCDIR:=src

CXXSRCS:=$(wildcard src/*.cpp)
CXXOBJS:=$(patsubst src/%.cpp, obj/%.o, $(CXXSRCS))
CXXHDRS:=$(wildcard src/*.hpp src/hdr/*.hpp include/*.hpp)

crawler : $(CXXOBJS)
	$(CCXX) -o $@ -g $(CXXFLAGS) $(CXXOBJS) $(LDFLAGS)

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CCXX) -c -g $< -o $@ $(CXXFLAGS) $(LDFLAGS)


test-mandelbrot : test/test.cpp
	$(CCXX) -o $@ -g $(LDFLAGS) $(CXXFLAGS) -Itest

clean : 
	rm -r obj/*
	rm -f crawler
