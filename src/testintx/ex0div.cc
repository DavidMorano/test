/* ex0div */


/*******************************************************************************

	Name:
	ex0div

	Description:
	This provides a 32-bit ÷ 32-bit division.
	This uses only a fundamental 16÷8 division operator.

*******************************************************************************/


#include <climits>
#include <cstring>

import bitmanip ;


typedef unsigned char  uchar;
typedef unsigned short ushort;

constexpr int	chlim = (UCHAR_MAX+1) ;


#ifdef	COMMENT
local int cmp(con uchar *a,con uchar *b,int n) {
    for (int i = n - 1 ; i >= 0 ; --i) {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return +1;
    }
    return 0;
} /* end subroutine */
#endif /* COMMENT */

/*
 * Compare n-byte unsigned values
 * arrays are little-endian externally,
 * but comparison here is done high-byte first.
 */
local int vcmp(int n,con uchar *a,con uchar *b) {
    int rc = 0 ;
    for (int i = (n-1) ; i >= 0 ; --i) {
	if (a[i] != b[i]) {
	    rc = (a[i] > b[i]) ? +1 : -1 ;
	    break ;
	}
    } /* end for */
    return rc ;
} /* end subroutine */

template<typename Dig> constexpr void vclear(int n,mut Dig *v) noex {
	for (int i = 0 ; i < n ; i += 1) {
	    v[i] = 0 ;
	}
} /* end subroutine (vclear) */

template<typename Dig> constexpr void vcopy(int n,mut Dig *r,con Dig *v) noex {
	for (int i = 0 ; i < n ; i += 1) {
	    r[i] = v[i] ;
	}
} /* end subroutine (vcopy) */

/*
 * a := a - b   over n bytes
 * little-endian
 */
local int vsub(int n,mut uchar *a,con uchar *b) {
    int borrow = 0 ;
    for (int i = 0 ; i < n ; ++i) {
        int t = int(a[i]) - int(b[i]) - borrow ;
        if (t < 0) {
            t += chlim ;
            borrow = 1 ;
        } else {
            borrow = 0 ;
	}
        a[i] = uchar(t) ;
    } /* end for */
    return borrow ;
} /* end subroutine (vsub) */

/* how many non-zero digits are in a divisor-array, on the low end */
export {
    template<typename TA> constexpr int nsigdig(int n,con TA *d) noex {
    	int c = 0 ;
    	for (int i = (n - 1) ; i >= 0 ; --i) {
	    if (d[i]) {
		c = (i + 1) ;
		break ;
	    }
	} /* end for */
    	return c ;
    } /* end subroutine-template (nsigdig) */
} /* end export */

/*
 * Multiply 4-byte divisor by one byte q
 * result = 5-byte product
 * little-endian
 */
local void mul_byte(mut uchar *temp,con uchar *divisor,uchar q) {
    int carry = 0;
    for (int i = 0 ; i < 4 ; ++i) {
        int t = divisor[i] * q + carry ;
        temp[i] = uchar(t & UCHAR_MAX) ;
        carry = t >> CHAR_BIT ;
    } /* end for */
    temp[4] = uchar(carry) ;
} /* end subroutine */

/*
 * Shift left by one byte:
 * multiply by 256
 * little-endian means move upward
 */
local void shift_left(mut uchar *x,int n) {
    for (int i = (n-1) ; i > 0 ; --i) {
        x[i] = x[i-1] ;
    } /* end for */
    x[0] = 0 ;
} /* end subroutine */

/*
 * + Divide 8-byte dividend by 4-byte divisor
 * + all arrays little-endian
   + n= number-of-dividend (and quotient) digits
 */
/*
   template<typename T2,typename T1>
*/
n = 8 ;
void vdiv(int n,mut uchar *quotient,mut uchar *remainder,
         con uchar *dividend,con uchar *divisor) {
    cint	nb = nbits<uchar>
    cint	nh = (n/2) ;
    uchar rem[nh+2] ;
    uchar prod[nh+2] ;
    vclear(n,quotient) ;
    vcopy(nh,rem,dividend) ;
    rem[nh+0] = 0 ;
    rem[nh+1] = 0 ;
    /* * Process from most-significant dividend byte downward */
    for (int i = (n-1) ; i >= 0 ; --i) {
        shift_left(rem,(nh+1)) ;
        rem[nh-1] = dividend[i] ;
        /* * Estimate quotient digit from top two bytes */
        ushort top = (ushort(rem[nh]) << nb) | rem[nh-1] ;
        uchar q = uchar(top / divisor[nh-1]) ;
        /* * Correct estimate downward if needed */
        forever {
            mul_byte(prod,divisor,q) ;
            if (vcmp((nh+1),rem,prod) >= 0) break ;
            q -= 1 ;
        } /* end forever */
        quotient[i] = q ;
        /* mul_byte(prod,divisor,q); */
        vsub((nh+1),rem,prod) ;
    } /* end for */
    /* * final remainder: low 4 bytes */
    for (int i = 0 ; i < nh ; ++i) {
        remainder[i] = rem[i] ;
    }
} /* end subroutine (div) */


