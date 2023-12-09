/* uucp */

/* send a FD over to another host using UUCP */
/* version %I% last-modified %G% */


#define	CF_DEBUGS	0		/* run-time debuging */


/* revision history :

	= 1986-07-10, David A�D� Morano
	This subroutine was originally written.

*/

/* Copyright � 1998 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

	Something w/ UUCP.


*******************************************************************************/


#include	<envstandards.h>

#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/socket.h>
#include	<sys/wait.h>
#include	<netinet/in.h>
#include	<netdb.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<strings.h>		/* for |strcasecmp(3c)| */

#include	<usystem.h>
#include	<bfile.h>
#include	<exitcodes.h>
#include	<localmisc.h>


/* local defines */

#define	PROG_UUNAME	"/bin/uuname"
#define	PROG_UUCP	"/bin/uucp"
#define	CACHEDIR	"/var/tmp/cache"
#define	DUMPLEN		50
#define	DSTLEN		(2 * MAXPATHLEN)
#define	LINELEN		(NODENAMELEN + 3)


/* external subroutines */

#if	CF_DEBUGS
extern int	debugprintf(const char *,...) ;
#endif

extern int	sfshrink(const char *,int,char **) ;
extern int	mktmpfile(char *,mode_t,const char *) ;

extern char	*strshrink(char *) ;


/* external variables */


/* forward reference */

static int	testuucp() ;

static void	bdump() ;


/* exported subroutines */


int uucp(rhost,filename,fd2p)
char	rhost[] ;
char	filename[] ;
int	*fd2p ;
{
	pid_t		child_pid ;
	int		rs = S_ROK ;
	int		;
	int	srs ;
	int	pipes[3][2] ;
	int	pfd ;
	int	child_stat ;
	int	f_bad = FALSE ;

	char	*cmd_uucp = PROG_UUCP ;
	char	pfname[MAXPATHLEN + 1] ;
	char	dst[DSTLEN + 1] ;


#if	CF_DEBUGS
	eprintf("uucp: ent\n") ;
#endif

/* check for bad input */

	if ((rhost == NULL) || (rhost[0] == '\0'))
	    return SR_INVALID ;

	if (u_access(cmd_uucp,X_OK) < 0) 
	    return SR_PROTO ;


#if	CF_DEBUGS
	eprintf("uucp: got in\n") ;
#endif

/* test the remote host for accessibility */

	if ((srs = testuucp(rhost)) < 0)
	    return SR_HOSTUNREACH ;

#if	CF_DEBUGS
	eprintf("uucp: continuing\n") ;
#endif

	pfname[0] = '\0' ;

/* open up the necessary pipes */

	if ((fd2p != NULL) && ((rs = u_pipe(pipes[2])) < 0))
	    goto badpipes ;


#if	CF_DEBUGS
	eprintf("uucp: about to make pipe file\n") ;
#endif

	rs = mktmpfile( pfname, (0600 | S_IFIFO), "/tmp/uufileXXXXXXXX") ;
	if (rs < 0) {
	    rs = SR_PROTO ;
	    goto badpipemk ;
	}


#if	CF_DEBUGS
	eprintf("uucp: got pipes \n") ;
#endif

/* form the necessary UUCP command */

	rs = bufprintf(dst,(DSTLEN + 1),"%s!%s",rhost,filename) ;

	if (rs < 0) {

		rs = SR_TOOBIG ;
		goto baddst ;
	}

/* we fork the command */

#if	CF_DEBUGS
	eprintf("uucp: about to fork\n") ;
#endif

	rs = uc_fork() ;

	if (rs < 0)
		goto badfork ;

	if (rs == 0) {
	    int	fd ;

#if	CF_DEBUGS
	    eprintf("uucp: inside fork\n") ;
#endif

	    for (i = 0 ; i < 3 ; i += 1)
	        u_close(i) ;

	    fd = u_open("/dev/null",O_RDWR,0600) ;

	    u_dup(fd) ;

	    if (fd2p != NULL) {

	        u_close(pipes[2][0]) ;

	        u_dup(pipes[2][1]) ;

	        u_close(pipes[2][1]) ;

	    } else {

	        u_dup(fd) ;

	    }

/* do the exec */

	    execl(cmd_uucp,"uucp","-C",pfname,dst,NULL) ;

	    u_exit(EC_NOEXEC) ;

	} /* end if (fork) */

#if	CF_DEBUGS
	eprintf("uucp: main line continue\n") ;
#endif

/* close some pipe ends */

	if (fd2p != NULL)
	    u_close(pipes[2][1]) ;

/* open the pipe file */

#if	CF_DEBUGS
	eprintf("uucp: about to open the pipe\n") ;
#endif

	if ((rs = u_open(pfname,O_WRONLY,0600)) < 0)
	    goto badpipeopen ;

	pfd = rs ;

#if	CF_DEBUGS
	eprintf("uucp: opened pipe, about to read answer\n") ;

	sleep(10) ;

	system("ps -f") ;
#endif

/* read out the answer */

#ifdef	COMMENT
	f_bad = FALSE ;
	while ((rs = reade(pipes[2][0],pfname,1,0,10)) > 0) {

#if	CF_DEBUGS
	    eprintf("uucp: 'reade' goto one\n") ;
#endif

	    f_bad = TRUE ;
	}

#if	CF_DEBUGS
	eprintf("uucp: read answer, f_bad=%d\n",f_bad) ;
#endif
#endif /* COMMENT */

/* we are out of here */

#ifdef	COMMENT
	u_close(pipes[2][0]) ;
#endif

	u_unlink(pfname) ;

#if	CF_DEBUGS
	eprintf("uucp: exiting, fd=%d\n",
	    pfd) ;
#endif

	return pfd ;

/* handle the bad cases */
badpipeopen:

badfork:
baddst:
	if (pfname[0] != '\0')
		u_unlink(pfname) ;

badpipemk:
	if (fd2p != NULL) {

	    u_close(pipes[2][0]) ;

	    u_close(pipes[2][1]) ;

	}

badpipes:

#if	CF_DEBUGS
	eprintf("uucp: bad exit, rs=%d\n",rs) ;
#endif

	return rs ;
}
/* end subroutine (uucp) */



