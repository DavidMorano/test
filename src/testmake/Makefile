# MAKEFILE (testmake)

CPP	?= cpp
CC	?= gcc
CXX	?= gpp
LD	?= gld
RANLIB	?= granlib
AR	?= gar
NM	?= gnm
COV	?= gcov
LORDER	?= lorder
TSORT	?= tsort
LINT	?= lint
RM	?= rm -f
TOUCH	?= touch
LINT	?= lint


UUCLIB= libuuc.a

OBJ= a.o b.o


default:
	print -- CC=$(CC) CFLAGS=$(CFLAGS) CXX=$(CXX) CXXFLAGS=$(CXXFLAGS)
	print -- CPP=$(CPP) NM=$(NM) LINT=$(LINT)

ucc(%o):	%.o


$(UUCLIB):	$(OBJ)
	$(AR) -r $@ $?


