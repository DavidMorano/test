/* testcase SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the variaous system case-insensitive comparisons against my own */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/*******************************************************************************

 	Description:
	I test some standar case-insensitive string comparison functions
	against my own vesion.

*******************************************************************************/

#include	<envstandards.h>	/* must be ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<cstring>		/* CSTD |strcasecmp(3c)| */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<strn.h>		/* LIBUC |strnsub(3uc)| */
#include	<strxcmp.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */

using std::cout ;			/* variable */

cchar		str_main[] = "Héllo" ;
cchar		str_all[] = "HÉllo" ;
cchar		str_sub[] = "HÉl" ;

local void	cmpall() noex ;
local void	cmpsub() noex ;

int main(int,con mainv,con mainv) {
    	cmpall() ;
	cmpsub() ;
} /* end subroutine (main) */

local void cmpall() noex {
    	cnullptr	np{} ;
	printf("cmp-all\n") ;
    if (strcmp(str_main,str_all) == 0) {
	cout << "strcmp" << eol ;
    }
    if (strcasecmp(str_main,str_all) == 0) {
	cout << "strcasecmp" << eol ;
    }
    if (strcasecmpo(str_main,str_all) == 0) {
	cout << "strcasecmpo" << eol ;
    }
    if (strfoldcmp(str_main,str_all) == 0) {
	cout << "strfoldcmp" << eol ;
    }
} /* end subroutine (cmpall) */

local void cmpsub() noex {
    	cnullptr	np{} ;
	printf("cmp-sub\n") ;
    if (cc *tp ; (tp = strstr(str_main,str_sub)) != np) {
	cout << "strstr" << eol ;
    }
    if (cc *tp ; (tp = strcasestr(str_main,str_sub)) != np) {
	cout << "strcasestr" << eol ;
    }
    if (cc *tp ; (tp = strncasesub(str_main,-1,str_sub)) != np) {
	cout << "strncasesub" << eol ;
    }
    if (cc *tp ; (tp = strnfoldsub(str_main,-1,str_sub)) != np) {
	cout << "strnfoldsub" << eol ;
    }
} /* end subroutine (cmpsub) */


