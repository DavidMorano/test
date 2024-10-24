/* teststatic SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++20 */

#include	<envstandards.h>	/* ordered first to configure */
#include	<stdio.h>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>

int statsub()  noex {
    printf("statsub\n") ;
    return 0 ;
}

void sub() noex {
    static int	rsv = statsub() ;
    printf("sub\n") ;
}

int main(int,mainv,mainv) {
    printf("main ent\n") ;
    sub() ;
    sub() ;
    printf("main ret\n") ;
    return 0 ;
}


