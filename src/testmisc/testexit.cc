/* testexit SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/****

Compile and execute:
$ gpp -o testexit.x testexit.cc

****/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstdlib>
#include	<cstring>
#include	<dlfcn.h>
#include	<utypedefs.h>
#include	<clanguage.h>
#include	<iostream>

using namespace std ;

extern "C" {
    local void efunc() noex ;
}

struct obj {
	obj() noex {
	    cchar	*sp = "main.ctor\n" ;
	    cint	sl = strlen(sp) ;
	    write(1,sp,sl) ;
	} ;
	~obj() noex {
	    cchar	*sp = "main.dtor\n" ;
	    cint	sl = strlen(sp) ;
	    write(1,sp,sl) ;
	} ;
} ;

static const obj	obj_data ;

int main(int,cchar **,cchar **) {
	cout << "main.begin\n" ;
	{
	    atexit(efunc) ;
	}
	cout << "main.end\n" ;
	exit(0) ;
}

local void efunc() noex {
	cchar	*sp = "main.efunc\n" ;
	cint	sl = strlen(sp) ;
	write(1,sp,sl) ;
}


