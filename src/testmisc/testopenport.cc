/* testopenport */
/* lang=C89 */

#define	CF_DEBUGS	1		/* compile-time debugging */
#define	CF_DEBUGMALL	1		/* debugging memory-allocations */
#include	<envstandards.h>
#include	<sys/types.h>
#include	<cstdarg>
#include	<cstdio>
#include	<usystem.h>
#include	<sockaddress.h>
#include	<openport.h>
#include	<localmisc.h>		/* TIMEBUFLEN */

#ifndef	INETXADDRLEN
#define	INETXADDRLEN		MAX(INET4ADDRLEN,INET6ADDRLEN)
#endif

#define	VARDEBUGFNAME	"TESTOPENPORT_DEBUGFILE"

extern int	getportnum(cchar *,cchar *) ;
extern int	fbwrite(FILE *,const void *,int) ;
extern int	bufprintf(char *,int,cchar *,...) ;

#if	CF_DEBUGS
extern int	debugopen(cchar *) ;
extern int	debugprintf(cchar *,...) ;
extern int	debugclose() ;
extern int	strlinelen(cchar *,int,int) ;
#endif

extern cchar 	*getourenv(cchar **,cchar *) ;

extern char	*timestr_logz(time_t,char *) ;

/* forward references */

static int procopen(cchar *) ;


/* exported subroutines */


int main(int argc,cchar **argv,cchar **envv)
{

#if	CF_DEBUGS && CF_DEBUGMALL
	uint		mo_start = 0 ;
#endif

	int		rs = SR_OK ;
	int		rs1 ;

#if	CF_DEBUGS
	{
	    cchar	*cp ;
	    if ((cp = getourenv(envv,VARDEBUGFNAME)) != NULL) {
	        rs = debugopen(cp) ;
	        debugprintf("main: starting rs=%d\n",rs) ;
	    }
	}
#endif /* CF_DEBUGS */

#if	CF_DEBUGS && CF_DEBUGMALL
	uc_mallset(1) ;
	uc_mallout(&mo_start) ;
#endif

	if (argv != NULL) {
	    int		ai ;
	    for (ai = 1 ; (ai < argc) && (argv[ai] != NULL) ; ai += 1) {
		cint	to = 60 ;
	        cint	of = O_RDONLY ;
	        cchar	*ps = argv[ai] ;
		cchar		*sp = "hello world!\n" ;
#if	CF_DEBUGS
	        debugprintf("main: ps=%s\n",ps) ;
#endif
		if ((rs = procopen(ps)) >= 0) {	
		    SOCKADDR	sa ;
		    cint	sfd = rs ;
		    cint	sl = strlen(sp) ;
		    int		sal = 0 ;
#if	CF_DEBUGS
	        debugprintf("main: procopen() rs=%d\n",rs) ;
#endif
		    while ((rs = uc_accepte(sfd,&sa,&sal,to)) >= 0) {
			cint	cfd = rs ;
			{
			    if ((rs = uc_writen(cfd,sp,sl)) >= 0) {
				u_close(cfd) ;
			    }
			}
			if (rs < 0) break ;
		    } /* end while */
		    u_close(sfd) ;
		} /* end if (procopen) */
#if	CF_DEBUGS
	        debugprintf("main: procopen-out rs=%d\n",rs1) ;
#endif
	        if (rs < 0) break ;
	    } /* end for */
	} /* end if (arguments) */

	if (rs < 0)
	printf("failure (%d)\n",rs) ;

#if	CF_DEBUGS
	debugprintf("main: out rs=%d\n",rs) ;
#endif

#if	CF_DEBUGS && CF_DEBUGMALL
	{
	    uint	mo ;
	    uc_mallout(&mo) ;
	    debugprintf("main: final mallout=%u\n",(mo-mo_start)) ;
	    uc_mallset(0) ;
	}
#endif

#if	CF_DEBUGS
	debugclose() ;
#endif

	return 0 ;
}
/* end subroutine (main) */


/* local subroutines */

static int procopen(cchar *ps) noex {
	cint		alen = INETXADDRLEN ;
	cint		af = AF_INET ;
	cint		fl = 0 ;
	int		rs ;
	int		rs1 ;
	int		fd = -1 ;
	cchar		*pn = "tcp" ;
	char		addr[INETXADDRLEN+1] ;
	(void) alen ;
	if ((rs = getportnum(pn,ps)) >= 0) {
	    cint	port = rs ;
	    sockaddress	sa ;
	    if ((rs = sockaddress_start(&sa,af,addr,port,fl)) >= 0) {
		cint	pf = PF_INET4 ;
		cint	st = SOCK_STREAM ;
		cint	proto = 0 ;
		if ((rs = openport(pf,st,proto,&sa)) >= 0) {
	            fd = rs ;
	            rs = u_listen(fd,10) ;
		    if ((rs < 0) && (fd >= 0)) {
			u_close(fd) ;
			fd = -1 ;
		    } /* end if (error) */
	        } /* end if (openport) */
	        rs1 = sockaddress_finish(&sa) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if (sockaddress) */
	} /* end if (getportnum) */
	return (rs >= 0) ? fd : rs ;
}
/* end subroutine (procoptn) */


