/* main (testsort) */

/* sorted list testing */


#define	CF_DEBUGS	1




#include	<sys/types.h>
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	<fcntl.h>
#include	<csignal>
#include	<time.h>
#include	<ftw.h>
#include	<dirent.h>
#include	<cstring>
#include	<cstdlib>
#include	<cerrno>

#include	<bfile.h>
#include	<field.h>
#include	<logfile.h>
#include	<vechand.h>
#include	<userinfo.h>
#include	<baops.h>
#include	<char.h>

#include	"localmisc.h"
#include	"sortvec.h"



/* local defines */

#define	LINELEN	100



/* external subroutines */

extern char	*malloc_str(char *) ;


/* forward references */

static int	slcmp() ;





int main(argc,argv)
int	argc ;
char	*argv[] ;
{
	bfile	infile, *ifp = &infile ;
	bfile	outfile, *ofp = &outfile ;
	bfile	tmpfile, *tfp = &tmpfile ;

	SORTVEC	list1 ;

	VECHAND	list2 ;

	int	rs, i, j, len ;
	int	err_fd ;

	char	linebuf[LINELEN + 1] ;
	char	tmpfname_buf[MAXPATHLEN + 1] ;
	char	*cp, *cp1, *cp2 ;
	char	*lp ;
	char	*ep ;
	char	*progname ;


	if (((cp = getenv("ERROR_FD")) != NULL) &&
	    (cfdeci(cp,-1,&err_fd) >= 0))
	    debugsetfd(err_fd) ;


	progname = argv[0] ;
	(void) bopen(ofp,BFILE_STDOUT,"wct",0666) ;

#if	CF_DEBUGS
	debugprintf("main: entered\n") ;
#endif


	if (argc > 1)
	rs = bopen(ifp,argv[1],"r",0666) ;

	else
	rs = bopen(ifp,BFILE_STDIN,"dr",0666) ;

	if (rs < 0) goto badopen ;



	rs = vechand_start(&list2,0,VECHAND_OSORTED) ;

	rs = sortvec_init(&list1,0,slcmp) ;

#if	CF_DEBUGS
	debugprintf("main: sortvec_init rs=%d\n",rs) ;
#endif

	while ((len = breadln(ifp,linebuf,LINELEN)) > 0) {

	    if (linebuf[len - 1] == '\n') len -= 1 ;

	    linebuf[len] = '\0' ;
	    cp = linebuf ;
	    while (CHAR_ISWHITE(*cp)) cp += 1 ;

	    cp1 = cp ;
	    while (*cp && (! CHAR_ISWHITE(*cp))) cp += 1 ;

	    if (*cp != '\0') *cp++ = '\0' ;

	    while (CHAR_ISWHITE(*cp)) cp += 1 ;

	    cp2 = cp ;


	    ep = malloc_str(cp1) ;

	    rs = sortvec_add(&list1,(void *) ep) ;

#if	CF_DEBUGS
	    debugprintf("main: sortvec_add rs=%d\n",rs) ;
#endif

	    vechandadd(&list2,ep) ;

	} /* end while (reading lines) */

	vechandsort(&list2,slcmp) ;


#if	CF_DEBUGS
	debugprintf("main: outputting phase\n") ;
#endif

	bprintf(ofp,"outputting phase\n\n") ;


	for (i = 0 ; sortvec_get(&list1,i,(void **) &lp) >= 0 ; i += 1) {

	    if (lp == NULL) continue ;

	    write(4,lp,strlen(lp)) ;

	    write(4,"\n",1) ;

	}


#if	CF_DEBUGS
	debugprintf("main: output the vector list\n") ;
#endif

	for (i = 0 ; vechandget(&list2,i,&lp) >= 0 ; i += 1) {

	    if (lp == NULL) continue ;

#if	CF_DEBUGS
	debugprintf("main: lp=%s\n",lp) ;
#endif

	    write(5,lp,strlen(lp)) ;

	    write(5,"\n",1) ;

	}



#if	CF_DEBUGS
	debugprintf("main: compare phase\n") ;
#endif

	bprintf(ofp,"comparing phase\n\n") ;


	for (i = 0 ; vechandget(&list2,i,&lp) >= 0 ; i += 1) {

	    if (lp == NULL) continue ;

#if	CF_DEBUGS
	    debugprintf("main: i=%d ep2=%s\n",i,lp) ;
#endif

	    if (sortvec_get(&list1,i,(void **) &ep) < 0) goto badcheck ;

	    if (ep == NULL) goto badcheck2 ;

#if	CF_DEBUGS
	    debugprintf("main: ep1=%s\n",ep) ;
#endif

	    if (strcmp(lp,ep) != 0) goto badcheck3 ;

	} /* end for */

	bprintf(ofp,"\n") ;

	rs = 0 ;


done:
	sortvec_free(&list1) ;

	vechandfree(&list2) ;

	bclose(ifp) ;

	bclose(ofp) ;

	return rs ;

badcheck:
	bprintf(ofp,"badcheck i=%d\n",i) ;

	goto done ;

badcheck2:
	bprintf(ofp,"badcheck2 i=%d\n",i) ;

	goto done ;

badcheck3:
	bprintf(ofp,"badcheck3 i=%d\n",i) ;

	goto done ;

badopen:
	bprintf(ofp,"%s: could not open input file (rs=%d\n",
		progname,rs) ;

	goto done ;

}
/* end subroutine (main) */



static int slcmp(app,bpp)
char	**app, **bpp ;
{


	return strcmp(*app,*bpp) ;
}



