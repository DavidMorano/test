/* testfilereadln HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* TESTFILEREADLN program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	TESTFILEREADLN_INCLUDE
#define	TESTFILEREADLN_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */


#define	VERSION		"0"
#define	WHATINFO	"@(#)TESTFILEREADLN "
#define	BANNER		"Test File-Read-Line"
#define	SEARCHNAME	"cal"
#define	VARPRNAME	"TESTFILEREADLN"

#ifndef	PROGRAMROOT
#define	PROGRAMROOT	"/usr/add-on/local"
#endif

#define	VARPROGRAMROOT1	"TESTFILEREADLN_PROGRAMROOT"
#define	VARPROGRAMROOT2	VARPRNAME
#define	VARPROGRAMROOT3	"PROGRAMROOT"

#define	VARBANNER	"TESTFILEREADLN_BANNER"
#define	VARSEARCHNAME	"TESTFILEREADLN_NAME"
#define	VARPROGTESTFILEREADLN	"TESTFILEREADLN_PROGTESTFILEREADLN"
#define	VAROPTS		"TESTFILEREADLN_OPTS"
#define	VARAFNAME	"TESTFILEREADLN_AF"
#define	VAREFNAME	"TESTFILEREADLN_EF"

#define	VARDEBUGFNAME	"TESTFILEREADLN_DEBUGFILE"
#define	VARDEBUGFD1	"TESTFILEREADLN_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#define	VARHOMEDNAME	"HOME"
#define	VARTMPDNAME	"TMPDIR"
#define	VARMAILDNAME	"MAILDIR"
#define	VARMAILDNAMES	"MAILDIRS"

#define	VARPRTESTFILEREADLN	"TESTFILEREADLN"

#define	CONFFNAME	"conf"
#define	LOGFNAME	"log/cal"
#define	HELPFNAME	"help"

#define	PO_OPTION	"option"

#define	LOGSIZE		(80*1024)


#endif /* TESTFILEREADLN_INCLUDE */


