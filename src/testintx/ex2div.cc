/* ex2div */

/****

  Bit-by-bit long division.

****/

typedef unsigned int UTItype __attribute__ ((mode (TI)));

UTItype __udivmodti4 (UTItype nn, UTItype dd, UTItype *rp) {
  // If the divisor is 0, this usually triggers a hardware exception
  // or a specific error handler.
  UTItype q = 0;
  if (dd) {
    UTItype r = 0;
    // Standard bit-by-bit long division algorithm
    // This loop runs for each bit in the 128-bit numerator
    for (int i = 127; i >= 0; i--) {
        r <<= 1;          // Shift remainder left
        r |= (nn >> i) & 1; // Pull down the next bit of the numerator
        if (r >= dd) {    // If current remainder is greater than divisor
	    r -= dd;      // Subtract divisor from remainder
	    q |= ((UTItype)1 << i); // Set the corresponding bit in quotient
	}
    } /* end for */
    // If a pointer was provided, return the remainder
    if (rp) {
      *rp = r;
    }
  } /* end if (non-zero divisor) */
  return q; // Return the quotient
} /* end subroutine */


