/* teststrtox_main SUPPORT (teststrtox) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test the |hostequiv(3dam)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 2026-03-30, David A-D- Morano
	I just saw that there are tests for the GNU GLIB version
	of their various |strto{x}(3c)| subroutines.  I thought
	that it was high time (after all of these years) to see
	if my own versions of these subroutines (specifically
	my look-alikes for |strtol(3c)| and |strtoul(3c)|) can
	pass those tests.

*/

/* Copyright © 2026 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

/* Copyright © 2026 GNU GLIB.  All rights reserved. */

/**** 
  
Copyright © 2026 GNU GLIB.  All rights reserved.
Some code below (the test entries and test entry structure) were
taken from the GNU GLIBC test code for their versions of the various
|strto{x}| subroutines.  I only took the tests for the |strtol(3c)|
type subroutine.

****/

/*******************************************************************************

  	Name:
	teststrtox

	Description:
	This test program tests the |strtoxl(3u)| subroutine.  I
	took (borrowed?) the tests from the GNU GLIBC implementation
	of their |stro{x}(3c)| subroutines and included it (pretty
	much untouched) below.  I had to make a few clean-ups for
	it (the data) to compile properly under C++ rules.

	Copyright-note:
	The tests below were taken from the tests included with the
	GNU LIBC implementation.  See that original file (under the
	'stdlib' directory witin the repository for GNU GLIBC) for
	more copyright information on that code.

	Results:
	There are both signed and unsigned tests.  I had to separate
	out the two and only run each with its respective intended
	function: either |strtoxl(3)| or |strtoxul(3u)|.  For
	control, I also ran the tests against the macOS (Apple
	Datwin) version of the standard C-language subroutines.
	All of these test cases pass on all subroutines.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |geprogname(3c)| */
#include	<cstdint>
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<usysflag.h>		/* |usysflag(3u)| */
#include	<prognamevar.hh>
#include	<stdintx.h>
#include	<strtox.h>		/* LIBU */
#include	<localmisc.h>		/* |MAXPATHLEN| */


/* local defines */


/* local namespaces */

using libu::cfdec ;			/* subroutine */
using libu::ctdec ;			/* subroutine */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

struct ltest {				/* <- taken from GNU GLIBC */
    cchar	*str ;			/* Convert this.  */
    ulong	expect ;		/* To get this.  */
    int		base ;			/* Use this base.  */
    char	left ;			/* With this left over.  */
    int		err ;			/* And this in errno. */
} ; /* end struct (ltest) */


/* forward references */

local int test(int,const ltest *) noex ;


/* local variables */

