/*
Owner: Uri Naor
Date: Feb, 10 2024
*/

#define BITS_IN_BYTE 8
#define NIBBLE 4
#define BITARR_LENGTH_BITS 64

#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

typedef size_t bitarr_t;

/* each number represents bits that are set in the corresponding cell number
for example num 5 is 0101, has two set bits so LUT[5] has 2 set bits. */
static size_t CountLUT[16] = {0, 1, 1, 2, 1, 2, 2, 3,1, 2, 2, 3, 2, 3, 3, 4};
/* each number represents a nibble mirror image of the corresponding cell number
for example num 5 is 0101, so it is equals to 10. 10 because is 1010. */
static bitarr_t MirrorLUT[16] = {0, 8, 4, 12, 2, 10, 6, 14,
 1, 9, 5, 13, 3, 11, 7, 15};

/******************** FUNCTIONS ********************/
bitarr_t BitArrSetAll(bitarr_t arr)
{
	(void)arr;
	
	return (~(bitarr_t)0x0000000000000000);
}

bitarr_t BitArrResetAll(bitarr_t arr)
{
	(void)arr;	
	
	return ((bitarr_t)0x0000000000000000);
}

bitarr_t BitArrSetOff(bitarr_t arr, size_t idx)
{
	assert(idx < BITARR_LENGTH_BITS);
	
	return (arr & (~((bitarr_t)0x0000000000000001 << idx)));
}

bitarr_t BitArrSetOn(bitarr_t arr, size_t idx)
{
	assert(idx < BITARR_LENGTH_BITS);
		
	return (arr | ((bitarr_t)0x0000000000000001 << idx));
}

bitarr_t BitArrSetBit(bitarr_t arr, size_t idx, int value)
{

	assert(idx < BITARR_LENGTH_BITS);	
	
	if (value != 0)
	{
		return BitArrSetOn(arr, idx);
	}
	
	return BitArrSetOff(arr, idx);
}

int BitArrGetBit(bitarr_t arr, size_t idx)
{
	bitarr_t mask = 0x0000000000000001;
	
	assert(idx < BITARR_LENGTH_BITS);
	
	arr = arr >> idx;
	
	return arr & mask;
}

bitarr_t BitArrFlipBit(bitarr_t arr, size_t idx)
{
	assert(idx < BITARR_LENGTH_BITS);

	/* Optimized using XOR bitwise operator to flip the bit without branching. 
	   XORing a bit with 1 flips it, XORing with 0 leaves it unchanged. */
	return (arr ^ ((bitarr_t)0x0000000000000001 << idx));
}

bitarr_t BitArrMirror(bitarr_t arr)
{
	arr = (((arr & 0xFFFFFFFF00000000) >> (BITARR_LENGTH_BITS / 2)) |
	 	   ((arr & 0x00000000FFFFFFFF) << (BITARR_LENGTH_BITS / 2)));
	arr = (((arr & 0xFFFF0000FFFF0000) >> (BITARR_LENGTH_BITS / 4)) |
	 	   ((arr & 0x0000FFFF0000FFFF) << (BITARR_LENGTH_BITS / 4)));
	arr = (((arr & 0xFF00FF00FF00FF00) >> (BITARR_LENGTH_BITS / 8)) |
	       ((arr & 0x00FF00FF00FF00FF) << (BITARR_LENGTH_BITS / 8)));
	arr = (((arr & 0xF0F0F0F0F0F0F0F0) >> (BITARR_LENGTH_BITS / 16)) |
	       ((arr & 0x0F0F0F0F0F0F0F0F) << (BITARR_LENGTH_BITS / 16)));
	arr = (((arr & 0xCCCCCCCCCCCCCCCC) >> (BITARR_LENGTH_BITS / 32)) |
	       ((arr & 0x3333333333333333) << (BITARR_LENGTH_BITS / 32)));
	arr = (((arr & 0xAAAAAAAAAAAAAAAA) >> (BITARR_LENGTH_BITS / 64)) |
	       ((arr & 0x5555555555555555) << (BITARR_LENGTH_BITS / 64)));
	
	return arr;
}

bitarr_t BitArrRotateRight(bitarr_t arr, size_t n)
{
	n = n % BITARR_LENGTH_BITS;
	
	/* Added check for n == 0. Shifting by BITARR_LENGTH_BITS (64) is 
	   Undefined Behavior in C, which happens if n % 64 == 0. */
	if (0 == n)
	{
		return arr;
	}
	
	return ((arr >> n) | (arr << (BITARR_LENGTH_BITS - n)));
}

bitarr_t BitArrRotateLeft(bitarr_t arr, size_t n)
{
	n = n % BITARR_LENGTH_BITS;
	
	/* Added check for n == 0 to prevent Undefined Behavior when shifting by 64. */
	if (0 == n)
	{
		return arr;
	}
	
	return ((arr << n) | (arr >> (BITARR_LENGTH_BITS - n)));
}

size_t BitArrCountOn(bitarr_t arr)
{
	arr = ((arr >>  (BITARR_LENGTH_BITS / 64)) & 0x5555555555555555) + 
		   (arr & 0x5555555555555555);
	arr = ((arr >>  (BITARR_LENGTH_BITS / 32)) & 0x3333333333333333) + 
		   (arr & 0x3333333333333333);
	arr = ((arr >>  (BITARR_LENGTH_BITS / 16)) & 0x0F0F0F0F0F0F0F0F) + 
		   (arr & 0x0F0F0F0F0F0F0F0F);
	arr = ((arr >>  (BITARR_LENGTH_BITS / 8)) & 0x00FF00FF00FF00FF) + 
		   (arr & 0x00FF00FF00FF00FF);
	arr = ((arr >> (BITARR_LENGTH_BITS / 4)) & 0x0000FFFF0000FFFF) + 
		   (arr & 0x0000FFFF0000FFFF);
	arr = ((arr >> (BITARR_LENGTH_BITS / 2)) & 0x00000000FFFFFFFF) + 
		   (arr & 0x00000000FFFFFFFF);
	
	return arr;
}

size_t BitArrCountOff(bitarr_t arr)
{
	return (BITARR_LENGTH_BITS - BitArrCountOn(arr));
}

char *BitArrToString(bitarr_t arr, char *buffer)
{
	int i = BITARR_LENGTH_BITS - 1;
	
	assert(buffer);
	
	for (i = BITARR_LENGTH_BITS - 1; i >= 0; i--)
	{
		if(1 == (arr & 1))
		{
			buffer[i] = '1';
		}
		else
		{
			buffer[i] = '0';
		}
		
		arr = arr >> 1;
	}
	
	buffer[BITARR_LENGTH_BITS] = '\0';
	
	/* Removed the printf statement to prevent unexpected side effects 
	   when a user just wants to populate the string buffer. */
	
	return buffer;
}

bitarr_t BitArrMirrorLut(bitarr_t arr)
{
	size_t mirrored_arr = 0;
	int i = 0;
	for (i = 0; i < BITARR_LENGTH_BITS / NIBBLE; i++)
	{
		mirrored_arr = mirrored_arr << NIBBLE;
		mirrored_arr = mirrored_arr | MirrorLUT[arr & 0x000000000000000F];
		arr = arr >> NIBBLE;
	}
	
	return mirrored_arr;
}

size_t BitArrCountOnLut(bitarr_t arr)
{
	size_t count = 0;
	
	while(0 != arr)
	{
		count = count + CountLUT[arr & 0x000000000000000F];
		arr = arr >> NIBBLE;
	}
	
	return count;
}
