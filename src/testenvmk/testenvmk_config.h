/* testenvmk_config HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* test the |envmk(3uc)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#define	VERSION		"0"
#define	WHATINFO	"@(#)testenvmk "
#define	BANNER		"Test ENVMK"
#define	SEARCHNAME	"testenvmk"
#define	VARPRNAME	"LOCAL"

#define	VARPROGRAMROOT1	"TESTENVMK_PROGRAMROOT"
#define	VARPROGRAMROOT2	VARPRNAME
#define	VARPROGRAMROOT3	"PROGRAMROOT"

#define	VARBANNER	"TESTENVMK_BANNER"
#define	VARSEARCHNAME	"TESTENVMK_NAME"
#define	VAROPTS		"TESTENVMK_OPTS"
#define	VARFILEROOT	"TESTENVMK_FILEROOT"
#define	VARLOGTAB	"TESTENVMK_LOGTAB"
#define	VARMSFNAME	"TESTENVMK_MSFILE"
#define	VARUTFNAME	"TESTENVMK_UTFILE"
#define	VARERRORFNAME	"TESTENVMK_ERRORFILE"

#define	VARDEBUGFNAME	"TESTENVMK_DEBUGFILE"
#define	VARDEBUGFD1	"TESTENVMK_DEBUGFD"
#define	VARDEBUGFD2	"DEBUGFD"

#define	VARSYSNAME	"SYSNAME"
#define	VARRELEASE	"RELEASE"
#define	VARMACHINE	"MACHINE"
#define	VARARCHITECTURE	"ARCHITECTURE"
#define	VARNODE		"NODE"
#define	VARCLUSTER	"CLUSTER"
#define	VARSYSTEM	"SYSTEM"
#define	VARDOMAIN	"DOMAIN"
#define	VARNISDOMAIN	"NISDOMAIN"
#define	VARTERM		"TERM"
#define	VARPRINTER	"PRINTER"
#define	VARLPDEST	"LPDEST"
#define	VARPAGER	"PAGER"
#define	VARMAIL		"MAIL"
#define	VARORGANIZATION	"ORGANIZATION"
#define	VARLINES	"LINES"
#define	VARCOLUMNS	"COLUMNS"
#define	VARNAME		"NAME"
#define	VARFULLNAME	"FULLNAME"
#define	VARHZ		"HZ"
#define	VARTZ		"TZ"
#define	VARUSERNAME	"USERNAME"
#define	VARLOGNAME	"LOGNAME"

#define	VARHOMEDNAME	"HOME"
#define	VARTMPDNAME	"TMPDIR"
#define	VARMAILDNAME	"MAILDIR"
#define	VARMAILDNAMES	"MAILDIRS"

#define	VARPRLOCAL	"LOCAL"
#define	VARPRPCS	"PCS"

#ifndef	PROGRAMROOT
#define	PROGRAMROOT	"/usr/add-on/local"
#endif

#define	TMPDNAME	"/tmp"
#define	WORKDNAME	"/tmp"
#define	LOGCNAME	"log"

#define	DEFINITFNAME	"/etc/default/init"
#define	DEFLOGFNAME	"/etc/default/login"
#define	NISDOMAINNAME	"/etc/defaultdomain"

#define	CONFIGFNAME	"conf"
#define	ENVFNAME	"environ"
#define	PATHSFNAME	"paths"
#define	HELPFNAME	"help"

#define	PIDFNAME	"run/testenvmk"		/* mutex PID file */
#define	LOGFNAME	"var/log/testenvmk"	/* activity log */
#define	LOCKFNAME	"spool/locks/testenvmk"	/* lock mutex file */
#define	MSFNAME		"ms"

#define	LOGSIZE		(80*1024)

#define	DEFRUNINT	60
#define	DEFPOLLINT	8
#define	DEFNODES	50

#define	TO_CACHE	2
#define	TO_LOADAVG	1

#define	USAGECOLS	4