constexpr ltest		tests_signed[] = { /* <- taken from GNU GLIBC */
  /* First, signed numbers:  */
  /* simple... */
  {"123", 123, 0, 0, 0},
  {"+123", 123, 0, 0, 0},
  {"  123", 123, 0, 0, 0},
  {" 123 ", 123, 0, ' ', 0},
  {"   -17", ulong(-17), 0, 0, 0},

  /* implicit base... */
  {"0123", 0123, 0, 0, 0},
  {"0123a", 0123, 0, 'a', 0},
  {"01239", 0123, 0, '9', 0},
  {"0x123", 0x123, 0, 0, 0},
  {"-0x123", ulong(-0x123), 0, 0, 0},
  {"0x0xc", 0, 0, 'x', 0},
  {" +0x123fg", 0x123f, 0, 'g', 0},

  /* explicit base... */
  {"123", 0x123, 16, 0, 0},
  {"0x123", 0x123, 16, 0, 0},
  {"123", 0123, 8, 0, 0},
  {"0123", 0123, 8, 0, 0},
  {"0123", 123, 10, 0, 0},
  {"0x123", 0, 10, 'x', 0},

  /* case insensitivity... */
  {"abcd", 0xabcd, 16, 0, 0},
  {"AbCd", 0xabcd, 16, 0, 0},
  {"0xABCD", 0xabcd, 16, 0, 0},
  {"0Xabcd", 0xabcd, 16, 0, 0},

  /* odd bases... */
  {"0xyz", 33 * 35 + 34, 35, 'z', 0},
  {"yz!", 34 * 36 + 35, 36, '!', 0},
  {"-yz", ulong(-(34*36 + 35)), 36, 0, 0},
  {"GhI4", ((16*20 + 17)*20 + 18)*20 + 4, 20, 0, 0},

  /* extremes... */
  {"9223372036854775807", 9223372036854775807, 0, 0, 0},
  {"9223372036854775808", 9223372036854775807, 0, 0, ERANGE},
  {"922337203685477580777", 9223372036854775807, 0, 0, ERANGE},
  {"9223372036854775810", 9223372036854775807, 0, 0, ERANGE},
  {"-2147483648", ulong(-2147483648), 0, 0, 0},
  {"-9223372036854775808", 0x8000000000000000, 0, 0, 0},
  {"-9223372036854775809", 0x8000000000000000, 0, 0, ERANGE},
  {"0x112233445566778899z", 9223372036854775807, 16, 'z', ERANGE},
  {"0xFFFFFFFFFFFF00FF" , 9223372036854775807, 0, 0, ERANGE},

  {"111111111111111111111111111111111111111111111111111111111111111",
   9223372036854775807, 2, 0, 0},
  {"1000000000000000000000000000000000000000000000000000000000000000",
   9223372036854775807, 2, 0, ERANGE},
  {"2021110011022210012102010021220101220221",
   9223372036854775807, 3, 0, 0},
  {"2021110011022210012102010021220101220222",
   9223372036854775807, 3, 0, ERANGE},
  {"13333333333333333333333333333333", 9223372036854775807, 4, 0, 0},
  {"20000000000000000000000000000000", 9223372036854775807, 4, 0, ERANGE},
  {"1104332401304422434310311212", 9223372036854775807, 5, 0, 0},
  {"1104332401304422434310311213", 9223372036854775807, 5, 0, ERANGE},
  {"1540241003031030222122211", 9223372036854775807, 6, 0, 0},
  {"1540241003031030222122212", 9223372036854775807, 6, 0, ERANGE},
  {"22341010611245052052300", 9223372036854775807, 7, 0, 0},
  {"22341010611245052052301", 9223372036854775807, 7, 0, ERANGE},
  {"777777777777777777777", 9223372036854775807, 8, 0, 0},
  {"1000000000000000000000", 9223372036854775807, 8, 0, ERANGE},
  {"67404283172107811827", 9223372036854775807, 9, 0, 0},
  {"67404283172107811828", 9223372036854775807, 9, 0, ERANGE},
  {"9223372036854775807", 9223372036854775807, 10, 0, 0},
  {"9223372036854775808", 9223372036854775807, 10, 0, ERANGE},
  {"1728002635214590697", 9223372036854775807, 11, 0, 0},
  {"1728002635214590698", 9223372036854775807, 11, 0, ERANGE},
  {"41a792678515120367", 9223372036854775807, 12, 0, 0},
  {"41a792678515120368", 9223372036854775807, 12, 0, ERANGE},
  {"10b269549075433c37", 9223372036854775807, 13, 0, 0},
  {"10b269549075433c38", 9223372036854775807, 13, 0, ERANGE},
  {"4340724c6c71dc7a7", 9223372036854775807, 14, 0, 0},
  {"4340724c6c71dc7a8", 9223372036854775807, 14, 0, ERANGE},
  {"160e2ad3246366807", 9223372036854775807, 15, 0, 0},
  {"160e2ad3246366808", 9223372036854775807, 15, 0, ERANGE},
  {"7fffffffffffffff", 9223372036854775807, 16, 0, 0},
  {"8000000000000000", 9223372036854775807, 16, 0, ERANGE},
  {"33d3d8307b214008", 9223372036854775807, 17, 0, 0},
  {"33d3d8307b214009", 9223372036854775807, 17, 0, ERANGE},
  {"16agh595df825fa7", 9223372036854775807, 18, 0, 0},
  {"16agh595df825fa8", 9223372036854775807, 18, 0, ERANGE},
  {"ba643dci0ffeehh", 9223372036854775807, 19, 0, 0},
  {"ba643dci0ffeehi", 9223372036854775807, 19, 0, ERANGE},
  {"5cbfjia3fh26ja7", 9223372036854775807, 20, 0, 0},
  {"5cbfjia3fh26ja8", 9223372036854775807, 20, 0, ERANGE},
  {"2heiciiie82dh97", 9223372036854775807, 21, 0, 0},
  {"2heiciiie82dh98", 9223372036854775807, 21, 0, ERANGE},
  {"1adaibb21dckfa7", 9223372036854775807, 22, 0, 0},
  {"1adaibb21dckfa8", 9223372036854775807, 22, 0, ERANGE},
  {"i6k448cf4192c2", 9223372036854775807, 23, 0, 0},
  {"i6k448cf4192c3", 9223372036854775807, 23, 0, ERANGE},
  {"acd772jnc9l0l7", 9223372036854775807, 24, 0, 0},
  {"acd772jnc9l0l8", 9223372036854775807, 24, 0, ERANGE},
  {"64ie1focnn5g77", 9223372036854775807, 25, 0, 0},
  {"64ie1focnn5g78", 9223372036854775807, 25, 0, ERANGE},
  {"3igoecjbmca687", 9223372036854775807, 26, 0, 0},
  {"3igoecjbmca688", 9223372036854775807, 26, 0, ERANGE},
  {"27c48l5b37oaop", 9223372036854775807, 27, 0, 0},
  {"27c48l5b37oaoq", 9223372036854775807, 27, 0, ERANGE},
  {"1bk39f3ah3dmq7", 9223372036854775807, 28, 0, 0},
  {"1bk39f3ah3dmq8", 9223372036854775807, 28, 0, ERANGE},
  {"q1se8f0m04isb", 9223372036854775807, 29, 0, 0},
  {"q1se8f0m04isc", 9223372036854775807, 29, 0, ERANGE},
  {"hajppbc1fc207", 9223372036854775807, 30, 0, 0},
  {"hajppbc1fc208", 9223372036854775807, 30, 0, ERANGE},
  {"bm03i95hia437", 9223372036854775807, 31, 0, 0},
  {"bm03i95hia438", 9223372036854775807, 31, 0, ERANGE},
  {"7vvvvvvvvvvvv", 9223372036854775807, 32, 0, 0},
  {"8000000000000", 9223372036854775807, 32, 0, ERANGE},
  {"5hg4ck9jd4u37", 9223372036854775807, 33, 0, 0},
  {"5hg4ck9jd4u38", 9223372036854775807, 33, 0, ERANGE},
  {"3tdtk1v8j6tpp", 9223372036854775807, 34, 0, 0},
  {"3tdtk1v8j6tpq", 9223372036854775807, 34, 0, ERANGE},
  {"2pijmikexrxp7", 9223372036854775807, 35, 0, 0},
  {"2pijmikexrxp8", 9223372036854775807, 35, 0, ERANGE},
  {"1y2p0ij32e8e7", 9223372036854775807, 36, 0, 0},
  {"1y2p0ij32e8e8", 9223372036854775807, 36, 0, ERANGE},

  {"-1000000000000000000000000000000000000000000000000000000000000000",
   -9223372036854775808UL, 2, 0, 0},
  {"-1000000000000000000000000000000000000000000000000000000000000001",
   -9223372036854775808UL, 2, 0, ERANGE},
  {"-2021110011022210012102010021220101220222",
   -9223372036854775808UL, 3, 0, 0},
  {"-2021110011022210012102010021220101221000",
   -9223372036854775808UL, 3, 0, ERANGE},
  {"-20000000000000000000000000000000", -9223372036854775808UL, 4, 0, 0},
  {"-20000000000000000000000000000001", -9223372036854775808UL, 4, 0, ERANGE},
  {"-1104332401304422434310311213", -9223372036854775808UL, 5, 0, 0},
  {"-1104332401304422434310311214", -9223372036854775808UL, 5, 0, ERANGE},
  {"-1540241003031030222122212", -9223372036854775808UL, 6, 0, 0},
  {"-1540241003031030222122213", -9223372036854775808UL, 6, 0, ERANGE},
  {"-22341010611245052052301", -9223372036854775808UL, 7, 0, 0},
  {"-22341010611245052052302", -9223372036854775808UL, 7, 0, ERANGE},
  {"-1000000000000000000000", -9223372036854775808UL, 8, 0, 0},
  {"-1000000000000000000001", -9223372036854775808UL, 8, 0, ERANGE},
  {"-67404283172107811828", -9223372036854775808UL, 9, 0, 0},
  {"-67404283172107811830", -9223372036854775808UL, 9, 0, ERANGE},
  {"-9223372036854775808", -9223372036854775808UL, 10, 0, 0},
  {"-9223372036854775809", -9223372036854775808UL, 10, 0, ERANGE},
  {"-1728002635214590698", -9223372036854775808UL, 11, 0, 0},
  {"-1728002635214590699", -9223372036854775808UL, 11, 0, ERANGE},
  {"-41a792678515120368", -9223372036854775808UL, 12, 0, 0},
  {"-41a792678515120369", -9223372036854775808UL, 12, 0, ERANGE},
  {"-10b269549075433c38", -9223372036854775808UL, 13, 0, 0},
  {"-10b269549075433c39", -9223372036854775808UL, 13, 0, ERANGE},
  {"-4340724c6c71dc7a8", -9223372036854775808UL, 14, 0, 0},
  {"-4340724c6c71dc7a9", -9223372036854775808UL, 14, 0, ERANGE},
  {"-160e2ad3246366808", -9223372036854775808UL, 15, 0, 0},
  {"-160e2ad3246366809", -9223372036854775808UL, 15, 0, ERANGE},
  {"-8000000000000000", -9223372036854775808UL, 16, 0, 0},
  {"-8000000000000001", -9223372036854775808UL, 16, 0, ERANGE},
  {"-33d3d8307b214009", -9223372036854775808UL, 17, 0, 0},
  {"-33d3d8307b21400a", -9223372036854775808UL, 17, 0, ERANGE},
  {"-16agh595df825fa8", -9223372036854775808UL, 18, 0, 0},
  {"-16agh595df825fa9", -9223372036854775808UL, 18, 0, ERANGE},
  {"-ba643dci0ffeehi", -9223372036854775808UL, 19, 0, 0},
  {"-ba643dci0ffeei0", -9223372036854775808UL, 19, 0, ERANGE},
  {"-5cbfjia3fh26ja8", -9223372036854775808UL, 20, 0, 0},
  {"-5cbfjia3fh26ja9", -9223372036854775808UL, 20, 0, ERANGE},
  {"-2heiciiie82dh98", -9223372036854775808UL, 21, 0, 0},
  {"-2heiciiie82dh99", -9223372036854775808UL, 21, 0, ERANGE},
  {"-1adaibb21dckfa8", -9223372036854775808UL, 22, 0, 0},
  {"-1adaibb21dckfa9", -9223372036854775808UL, 22, 0, ERANGE},
  {"-i6k448cf4192c3", -9223372036854775808UL, 23, 0, 0},
  {"-i6k448cf4192c4", -9223372036854775808UL, 23, 0, ERANGE},
  {"-acd772jnc9l0l8", -9223372036854775808UL, 24, 0, 0},
  {"-acd772jnc9l0l9", -9223372036854775808UL, 24, 0, ERANGE},
  {"-64ie1focnn5g78", -9223372036854775808UL, 25, 0, 0},
  {"-64ie1focnn5g79", -9223372036854775808UL, 25, 0, ERANGE},
  {"-3igoecjbmca688", -9223372036854775808UL, 26, 0, 0},
  {"-3igoecjbmca689", -9223372036854775808UL, 26, 0, ERANGE},
  {"-27c48l5b37oaoq", -9223372036854775808UL, 27, 0, 0},
  {"-27c48l5b37oap0", -9223372036854775808UL, 27, 0, ERANGE},
  {"-1bk39f3ah3dmq8", -9223372036854775808UL, 28, 0, 0},
  {"-1bk39f3ah3dmq9", -9223372036854775808UL, 28, 0, ERANGE},
  {"-q1se8f0m04isc", -9223372036854775808UL, 29, 0, 0},
  {"-q1se8f0m04isd", -9223372036854775808UL, 29, 0, ERANGE},
  {"-hajppbc1fc208", -9223372036854775808UL, 30, 0, 0},
  {"-hajppbc1fc209", -9223372036854775808UL, 30, 0, ERANGE},
  {"-bm03i95hia438", -9223372036854775808UL, 31, 0, 0},
  {"-bm03i95hia439", -9223372036854775808UL, 31, 0, ERANGE},
  {"-8000000000000", -9223372036854775808UL, 32, 0, 0},
  {"-8000000000001", -9223372036854775808UL, 32, 0, ERANGE},
  {"-5hg4ck9jd4u38", -9223372036854775808UL, 33, 0, 0},
  {"-5hg4ck9jd4u39", -9223372036854775808UL, 33, 0, ERANGE},
  {"-3tdtk1v8j6tpq", -9223372036854775808UL, 34, 0, 0},
  {"-3tdtk1v8j6tpr", -9223372036854775808UL, 34, 0, ERANGE},
  {"-2pijmikexrxp8", -9223372036854775808UL, 35, 0, 0},
  {"-2pijmikexrxp9", -9223372036854775808UL, 35, 0, ERANGE},
  {"-1y2p0ij32e8e8", -9223372036854775808UL, 36, 0, 0},
  {"-1y2p0ij32e8e9", -9223372036854775808UL, 36, 0, ERANGE},
  {nullptr, 0, 0, 0, 0}
} ; /* end array (tests_signed) */

