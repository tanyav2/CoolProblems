#include <stdint.h>
#include <stdio.h>

/**
 * Struct that stores a 128-bit
 * unsigned number in two parts
 * The low bits are the 64 least significant bits.
 * The high bits are the 64 most significant bits.
 */
typedef struct uint128 {
        uint64_t low;
        uint64_t high;
} uint128;

/**
 * This struct is similar to the struct 
 * described above. It stores a 256-bit
 * unsigned number in two parts.
 */
typedef struct uint256 {
	uint128 low;
	uint128 high;
} uint256;

/** 
 * This is a helper struct
 * to store the sum and carry 
 * when adding two uint128 numbers
 */
typedef struct add_uint128 {
	uint128 sum;
	int carry;
} add_uint128;

/**
 * This is a helper function to multiply
 * two uint64_t numbers
 */
uint128 mult_64(uint64_t x, uint64_t y) {
	// step 1: split into two
	uint64_t x_low = x & 0xFFFFFFFF;
	uint64_t y_low = y & 0xFFFFFFFF;
	uint64_t x_hi = (uint64_t)((x & 0xFFFFFFFF00000000) >> 32);
	uint64_t y_hi = (uint64_t)((y & 0xFFFFFFFF00000000) >> 32);

	uint64_t low = x_low * y_low;
	uint64_t hi = x_hi * y_hi;
	uint64_t mid1 = x_low * y_hi;
	uint64_t mid2 = y_low * x_hi;
	uint64_t mid = mid1 + mid2;
	uint64_t overflow;
	// check for overflow
	int flag_for_mid = 0;
	if (__builtin_add_overflow(mid1, mid2, &overflow)) {
		flag_for_mid = 1;
	}

	// multiply mid by 2**32
	uint64_t mid_low = mid << 32;
	uint64_t mid_hi = (mid & 0xFFFFFFFF00000000) >> 32;

	// check for overflow with mid + low
	int flag_for_low = 0;
	uint64_t overflow2;

	if (__builtin_add_overflow(mid_low, low, &overflow2)) {
		flag_for_low = 1;
	}	

	low = low + mid_low;

	// add all the overflows to high
	uint128 prod;
	prod.low = low;
	if (flag_for_mid) {
		mid_hi = mid_hi | (1ULL << 32);
	}
	if (flag_for_low) {
		hi += 1;
	}
	prod.high = hi + mid_hi;
	return prod;
}

/**
 * This is a helper function that 
 * adds two uint128 numbers and returns the 
 * sum and overflow bit (if any overflow occurs)
 */
add_uint128 add_128(uint128 x, uint128 y) {
	add_uint128 result;

	// add the low 64 bits
	result.sum.low = x.low + y.low;

	// check if this addition overflowed
	uint64_t temp = 0;
	int low_of = 0;
	if (__builtin_add_overflow(x.low, y.low, &temp)) {
		low_of = 1;
	}

	// now add higher bits
	result.sum.high = x.high + y.high;
	
	// check for overflow
	int high_of = 0;
	if (__builtin_add_overflow(x.high, y.high, &temp)) {
		high_of = 1;
	}

	// now add the low overflow to the high bits
	if (low_of) {
		if (__builtin_add_overflow(result.sum.high, 1ULL, &temp)) {
			high_of = 1;
		}
		result.sum.high += 1ULL;
	}

	if (high_of) {
		result.carry = 1;
	} else {
		result.carry = 0;
	}
	return result;
}


/**
 * This is the desired function that
 * multiplies two 128 bit unsigned numbers
 * and returns a 256 bit number
 */
uint256 mult_128(uint128 x, uint128 y) {
	uint128 low, hi, mid1, mid2;
	low = mult_64(x.low, y.low);
	hi = mult_64(x.high, y.high);
	mid1 = mult_64(x.low, y.high);
	mid2 = mult_64(x.high, y.low);
	add_uint128 mid = add_128(mid1, mid2);
	
	uint128 mid_low = {0, mid.sum.low};
	uint128 mid_high = {mid.sum.high, 0}; 

	// check for overflow with low and mid_low
	add_uint128 new_low = add_128(low, mid_low);
	
	// add all the overflows to high
	uint256 prod;
	prod.low = new_low.sum;
	if (mid.carry) {
		mid_high.high = 1;
	}
	if (new_low.carry) {
		uint128 one = {1, 0};
		add_uint128 temp = add_128(hi, one);
		hi = temp.sum;
	}
	add_uint128 temp = add_128(hi, mid_high);
	prod.high = temp.sum;

	printf("prod.low.low: %llu\n", prod.low.low);
	printf("prod.low.high: %llu\n", prod.low.high);
	printf("prod.high.low: %llu\n", prod.high.low);
	printf("prod.high.high: %llu\n", prod.high.high);

	return prod;
}

int main() {
	uint128 x = {8007526156730973804, 14862546890568808411};
	uint128 y = {5318592275759306797, 9932520760147935039};
	uint256 result = mult_128(x, y);
	return 0;
}
	
