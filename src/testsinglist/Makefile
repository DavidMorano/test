# MAKEFILE (testsinglist)

T= testsinglist

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
CXXFLAGS= $(MAKECXXFLAGS)
ARFLAGS= $(MAKEARFLAGS)
LDFLAGS= $(MAKELDFLAGS)


INCS= testsinglist.h


OBJ0_TESTSINGLIST= main.o
OBJ1_TESTSINGLIST= 
OBJ2_TESTSINGLIST= 
OBJ3_TESTSINGLIST= 


OBJA_TESTSINGLIST= obj0_testsinglist.o 
#OBJA_TESTSINGLIST= obj0_testsinglist.o obj1_testsinglist.o
#OBJB_TESTSINGLIST= obj2_testsinglist.o obj3_testsinglist.o

OBJ_TESTSINGLIST= $(OBJA_TESTSINGLIST) $(OBJB_TESTSINGLIST)


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
	$(CXX)  $(CPPFLAGS) $(CXXFLAGS) -c $<


$(T).x:			$(OBJ_TESTSINGLIST)
	$(LD) -o $@ $(LDFLAGS) $(OBJ_TESTSINGLIST)

$(T).o:			$(OBJ_TESTSINGLIST)
	$(LD) -r -o $@ $(LDFLAGS) $(OBJ_TESTSINGLIST)

$(T).a:			$(OBJ_TESTSINGLIST)
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

obj0_testsinglist.o:	$(OBJ0_TESTSINGLIST)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ0_TESTSINGLIST)

obj1_testsinglist.o:	$(OBJ1_TESTSINGLIST)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ1_TESTSINGLIST)

obj2_testsinglist.o:	$(OBJ2_TESTSINGLIST)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ2_TESTSINGLIST)

obj3_testsinglist.o:	$(OBJ3_TESTSINGLIST)
	$(LD) $(LDFLAGS) -r -o $@ $(OBJ3_TESTSINGLIST)


