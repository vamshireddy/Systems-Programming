/* 
 * CSE 351 HW1 (Data Lab )
 * 
 * <Vamshi k.vamshi2008@gmail.com>
 * 
* bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   Use the dlc compiler to check that your solutions conform
 *   to the coding rules.
 */


#endif
// Rating: 1
/* 
 *   bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
 /*
  * Computes bitwise and between x and y. returns x&y where 0<= x,y <=2^32
  */
 return ~(~x|~y);
}
/* 
 *   bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /*
   * Computes bitwise Xor between x and y. returns x ^ y where 0<= x,y <=2^32
   */
  int result1 = x & ~y;
  int result2 = ~x & y;
  int result = ~(~result1 & ~result2);
  return result;
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 * and the rest set to 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  /*
  	This sets every 3 bit starting from the LSB and returns the result
  */
  int result = 0;
  int setter1 = 0x49;
  int setter2 = 0x24;
  int setter3 = 0x92;

  result = result | setter1;
  result = result << 8 | setter2;
  result = result << 8 | setter3;
  result = result << 8 | setter1;
  return result;
}
// Rating: 2
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	n = n + ~0;
	x = x >> n;
	return 1;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
	/* 
	1. Extract the sign of the number by shifting by 31. This will extend the sign bit to all of the bits in the number 
	2. This will result in either all 0's or all 1's.
	3. If all 1's ( -1 )then return the number as it is as it matches with the spec.
	4. But we can't differentiate the postive and 0 by all 0's 
	5. If its positive, check whether any bit is set in the last 31 bits 
	6. If any, then return 1, else return 0
	7. To check, use the logarithmic or'ing as described below
	8. If any bit is set in the number, it set's the LSB to 1, else it sets to 0
	*/
	
	int p = x >> 31;
	int result;
	x = (x << 1);
	x = x | ( x >> 16 );
	x = x | ( x >> 8 );
	x = x | ( x >> 4 );
	x = x | ( x >> 2 );
	x = x | ( x >> 1 );
	x = x & 1;
	result = (~p & x) + p;
	return result;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  
  int byte_pow  = n<<3;
  int result = x >> byte_pow;
  int mask = 0xFF;
  return result & mask;
}
// Rating: 3
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	
	int p = n;
	int temp;
	n = n | ( n >> 16 );
	n = n | ( n >> 8 );
	n = n | ( n >> 4 );
	n = n | ( n >> 2 );
	n = n | ( n >> 1 );
	n = (n << 31) >> 31;

        temp = ( n & ( ( 1 << 31 ) >> ( p+~0 ) ) ) +  ( ~n & 0);

	x = x >> p;
	x = x & ~temp;
	return x;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
	return 1;	
}
// Rating: 4
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {

	int temp = x;
	x = x | ( x >> 16 );
	x = x | ( x >> 8 );
	x = x | ( x >> 4 );
	x = x | ( x >> 2 );
	x = x | ( x >> 1 );
	x = (x<<31) >> 31;
	temp = ( ~x & 1 ) + ( x & 0 );
	return temp;
}
// Extra Credit: Rating: 3
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	int temp;	
	x = x | ( x >> 16 );
	x = x | ( x >> 8 );
	x = x | ( x >> 4 );
	x = x | ( x >> 2 );
	x = x | ( x >> 1 );
	x = (x<<31) >> 31;
	temp = ( ~x & z) + ( x & y);
	return temp;
}
// Extra Credit: Rating: 4
/*
 *   isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
	

	int neg = (x >> 31); 
	int r = x;
//	printf("init : %x\n",x);
	int p = x + ~0;
	int result = x & p;
//	printf("after and : %x\n",result);
	int output;
	
	result = result | ( result >> 16 );
	result = result | ( result >> 8 );
	result = result | ( result >> 4 );
	result = result | ( result >> 2 );
	result = result | ( result >> 1 );

//	printf("Jeer %x\n",result);

	result = (result << 31)>>31;
//	printf("\n\n%x\n\n",result);

	r = r | ( r >> 16 );
	r = r | ( r >> 8 );
	r = r | ( r >> 4 );
	r = r | ( r >> 2 );
	r = r | ( r >> 1 );
	r = (r<<31) >> 31;
	
	output =  (  ( ~r&0 ) + ( r & (( ~neg & ( (~result & 1) + (result & 0) ) ) + ( neg & 0 ))));
	return output;
}
/*
int main()
{
	int a = 0x80044500;
	printf("input is %d and out is %d\n",a,isPower2(a));
}
*/