constexpr ltest		tests_unsigned[] = { /* <- taken from GNU GLIBC */
  /* Then unsigned.  */
  {"  0", 0, 0, 0, 0},
  {"0xffffffffg", 0xffffffff, 0, 'g', 0},
  {"0xffffffffffffffffg", 0xffffffffffffffff, 0, 'g', 0},
  {"-0xfedcba987654321", 0xf0123456789abcdf, 0, 0, 0},
  {"0xf1f2f3f4f5f6f7f8f9", 0xffffffffffffffff, 0, 0, ERANGE},
  {"-0x123456789abcdef01", 0xffffffffffffffff, 0, 0, ERANGE},

  {"1111111111111111111111111111111111111111111111111111111111111111",
   0xffffffffffffffff, 2, 0, 0},
  {"10000000000000000000000000000000000000000000000000000000000000000",
   0xffffffffffffffff, 2, 0, ERANGE},
  {"11112220022122120101211020120210210211220",
   0xffffffffffffffff, 3, 0, 0},
  {"11112220022122120101211020120210210211221",
   0xffffffffffffffff, 3, 0, ERANGE},
  {"33333333333333333333333333333333", 0xffffffffffffffff, 4, 0, 0},
  {"100000000000000000000000000000000", 0xffffffffffffffff, 4, 0, ERANGE},
  {"2214220303114400424121122430", 0xffffffffffffffff, 5, 0, 0},
  {"2214220303114400424121122431", 0xffffffffffffffff, 5, 0, ERANGE},
  {"3520522010102100444244423", 0xffffffffffffffff, 6, 0, 0},
  {"3520522010102100444244424", 0xffffffffffffffff, 6, 0, ERANGE},
  {"45012021522523134134601", 0xffffffffffffffff, 7, 0, 0},
  {"45012021522523134134602", 0xffffffffffffffff, 7, 0, ERANGE},
  {"1777777777777777777777", 0xffffffffffffffff, 8, 0, 0},
  {"2000000000000000000000", 0xffffffffffffffff, 8, 0, ERANGE},
  {"145808576354216723756", 0xffffffffffffffff, 9, 0, 0},
  {"145808576354216723757", 0xffffffffffffffff, 9, 0, ERANGE},
  {"18446744073709551615", 0xffffffffffffffff, 10, 0, 0},
  {"18446744073709551616", 0xffffffffffffffff, 10, 0, ERANGE},
  {"335500516a429071284", 0xffffffffffffffff, 11, 0, 0},
  {"335500516a429071285", 0xffffffffffffffff, 11, 0, ERANGE},
  {"839365134a2a240713", 0xffffffffffffffff, 12, 0, 0},
  {"839365134a2a240714", 0xffffffffffffffff, 12, 0, ERANGE},
  {"219505a9511a867b72", 0xffffffffffffffff, 13, 0, 0},
  {"219505a9511a867b73", 0xffffffffffffffff, 13, 0, ERANGE},
  {"8681049adb03db171", 0xffffffffffffffff, 14, 0, 0},
  {"8681049adb03db172", 0xffffffffffffffff, 14, 0, ERANGE},
  {"2c1d56b648c6cd110", 0xffffffffffffffff, 15, 0, 0},
  {"2c1d56b648c6cd111", 0xffffffffffffffff, 15, 0, ERANGE},
  {"ffffffffffffffff", 0xffffffffffffffff, 16, 0, 0},
  {"10000000000000000", 0xffffffffffffffff, 16, 0, ERANGE},
  {"67979g60f5428010", 0xffffffffffffffff, 17, 0, 0},
  {"67979g60f5428011", 0xffffffffffffffff, 17, 0, ERANGE},
  {"2d3fgb0b9cg4bd2f", 0xffffffffffffffff, 18, 0, 0},
  {"2d3fgb0b9cg4bd2g", 0xffffffffffffffff, 18, 0, ERANGE},
  {"141c8786h1ccaagg", 0xffffffffffffffff, 19, 0, 0},
  {"141c8786h1ccaagh", 0xffffffffffffffff, 19, 0, ERANGE},
  {"b53bjh07be4dj0f", 0xffffffffffffffff, 20, 0, 0},
  {"b53bjh07be4dj0g", 0xffffffffffffffff, 20, 0, ERANGE},
  {"5e8g4ggg7g56dif", 0xffffffffffffffff, 21, 0, 0},
  {"5e8g4ggg7g56dig", 0xffffffffffffffff, 21, 0, ERANGE},
  {"2l4lf104353j8kf", 0xffffffffffffffff, 22, 0, 0},
  {"2l4lf104353j8kg", 0xffffffffffffffff, 22, 0, ERANGE},
  {"1ddh88h2782i515", 0xffffffffffffffff, 23, 0, 0},
  {"1ddh88h2782i516", 0xffffffffffffffff, 23, 0, ERANGE},
  {"l12ee5fn0ji1if", 0xffffffffffffffff, 24, 0, 0},
  {"l12ee5fn0ji1ig", 0xffffffffffffffff, 24, 0, ERANGE},
  {"c9c336o0mlb7ef", 0xffffffffffffffff, 25, 0, 0},
  {"c9c336o0mlb7eg", 0xffffffffffffffff, 25, 0, ERANGE},
  {"7b7n2pcniokcgf", 0xffffffffffffffff, 26, 0, 0},
  {"7b7n2pcniokcgg", 0xffffffffffffffff, 26, 0, ERANGE},
  {"4eo8hfam6fllmo", 0xffffffffffffffff, 27, 0, 0},
  {"4eo8hfam6fllmp", 0xffffffffffffffff, 27, 0, ERANGE},
  {"2nc6j26l66rhof", 0xffffffffffffffff, 28, 0, 0},
  {"2nc6j26l66rhog", 0xffffffffffffffff, 28, 0, ERANGE},
  {"1n3rsh11f098rn", 0xffffffffffffffff, 29, 0, 0},
  {"1n3rsh11f098ro", 0xffffffffffffffff, 29, 0, ERANGE},
  {"14l9lkmo30o40f", 0xffffffffffffffff, 30, 0, 0},
  {"14l9lkmo30o40g", 0xffffffffffffffff, 30, 0, ERANGE},
  {"nd075ib45k86f", 0xffffffffffffffff, 31, 0, 0},
  {"nd075ib45k86g", 0xffffffffffffffff, 31, 0, ERANGE},
  {"fvvvvvvvvvvvv", 0xffffffffffffffff, 32, 0, 0},
  {"g000000000000", 0xffffffffffffffff, 32, 0, ERANGE},
  {"b1w8p7j5q9r6f", 0xffffffffffffffff, 33, 0, 0},
  {"b1w8p7j5q9r6g", 0xffffffffffffffff, 33, 0, ERANGE},
  {"7orp63sh4dphh", 0xffffffffffffffff, 34, 0, 0},
  {"7orp63sh4dphi", 0xffffffffffffffff, 34, 0, ERANGE},
  {"5g24a25twkwff", 0xffffffffffffffff, 35, 0, 0},
  {"5g24a25twkwfg", 0xffffffffffffffff, 35, 0, ERANGE},
  {"3w5e11264sgsf", 0xffffffffffffffff, 36, 0, 0},
  {"3w5e11264sgsg", 0xffffffffffffffff, 36, 0, ERANGE},
  {nullptr, 0, 0, 0, 0},
} ; /* end arrat (tests_unsigned) */

