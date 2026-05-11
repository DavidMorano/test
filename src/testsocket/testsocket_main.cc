/* testsocket_main (testsocket) */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* program to test 'socket(3socket)' API */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* compile-time debug switch */

/* revision history:

	- 1998-05-23, David A­D­ Morano
	This subroutine was originally written.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

  	Name:

	Synopsis:
	$ testsocket

*******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<netdb.h>
#include	<ctime>
#include	<cstddef>
#include	<cstdlib>
#include	<cstring>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<uinet.h>
#include	<getproto.h>
#include	<getpf.h>
#include	<getaf.h>
#include	<inetaddr.h>
#include	<hostinfo.h>
#include	<hostaddr.h>
#include	<sockaddress.h>
#include	<mapex.h>
#include	<exitcodes.h>
#include	<localmisc.h>
#include	<dprint.hh>		/* |DPRINT(3u)| */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */

/* local defines */

#ifndef	LOCALHOST
#define	LOCALHOST	"localhost"
#endif

#ifndef	CF_DEBUG
#define	CF_DEBUG	0		/* compile-time debug switch */
#endif


/* imported namespaces */

using libu::umem ;			/* variable */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */


/* forward references */

local int	mainproc() noex ;
local int	mainbind() noex ;
local int	mainopen() noex ;


/* local variables */

constexpr MAPEXENT	mapexs[] = {
	{ SR_NOENT,	EX_NOUSER },
	{ SR_AGAIN,	EX_TEMPFAIL },
	{ SR_DEADLK,	EX_TEMPFAIL },
	{ SR_NOLCK,	EX_TEMPFAIL },
	{ SR_TXTBSY,	EX_TEMPFAIL },
	{ SR_ACCESS,	EX_NOPERM },
	{ SR_REMOTE,	EX_PROTOCOL },
	{ SR_NOSPC,	EX_TEMPFAIL },
	{ SR_INTR,	EX_INTR },
	{ SR_EXIT,	EX_TERM },
	{ 0, 0 }
} ; /* end array (mapexs) */

cchar fn[] = "sockfile" ;

cbool	f_debug	= CF_DEBUG ;


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	int	rs = SR_OK ;
	int	ex = EX_OK ;
	printf("hello world!\n") ;
	{
	    rs = mainproc() ;
	}
	if ((rs < 0) && (ex == EX_OK)) {
	    ex = mapex(mapexs,rs) ;
	} /* end if */
	return ex ;
}
/* end subroutine (main) */


/* local subroutines */

local int mainproc() noex {
    	int		rs ;
	DPRINTF("ent\n") ;
	if ((rs = mainbind()) >= 0) {
	    DPRINTF("mainbind rs=%d\n",rs) ;
	    rs = mainopen() ;
	    DPRINTF("mainopen rs=%d\n",rs) ;
	}
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (mainproc) */

local int mainbind() noex {
    	cint		rsn = SR_NOTFOUND ;
    	cint		pf = PF_UNIX ;
    	int		rs ;
	int		rs1 ;
	int		rv = 0 ; /* return-value */
	DPRINTF("ent fn=%s\n",fn) ;
	if ((rs = u_socket(pf,SOCK_STREAM,0)) >= 0) {
	    cint af = AF_UNIX ;
	    cint fd = rs ;
	    if (sockaddress sa ; (rs = sa.start(af,fn,0,0)) >= 0) {
		cint sal = rs ;
		if ((rs = u_unlink(fn)) >= 0) {
		    sockaddr *sap = cast_reinterpret<sockaddr *>(&sa) ;
		    rs = u_bind(fd,sap,sal) ;
		    rv = rs ;
		} else if (rs == rsn) {
		    rs = SR_OK ;
		}
		rs1 = sa.finish ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (sockaddress) */
	    rs1 = u_close(fd) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (u_socket) */
	DPRINTF("ret rs=%d rv=%d\n",rs,rv) ;
	return (rs >= 0) ? rv : rs ;
} /* end subroutine (mainbind) */

local int mainopen() noex {
    	int		rs ;
	int		rs1 ;
	int		rv = 0 ; /* return-value */
	cint		llen = MAXLINELEN ;
	DPRINTF("ent fn=%s\n",fn) ;
	if (char *lbuf ; (rs = umem.mall((llen+1),&lbuf)) >= 0) {
    	    cint	of = O_RDWR ;
	    cmode	om = 0 ;
	    if ((rs = u_open(fn,of,om)) >= 0) {
		cint fd = rs ;
		DPRINTF("opened! fd=%d\n",rs) ;
	        {
		    rs = u_read(fd,lbuf,llen) ;
		    rv = rs ;
	        }
	        rs1 = u_close(fd) ;
	        if (rs >= 0) rs = rs1 ;
	    } /* end if (u_open) */
	    rs1 = umem.free(lbuf) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (m-a-f) */
	DPRINTF("ret rs=%d rv=%d\n",rs,rv) ;
	return (rs >= 0) ? rv : rs ;
} /* end subroutine (mainopen) */


