#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
	puts("This is the C++ pointer koan.");
	puts("Meant to practice pointer arithmetic");
	puts("It simply uses assert on a known data structure, and you fill in the rest");

	// Start with operations on an unsigned char - where a char is 1 byte
	unsigned char originalPointer[256];
	for (int i = 0; i < 256; i++)
		originalPointer[i] = i;

	unsigned char *p = originalPointer;

	assert(p[0] == 0);
	assert(*p == 0);

	p = p + 3;
	assert(*p == 3); /* FIXED */

	unsigned char a = *p++;
	assert(a == 3); /* FIXED */
	assert(*p == 4); /* FIXED */

	unsigned char b = *(p++);
	assert(b == 4); /* FIXED */
	assert(*p == 5); /* FIXED */

	// Would love to deal with the 'endianness' of the memory.
	// Not sure I can
	unsigned char c = *++p;
	assert(c == 6); /* FIXED */
	assert(*p == 6); /* FIXED */

	// Sure you can - cast and display the hex value
	// but how would you simulate the memory?
	unsigned char *np = p + 3;
	assert(*np == 9); /* FIXED */
	assert(*p == 6); /* FIXED */

	//Let's setup an integer pointer
	unsigned int *intP = (unsigned int*) originalPointer;

	// Hint remember your processors Endianness
	// Also you should probably do these as hex
	assert(*intP == 0x03020100); /* NOTE: the problem here was that the integer embraces FOUR char values (0, 1, 2, 3) */

	intP = intP + 3;
	assert(*intP == 0x0F0E0D0C); /* FIXED. Notice that we stepped 3 INTEGER positions, which means 3*4 = 12 char positions */

	intP = (unsigned int *)((unsigned char *) (intP) + 3); /* intP -> uchar* then do the 3 pointer steps forward */
    assert(*intP == 0x1211100F); 
    
    /* Explanation to the line 54:  The pointer had an integer reference, which was lost in the cast to unsigned char
     * We stepped the pointer 3 times, under char point arithmetic, which lead us to the '0x0F' value (see l.51)
     * Finally, the cast to integer pointer have the propertie to pointing out the value of 4 hex positions */

	unsigned int intX = *intP--;
	assert(intX == 0x1211100F); /* FIXED: the same as before */
	assert(*intP == 0x0E0D0C0B); /* You decrement the pointer as integer, then move 4 positions backwards */

	unsigned int *subtractedP = intP - 1;
	assert(*subtractedP == 0x0A090807); /* the same logic as before */
	assert(intP - subtractedP == 1); /* this difference follows from the subtraction on the l.64 */

	// Obscure C trick
	intP = (unsigned int*) originalPointer;
    assert(3[intP] == 0x0F0E0D0C); /* 3[x] means *(3+x) actually, so this line means *(intP + 3) == anAddress (original intP) */

	puts("Congrats you did it!  You must know your pointers");
	return 0;
}
