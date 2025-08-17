/* main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */


#include	<envstandards.h>	/* must be ordered first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<iostream>
#include	<math.h>
#include	<usystem.h>
#include	<exitcodes.h>
#include	<localmisc.h>


/* forward refernces */

local double	sum_sin(double,double) noex ;


/* local variables */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv argv) {
	double	y, x ;
	double	pi = 4.0 * atan(1) ;
	double	inc = 0.01 ;
	double	lower, upper ;
	double	sum ;
	double	avg, avg1, avg2 ;
	double	period ;
	double	factor ;
	int	rs = SR_OK ;

	std::cout << "pi=" << pi << "\n" ;

	sum = sum_sin(0.0,pi) ;
	period = (pi - 0.0) ;
	avg = sum / period ;
	avg1 = avg ;
	std::cout << "sum=" << sum << "\n" ;
	std::cout << "avg=" << avg << "\n" ;

	lower = pi / 3.0 ;
	upper = lower * 2.0 ;
	sum = sum_sin(lower,upper) ;
	period = (upper - lower) ;
	avg = sum / period ;
	avg2 = avg ;
	std::cout << "sum=" << sum << "\n" ;
	std::cout << "avg=" << avg << "\n" ;

	factor = avg2 / avg1 ;
	std::cout << "fac=" << factor << "\n" ;

	return EX_OK ;
}
/* end subroutine (main) */


/* local subroutines */

local double sum_sin(double lower,double upper) noex {
	double	x, y ;
	double	inc = 0.01 ;
	double	sum = 0.0 ; /* return-value */
	for (x = lower ; x < upper ; x += inc) {
		y = sin(x) ;
		sum += (y * inc) ;
	} /* end for */
	return sum ;
}
/* end subroutine (sum_sin) */


