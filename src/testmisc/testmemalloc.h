/* config (testmemalloc) */
/* lang=C20 */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright � 2017 David A�D� Morano.  All rights reserved. */
/* Use is subject to license terms. */

#define	VERSION		"0"
#define	WHATINFO	"@(#)testmemalloc "
#define	BANNER		"Test Memory-Allocation"
#define	SEARCHNAME	"testmemalloc"
#define	VARPRNAME	"LOCAL"

#define	VARPROGRAMROOT1	"TESTMEMALLOC_PROGRAMROOT"
#define	VARPROGRAMROOT2	VARPRNAME
#define	VARPROGRAMROOT3	"PROGRAMROOT"

#define	VARBANNER	"TESTMEMALLOC_BANNER"
#define	VARSEARCHNAME	"TESTMEMALLOC_NAME"
#define	VAROPTS		"TESTMEMALLOC_OPTS"
#define	VARFILEROOT	"TESTMEMALLOC_FILEROOT"
#define	VARLOGTAB	"TESTMEMALLOC_LOGTAB"
#define	VARMSFNAME	"TESTMEMALLOC_MSFILE"
#define	VARUTFNAME	"TESTMEMALLOC_UTFILE"
#define	VAREFNAME	"TESTMEMALLOC_EF"

#define	VARDEBUGFNAME	"TESTMEMALLOC_DEBUGFILE"
#define	VARDEBUGFD1	"TESTMEMALLOC_DEBUGFD"
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



