/* ex6div SUPPORT */


/* Logic representing the 'slow path' for 128-bit division */
u64 div128_u64(u64 hl, u64 ll, u64 divisor)
{
	u64 high = hl;
	u64 low = ll;
	u64 quot = 0;
	int i;

	/* If high part is 0, just use standard 64-bit div */
	if (high == 0)
		return low / divisor;

	/* * Loop through each of the 64 bits of the dividend.
	 * This is the classic "Restoring Division" algorithm.
	 */
	for (i = 0; i < 64; i++) {
		u64 mask = (int64_t)high >> 63;
		high = (high << 1) | (low >> 63);
		low <<= 1;
		if ((high | mask) >= divisor) {
			high -= divisor;
			quot |= 1ULL << (63 - i);
		}
	} /* end for */
	return quot;
} /* end subroutine (div128_u64) */


