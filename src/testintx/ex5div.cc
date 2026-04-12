/* ex5div SUPPORT */


/* Found in lib/math/div64.c */

u64 mul_u64_u64_div64(u64 a, u64 b, u64 c)
{
	u64 res, x, y, z;

	/* * The operation is (a * b) / c 
	 * Since (a * b) can result in 128 bits, we split it.
	 */
	if ((((a | b) >> 32) == 0)) {
		/* Optimization: If both are 32-bit, it's a simple 64-bit div */
		res = a * b;
		do_div(res, c);
		return res;
	}

	/* * This handles the 128-bit intermediate product 
	 * It uses the 'long long' __int128 type where supported by the compiler
	 */
#ifdef __SIZEOF_INT128__
	{
		unsigned __int128 ml = (unsigned __int128)a * b;
		return (u64)(ml / c);
	}
#else
	/* * Fallback for architectures without 128-bit integer support.
	 * This involves bit-shifting and manual long division.
	 */
	return manual_div128_64(a, b, c);
#endif
} /* end subroutine (mul_u64_u64_div64) */


