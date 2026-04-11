# MAKEFILE (varithmetic)

T= varithmetic

ALL= $(T).x


BINDIR		?= $(REPOROOT)/bin
INCDIR		?= $(REPOROOT)/include
LIBDIR		?= $(REPOROOT)/lib
MANDIR		?= $(REPOROOT)/man
INFODIR		?= $(REPOROOT)/info
HELPDIR		?= $(REPOROOT)/share/help
CRTDIR		?= $(CGS_CRTDIR)
VALDIR		?= $(CGS_VALDIR)
RUNDIR		?= $(CGS_RUNDIR)

CPP		?= cpp
CC		?= gcc
CXX		?= gxx
LD		?= gld
RANLIB		?= granlib
AR		?= gar
NM		?= gnm
COV		?= gcov
LORDER		?= lorder
TSORT		?= tsort
LINT		?= lint
RM		?= rm -f
TOUCH		?= touch
LINT		?= lint


DEFS +=

INCS +=

MODS +=

LIBS += -lf -luo -lu


ODEPS += varithmetic-util.o
ODEPS += varithmetic-shift.o
ODEPS += varithmetic-rotate.o
ODEPS += varithmetic-add.o
ODEPS += varithmetic-sub.o
ODEPS += varithmetic-mul.o
ODEPS += varithmetic-div.o

OBJ0= varithmetic.o
OBJ1= varithmetic-util.o
OBJ2= varithmetic-shift.o
OBJ3= varithmetic-rotate.o
OBJ3= varithmetic-add.o
OBJ4= varithmetic-sub.o
OBJ5= varithmetic-mul.o
OBJ6= varithmetic-div.o
OBJ7=

OBJA= obj0.o obj1.o obj2.o obj3.o
OBJB= obj4.o obj5.o obj7.o

OBJ= obja.o objb.o


INCDIRS=

#LIBDIRS= -L $(LIBDIR)
LIBDIRS= -L lib

RUNINFO= -rpath $(RUNDIR)
LIBINFO= $(LIBDIRS) $(LIBS)

# flag setting
CPPFLAGS	?= $(DEFS) $(INCDIRS) $(MAKECPPFLAGS)
CFLAGS		?= $(MAKECFLAGS)
CXXFLAGS	?= $(MAKECXXFLAGS) -g
ARFLAGS		?= $(MAKEARFLAGS)
LDFLAGS		?= $(MAKELDFLAGS)


.SUFFIXES:		.hh .ii .iim .ccm


default:		$(T).x

all:			$(ALL)


.c.i:
	$(CPP) $(CPPFLAGS) $< > $(*).i

.cc.ii:
	$(CPP) $(CPPFLAGS) $< > $(*).ii

.ccm.iim:
	$(CPP) $(CPPFLAGS) $< > $(*).iim

.c.s:
	$(CC) -S $(CPPFLAGS) $(CFLAGS) $<

.cc.s:
	$(CXX) -S $(CPPFLAGS) $(CXXFLAGS) $<

.c.o:
	$(COMPILE.c) $<

.cc.o:
	$(COMPILE.cc) $<

.ccm.o:
	makemodule $(*)


$(T).x:			obj.o Makefile
	$(CXX) -o $@ $(LDFLAGS) $(RUNINFO) obj.o $(LIBINFO)

$(T).nm:		$(T).x
	$(NM) $(NMFLAGS) $(T).x > $(T).nm

again:
	rm -f $(T).x

clean:
	makeclean $(ALL)

control:
	(uname -n ; date) > Control


obj0.o:			$(OBJ0)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj1.o:			$(OBJ1)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj2.o:			$(OBJ2)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj3.o:			$(OBJ3)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj4.o:			$(OBJ4)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj5.o:			$(OBJ5)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj6.o:			$(OBJ6)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj7.o:			$(OBJ7)
	$(LD) -r $(LDFLAGS) -o $@ $^


obja.o:			$(OBJA)
	$(LD) -r $(LDFLAGS) -o $@ $^

objb.o:			$(OBJB)
	$(LD) -r $(LDFLAGS) -o $@ $^


obj.o:			$(OBJ)
	$(LD) -r $(LDFLAGS) -o $@ $^


ODEPS+=

# VARITHMETIC
varithmetic.o:		varithmetic.ccm	builtin.o bitmanip.o muldigs.o 
	makemodule $@

varithmetic.o:		varithmetic.ccm	builtin.o bitmanip.o muldigs.o 

arithsteps.o:		arithsteps.ccm	builtin.o bitmanip.o muldigs.o

loadvals.o:		loadvals.ccm	bitmanip.o

muldigs.o:		muldigs.ccm	builtin.o

bitmanip.o:		bitmanip.ccm

builtin.o:		builtin.ccm


