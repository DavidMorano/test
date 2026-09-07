/* main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test the DSTR object */
/* version %I% last-modified %G% */


/* exported variables */


/* exported subroutines */

int main(int,con mainv,con mainv) {
	DSTR	a ;
	DSTR	b ;
	dstr_start(&a,"here",-1) ;
	dstr_start(&a,NULL,0) ;

	dstr_assign(&b,&a) ;

	dstr_finish(&a) ;
	dstr_finish(&b) ;
} /* end subroutine (main) */


