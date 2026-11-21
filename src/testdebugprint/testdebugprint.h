/* testdebugprint HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* TESTDEBUGPRINT program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	TESTDEBUGPRINTCONFIG_INCLUDE
#define	TESTDEBUGPRINTCONFIG_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */


#define	VERSION		"0"
#define	WHATINFO	"@(#)TESTDEBUGPRINT "
#define	BANNER		"Test DebugPrint"
#define	SEARCHNAME	"cal"
#define	VARPRNAME	"TESTDEBUGPRINT"

#ifndef	PROGRAMROOT
#define	PROGRAMROOT	"/usr/add-on/local"
#endif

#define	VARPROGRAMROOT1	"TESTDEBUGPRINT_PROGRAMROOT"
#define	VARPROGRAMROOT2	VARPRNAME
#define	VARPROGRAMROOT3	"PROGRAMROOT"

#define	VARBANNER	"TESTDEBUGPRINT_BANNER"
#define	VARSEARCHNAME	"TESTDEBUGPRINT_NAME"
#define	VARPROGTESTDEBUGPRINT	"TESTDEBUGPRINT_PROGTESTDEBUGPRINT"
#define	VAROPTS		"TESTDEBUGPRINT_OPTS"
#define	VARAFNAME	"TESTDEBUGPRINT_AF"
#define	VAREFNAME	"TESTDEBUGPRINT_EF"

#define	VARDEBUGFNAME	"TESTDEBUGPRINT_DEBUGFILE"
#define	VARDEBUGFD1	"TESTDEBUGPRINT_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#define	VARHOMEDNAME	"HOME"
#define	VARTMPDNAME	"TMPDIR"
#define	VARMAILDNAME	"MAILDIR"
#define	VARMAILDNAMES	"MAILDIRS"

#define	VARPRTESTDEBUGPRINT	"TESTDEBUGPRINT"

#define	CONFFNAME	"conf"
#define	LOGFNAME	"log/cal"
#define	HELPFNAME	"help"

#define	PO_OPTION	"option"

#define	LOGSIZE		(80*1024)


#endif /* TESTDEBUGPRINTCONFIG_INCLUDE */


