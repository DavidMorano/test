/* dater */

/* general dater object */


#define	CF_DEBUGS	0		/* non-switchable debug print-outs */
#define	CF_ASSUMEZN	0		/* assume a zone-name */
#define	CF_SNTMTIME	1		/* use 'sntmtime(3dam)' */


/* revision history:

	= 1998-05-01, David A�D� Morano
        Originally created due to frustration with various other "fuzzy" date
        conversion subroutines.

*/

/* Copyright � 1998 David A�D� Morano.  All rights reserved. */

/*******************************************************************************
 
	This object can be used to create daters from various input data
	including strings.

	Note:

        The timezone offset value in 'struct timeb' is the minutes west of GMT.
        This is a positive value for timezones that are west of Greenwich. It is
        negative for timezones east of Greenwich. This is opposite from what you
        will see in email headers (for example). Our number here must be
        subtracted from GMT in order to get the local time.

	Frustration note:

	What an incredible pain this time-dater handling stuff all is?  This
	file doesn't even do justice to a small fraction of the real problems
	associated with date management!  The problem is that the dater changes
	as time progresses.  Changes are due to timezone differences and year
	leaps and leap seconds.  The fact that timezone data is not a part of
	many daters only complicates matters worse as we then have to try and
	figure out a reasonable timezone when they are not supplied.

	Comment parseing for RFC-822 dates:

	Note that dates given to us for MSG (RFC-822) processing, might have
	comments in them.  These comments are those specified in RFC-822.  Note
	that the TMZ object does some comment processing on MSG dates but only
	in the same way that NetNews does ; namely, only for a comment at the
	end of the string and which contains a time-zone-name.

        Full comment parsing is done on MSG dates using a COMPARSE object. With
        COMPARSE processing, we still try to divine a time-zone-name from the
        leading part of the resulting comment.


*******************************************************************************/


#define	DATER_MASTER	0


#include	<envstandards.h>

#include	<sys/types.h>
#include	<sys/timeb.h>
#include	<time.h>
#include	<tzfile.h>		/* for TM_YEAR_BASE */
#include	<stdlib.h>
#include	<string.h>

#include	<usystem.h>
#include	<estrings.h>
#include	<sbuf.h>
#include	<getdefzinfo.h>
#include	<tmtime.h>
#include	<localmisc.h>

#include	"dater.h"
#include	"zos.h"
#include	"comparse.h"	/* arguably should be handled elsewhere */
#include	"tmz.h"
#include	"zdb.h"


/* local defines */

#ifndef	NYEARS_CENTURY
#define	NYEARS_CENTURY	100
#endif

#ifndef	CENTURY_BASE
#define	CENTURY_BASE	19
#endif

#define	ISSIGN(c)	(((c) == '-') || ((c) == '+'))

#ifndef	TZO_EMPTY
#define	TZO_EMPTY	SHORT_MAX
#endif
#ifndef	TZO_MAXZOFF
#define	TZO_MAXZOFF	(14*60)
#endif

#ifndef	TIMEBUFLEN
#define	TIMEBUFLEN	80
#endif


/* external subroutines */

extern int	snwcpy(char *,int,cchar *,int) ;
extern int	sncpy1(char *,int,cchar *) ;
extern int	sncpy1w(char *,int,cchar *,int) ;
extern int	bufprintf(char *,int,cchar *,...) ;
extern int	isdigitlatin(int) ;
extern int	isNotPresent(int) ;

#if	CF_SNTMTIME
extern int	sntmtime(char *,int,TMTIME *,cchar *) ;
#endif

#if	CF_DEBUGS || CF_DEBUG
extern int	debugprintf(cchar *,...) ;
extern int	strlinelen(cchar *,int,int) ;
#endif

extern char	*strwcpy(char *,cchar *,int) ;
extern char	*strwcpylc(char *,cchar *,int) ;
extern char	*strwcpyuc(char *,cchar *,int) ;
extern char	*strcpylc(char *,cchar *) ;
extern char	*strcpyuc(char *,cchar *) ;
extern char	*strncpylc(char *,cchar *,int) ;
extern char	*strncpyuc(char *,cchar *,int) ;
extern char	*strnwcpy(char *,int,cchar *,int) ;
extern char	*strnpbrk(cchar *,int,cchar *) ;
extern char	*strdcpy1w(char *,int,cchar *,int) ;

extern char	*timestr_gmlog(time_t,char *) ;
extern char	*timestr_gmlogz(time_t,char *) ;
extern char	*timestr_log(time_t,char *) ;
extern char	*timestr_logz(time_t,char *) ;


/* external variables */


/* local structures */

struct knownzone {
	cchar		*zname ;
	int		zoff ;
	int		isdst ;
} ;


/* forward references */

int 		dater_settmzon(DATER *,struct tm *,int,cchar *,int) ;
int 		dater_settmzo(DATER *,struct tm *,int) ;
int 		dater_settmzn(DATER *,struct tm *,cchar *,int) ;
int		dater_mkdatestr(DATER *,int,char *,int) ;

static int	dater_initcur(DATER *) ;
static int	dater_ldname(DATER *,cchar *,int) ;
static int	dater_pname(DATER *) ;
static int	dater_pnum(DATER *) ;
static int	dater_findzname(DATER *) ;
static int	dater_findzoff(DATER *,struct tm *) ;
static int	dater_mkptime(DATER *,struct tm *,int) ;
static int	dater_mktime(DATER *,struct tm *) ;
static int	dater_mkpzoff(DATER *,struct tm *,int) ;

static int	mkzname(char *,cchar *,int) ;

#ifdef	COMMENT
static int	findtzcomment(char *,int,cchar *) ;
#endif


/* local variables */

#ifdef	COMMENT
static const struct knownzone	knownzones[] = {
	{ "gmt", 0*60, 0 },
	{ "usakdt", 8*60, 1 },	/* Alaska (US) */
	{ "usakst", 9*60, 0 },	/* Alaska (US) */
	{ "uscdt", 5*60, 1 },	/* central daylight time (US) */
	{ "uscst", 6*60, 0 },	/* central standard time (US) */
	{ "usedt", 4*60, 1 },	/* eastern daylight time (US) */
	{ "usest", 5*60, 0 },	/* eastern standard time (US) */
	{ "ushst", 10*60, 0 },	/* Hawaii */
	{ "usmdt", 6*60, 1 },	/* mountain daylight time (US) */
	{ "usmst", 7*60, 0 },	/* mountain standard time (US) */
	{ "uspdt", 7*60, 1 },	/* pacific daylight time (US) */
	{ "uspst", 8*60, 0 },	/* pacific standard time (US) */
	{  "ut", 0*60, 0 },	/* universal time? */
	{ "utc", 0*60, 0 },	/* UTC */
	{ "z", 0*60, 0 },
	{ NULL, 0, 0 }
} ;
#endif /* COMMENT */

#if	CF_SNTMTIME

#else /* CF_SNTMTIME */

static cchar	*months[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec",
} ;

static cchar	*days[] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat",
} ;

#endif /* CF_SNTMTIME */

#if	CF_DEBUGS
static cchar	*types[] = {
	"std",
	"msg",
	"strdig",
	"logz",
	"gmlogz",
	NULL
} ;
#endif /* CF_DEBUGS */


/* exported subroutines */


int dater_start(DATER *dp,struct timeb *nowp,cchar znp[],int znl)
{

	if (dp == NULL) return SR_FAULT ;

	memset(dp,0,sizeof(DATER)) ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;

/* continue */

	if (nowp != NULL) {
	    dp->f.cb = TRUE ;
	    dp->cb = *nowp ;
	} /* end if (time-offset) */

	if ((znp != NULL) && (znl != 0)) {
	    dp->f.czn = TRUE ;
	    strnwcpy(dp->cname,DATER_ZNAMESIZE,znp,znl) ;
	}

	dp->magic = DATER_MAGIC ;
	return SR_OK ;
}
/* end subroutine (dater_start) */


/* initialize a DATER object from another */
int dater_startcopy(DATER *dp,DATER *d2p)
{

	if (dp == NULL) return SR_FAULT ;
	if (d2p == NULL) return SR_FAULT ;

	if (d2p->magic != DATER_MAGIC) return SR_NOTOPEN ;

	memcpy(dp,d2p,sizeof(DATER)) ;

#if	CF_DEBUGS
	{
	    char	timebuf[TIMEBUFLEN + 1] ;
	    debugprintf("dater_startcopy: new loctime=%s\n",
	        timestr_logz(dp->b.time,timebuf)) ;
	}
#endif

	return SR_OK ;
}
/* end subroutine (dater_startcopy) */


