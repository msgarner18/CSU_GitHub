# This is a little Makefile.  Its purpose is to create the program “small”.
#
# The rules, below, indicate what depends on what, and how to build
# things when they get out-of-date.  It is VERY important to know
# that what looks like leading spaces is really a leading tab character.
#
# The TA will explain the structure and purpose of a Makefile.
#
# Write down your answers to the following questions, to show to
# the TA later.
#
# 1) Type “make”, observe what happens.
# 2) Run the resulting program “small”.
#
# 3) Type “make”, again.  Why did nothing much happen?
#
# 4) rm small
# 5) make (What got remade, and why?)
#
# 6) rm foo.o
# 7) make (What got remade, and why?)
#
# 8) make clean (What did that do?)
# 9) make (What got remade, and why?)
#
# 10) Why does main.o depend on foo.h?
#     I know that it’s because the Makefile said so.
#     Why was that dependency put into the Makefile?
#
# 11) Create a new function bar() in bar.cc & bar.h, similar to foo.cc
# 12) Change main.cc to use the new bar()
# 13) make (Why did it fail?)
# 14) Fix the Makefile
#
# 15) Uncomment the CXXFLAGS= line.
# 16) make (Why didn't anything happen?)
# 17) make clean
# 18) make (Observe the extra error-checking for g++)
#
# 19) When you type “make clean”, no file “clean” gets created.  Why not?
#
# 20) Show your answers to the TA.
#
# For extra fame & glory:
#
# Consult the make manual at https://www.gnu.org/software/make/manual/make.html
# and improve this makefile:
#
# 21) Use $@ in the rule that creates “small” itself.

CXX=g++
# CXXFLAGS=-std=c++14 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -Wctor-dtor-privacy -Wold-style-cast -D_GLIBCXX_DEBUG -fno-diagnostics-show-option

small: main.o foo.o
	$(CXX) $(CXXFLAGS) main.o foo.o -o small

main.o: main.cc foo.h
	$(CXX) $(CXXFLAGS) -c main.cc

foo.o: foo.cc foo.h
	$(CXX) $(CXXFLAGS) -c foo.cc

clean:
	-rm -f small *.o
