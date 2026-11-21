/* testrealname HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* TESTREALNAME program */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#ifndef	TESTREALNAME_INCLUDE
#define	TESTREALNAME_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */


#define	VERSION		"0"
#define	WHATINFO	"@(#)TESTREALNAME "
#define	BANNER		"Test Real Name"
#define	SEARCHNAME	"cal"
#define	VARPRNAME	"TESTREALNAME"

#ifndef	PROGRAMROOT
#define	PROGRAMROOT	"/usr/add-on/local"
#endif

#define	VARPROGRAMROOT1	"TESTREALNAME_PROGRAMROOT"
#define	VARPROGRAMROOT2	VARPRNAME
#define	VARPROGRAMROOT3	"PROGRAMROOT"

#define	VARBANNER	"TESTREALNAME_BANNER"
#define	VARSEARCHNAME	"TESTREALNAME_NAME"
#define	VARPROGTESTREALNAME	"TESTREALNAME_PROGTESTREALNAME"
#define	VAROPTS		"TESTREALNAME_OPTS"
#define	VARAFNAME	"TESTREALNAME_AF"
#define	VAREFNAME	"TESTREALNAME_EF"

#define	VARDEBUGFNAME	"TESTREALNAME_DEBUGFILE"
#define	VARDEBUGFD1	"TESTREALNAME_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#define	VARHOMEDNAME	"HOME"
#define	VARTMPDNAME	"TMPDIR"
#define	VARMAILDNAME	"MAILDIR"
#define	VARMAILDNAMES	"MAILDIRS"

#define	VARPRTESTREALNAME	"TESTREALNAME"

#define	CONFFNAME	"conf"
#define	LOGFNAME	"log/cal"
#define	HELPFNAME	"help"

#define	PO_OPTION	"option"

#define	LOGSIZE		(80*1024)


#endif /* TESTREALNAME_INCLUDE */