/* deconstruct up a DATER object */
int dater_finish(DATER *dp)
{

	if (dp == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;

	dp->b.time = 0 ;
	dp->magic = 0 ;
	return SR_OK ;
}
/* end subroutine (dater_finish) */


#ifdef	COMMENT
/* copy a DATER object */
int dater_copy(DATER *dp,DATER *d2p)
{

	if (dp == NULL) return SR_FAULT ;
	if (d2p == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;

	memcpy(dp,d2p,sizeof(DATER)) ;

	return SR_OK ;
}
/* end subroutine (dater_copy) */
#endif /* COMMENT */


/* copy one dater to another */
int dater_setcopy(DATER *dp,DATER *d2p)
{

	if (dp == NULL) return SR_FAULT ;
	if (d2p == NULL) return SR_FAULT ;

	if (d2p->magic != DATER_MAGIC) return SR_NOTOPEN ;

#if	CF_DEBUGS
	debugprintf("dater_setcopy: ent\n") ;
#endif

#ifdef	COMMENT
	memcpy(&dp->b,&d2p->b,sizeof(struct timeb)) ;
	strncpy(dp->zname,d2p->zname,DATER_ZNAMESIZE) ;
	dp->f.zname = d2p->f.zname ;
	dp->f.zoff = d2p->f.zoff ;
	dp->f.tzset = d2p->f.tzset ;
#else /* COMMENT */
	memcpy(dp,d2p,sizeof(DATER)) ;
#endif /* COMMENT */

	return SR_OK ;
}
/* end subroutine (dater_setcopy) */


/* set from a standard time string (like UNIX�) */
int dater_setstd(DATER *dp,cchar *sp,int sl)
{
	struct tm	dst ;
	TMZ		stz ;
	int		rs ;

#if	CF_DEBUGS
	char	timebuf[TIMEBUFLEN + 1] ;
#endif

#if	CF_DEBUGS
	debugprintf("dater_setstd: ent >%t<\n",
	    sp,strnlen(sp,sl)) ;
#endif

	if (dp == NULL) return SR_FAULT ;
	if (sp == NULL) return SR_FAULT ;

	if (sl < 0)
	    sl = strlen(sp) ;

	if (sl > 99)
	    return SR_TOOBIG ;

/* initialize */

	dp->zname[0] = '\0' ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;
	dp->f.zname = FALSE ;
	dp->f.zoff = FALSE ;

/* continue */

	if ((rs = tmz_std(&stz,sp,sl)) >= 0) {
	    int	f = FALSE ;

#if	CF_DEBUGS
	debugprintf("dater_setstd: tmz_std() rs=%d\n",rs) ;
	debugprintf("dater_setstd: year=%u mon=%u mday=%d wday=%d\n",
	    stz.st.tm_year,
	    stz.st.tm_mon,
	    stz.st.tm_mday,stz.st.tm_wday) ;
	debugprintf("dater_setstd: hour=%u min=%u sec=%u\n",
	    stz.st.tm_hour,
	    stz.st.tm_min,
	    stz.st.tm_sec) ;
	debugprintf("dater_setstd: timezone=%d (%dm) zname=>%t<\n",
	    stz.zoff,(stz.zoff / 60),
	    stz.zname,strnlen(stz.zname,MIN(rs,TMZ_ZNAMESIZE))) ;
#endif /* CF_DEBUGS */

	    dst = stz.st ;
	    dp->b.timezone = stz.zoff ;
	    dp->b.dstflag = stz.st.tm_isdst ;
	    dp->f.zoff = stz.f.zoff ;
	    strncpylc(dp->zname,stz.zname,DATER_ZNAMESIZE) ;
	    dp->f.zname = (dp->zname[0] != '\0') ;

	            f = f || (tmz_haszone(&stz) == 0) ;
	            f = f || (tmz_hasyear(&stz) == 0) ;
	            f = f || (tmz_haszoff(&stz) == 0) ;
	    if (f) {
		rs = dater_initcur(dp) ;
	    }
	    if (rs >= 0) {
		if (tmz_hasyear(&stz) == 0) {
	    	    dst.tm_year = dp->cyear ;
		}
		if (! dp->f.zoff) {
	    	    rs = dater_findzoff(dp,&dst) ;
		}
		if (rs >= 0) {
	    	    rs = dater_mktime(dp,&dst) ;
		}
	    } /* end if (ok) */
	} /* end if (tmz_std) */

#if	CF_DEBUGS
	debugprintf("dater_setstd: dater_settmzn() rs=%d\n",rs) ;
	debugprintf("dater_setstd: loctime=%s\n",
	    timestr_log(dp->b.time,timebuf)) ;
#endif

	return rs ;
}
/* end subroutine (dater_setstd) */


/* set the dater from a message-type string */
int dater_setmsg(DATER *dp,cchar *sp,int sl)
{
	struct tm	dst ;
	TMZ		stz ;
	COMPARSE	vc ;
	int		rs ;
	int		vl ;
	cchar		*vp ;
	char		zname[DATER_ZNAMESIZE + 1] ;

#if	CF_DEBUGS
	debugprintf("dater_setmsg: ent >%t<\n",
	    sp,strnlen(sp,sl)) ;
#endif

	if (dp == NULL) return SR_FAULT ;
	if (sp == NULL) return SR_FAULT ;

	if (sl < 0)
	    sl = strlen(sp) ;

	if (sl > 99)
	    return SR_TOOBIG ;

/* initialize */

	dp->zname[0] = '\0' ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;
	dp->f.zname = FALSE ;
	dp->f.zoff = FALSE ;

/* continue */

	if ((rs = comparse_start(&vc,sp,sl)) >= 0) {
	    if ((rs = comparse_getval(&vc,&vp)) >= 0) {
		int	znl ;
		cchar	*znp ;
	        vl = rs ;

#if	CF_DEBUGS
	        debugprintf("dater_setmsg: datestr=>%t<\n",vp,vl) ;
#endif

	        rs = tmz_msg(&stz,vp,vl) ;
	        znl = rs ;

#if	CF_DEBUGS
	        debugprintf("dater_setmsg: tmz_msg() rs=%d\n",rs) ;
	        debugprintf("dater_setmsg: year=%u mon=%u mday=%d wday=%d\n",
	            stz.st.tm_year,
	            stz.st.tm_mon,
	            stz.st.tm_mday,stz.st.tm_wday) ;
	        debugprintf("dater_setmsg: hour=%u min=%u sec=%u\n",
	            stz.st.tm_hour,
	            stz.st.tm_min,
	            stz.st.tm_sec) ;
	        debugprintf("dater_setmsg: f_zoff=%d zoff=%dm zname=>%t<\n",
	            stz.f.zoff,
	            stz.zoff,
	            stz.zname,strnlen(stz.zname,MIN(rs,TMZ_ZNAMESIZE))) ;
#endif /* CF_DEBUGS */

/* does it have a comment (first 8 chars only) that looks like a TZ? */

	        znp = stz.zname ;
	        if ((rs >= 0) && (znp[0] == '\0')) {
	            int		cl ;
	            cchar	*cp ;

#if	CF_DEBUGS
	            debugprintf("dater_setmsg: check comments for ZN\n") ;
#endif
	            if ((cl = comparse_getcom(&vc,&cp)) > 0) {
	                znp = zname ;
	                znl = mkzname(zname,cp,cl) ;
	            }
	        }

	        if (rs >= 0) {
	            dst = stz.st ;
	            dp->b.timezone = stz.zoff ;
	            dp->b.dstflag = stz.st.tm_isdst ;
	            dp->f.zoff = stz.f.zoff ;
	            strnwcpy(dp->zname,DATER_ZNAMESIZE,znp,znl) ;
	            dp->f.zname = (dp->zname[0] != '\0') ;
	        }

/* can we supply some missing pieces? */

	        if (rs >= 0) {
	            int	f = FALSE ;
	            f = f || (tmz_haszone(&stz) == 0) ;
	            f = f || (tmz_hasyear(&stz) == 0) ;
	            f = f || (tmz_haszoff(&stz) == 0) ;
	            if (f) rs = dater_initcur(dp) ;
	        } /* end if */

	        if ((rs >= 0) && (tmz_hasyear(stz) == 0)) {
	            dst.tm_year = dp->cyear ;
	        }

	        if ((rs >= 0) && (! dp->f.zoff)) {
	            rs = dater_findzoff(dp,&dst) ;
		}

	        if (rs >= 0) {
	            rs = dater_mktime(dp,&dst) ;
		}

	    } /* end if */
	    comparse_finish(&vc) ;
	} /* end if (comparse) */

#if	CF_DEBUGS
	{
	    char	timebuf[TIMEBUFLEN+1] ;
	    debugprintf("dater_setmsg: ret rs=%d\n",rs) ;
	    debugprintf("dater_setmsg: loctime=%s\n",
	        timestr_logz(dp->b.time,timebuf)) ;
	    debugprintf("dater_setmsg: gmttime=%s\n",
	        timestr_gmlogz(dp->b.time,timebuf)) ;
	}
#endif

	return rs ;
}
/* end subroutine (dater_setmsg) */


/* set from a dater-like or decimal digit time string */
/* format> [CC]YYMMDDhhmm[ss][�<zoff>][<zname>] */
int dater_setstrdig(DATER *dp,cchar *sp,int sl)
{
	struct tm	dst ;
	TMZ		stz ;
	int		rs ;
#if	CF_DEBUGS
	char		timebuf[TIMEBUFLEN + 1] ;
#endif

#if	CF_DEBUGS
	debugprintf("dater_setstrdig: ent >%t<\n",
	    sp,strnlen(sp,sl)) ;
#endif

	if (dp == NULL) return SR_FAULT ;
	if (sp == NULL) return SR_FAULT ;

	if (sl < 0)
	    sl = strlen(sp) ;

	if (sl > 99)
	    return SR_TOOBIG ;

/* initialize */

	dp->zname[0] = '\0' ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;
	dp->f.zname = FALSE ;
	dp->f.zoff = FALSE ;

/* continue */

	if ((rs = tmz_strdig(&stz,sp,sl)) >= 0) {
	    const int	f_year = tmz_hasyear(&stz) ;
	    const int	f_zoff = tmz_haszoff(&stz) ;
	    const int	f_zone = tmz_haszone(&stz) ;

#if	CF_DEBUGS
	debugprintf("dater_setstrdig: tmz_msg() rs=%d\n",rs) ;
	debugprintf("dater_setstrdig: year=%u mon=%u mday=%u\n",
	    stz.st.tm_year,
	    stz.st.tm_mon,
	    stz.st.tm_mday) ;
	debugprintf("dater_setstrdig: hour=%u min=%u sec=%u\n",
	    stz.st.tm_hour,
	    stz.st.tm_min,
	    stz.st.tm_sec) ;
	debugprintf("dater_setstrdig: f_zoff=%d zoff=%dm zname=>%t<\n",
	    stz.f.zoff,
	    stz.zoff,
	    stz.zname,strnlen(stz.zname,MIN(rs,TMZ_ZNAMESIZE))) ;
#endif /* CF_DEBUGS */

	    dst = stz.st ;
	    dp->b.timezone = stz.zoff ;
	    dp->b.dstflag = stz.st.tm_isdst ;
	    dp->f.zoff = f_zoff ;
	    strncpylc(dp->zname,stz.zname,DATER_ZNAMESIZE) ;
	    dp->f.zname = f_zone ;

/* can we supply some missing pieces? */

	if (rs >= 0) {
	    int	f = FALSE ;
	    f = f || (! f_year) ;
	    f = f || (! f_zoff) ;
	    f = f || (! f_zone) ;
	    if (f) rs = dater_initcur(dp) ;
	} /* end if */

	if ((rs >= 0) && (! f_year)) {
	    dst.tm_year = dp->cyear ;
	}

	if ((rs >= 0) && (! dp->f.zoff)) {
	    rs = dater_findzoff(dp,&dst) ;
	}

#if	CF_DEBUGS
	debugprintf("dater_setstd: adjusted year=%d timezone=%dm\n",
	    stz.st.tm_year, stz.zoff) ;
	debugprintf("dater_setstd: adjusted zname=>%t<\n",
	    stz.zname,strnlen(stz.zname,TMZ_ZNAMESIZE)) ;
#endif /* CF_DEBUGS */

/* go for it */

#if	CF_DEBUGS
	debugprintf("dater_setstd: dater_mktime() zname=>%t<\n",
	    stz.zname,strnlen(stz.zname,TMZ_ZNAMESIZE)) ;
#endif

	if (rs >= 0) {
	    rs = dater_mktime(dp,&dst) ;
	}

	} /* end if tmz_strdig) */

#if	CF_DEBUGS
	if (rs < 0)
	    debugprintf("dater_setstrdig: dater_settmz[on]() rs=%d\n",rs) ;
	debugprintf("dater_setstrdig: local=%s\n",
	    timestr_log(dp->b.time,timebuf)) ;
	debugprintf("dater_setstrdig: gmt=%s\n",
	    timestr_gmlog(dp->b.time,timebuf)) ;
	debugprintf("dater_setstrdig: f_zoff zoff=%dm\n",
		dp->f.zoff,dp->b.timezone) ;
	debugprintf("dater_setstrdig: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (dater_setstrdig) */


/* set from a LOGZ-type string */

/*
This amounts to a conversion from the string:
      990704_1647:33_EDT
to the DATER object.
*/

int dater_setlogz(DATER *dp,cchar *sp,int sl)
{
	TMZ		stz ;
	int		rs ;
	int		znlen ;

#if	CF_DEBUGS
	debugprintf("dater_setlogz: ent >%t<\n",
	    sp,strnlen(sp,sl)) ;
#endif

	if (dp == NULL) return SR_FAULT ;
	if (sp == NULL) return SR_FAULT ;

	if (sl < 0)
	    sl = strlen(sp) ;

	if (sl > 99)
	    return SR_TOOBIG ;

/* initialize */

	dp->zname[0] = '\0' ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;
	dp->f.zname = FALSE ;
	dp->f.zoff = FALSE ;

/* continue */

	if ((rs = tmz_logz(&stz,sp,sl)) >= 0) {
	    const int	f_year = tmz_hasyear(&stz) ;
	    const int	f_zoff = tmz_haszoff(&stz) ;
	    const int	f_zone = tmz_haszone(&stz) ;
	znlen = rs ;

#if	CF_DEBUGS
	debugprintf("dater_setlogz: tmz_msg() rs=%d\n",rs) ;
	debugprintf("dater_setlogz: year=%u mon=%u mday=%u\n",
	    stz.st.tm_mon,
	    stz.st.tm_mday,
	    stz.st.tm_hour) ;
	debugprintf("dater_setlogz: hour=%u min=%u sec=%u\n",
	    stz.st.tm_year,
	    stz.st.tm_min,
	    stz.st.tm_sec) ;
	debugprintf("dater_setlogz: f_zoff=%d zoff=%dm zname=>%t<\n",
	    stz.f.zoff,
	    stz.zoff,
	    stz.zname,strnlen(stz.zname,MIN(rs,TMZ_ZNAMESIZE))) ;

#endif /* CF_DEBUGS */

/* can we supply some missing pieces? */

	if ((rs >= 0) &&
	    ((! stz.f.zoff) && (stz.zname[0] == '\0'))) {

	    rs = dater_initcur(dp) ;

	    if (stz.zname[0] == '\0') {
	        znlen = -1 ;
	        strncpy(stz.zname,dp->cname,TMZ_ZNAMESIZE) ;
	    }

#if	CF_DEBUGS
	    debugprintf("dater_setlogz: adjusted year=%d timezone=%dm\n",
	        stz.st.tm_year, stz.zoff) ;
	    debugprintf("dater_setlogz: adjusted zname=>%t<\n",
	        stz.zname,strnlen(stz.zname,TMZ_ZNAMESIZE)) ;
#endif /* CF_DEBUGS */

	} /* end if (getting missing stuff) */

/* do it */

	if (rs >= 0) {
	    if (stz.f.zoff && (stz.zname[0] != '\0')) {
	        rs = dater_settmzon(dp,&stz.st,stz.zoff,stz.zname,znlen) ;
	    } else if (stz.f.zoff) {
	        rs = dater_settmzo(dp,&stz.st,stz.zoff) ;
	    } else if (stz.zname[0] != '\0') {
	        rs = dater_settmzn(dp,&stz.st,stz.zname,znlen) ;
	    }
	} /* end if */

#if	CF_DEBUGS
	if (rs < 0)
	    debugprintf("dater_setlogz: dater_settmz[on]() rs=%d\n",rs) ;
	debugprintf("dater_setlogz: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (dater_setlogz) */


/* set from TOUCH (original) time string */
int dater_settouch(DATER *dp,cchar *sp,int sl)
{
	TMZ		stz ;
	int		rs ;
	int		znlen ;

#if	CF_DEBUGS
	debugprintf("dater_settouch: ent >%t<\n",
	    sp,strnlen(sp,sl)) ;
#endif

	if (dp == NULL) return SR_FAULT ;

	if (sl < 0)
	    sl = strlen(sp) ;

	if (sl > 99)
	    return SR_TOOBIG ;

/* initialize */

	dp->zname[0] = '\0' ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;
	dp->f.zname = FALSE ;
	dp->f.zoff = FALSE ;

/* continue */

	rs = tmz_touch(&stz,sp,sl) ;
	znlen = rs ;

#if	CF_DEBUGS
	debugprintf("dater_settouch: tmz_msg() rs=%d\n",rs) ;
	debugprintf("dater_settouch: year=%u mon=%u mday=%u\n",
	    stz.st.tm_mon,
	    stz.st.tm_mday,
	    stz.st.tm_hour) ;
	debugprintf("dater_settouch: hour=%u min=%u sec=%u\n",
	    stz.st.tm_year,
	    stz.st.tm_min,
	    stz.st.tm_sec) ;
	debugprintf("dater_settouch: timezone=%d zname=>%t<\n",
	    stz.zoff,
	    stz.zname,strnlen(stz.zname,MIN(rs,TMZ_ZNAMESIZE))) ;
#endif /* CF_DEBUGS */

/* can we supply some missing pieces? */

	if (rs >= 0) {
	    const int	f_year = tmz_hasyear(&stz) ;
	    const int	f_zone = tmz_haszone(&stz) ;
	    if ((! f_year) || (! f_zone)) {

	    if (! f_year) {

#if	CF_DEBUGS
	        debugprintf("dater_settouch: try get cyear, f_cyear=%d\n",
	            dp->f.czn) ;
#endif

	        if (! dp->f.cyear) {
	            rs = dater_initcur(dp) ;
		}

	        tmz_setyear(&stz,dp->cyear) ;

	    }

	    if ((rs >= 0) &&
	        ((znlen == 0) || (! f_zone))) {

	        if (! dp->f.czn) {
	            rs = dater_initcur(dp) ;
		}

	        znlen = -1 ;
	        strncpy(stz.zname,dp->cname,TMZ_ZNAMESIZE) ;

	    }

#if	CF_DEBUGS
	    debugprintf("dater_settouch: adjusted year=%d timezone=%dm\n",
	        stz.st.tm_year, stz.zoff) ;
	    debugprintf("dater_settouch: adjusted zname=>%t<\n",
	        stz.zname,strnlen(stz.zname,TMZ_ZNAMESIZE)) ;
#endif /* CF_DEBUGS */

	} /* end if (getting missing stuff) */

/* go for it */

#if	CF_DEBUGS
	debugprintf("dater_settouch: dater_settmzn() zname=>%t<\n",
	    stz.zname,strnlen(stz.zname,TMZ_ZNAMESIZE)) ;
#endif

	if (rs >= 0) {
	    rs = dater_settmzn(dp,&stz.st,stz.zname,znlen) ;
	}

#if	CF_DEBUGS
	if (rs < 0)
	    debugprintf("dater_settouch: dater_settmzn() rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (dater_settouch) */


/* set from TOUCH-t (new '-t' version) time string */
int dater_settoucht(DATER *dp,cchar *sp,int sl)
{
	TMZ		stz ;
	int		rs ;
	int		znlen ;

#if	CF_DEBUGS
	debugprintf("dater_settoucht: ent >%t<\n",
	    sp,strnlen(sp,sl)) ;
#endif

	if (dp == NULL) return SR_FAULT ;

	if (sl < 0)
	    sl = strlen(sp) ;

	if (sl > 99)
	    return SR_TOOBIG ;

/* initialize */

	dp->zname[0] = '\0' ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;
	dp->f.zname = FALSE ;
	dp->f.zoff = FALSE ;

/* continue */

	if ((rs = tmz_toucht(&stz,sp,sl)) >= 0) {
	    const int	f_year = tmz_hasyear(&stz) ;
	    const int	f_zone = tmz_haszone(&stz) ;
	    znlen = rs ;

#if	CF_DEBUGS
	debugprintf("dater_settoucht: tmz_msg() rs=%d\n",rs) ;
	debugprintf("dater_settoucht: year=%u mon=%u mday=%u\n",
	    stz.st.tm_mon,
	    stz.st.tm_mday,
	    stz.st.tm_hour) ;
	debugprintf("dater_settoucht: hour=%u min=%u sec=%u\n",
	    stz.st.tm_year,
	    stz.st.tm_min,
	    stz.st.tm_sec) ;
	debugprintf("dater_settoucht: timezone=%d zname=>%t<\n",
	    stz.zoff,
	    stz.zname,strnlen(stz.zname,MIN(rs,TMZ_ZNAMESIZE))) ;
#endif /* CF_DEBUGS */

/* can we supply some missing pieces? */

	    if ((! f_year) || (! f_zone)) {

	    if (! f_year) {
	        if (! dp->f.cyear) rs = dater_initcur(dp) ;
	        tmz_setyear(&stz,dp->cyear) ;
	    }

	    if ((rs >= 0) && ((znlen == 0) || (! f_zone))) {
	        if (! dp->f.czn) rs = dater_initcur(dp) ;
	        znlen = -1 ;
	        strncpy(stz.zname,dp->cname,TMZ_ZNAMESIZE) ;
	    }

#if	CF_DEBUGS
	    debugprintf("dater_settoucht: adjusted year=%d timezone=%dm\n",
	        stz.st.tm_year, stz.zoff) ;
	    debugprintf("dater_settoucht: adjusted zname=>%t<\n",
	        stz.zname,strnlen(stz.zname,TMZ_ZNAMESIZE)) ;
#endif /* CF_DEBUGS */

	    } /* end if (needed) */

	} /* end if (getting missing stuff) */

/* go for it */

#if	CF_DEBUGS
	debugprintf("dater_settoucht: dater_settmzn() zname=>%t<\n",
	    stz.zname,strnlen(stz.zname,TMZ_ZNAMESIZE)) ;
#endif

	if (rs >= 0) {
	    rs = dater_settmzn(dp,&stz.st,stz.zname,znlen) ;
	}

#if	CF_DEBUGS
	if (rs < 0)
	    debugprintf("dater_settoucht: dater_settmzn() rs=%d\n",rs) ;
#endif

#if	CF_DEBUGS
	debugprintf("dater_settoucht: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (dater_settoucht) */


/* set from a split-out time, zone offset, and zone-name */
int dater_settmzon(DATER *dp,struct tm *stp,int zoff,cchar *zstr,int zlen)
{
	int		rs = SR_OK ;

#if	CF_DEBUGS
	{
	    int	n ;
	    if (zlen >= 0) {
	        n = MIN(zlen,DATER_ZNAMESIZE) ;
	    } else
	        n = strnlen(zstr,DATER_ZNAMESIZE) ;
	    debugprintf("dater_settmzon: zoff=%dm zlen=%d zstr=>%t<\n",
	        zoff,zlen,zstr,n) ;
	}
#endif /* CF_DEBUGS */

	if (dp == NULL) return SR_FAULT ;
	if (stp == NULL) return SR_FAULT ;

/* reportedly there are zones up to 14 hours away from GMT! */

	if ((zoff != TZO_EMPTY) && (abs(zoff) > TZO_MAXZOFF))
	    return SR_INVALID ;

/* initialize */

	dp->zname[0] = '\0' ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;
	dp->f.zname = FALSE ;
	dp->f.zoff = FALSE ;

/* go */

	if (! dp->f.cb)
	    rs = dater_initcur(dp) ;

/* load the zone-offset (authoritative) */

	if ((rs >= 0) && (zoff != TZO_EMPTY)) {
	    dp->f.zoff = TRUE ;
	    dp->b.timezone = zoff ;
	}

/* lookup the zone-name */

	if ((rs >= 0) && (zstr != NULL) && (zstr[0] != '\0')) {
	    ZDB	zr ;

	    dp->f.zname = TRUE ;
	    strnwcpy(dp->zname,DATER_ZNAMESIZE,zstr,zlen) ;

#if	CF_DEBUGS
	    debugprintf("dater_settmzon: copied zname=%t\n",
	        dp->zname,strnlen(dp->zname,DATER_ZNAMESIZE)) ;
#endif

	    if ((rs = zdb_nameoff(&zr,zstr,zlen,zoff)) >= 0) {
	        if (stp->tm_isdst < 0) stp->tm_isdst = zr.isdst ;
	        if (zoff == TZO_EMPTY) zoff = zr.off ;
	    } else if (isNotPresent(rs)) {
		rs = SR_OK ;
	    } /* end if (got a match) */

	} /* end if (name lookup) */

/* calculate the time */

	if (rs >= 0)
	    rs = dater_mkptime(dp,stp,zoff) ;

/* now do something with the name */

	if ((rs >= 0) && (dp->zname[0] == '\0'))
	    rs = dater_mkpzoff(dp,stp,zoff) ;

#if	CF_DEBUGS
	debugprintf("dater_settmzon: ret rs=%d zname=>%t<\n",
	    rs,dp->zname,strnlen(dp->zname,DATER_ZNAMESIZE)) ;
#endif

	if (rs >= 0)
	    dp->magic = DATER_MAGIC ;

	return rs ;
}
/* end subroutine (dater_settmzon) */


/* set from split-out time and zone offset only (minutes west of GMT) */
int dater_settmzo(DATER *dp,struct tm *stp,int zoff)
{
	int		rs = SR_OK ;
#if	CF_DEBUGS
	char		timebuf[TIMEBUFLEN + 1] ;
#endif

#if	CF_DEBUGS
	debugprintf("dater_settmzo: ent zoff=%dm\n",zoff) ;
#endif

	if (dp == NULL) return SR_FAULT ;
	if (stp == NULL) return SR_FAULT ;

/* start processing */

	if ((zoff != TZO_EMPTY) && (abs(zoff) > TZO_MAXZOFF))
	    return SR_INVALID ;

/* initialize */

	dp->zname[0] = '\0' ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;
	dp->f.zname = FALSE ;
	dp->f.zoff = FALSE ;

/* go */

	if (! dp->f.cb)
	    rs = dater_initcur(dp) ;

/* calculate the time */

	if (rs >= 0)
	    rs = dater_mkptime(dp,stp,zoff) ;

/* try to find a time zone-name for the information we have */

#ifdef	COMMENT
	if (rs >= 0)
	    rs = dater_mkpzoff(dp,stp,zoff) ;
#endif /* COMMENT */

	if (rs >= 0)
	    dp->magic = DATER_MAGIC ;

#if	CF_DEBUGS
	debugprintf("dater_settmzo: ret rs=%d\n",rs) ;
	debugprintf("dater_settmzo: loctime=%s\n",
	    timestr_log(dp->b.time,timebuf)) ;
	debugprintf("dater_settmzo: isdst=%d\n",
	    dp->b.dstflag) ;
	debugprintf("dater_settmzo: f_zoff=%u zoff=%dm\n",
	    dp->f.zoff,dp->b.timezone) ;
	debugprintf("dater_settmzo: f_zname=%u zname=%t\n",
	    dp->f.zname,
	    dp->zname,strnlen(dp->zname,DATER_ZNAMESIZE)) ;
#endif

	return rs ;
}
/* end subroutine (dater_settmzo) */


/* set from a split-out time and zone-name only */
int dater_settmzn(DATER *dp,struct tm *stp,cchar *zstr,int zlen)
{
	int		rs = SR_OK ;
	int		rs1 ;
	int		zoff = TZO_EMPTY ;

#if	CF_DEBUGS
	debugprintf("dater_settmzn: zlen=%d zstr=>%t<\n",
	    zlen,zstr,strnlen(zstr,DATER_ZNAMESIZE)) ;
#endif

	if (dp == NULL) return SR_FAULT ;
	if (stp == NULL) return SR_FAULT ;

/* initialize */

	dp->zname[0] = '\0' ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;
	dp->f.zname = FALSE ;
	dp->f.zoff = FALSE ;

/* go */

	if (! dp->f.cb)
	    rs = dater_initcur(dp) ;

/* lookup the zone-name */

#if	CF_DEBUGS
	debugprintf("dater_settmzn: zone-name lookup rs=%d\n",rs) ;
#endif

	if ((rs >= 0) && (zstr != NULL) && (zstr[0] != '\0')) {
	    ZDB	zr ;

	    dp->f.zname = TRUE ;
	    strnwcpy(dp->zname,DATER_ZNAMESIZE,zstr,zlen) ;

	    rs1 = zdb_name(&zr,zstr,zlen) ;

#if	CF_DEBUGS
	    debugprintf("dater_settmzn: zdb_nameoff() rs=%d\n",rs1) ;
#endif

	    if (rs1 >= 0) {

	        if (stp->tm_isdst < 0) stp->tm_isdst = zr.isdst ;

	        if (zoff == TZO_EMPTY) zoff = zr.off ;

	    } /* end if (got a match) */

	} /* end if (name lookup) */

/* calculate the time */

	if (rs >= 0)
	    rs = dater_mkptime(dp,stp,zoff) ;

	if (rs >= 0)
	    dp->magic = DATER_MAGIC ;

	return rs ;
}
/* end subroutine (dater_settmzn) */


/* set from ( time, timezone_name, DST_indication ) */
int dater_settimezn(DATER *dp,time_t t,cchar *name,int isdst)
{
	TMTIME		tmt ;
	int		rs = SR_OK ;
#if	CF_DEBUGS
	char		timebuf[TIMEBUFLEN + 1] ;
#endif

#if	CF_DEBUGS
	debugprintf("dater_settimezn: ent t=%s\n",
	    timestr_logz(t,timebuf)) ;
	debugprintf("dater_settimezn: name=%s isdst=%d\n",
	    name,isdst) ;
#endif

	if (dp == NULL) return SR_FAULT ;

/* initialize */

	dp->zname[0] = '\0' ;
	dp->b.timezone = TZO_EMPTY ;
	dp->b.dstflag = -1 ;
	dp->f.zname = FALSE ;
	dp->f.zoff = FALSE ;

/* continue */

	if (! dp->f.cb)
	    rs = dater_initcur(dp) ;

	dp->b.dstflag = isdst ;

/* start processing */

	dp->b.time = t ;

#if	CF_DEBUGS
	debugprintf("dater_settimezn: supplied loctime=%s\n",
	    timestr_log(dp->b.time,timebuf)) ;
#endif

	if ((name == NULL) || (name[0] == '\0')) {

#if	CF_DEBUGS
	    debugprintf("dater_settimezn: no zone given\n") ;
#endif

	    dp->f.tzset = TRUE ;
	    if ((rs = tmtime_localtime(&tmt,t)) >= 0) {
	        name = tmt.zname ;
	        dp->f.zname = TRUE ;
	        strncpylc(dp->zname,name,DATER_ZNAMESIZE) ;
	        if (isdst < 0) isdst = tmt.isdst ;
	    } /* end if */

	    dp->b.dstflag = isdst ;

	    dp->f.zoff = TRUE ;
	    dp->b.timezone = 0 ;
	    if (isdst >= 0)
	        dp->b.timezone = (short) (tmt.gmtoff / 60) ;

#if	CF_DEBUGS
	    debugprintf("dater_settimezn: determined zone=%s\n",name) ;
#endif

	} else {

#if	CF_DEBUGS
	    debugprintf("dater_settimezn: given zone=%s\n",name) ;
#endif

	    rs = dater_ldname(dp,name,-1) ;

	} /* end if */

#if	CF_DEBUGS
	{
	    debugprintf("dater_settimezn: loctime=%s\n",
	        timestr_log(dp->b.time,timebuf)) ;
	    debugprintf("dater_settimezn: name=%t\n",
	        dp->zname,
	        strnlen(dp->zname,DATER_ZNAMESIZE)) ;
	    debugprintf("dater_settimezn: zoff=%dm\n",
	        (int) dp->b.timezone) ;
	    debugprintf("dater_settimezn: dstflag=%d\n",
	        dp->b.dstflag) ;
	}
#endif /* CF_DEBUGS */

	if (rs >= 0)
	    dp->magic = DATER_MAGIC ;

#if	CF_DEBUGS
	debugprintf("dater_settimezn: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (dater_settimezn) */


/* set from ( time, tz-offset, tz-name, tz-DST_indication ) */
int dater_settimezon(DATER *dp,time_t t,int zoff,cchar *zname,int isdst)
{
	TMTIME		tmt ;
	int		rs = SR_OK ;
#if	CF_DEBUGS
	char		timebuf[TIMEBUFLEN + 1] ;
#endif

#if	CF_DEBUGS
	debugprintf("dater_settimezn: ent t=%lu t=%s\n",
	    t,timestr_logz(t,timebuf)) ;
	debugprintf("dater_settimezn: name=%s isdst=%d\n",
	    zname,isdst) ;
#endif

	if (dp == NULL) return SR_FAULT ;

/* initialize */

	dp->b.time = t ;
	dp->b.timezone = zoff ;
	dp->b.dstflag = isdst ;
	dp->zname[0] = '\0' ;

	dp->f.zname = TRUE ;
	dp->f.zoff = TRUE ;

/* continue */

	if (! dp->f.cb)
	    rs = dater_initcur(dp) ;

#if	CF_DEBUGS
	debugprintf("dater_settimezn: supplied loctime=%s\n",
	    timestr_log(dp->b.time,timebuf)) ;
#endif

	if ((zname == NULL) || (zname[0] == '\0')) {

#if	CF_DEBUGS
	    debugprintf("dater_settimezn: no zone given\n") ;
#endif

	    dp->f.tzset = TRUE ;
	    if ((rs = tmtime_localtime(&tmt,t)) >= 0) {

	        zname = tmt.zname ;
	        dp->f.zname = TRUE ;
	        strncpylc(dp->zname,zname,DATER_ZNAMESIZE) ;

	        if (isdst < 0)
	            isdst = tmt.isdst ;

	    } /* end if */

	    dp->b.dstflag = isdst ;

	    dp->f.zoff = TRUE ;
	    dp->b.timezone = 0 ;
	    if (isdst >= 0)
	        dp->b.timezone = (short) (tmt.gmtoff / 60) ;

#if	CF_DEBUGS
	    debugprintf("dater_settimezn: determined zone=%s\n",zname) ;
#endif

	} else {

#if	CF_DEBUGS
	    debugprintf("dater_settimezn: given zone=%s\n",zname) ;
#endif

	    strncpylc(dp->zname,zname,DATER_ZNAMESIZE) ;

	} /* end if */

	if (rs >= 0)
	    dp->magic = DATER_MAGIC ;

#if	CF_DEBUGS
	debugprintf("dater_settimezn: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (dater_settimezon) */


int dater_mkdatestr(DATER *dp,int type,char *dbuf,int dlen)
{
	TMTIME		tmt ;
	time_t		t ;
	int		rs = SR_OK ;
	int		zoff ;
	int		sl ;
	cchar		*znp ;
	cchar		*fmt ;

	if (dp == NULL) return SR_FAULT ;
	if (dbuf == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;

	if ((type < 0) || (type >= DATER_DTSEND))
	    return SR_INVALID ;

	if (dlen < 0)
	    dlen = TIMEBUFLEN ;

#if	CF_DEBUGS
	debugprintf("dater_mkdatestr: type=%u (%s)\n",type,types[type]) ;
#endif

/* go */

	t = dp->b.time ;
	zoff = dp->b.timezone ;
	znp = dp->zname ;
	if ((dp->b.timezone == TZO_EMPTY) || (! dp->f.zoff)) {
	    zoff = 0 ;
	    znp = "GMT" ;
	}

#if	CF_DEBUGS
	{
	    char	timebuf[TIMEBUFLEN+1] ;
	    debugprintf("dater_mkdatestr: timezone=%d zoff=%d\n",
	        dp->b.timezone,zoff) ;
	    debugprintf("dater_mkdatestr: pre t=%lu t=%s\n",
	        t,timestr_logz(t,timebuf)) ;
	    debugprintf("dater_mkdatestr: zn=%s\n",dp->zname) ;
	}
#endif

/* selective adjustment */

	switch (type) {
	case DATER_DTSENV:
	case DATER_DTSLOGZ:
	    if (dp->zname[0] == '\0') {
	        zoff = 0 ;
	        znp = "Z" ;
	    }
	    break ;
	case DATER_DTSGMLOGZ:
	    zoff = 0 ;
	    znp = "GMT" ;
	    break ;
	} /* end switch (selective adjustment) */

#if	CF_DEBUGS
	{
	    char	timebuf[TIMEBUFLEN+1] ;
	    debugprintf("dater_mkdatestr: post t=%lu t=%s\n",
	        t,timestr_logz(t,timebuf)) ;
	}
#endif

/* conversion */

	if (rs >= 0) {
	    t -= (zoff * 60) ;
	    rs = tmtime_gmtime(&tmt,t) ;

#if	CF_DEBUGS
	    {
	        debugprintf("dater_mkdatestr: tmtime_gemtime() rs=%d\n",rs) ;
	        debugprintf("dater_mkdatestr: year=%u\n",tmt.year) ;
	        debugprintf("dater_mkdatestr: mon=%u\n",tmt.mon) ;
	    }
#endif
	} /* end if */

	if (rs >= 0) { /* write adjustment back to object */
	    tmt.gmtoff = (zoff * 60) ;
	    strwcpyuc(tmt.zname,znp,TMTIME_ZNAMESIZE) ;
	}

/* format */

	if (rs >= 0) {

#if	CF_SNTMTIME
#else /* CF_SNTMTIME */
	    char	zobuf[10] ;
#endif /* CF_SNTMTIME */

	    switch (type) {

/* UNIX� envelope */
	    case DATER_DTSENV:
#if	CF_SNTMTIME
	        fmt = "%a %b %d %T %Z %Y %O" ;
	        rs = sntmtime(dbuf,dlen,&tmt,fmt) ;
	        sl = rs ;
#else /* CF_SNTMTIME */
	        zobuf[0] = '\0' ;
	        if ((zoff != TZO_EMPTY) && dp->f.zoff)
	            zos_set(zobuf,10,zoff) ;
	        sl = bufprintf(dbuf,dlen,
	            "%3s %3s %02u %02u:%02u:%02u %s %04u %s",
	            days[tmt.wday],
	            months[tmt.mon],
	            tmt.mday,
	            tmt.hour,
	            tmt.min,
	            tmt.sec,
	            tmt.zname,
	            (tmt.year + TM_YEAR_BASE),
	            zobuf) ;
#endif /* CF_SNTMTIME */

	        break ;

/* message header */
	    case DATER_DTSHDR:

#if	CF_SNTMTIME
	        fmt = "%d %b %Y %T %O (%Z)" ;
	        if (tmt.zname[0] == '\0') fmt = "%d %b %Y %T %O" ;
	        rs = sntmtime(dbuf,dlen,&tmt,fmt) ;
	        sl = rs ;
#else /* CF_SNTMTIME */
	        zobuf[0] = '\0' ;
	        if ((zoff != TZO_EMPTY) && dp->f.zoff)
	            zos_set(zobuf,10,zoff) ;
	        fmt = "%2u %3s %4u %02u:%02u:%02u %s" ;
	        if (tz[0] != '\0')
	            fmt = "%2u %3s %4u %02u:%02u:%02u %s (%s)" ;
	        sl = bufprintf(dbuf,dlen,fmt,
	            tmt.mday,
	            months[tmt.mon],
	            (tmt.year + TM_YEAR_BASE),
	            tmt.hour,
	            tmt.min,
	            tmt.sec,
	            zobuf,
	            tmt.zname) ;
#endif /* CF_SNTMTIME */

	        break ;

	    case DATER_DTSSTRDIG:

#if	CF_SNTMTIME
	        fmt = "%y%m%d%H%M%S%O%Z" ;
	        if (tmt.zname[0] == '\0') fmt = "%y%m%d%H%M%S%O" ;
	        rs = sntmtime(dbuf,dlen,&tmt,fmt) ;
	        sl = rs ;
#else /* CF_SNTMTIME */
	        zobuf[0] = '\0' ;
	        if ((zoff != TZO_EMPTY) && dp->f.zoff)
	            zos_set(zobuf,10,zoff) ;
	        fmt = "%04u%02u%02u%02u%02u%02u%s" ;
	        if (dp->f.zname)
	            fmt = "%04u%02u%02u%02u%02u%02u%s%s" ;
	        sl = bufprintf(dbuf,dlen,fmt,
	            (tmt.year + TM_YEAR_BASE),
	            (tmt.mon + 1),
	            tmt.mday,
	            tmt.hour,
	            tmt.min,
	            tmt.sec,
	            zobuf,
	            tmt.zname) ;
#endif /* CF_SNTMTIME */

	        break ;

	    case DATER_DTSLOGZ:
	    case DATER_DTSGMLOGZ:

#if	CF_SNTMTIME
	        fmt = "%y%m%d_%H%M:%S_%Z" ;
	        if (tmt.zname[0] == '\0') fmt = "%y%m%d_%H%M:%S" ;
	        rs = sntmtime(dbuf,dlen,&tmt,fmt) ;
	        sl = rs ;
#else /* CF_SNTMTIME */
	        fmt = "%02u%02u%02u_%02u%02u:%02u" ;
	        if (dp->f.zname)
	            fmt = "%02u%02u%02u_%02u%02u:%02u_%s" ;
	        sl = bufprintf(dbuf,dlen,fmt,
	            (tmt.year % NYEARS_CENTURY),
	            (tmt.mon + 1),
	            tmt.mday,
	            tmt.hour,
	            tmt.min,
	            tmt.sec,
	            tmt.zname) ;
#endif /* CF_SNTMTIME */

	        break ;

	    default:
	        sl = -1 ;
	        strwcpy(dbuf,"** invalid type **",dlen) ;
	        break ;

	    } /* end switch */

	} /* end if */

#if	CF_DEBUGS
	debugprintf("dater_mkdatestr: ret rs=%d dbuf=>%s<\n",rs,dbuf) ;
#endif

	return (rs >= 0) ? sl : rs ;
}
/* end subroutine (dater_mkdatestr) */


/* make a mail envelope-type dater string */
int dater_mkstd(DATER *dp,char *dbuf,int dlen)
{

	return dater_mkdatestr(dp,DATER_DTSENV,dbuf,dlen) ;
}
/* end subroutine (dater_mkstd) */


/* make a mail envelope-type dater string */
int dater_mkenv(DATER *dp,char *dbuf,int dlen)
{

	return dater_mkdatestr(dp,DATER_DTSENV,dbuf,dlen) ;
}
/* end subroutine (dater_mkenv) */


/* make a mail envelope-type dater string */
int dater_mkmsg(DATER *dp,char *dbuf,int dlen)
{

	return dater_mkdatestr(dp,DATER_DTSMSG,dbuf,dlen) ;
}
/* end subroutine (dater_mkmsg) */


/* make a mail header dater string */
int dater_mkhdr(DATER *dp,char *dbuf,int dlen)
{

	return dater_mkdatestr(dp,DATER_DTSHDR,dbuf,dlen) ;
}
/* end subroutine (dater_mkhdr) */


/* make the old STRDIG type of dater string */
int dater_mkstrdig(DATER *dp,char *dbuf,int dlen)
{

	return dater_mkdatestr(dp,DATER_DTSSTRDIG,dbuf,dlen) ;
}
/* end subroutine (dater_mkstrdig) */


/* make the familiar LOGZ-type dater string */
int dater_mklogz(DATER *dp,char *dbuf,int dlen)
{

	return dater_mkdatestr(dp,DATER_DTSLOGZ,dbuf,dlen) ;
}
/* end subroutine (dater_mklogz) */


/* make the familiar LOGZ-type dater string */
int dater_mkgmtlogz(DATER *dp,char *dbuf,int dlen)
{

	return dater_mkdatestr(dp,DATER_DTSGMLOGZ,dbuf,dlen) ;
}
/* end subroutine (dater_mkgmlogz) */


/* return the UNIX� time out of DATER object */
int dater_gettime(DATER *dp,time_t *tp)
{

	if (dp == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;

	if (tp != NULL)
	    *tp = dp->b.time ;

	return SR_OK ;
}
/* end subroutine (dater_gettime) */


/* return the timezone in minutes west of GMT */
int dater_getzoneoff(DATER *dp,int *zp)
{

	if (dp == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;

	if (! dp->f.zoff) return SR_NOENT ;

	if (zp != NULL)
	    *zp = dp->b.timezone ;

	return SR_OK ;
}
/* end subroutine (dater_getzoneoff) */


/* return the timezone in minutes west of GMT */
int dater_getzonename(DATER *dp,char *rbuf,int rlen)
{
	int		rs ;

	if (dp == NULL) return SR_FAULT ;
	if (rbuf == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;

	rbuf[0] = '\0' ;
	if (! dp->f.zname)
	    return SR_NOENT ;

	rs = snwcpy(rbuf,rlen,dp->zname,DATER_ZNAMESIZE) ;

	return rs ;
}
/* end subroutine (dater_getzonename) */


int dater_setzinfo(DATER *dp,DATER_ZINFO *zip)
{
	int		rs ;

	if (dp == NULL) return SR_FAULT ;
	if (zip == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;

	dp->b.timezone = zip->zoff ;
	dp->b.dstflag = zip->isdst ;
	rs = strwcpy(dp->zname,zip->zname,DATER_ZNAMESIZE) - dp->zname ;

	return rs ;
}
/* end subroutine (dater_setzinfo) */


int dater_getzinfo(DATER *dp,DATER_ZINFO *zip)
{
	int		rs ;

	if (dp == NULL) return SR_FAULT ;
	if (zip == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;

	zip->zoff = dp->b.timezone ;
	zip->isdst = dp->b.dstflag ;
	rs = strwcpy(zip->zname,dp->zname,DATER_ZNAMESIZE) - zip->zname ;

	if ((rs >= 0) && (! dp->f.zoff)) rs = SR_NOTFOUND ;

	return rs ;
}
/* end subroutine (dater_getzinfo) */


/* get the difference in seconds between two daters */
int dater_diff(DATER *dp,DATER *d2p,time_t *rp)
{

	if (dp == NULL) return SR_FAULT ;
	if (d2p == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;
	if (d2p->magic != DATER_MAGIC) return SR_NOTOPEN ;

	if (rp != NULL)
	    *rp = (dp->b.time > d2p->b.time) ;

	return SR_OK ;
}
/* end subroutine (dater_diff) */


#ifdef	COMMENT

/* return the number of time zones that we have */
int dater_nzones(dp)
DATER		*dp ;
{
	ZDB		zr ;
	int		i ;

	if (dp == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;

	i = zdb_count(&zr) ;

	return i ;
}
/* end subroutine (dater_nzones) */


int dater_zinfo(DATER *dp,DATER_ZINFO *zip,int ei)
{
	const int	n = DATER_NZONES ;
	const int	znsize = DATER_ZNAMESIZE ;
	int		znlen ;

	if (dp == NULL) return SR_FAULT ;
	if (zip == NULL) return SR_FAULT ;

	if (dp->magic != DATER_MAGIC) return SR_NOTOPEN ;

	memset(zip,0,sizeof(DATER_ZINFO)) ;

	if ((ei < 0) || (ei >= n))
	    return SR_NOTFOUND ;

	zip->isdst = zones[ei].isdst ;
	zip->zoff = zones[ei].off ;
	znlen = strwcpy(zip->zname,zones[ei].zname,znsize) - zip->zname ;

	return znlen ;
}
/* end subroutine (dater_zinfo) */

#endif /* COMMENT */


/* private subroutines */


static int dater_initcur(DATER *dp)
{
	TMTIME		tmt ;
	int		rs = SR_OK ;
	int		zo ;

#if	CF_DEBUGS
	debugprintf("dater_initcur: f_cyear=%d\n",dp->f.cyear) ;
#endif

	if (! dp->f.cyear) {

	if (! dp->f.cb)
	    dp->cb.time = time(NULL) ;

	dp->f.tzset = TRUE ;
	rs = tmtime_localtime(&tmt,dp->cb.time) ;

#if	CF_DEBUGS
	debugprintf("dater_initcur: localtime() year=%d isdst=%d\n",
	    tmt.year,tmt.isdst) ;
#endif

	zo = tmt.gmtoff ; 		/* seconds west of GMT */

	dp->cyear = tmt.year ;
	dp->cb.timezone = (zo / 60) ;	/* minutes west of GMT */
	dp->cb.dstflag = tmt.isdst ;
	strncpylc(dp->cname,tmt.zname,DATER_ZNAMESIZE) ;

	dp->f.cb = TRUE ;
	dp->f.czn = TRUE ;
	dp->f.cyear = TRUE ;

	} /* end if (need current time) */

	return rs ;
}
/* end subroutine (dater_initcur) */


#ifdef	COMMENT

/* get any possible zone-name information from the zone offset */
static int dater_mkpzoff(dp,stp,zoff)
DATER		*dp ;
struct tm	*stp ;
int		zoff ;
{
	int		i ;
	int		f_havename = FALSE ;

#if	CF_DEBUGS
	debugprintf("dater_mkpzoff: ent zoff=%dm dstflag=%d\n",
	    zoff,stp->tm_isdst) ;
#endif

	if (zoff == dp->cb.timezone) {

#if	CF_ASSUMEZN
	    dp->f.zname = TRUE ;
#endif

	    strncpy(dp->zname,dp->cname,DATER_ZNAMESIZE) ;

	    if (dp->b.dstflag < 0)
	        dp->b.dstflag = dp->cb.dstflag ;

	} else if (zoff == 0) {

#if	CF_ASSUMEZN
	    dp->f.zname = TRUE ;
#endif

	    strncpy(dp->zname,"gmt",DATER_ZNAMESIZE) ;

	    if (dp->b.dstflag < 0)
	        dp->b.dstflag = 0 ;

	} else {

#if	CF_DEBUGS
	    debugprintf("dater_mkpzoff: need to search\n") ;
#endif

	    if (stp->tm_isdst >= 0) {

#if	CF_DEBUGS
	        debugprintf("dater_mkpzoff: supplied zone type dstflag=%d\n",
	            stp->tm_isdst) ;
#endif

	        for (i = 0 ; zones[i].zname != NULL ; i += 1) {

	            if ((zones[i].off == zoff) &&
	                (zones[i].isdst == stp->tm_isdst))
	                break ;

	        } /* end for */

	        f_havename = (zones[i].zname != NULL) ;

	    } else if (dp->cb.dstflag >= 0) {

#if	CF_DEBUGS
	        debugprintf("dater_mkpzoff: current zone type dstflag=%d\n",
	            dp->cb.dstflag) ;
#endif

	        for (i = 0 ; zones[i].zname != NULL ; i += 1) {

	            if ((zones[i].off == zoff) &&
	                (zones[i].isdst == dp->cb.dstflag))
	                break ;

	        } /* end for */

	        f_havename = (zones[i].zname != NULL) ;

	    } /* end if (searhing for zone type of current time-zone) */

	    if (! f_havename) {

#if	CF_DEBUGS
	        debugprintf("dater_mkpzoff: searching for any zone\n") ;
#endif

	        for (i = 0 ; zones[i].zname ; i += 1) {

	            if (zones[i].off == zoff)
	                break ;

	        } /* end for */

	        f_havename = (zones[i].zname != NULL) ;

	    } /* end if (searching for any zone) */

	    if (f_havename) {

#if	CF_DEBUGS
	        debugprintf("dater_mkpzoff: got a name=%t\n",
	            zones[i].zname,strnlen(zones[i].zname,DATER_ZNAMESIZE)) ;
#endif

#if	CF_ASSUMEZN
	        dp->f.zname = TRUE ;
#endif

	        strncpy(dp->zname,zones[i].zname,DATER_ZNAMESIZE) ;

	        if (dp->b.dstflag < 0)
	            dp->b.dstflag = zones[i].isdst ;

	    } else {

	        zos_set(dp->zname,8,zoff) ;

	    } /* end if */

	} /* end if */

	return f_havename ;
}
/* end subroutine (dater_mkpzoff) */

#else /* COMMENT */

/* get any possible zone-name information from the zone offset */
static int dater_mkpzoff(DATER *dp,struct tm *stp,int zoff)
{
	ZDB		zr ;
	int		rs ;

#if	CF_DEBUGS
	debugprintf("dater_mkpzoff: ent zoff=%dm dstflag=%d\n",
	    zoff,stp->tm_isdst) ;
#endif

	dp->zname[0] = '\0' ;
	rs = zdb_offisdst(&zr,zoff,stp->tm_isdst) ;

#if	CF_DEBUGS
	debugprintf("dater_mkpzoff: zdb_offisdst() rs=%d\n",rs) ;
#endif

	if (rs >= 0) {
	    rs = strnwcpy(dp->zname,DATER_ZNAMESIZE,zr.name,-1) - dp->zname ;
	} else
	    rs = 0 ;

#if	CF_DEBUGS
	debugprintf("dater_mkpzoff: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (dater_mkpzoff) */

#endif /* COMMENT */


/* store a time zone-name into the object */
static int dater_ldname(DATER *dp,cchar znp[],int znl)
{
	int		rs = SR_OK ;
	char		*dnp = dp->zname ;

#if	CF_DEBUGS
	debugprintf("dater_ldname: nlen=%d zn=>%t<\n",
	    znl,
	    znp,strnlen(znp,MIN(znl,DATER_ZNAMESIZE))) ;
#endif

	if ((znl < 0) || (znl > DATER_ZNAMESIZE))
	    znl = DATER_ZNAMESIZE ;

	dp->f.zname = TRUE ;
	strnwcpy(dnp,DATER_ZNAMESIZE,znp,znl) ;

#if	CF_DEBUGS
	debugprintf("dater_ldname: 1 f_zoff=%d\n",dp->f.zoff) ;
#endif

	if ((! dp->f.zoff) || (dp->b.dstflag < 0)) {
	    const int	ch = MKCHAR(dnp[0]) ;

	    if (ISSIGN(ch) || isdigitlatin(ch)) {
	        rs = dater_pnum(dp) ;
	    } else
	        rs = dater_pname(dp) ;

#if	CF_DEBUGS
	    debugprintf("dater_ldname: 2 f_zoff=%d\n",dp->f.zoff) ;
#endif

	} /* end if (needed zone offset from name) */

#if	CF_DEBUGS
	debugprintf("dater_ldname: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (dater_ldname) */


/* parse a time zone-name */

#ifdef	COMMENT
struct timeb {
	time_t	time;		/* time, seconds since the epoch */
	unsigned short millitm;	/* 1000 msec of additional accuracy */
	short	timezone;	/* timezone, minutes west of GMT */
	short	dstflag;	/* daylight savings when appropriate? */
} ;
#endif /* COMMENT */

static int dater_pname(DATER *dp)
{
	ZDB		zr ;
	int		rs ;
	int		zl = -1 ;
	cchar		*zp = dp->zname ;

	if (! dp->f.zoff)
	    dp->b.timezone = 0 ;

#if	CF_DEBUGS
	debugprintf("dater_pname: name=>%t<\n",
	    dp->zname,strnlen(dp->zname,DATER_ZNAMESIZE)) ;
#endif

	if ((rs = zdb_name(&zr,zp,zl)) >= 0) {

	    if (! dp->f.zoff) {

#if	CF_DEBUGS
	        debugprintf("dater_pname: adding missing ZOFF i=%d zoff=%dm\n",
	            zr.off) ;
#endif

	        dp->b.timezone = zr.off ;

	    }

	    if (dp->b.dstflag < 0)
	        dp->b.dstflag = zr.isdst ;

	    dp->f.zname = TRUE ;
	    dp->f.zoff = TRUE ;

	} else
	    rs = SR_NOTFOUND ;

#if	CF_DEBUGS
	debugprintf("dater_pname: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (dater_pname) */


/* get the timezone information out of an RFC822-type number string */
static int dater_pnum(DATER *dp)
{
	int		rs = SR_OK ;
	int		hours, mins ;
	int		i ;
	int		sign ;
	char		*bp = dp->zname ;

	if (dp->f.zoff)
	    return SR_OK ;

	dp->f.zname = FALSE ;

	dp->b.timezone = 0 ;
	sign = -1 ;
	if ((*bp == '-') || (*bp == '+')) {
	    sign = (*bp == '-') ? 1 : -1 ;
	    bp += 1 ;
	}

#ifdef	OPTIONAL
	if (strlen(bp) < 4)
	    return SR_INVALID ;
#endif

	for (i = 0 ; i < 4 ; i += 1) {
	    const int	ch = MKCHAR(bp[i]) ;
	    if (! isdigitlatin(ch)) {
	        rs = SR_INVALID ;
	        break ;
	    }
	} /* end for */

	if (rs >= 0) {

	    hours = (((int) *bp++) - '0') * 10 ;
	    hours += (((int) *bp++) - '0') ;

	    mins = (((int) *bp++) - '0') * 10 ;
	    mins += (((int) *bp++) - '0') ;

	    dp->b.timezone = (hours * 60) + mins ;
	    dp->b.timezone *= sign ;

	    dp->f.zoff = TRUE ;

	} /* end if */

	return rs ;
}
/* end subroutine (dater_pnum) */


static int dater_findzname(DATER *dp)
{
	int		rs = SR_OK ;

	if ((rs >= 0) && (dp->zname[0] == '\0')) {
	    if (! dp->f.cyear) rs = dater_initcur(dp) ;
	    if (dp->f.zoff && (dp->b.timezone == dp->cb.timezone)) {
	        cchar	*lp ;
	        dp->b.dstflag = dp->cb.dstflag ;
	        lp = strnwcpy(dp->zname,DATER_ZNAMESIZE,dp->cname,-1) ;
	        rs = (lp - dp->zname) ;
	        dp->f.zname = TRUE ;
	    }
	} /* end if */

	return rs ;
}
/* end subroutine (dater_findzname) */


static int dater_findzoff(DATER *dp,struct tm *stp)
{
	int		rs = SR_OK ;

	if (stp == NULL) return SR_FAULT ;

	if ((rs >= 0) && (! dp->f.zoff)) {
	    int	f_def = FALSE ;
	    if (! dp->f.cyear) rs = dater_initcur(dp) ;
	    if (dp->zname[0] != '\0') {
		ZDB		d ;
		const int	znlen = DATER_ZNAMESIZE ;
		f_def = FALSE ;
		if ((rs = zdb_name(&d,dp->zname,znlen)) >= 0) {
		    dp->b.timezone = d.off ;
		    dp->b.dstflag = d.isdst ;
		    dp->f.zoff = TRUE ;
		} else if (rs == SR_NOTFOUND)
		    rs = SR_OK ;
	    } /* end if (have a time-zone name) */
	    if ((rs >= 0) && f_def) {
	        dp->b.timezone = dp->cb.timezone ;
	        dp->b.dstflag = dp->cb.dstflag ;
	        dp->f.zoff = TRUE ;
	    }
	} /* end if */

	return (rs >= 0) ? (dp->f.zoff) : rs ;
}
/* end subroutine (dater_findzoff) */


/* try to make a time for the given date */
static int dater_mkptime(DATER *dp,struct tm *stp,int zoff)
{
	TMTIME		tmt ;
	int		rs = SR_OK ;
#if	CF_DEBUGS
	char		timebuf[TIMEBUFLEN + 1] ;
#endif

#if	CF_DEBUGS
	debugprintf("dater_mkptime: stp->tm_isdst=%d\n",stp->tm_isdst) ;
	debugprintf("dater_mkptime: zoff=%dm \n",zoff) ;
#endif

	if ((zoff == TZO_EMPTY) || (! dp->f.zoff)) {
	    if (! dp->f.cb) rs = dater_initcur(dp) ;
	    zoff = dp->cb.timezone ;
	}

#ifdef	OPTIONAL
	memset(&tmt,0,sizeof(TMTIME)) ;
#endif

	if (rs >= 0) {
	    rs = tmtime_insert(&tmt,stp) ;
	    tmt.gmtoff = (zoff*60) ;
	}

#if	CF_DEBUGS
	debugprintf("dater_mkptime: 0 tmt.isdst=%d\n",tmt.isdst) ;
#endif

	if (rs >= 0) {
	    time_t	t ;
	    dp->f.tzset = TRUE ;		/* mktime() calls it! */
	    rs = tmtime_mktime(&tmt,&t) ;
	    dp->b.time = t ;
	    dp->b.timezone = (short) zoff ;
	    dp->f.zoff = TRUE ;

#if	CF_DEBUGS
	debugprintf("dater_mkptime: tmtime_mktime() rs=%d\n",rs) ;
	debugprintf("dater_mkptime: CVT loctime=%s\n",
	    timestr_log(t,timebuf)) ;
	debugprintf("dater_mkptime: CVT gmttime=%s\n",
	    timestr_gmlog(t,timebuf)) ;
	debugprintf("dater_mkptime: CVT isdst=%d gmtoff=%d(%dm)\n",
	    tmt.isdst,tmt.gmtoff,
	    (tmt.gmtoff/60)) ;
#endif

	} /* end if */

#if	CF_DEBUGS
	debugprintf("dater_mkptime: ret rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (dater_mkptime) */


/* try to make a time for the given date */
static int dater_mktime(DATER *dp,struct tm *stp)
{
	TMTIME		tmt ;
	time_t		t ;
	int		rs = SR_OK ;

	if (dp->f.zoff) {

	    if ((rs = tmtime_insert(&tmt,stp)) >= 0) {
	        tmt.gmtoff = (dp->b.timezone*60) ; /* insert time-zone-offet */
	        dp->f.tzset = TRUE ;		/* mktime() calls it! */
	        rs = tmtime_mktime(&tmt,&t) ;
	        dp->b.time = t ;
	    }

	} else { /* must be local */

	    dp->f.tzset = TRUE ;		/* mktime() calls it! */
	    if ((rs = uc_mktime(stp,&t)) >= 0) {
		GETDEFZINFO	zi ;
		dp->b.time = t ;
		if ((rs = getdefzinfo(&zi,stp->tm_isdst)) >= 0) {
		    const int	znlen = GETDEFZINFO_ZNAMESIZE ;
	    	    strnwcpy(dp->zname,DATER_ZNAMESIZE,zi.zname,znlen) ;
		    dp->b.timezone = zi.zoff ;
		    dp->b.dstflag = stp->tm_isdst ;
		    dp->f.zoff = TRUE ;
		    dp->f.zname = TRUE ;
		}
	    }

	} /* end if (something or local) */

	if ((rs >= 0) && (dp->zname[0] == '\0')) {
	    rs = dater_findzname(dp) ;
	}

#if	CF_DEBUGS
	{
	    char	timebuf[TIMEBUFLEN+1] ;
	    debugprintf("dater_mktime: ret rs=%d\n",rs) ;
	    debugprintf("dater_mktime: loctime=%s\n",
		timestr_logz(dp->b.time,timebuf)) ;
	    debugprintf("dater_mktime: gmttime=%s\n",
		timestr_gmlogz(dp->b.time,timebuf)) ;
	}
#endif /* CF_DEBUGS */

	return rs ;
}
/* end subroutine (dater_mktime) */


#ifdef	COMMENT

/* try to "divine" a TZ abbreviation from the comments */
static int findtzcomment(char *rbuf,int rlen,cchar *comment)
{
	SBUF		tzbuf ;
	int		rs = SR_OK ;
	int		cl ;
	int		zl, zl1 ;
	int		i = -1 ;
	int		f_two = FALSE ;
	cchar		*cp ;

/* we first try to concatenate the first two tokens */

	rbuf[0] = '\0' ;
	if ((cl = nextfield(comment,-1,&cp)) <= rlen) {

	zl1 = 0 ;
	if ((rs = sbuf_start(&tzbuf,rbuf,rlen)) >= 0) {

	    zl = sbuf_strw(&tzbuf,cp,cl) ;

	    zl1 = zl ;
	    if ((zl >= 0) && (zl < rlen)) {

	        cl = nextfield((cp + cl),-1,&cp) ;

	        if ((zl + cl) <= rlen) {
	            f_two = TRUE ;
	            sbuf_strw(&tzbuf,cp,cl) ;
	        }

	    } /* end if (had more space) */

	    zl = sbuf_finish(&tzbuf) ;
	    if (rs >= 0) rs = zl ;
	} /* end if (sbuf) */

	if (rs >= 0) {

/* convert to lower case */

	    for (i = 0 ; tz[i] != '\0' ; i += 1)
	        tz[i] |= 0x20 ;

/* look it up */

	    i = findname(tz) ;

	    if ((i < 0) && f_two) {

	        tz[zl1] = '\0' ;
	        i = findname(tz) ;

	    }

	} /* end if (ok) */

	} /* end if (ok, will fit) */

	return (rs >= 0) ? i : rs ;
}
/* end subroutine (findtzcomment) */

#endif /* COMMENT */


static int mkzname(char zname[],cchar *sp,int sl)
{
	const int	znlen = DATER_ZNAMESIZE ;
	int		len ;
	cchar		*tp ;

	if ((tp = strnpbrk(sp,sl," \t")) != NULL) {
	    sl = (tp - sp) ;
	}

	len = strwcpy(zname,sp,MIN(znlen,sl)) - zname ;

	return len ;
}
/* end subroutine (mkzname) */


