/* testuserinfo HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* TESTUSERINFO program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	TESTUSERINFO_INCLUDE
#define	TESTUSERINFO_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */


#define	VERSION		"0"
#define	WHATINFO	"@(#)TESTUSERINFO "
#define	BANNER		"Test User Information"
#define	SEARCHNAME	"cal"
#define	VARPRNAME	"TESTUSERINFO"

#ifndef	PROGRAMROOT
#define	PROGRAMROOT	"/usr/add-on/local"
#endif

#define	VARPROGRAMROOT1	"TESTUSERINFO_PROGRAMROOT"
#define	VARPROGRAMROOT2	VARPRNAME
#define	VARPROGRAMROOT3	"PROGRAMROOT"

#define	VARBANNER	"TESTUSERINFO_BANNER"
#define	VARSEARCHNAME	"TESTUSERINFO_NAME"
#define	VARPROGTESTUSERINFO	"TESTUSERINFO_PROGTESTUSERINFO"
#define	VAROPTS		"TESTUSERINFO_OPTS"
#define	VARAFNAME	"TESTUSERINFO_AF"
#define	VAREFNAME	"TESTUSERINFO_EF"

#define	VARDEBUGFNAME	"TESTUSERINFO_DEBUGFILE"
#define	VARDEBUGFD1	"TESTUSERINFO_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#define	VARHOMEDNAME	"HOME"
#define	VARTMPDNAME	"TMPDIR"
#define	VARMAILDNAME	"MAILDIR"
#define	VARMAILDNAMES	"MAILDIRS"

#define	VARPRTESTUSERINFO	"TESTUSERINFO"

#define	CONFFNAME	"conf"
#define	LOGFNAME	"log/cal"
#define	HELPFNAME	"help"

#define	PO_OPTION	"option"

#define	LOGSIZE		(80*1024)


#endif /* TESTUSERINFO_INCLUDE */