/* LOCAL SUBROUTINES */



/* check for UUCP availability */
static int testuucp(queue_machine)
char	queue_machine[] ;
{
	bfile		file0, file2 ;
	bfile		procfile, *pfp = &procfile ;
	bfile		*fpa[3] ;

	pid_t		pid ;

	int		rs = SR_OK ;
	int		child_stat ;
	int		i, si, ri ;
	int	len, sl ;
	int	nlen ;
	int	f_found ;

	char	linebuf[LINELEN + 1] ;
	char	*sp, *cp ;
	char	*cmd_uuname = PROG_UUNAME ;


#if	CF_DEBUGS
	eprintf("testuucp: ent\n") ;
#endif

	if ((queue_machine == NULL) || (queue_machine[0] == '\0'))
	    return BAD ;

#if	CF_DEBUGS
	eprintf("testuucp: got in\n") ;
#endif

	if (u_access(cmd_uuname,X_OK) < 0) 
		return BAD ;

	fpa[0] = &file0 ;
	fpa[1] = pfp ;		/* capture the standard output ! */
	fpa[2] = &file2 ;

#if	CF_DEBUGS
	eprintf("testuucp: about to open command - FPA[1]=%08X\n",fpa[1]) ;
	eprintf("testuucp: FPA[0]=%08X\n",fpa[0]) ;
#endif

	if ((rs = bopencmd(fpa,cmd_uuname)) >= 0) {
	    pid = rs ;

#if	CF_DEBUGS
	    eprintf("testuucp: opened command OK\n") ;
#endif

	    bclose(fpa[0]) ;

/* find the part of the machine name that we like */

	    if ((cp = strchr(queue_machine,'.')) != NULL) {
	        nlen = cp - queue_machine ;
	} else {
	    nlen = strlen(queue_machine) ;
	}

/* loop through */

	f_found = FALSE ;
	    rs = BAD ;
	    while ((len = breadln(pfp,linebuf,LINELEN)) > 0) {

		sl = sfshrink(linebuf,len,&sp) ;

	        sp[sl] = '\0' ;
		if ((rs = strtab_already(&nst,sp,sl)) < 0) {

		si = strtab_add(&nst,sp,sl) ;

		ri = uunamerec_add(&u,si) ;


		if (! f_found) {

	        f_found = ((nlen == sl) && 
			(strcasecmp(sp,queue_machine) == 0)) ;

	        } /* end if (not found yet) */

		} /* end if (didn' have already) */

	    } /* end while (reading lines) */

#ifdef	COMMENT
	    bdump(fpa[0],fpa[2]) ;
#endif

	    bclose(pfp) ;

	    bclose(fpa[2]) ;

	    u_waitpid(pid,&child_stat,WUNTRACED) ;

	} /* end if (program spawned) */

#if	CF_DEBUGS
	eprintf("testuucp: passed the command OK\n") ;
#endif

	return rs ;
}
/* end subroutine (testuucp) */


static void bdump(fd1,fd2)
int	fd1, fd2 ;
{
	int	f_done1, f_done2 ;

	char	buf[DUMPLEN + 1] ;


	f_done1 = f_done2 = FALSE ;
	while ((! f_done1) || (! f_done2)) {

	    if (! f_done1) {

	        if (u_read(fd1,buf,DUMPLEN) <= 0)
	            f_done1 = TRUE ;

	    }

	    if (! f_done2) {

	        if (u_read(fd2,buf,DUMPLEN) <= 0)
	            f_done2 = TRUE ;

	    }

	} /* end while */

}
/* end subroutine (bdump) */



