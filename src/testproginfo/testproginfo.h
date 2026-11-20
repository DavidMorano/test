/* testproginfo HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* TESTPROGINFO program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	TESTPROGINFOCONFIG_INCLUDE
#define	TESTPROGINFOCONFIG_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */


#define	VERSION		"0"
#define	WHATINFO	"@(#)TESTPROGINFO "
#define	BANNER		"Test Program Information"
#define	SEARCHNAME	"cal"
#define	VARPRNAME	"TESTPROGINFO"

#ifndef	PROGRAMROOT
#define	PROGRAMROOT	"/usr/add-on/local"
#endif

#define	VARPROGRAMROOT1	"TESTPROGINFO_PROGRAMROOT"
#define	VARPROGRAMROOT2	VARPRNAME
#define	VARPROGRAMROOT3	"PROGRAMROOT"

#define	VARBANNER	"TESTPROGINFO_BANNER"
#define	VARSEARCHNAME	"TESTPROGINFO_NAME"
#define	VARPROGTESTPROGINFO	"TESTPROGINFO_PROGTESTPROGINFO"
#define	VAROPTS		"TESTPROGINFO_OPTS"
#define	VARAFNAME	"TESTPROGINFO_AF"
#define	VAREFNAME	"TESTPROGINFO_EF"

#define	VARDEBUGFNAME	"TESTPROGINFO_DEBUGFILE"
#define	VARDEBUGFD1	"TESTPROGINFO_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#define	VARHOMEDNAME	"HOME"
#define	VARTMPDNAME	"TMPDIR"
#define	VARMAILDNAME	"MAILDIR"
#define	VARMAILDNAMES	"MAILDIRS"

#define	VARPRTESTPROGINFO	"TESTPROGINFO"

#define	CONFFNAME	"conf"
#define	LOGFNAME	"log/cal"
#define	HELPFNAME	"help"

#define	PO_OPTION	"option"

#define	LOGSIZE		(80*1024)


#endif /* TESTPROGINFOCONFIG_INCLUDE */


