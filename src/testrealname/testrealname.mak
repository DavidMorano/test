# MAKEFILE (testrealname)

T= testrealname

ALL= $(T).o


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

INCS += testrealname.h

MODS +=

LIBS= -ldebug -luo -lu -lf


OBJ_PR=

OBJ_PA0=
OBJ_PA1=

OBJ_PA=

OBJ_IM0=
OBJ_IM1=

OBJ_IM=

DEPS_PI=

DEPS= 

OBJ00= testrealname_main.o
OBJ01= prognamevar.o
OBJ02= realname.o mkrealname.o mkmailname.o
OBJ0=

OBJ04= 
OBJ05= 
OBJ06= 
OBJ07= 

OBJA= obj00.o obj01.o obj02.o
OBJB= obj04.o obj05.o obj06.o obj07.o
OBJC= 
OBJD= 

OBJ= obja.o 

OBJ_INFO= $(OBJ_PA) $(OBJ_PR) $(OBJ_IM)


INCDIRS=
LIBDIRS= -L lib

RUNINFO= -rpath $(RUNDIR)
LIBINFO= $(LIBDIRS) $(LIBS)

# flag setting
CPPFLAGS	?= $(DEFS) $(INCDIRS) $(MAKECPPFLAGS)
CFLAGS		?= $(MAKECFLAGS)
CXXFLAGS	?= $(MAKECXXFLAGS)
ARFLAGS		?= $(MAKEARFLAGS)
LDFLAGS		?= $(MAKELDFLAGS)


.SUFFIXES:		.hh .ii .iim .ccm


default:		$(T).x

all:			$(ALL)

so:			$(T).so


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
	gxx -c -x c++ -o $@ $(CPPFLAGS) $(CXXFLAGS) $<


$(T).x:			$(OBJ)
	$(CXX) -o $@ $(LDFLAGS) $(RUNINFO) $^ $(LIBINFO)

$(T).o:			$(OBJ)
	$(LD) -r -o $@ $(LDFLAGS) $^

$(T).so:		$(OBJ)
	$(LD) -o $@ $(SOFL) $(LDFLAGS) $^ $(LIBINFO)

$(T).a:			$(OBJ)
	$(AR) -rc $(T).a $?

$(T).nm:		$(T).o
	$(NM) $(NMFLAGS) $(T).o > $(T).nm

$(T).order order:	$(OBJ) $(T).a
	$(LORDER) $(T).a | $(TSORT) > $(T).order
	$(RM) $(T).a
	while read O ; do $(AR) -cr $(T).a $${O} ; done < $(T).order

install-pre:
	filefind . -s h | makenewer -af - -d $(INCDIR)

install:		$(ALL) Makefile
	ranlib $(T).a
	install -S -p -m 0775 $(T).so $(LIBDIR)

install-incs:		$(INSTALLINCS)
	makenewer $(INSTALLINCS) $(INCDIR)

safe:
	makesafe -v=3 -I $(INCDIR) $(OBJ)

again:
	rm -f $(ALL)

clean:
	makeclean $(ALL) testrealname.x
	rmsubpat

control:
	(uname -n ; date) > Control


obj00.o:		$(OBJ00)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj01.o:		$(OBJ01)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj02.o:		$(OBJ02)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj03.o:		$(OBJ03)
	$(LD) -r $(LDFLAGS) -o $@ $^


obja.o:			$(OBJA)
	$(LD) -r $(LDFLAGS) -o $@ $^

objb.o:			$(OBJB)
	$(LD) -r $(LDFLAGS) -o $@ $^

objc.o:			$(OBJC)
	$(LD) -r $(LDFLAGS) -o $@ $^

objd.o:			$(OBJD)
	$(LD) -r $(LDFLAGS) -o $@ $^

obje.o:			$(OBJE)
	$(LD) -r $(LDFLAGS) -o $@ $^

objf.o:			$(OBJF)
	$(LD) -r $(LDFLAGS) -o $@ $^

objg.o:			$(OBJG)
	$(LD) -r $(LDFLAGS) -o $@ $^


# parts
obj_pa.o:		$(OBJ_PA)

# primary
obj_pr.o:		$(OBJ_PR)

# implementation
obj_im0.o:		$(OBJ_IM0)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj_im1.o:		$(OBJ_IM1)
	$(LD) -r $(LDFLAGS) -o $@ $^

obj_im.o:		$(OBJ_IM)

testrealname_main.o:	testrealname_main.cc			$(DEPS)	$(INCS)

# LIBUC
realname.o:		realname.dir
realname.dir:
	makesubdir $@

# LINPROG
proginfo.o:		proginfo.dir
proginfo.dir:
	makesubdir $@

# LIBDEBUG
libdebug.o:		libdebug.dir
libdebug.dir:
	makesubdir $@

# LIBDAM
logfile.o:		logfile.dir
logfile.dir:
	makesubdir $@

# LIBDAM
prognamevar.o:		prognamevar.cc	prognamevar.hh
userinfo.o:		userinfo.cc	userinfo.h
mkrealname.o:		mkrealname.cc
mkmailname.o:		mkmailname.cc