constexpr int		llen = LINEBUFLEN ;


/* exported variables */


/* exported subroutines */

int main(int argc,con mainv argv,con mainv envv) {
    	prognamevar	progname(argc,argv,envv) ;
	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	int		c = 0 ;
	printf("%s\n",ccp(progname)) ;
	for (int w = 0 ; w < 2 ; ++w) {
	    const ltest	*tests ;
	    printf("test-suite %d\n",w) ;
	    switch (w) {
	    case 0:
		tests = tests_signed ;
		break ;
	    case 1:
		tests = tests_unsigned ;
		break ;
	    } /* end witch */
	    for (int i = 0 ; tests[i].str ; ++i) {
		const ltest *ep = (tests + i) ;
	        rs = test(w,ep) ;
	        c += 1 ;
	        if (rs < 0) break ;
	    } /* end for */
	    if (rs < 0) break ;
	} /* end for */
	printf("%s: tests rs=%d c=%d\n",ccp(progname),rs,c) ;
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */

#ifdef	COMMENT
    cchar	*str ;			/* Convert this.  */
    ulong	expect ;		/* To get this.  */
    int		base ;			/* Use this base.  */
    char	left ;			/* With this left over.  */
    int		err ;			/* And this in errno. */
#endif /* COMMENT */

local int test(int w,const ltest *ep) noex {
    	cnothrow	nt{} ;
	int		rs = SR_OK ;
	if (ep && ep->str) {
	    rs = SR_NOMEM ;
	    if (char *lbuf = new(nt)  char [llen + 1] ; lbuf) {
    	    cchar	*str = ep->str ;
	    ulong	expect = ep->expect ;
	    int		base = ep->base ;
	    int		err{} ;
	    rs = SR_OK ;
	    errno = 0 ;
	    switch (w) {
	    case 0: /* signed */
		if (rs >= 0) {
    	            long res = strtoxl(str,nullptr,base) ;
    	            if (errno == 0) {
		        if (res != long(expect)) {
			    if ((rs = ctdec(lbuf,llen,expect)) >= 0) {
			        printf("failure strtoxl\n") ;
			        printf("failure expect=%016lX\n",expect) ;
			        printf("failure    got=%016lX\n",res) ;
			        printf("failure expect=%ld\n",expect) ;
			        printf("failure éxpect=%s\n",lbuf) ;
			        printf("failure    got=%ld\n",res) ;
			        rs = SR_NOMSG ;
			    } /* end if (ctdec) */
		        }
	            }  /* end if */
		} /* end if (signed-l) */
		if (rs >= 0) {
		    longlong resll = strtoxll(str,nullptr,base) ;
		    if (errno == 0) {
		        long res = long(resll) ;
		        if (res != long(expect)) {
			    printf("failure strtoxll\n") ;
			    printf("failure expect=%016lX\n",expect) ;
			    printf("failure    got=%016lX\n",res) ;
			    printf("failure expect=%ld\n",expect) ;
			    printf("failure    got=%ld\n",res) ;
			    rs = SR_NOMSG ;
		        }
	            }  /* end if */
		} /* end if (signed-ll) */
		break ;
	    case 1: /* un-signed */
		if (rs >= 0) {
    	            long res = strtoxul(str,nullptr,base) ;
    	            if (errno == 0) {
		        if (res != long(expect)) {
			    if ((rs = ctdec(lbuf,llen,expect)) >= 0) {
			        printf("failure strtoxl\n") ;
			        printf("failure expect=%016lX\n",expect) ;
			        printf("failure    got=%016lX\n",res) ;
			        printf("failure expect=%ld\n",expect) ;
			        printf("failure éxpect=%s\n",lbuf) ;
			        printf("failure    got=%ld\n",res) ;
			        rs = SR_NOMSG ;
			    } /* end if (ctdec) */
		        }
	            }  /* end if */
		} /* end if (signed-l) */
		if (rs >= 0) {
		    longlong resll = strtoxull(str,nullptr,base) ;
		    if (errno == 0) {
		        long res = long(resll) ;
		        if (res != long(expect)) {
			    printf("failure strtoxll\n") ;
			    printf("failure expect=%016lX\n",expect) ;
			    printf("failure    got=%016lX\n",res) ;
			    printf("failure expect=%ld\n",expect) ;
			    printf("failure    got=%ld\n",res) ;
			    rs = SR_NOMSG ;
		        }
	            }  /* end if */
		} /* end if (signed-ll) */
		break ;
	    default:
		printf("invalid suite %d\n",w) ;
		rs = SR_NOTSUP ;
		break ;
	    } /* end switch */
	    if ((rs >= 0) && errno) {
	        if ((err = ep->err) == errno) {
		    rs = SR_OK ;
	        } else {
	            rs = (- errno) ;
	        }
	    } /* end if */
	    if (rs < 0) {
	        printf("failure rs=%d err=%d\n",rs,err) ;
	        printf("failure str=>%s<\n",str) ;
		if (err) {
	            printf("failure errno=>%s<\n",strerror(err)) ;
		}
	    } /* end if (error) */
	    delete [] lbuf ;
	    } /* end if (m-a-f) */
	} /* end if (non-null) */
	return rs ;
} /* end subroutine (test) */


