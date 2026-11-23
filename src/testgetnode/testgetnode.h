/* testgetnodedomain HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* TESTGETNODEDOMAIN program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	TESTGETNODEDOMAIN_INCLUDE
#define	TESTGETNODEDOMAIN_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */


#define	VERSION		"0"
#define	WHATINFO	"@(#)TESTGETNODEDOMAIN "
#define	BANNER		"Test Get-Node-Domain"
#define	SEARCHNAME	"cal"
#define	VARPRNAME	"TESTGETNODEDOMAIN"

#ifndef	PROGRAMROOT
#define	PROGRAMROOT	"/usr/add-on/local"
#endif

#define	VARPROGRAMROOT1	"TESTGETNODEDOMAIN_PROGRAMROOT"
#define	VARPROGRAMROOT2	VARPRNAME
#define	VARPROGRAMROOT3	"PROGRAMROOT"

#define	VARBANNER	"TESTGETNODEDOMAIN_BANNER"
#define	VARSEARCHNAME	"TESTGETNODEDOMAIN_NAME"
#define	VARPROGTESTGETNODEDOMAIN	"TESTGETNODEDOMAIN_PROGTESTGETNODEDOMAIN"
#define	VAROPTS		"TESTGETNODEDOMAIN_OPTS"
#define	VARAFNAME	"TESTGETNODEDOMAIN_AF"
#define	VAREFNAME	"TESTGETNODEDOMAIN_EF"

#define	VARDEBUGFNAME	"TESTGETNODEDOMAIN_DEBUGFILE"
#define	VARDEBUGFD1	"TESTGETNODEDOMAIN_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#define	VARHOMEDNAME	"HOME"
#define	VARTMPDNAME	"TMPDIR"
#define	VARMAILDNAME	"MAILDIR"
#define	VARMAILDNAMES	"MAILDIRS"

#define	VARPRTESTGETNODEDOMAIN	"TESTGETNODEDOMAIN"

#define	CONFFNAME	"conf"
#define	LOGFNAME	"log/cal"
#define	HELPFNAME	"help"

#define	PO_OPTION	"option"

#define	LOGSIZE		(80*1024)


#endif /* TESTGETNODEDOMAIN_INCLUDE */


