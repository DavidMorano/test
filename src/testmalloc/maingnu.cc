/* maingnu */
/* lang=C++20 */


/*******************************************************************************

	This is a test of why the GNU compiler (g++) fails under
	certain circumstances.  This failure was found under both
	GCC-12 and GCC-13 versions.  Amazingly (but rather expected
	when dealing with people who do not know how to debug
	properly) the GNU compiler fails on certain combinations
	of using the C-language header |stdlib.h| when also using
	a compilation environment pre-processor define named
	_XOPEN_SOURCE!

	Apparently under certain values of the pre-processor define
	named _XOPEN_SOURCE, the GNU compiler (at least the versions
	above) fail with an incredibly weird error-message saying
	tha it (the compiler) does not have the symbol |aligned_allocation|
	(or some such weirdo name) in scope in the outermost scope
	of the compilation.

	This small test program was used to figure out how to make
	the GNU compilers to work properly.

	Also during testing (amazingly again!), the Apple-Clang
	compiler fails to regconize the C-langiage type of |
	ucontext_t| unless the compilation environment pre-processor
	define named _XOPEN_SOURCE is defined (instantiated)! Yes,
	we live in a very complicated world, indeed. But why is it
	that I (yes, why I) have to find these incredibly weirdo
	bugs in these very complicated source-generation-systems
	(SGSs)? Why cannot some other people, including the people
	who support these various tools and libraries, find these bugs
	instead? That is the eternal question.


*******************************************************************************/

#include	<envstandards.h>
#include	<sys/types.h>
#include	<ucontext.h>
#include	<stdlib.h>
#include	<stdio.h>


/* local defines */
#define	AMOUNT	100


int main(int,const char **,const char **) {
	char	*p = (char *) malloc(AMOUNT) ;
	free(p) ;
	return 0 ;
}
/* end subroutine (main) */


