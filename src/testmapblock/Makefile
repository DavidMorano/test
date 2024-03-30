# MAKEFILE (testmapblock)

T= testmapblock

ALL= $(T).o $(T).a


BINDIR= $(REPOROOT)/bin
INCDIR= $(REPOROOT)/include
LIBDIR= $(REPOROOT)/lib
MANDIR= $(REPOROOT)/man
INFODIR= $(REPOROOT)/info
HELPDIR= $(REPOROOT)/share/help


CRTDIR= $(CGS_CRTDIR)
VALDIR= $(CGS_VALDIR)
LIBDIR= $(CGS_LIBDIR)

CPP= cpp
CC= gcc
CXX= gpp
LD= gld
RANLIB= granlib
AR= gar
NM= gnm
COV= gcov

LORDER= lorder
TSORT= tsort
LINT= lint
RM= rm -f
TOUCH= touch
LINT= lint


DEFS=

LDRPATH= $(EXTRA)/lib

LIBDIRS= -L$(LIBDIR)

LIBS=


# flag setting
CPPFLAGS= $(DEFS) $(INCDIRS) $(MAKECPPFLAGS)
CFLAGS= $(MAKECFLAGS)
CCFLAGS= $(MAKECCFLAGS)
ARFLAGS= $(MAKEARFLAGS)
LDFLAGS= $(MAKELDFLAGS)


INCS= testmapblock.h


OBJ0_TESTMAPBLOCK= main.o
OBJ1_TESTMAPBLOCK= 
OBJ2_TESTMAPBLOCK= 
OBJ3_TESTMAPBLOCK= 


OBJA_TESTMAPBLOCK= obj0_testmapblock.o 
#OBJA_TESTMAPBLOCK= obj0_testmapblock.o obj1_testmapblock.o
#OBJB_TESTMAPBLOCK= obj2_testmapblock.o obj3_testmapblock.o

OBJ_TESTMAPBLOCK= $(OBJA_TESTMAPBLOCK) $(OBJB_TESTMAPBLOCK)


default:		$(T).x

all:			$(ALL)

.c.ln:
	$(LINT) -c $(LINTFLAGS) $(CPPFLAGS) $<

.c.ls:
	$(LINT) $(LINTFLAGS) $(CPPFLAGS) $<

.c.i:
	$(CPP) $(CPPFLAGS) $< > $(*).i

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

.cc.o:
	$(CXX)  $(CPPFLAGS) $(CCFLAGS) -c $<


$(T).x:			$(OBJ_TESTMAPBLOCK)
	$(LD) -o $@ $(LDFLAGS) $(OBJ_TESTMAPBLOCK)

$(T).o:			$(OBJ_TESTMAPBLOCK)
	$(LD) -r -o $@ $(LDFLAGS) $(OBJ_TESTMAPBLOCK)

$(T).a:			$(OBJ_TESTMAPBLOCK)
	$(AR) -rc $@ $(ARFLAGS) $?

$(T).nm:		$(T).so
	$(NM) $(NMFLAGS) $(T).so > $(T).nm

$(T).order:		$(OBJ) $(T).a
	$(LORDER) $(T).a | $(TSORT) > $(T).order
	$(RM) $(T).a
	while read O ; do $(AR) $(ARFLAGS) -cr $(T).a $${O} ; done < $(T).order

again:
	rm -f $(ALL)

clean:
	makeclean $(ALL)

control:
	(uname -n ; date) > Control

obj0_testmapblock.o:	$(OBJ0_TESTMAPBLOCK)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ0_TESTMAPBLOCK)

obj1_testmapblock.o:	$(OBJ1_TESTMAPBLOCK)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ1_TESTMAPBLOCK)

obj2_testmapblock.o:	$(OBJ2_TESTMAPBLOCK)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ2_TESTMAPBLOCK)

obj3_testmapblock.o:	$(OBJ3_TESTMAPBLOCK)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ3_TESTMAPBLOCK)


main.o:			main.cc mapblock.hh
mapblock.o:		mapblock.cc mapblock.hh


