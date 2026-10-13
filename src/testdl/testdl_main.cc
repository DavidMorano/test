/* main */


#define	CF_SLEEP	0


#include	<envstandards.h>	/* ordered first to configure */

#include	<sys/types.h>
#include	<dlfcn.h>
#include	<cstdio>

#include	<usystem.h>
#include	<localmisc.h>

#include	"config.h"
#include	"defs.h"


/* local defines */

#define	OBJECT	"printer.o"


/* exported subroutines */


int main(argc,argv,envv)
int		argc ;
cchar	*argv[] ;
cchar	*envv[] ;
{
	void	*sop ;

	int	rs = SR_OK ;
	int	dlmode = (RTLD_LAZY | RTLD_LOCAL) ;
	int	(*fp)(cchar *) ;

	cchar	*pn = "testdl" ;
	cchar	*soname = "printer.o" ;
	cchar	*symname = "printer" ;
	cchar	*msg = "hello world!" ;


	if ((sop = dlopen(soname,dlmode)) != NULL) {

	    if ((fp = dlsym(sop,symname)) != NULL) {
		rs = (*fp)(msg) ;
	    } else
		rs = SR_NOENT ;

	    dlclose(sop) ;
	} else
	    rs = SR_LIBACC ;

	fprintf(stdout,"%s: exiting rs=%d\n",pn,rs) ;

	fclose(stdout) ;

	return 0 ;
}
/* end subroutine (main) */



