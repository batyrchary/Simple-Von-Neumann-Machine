/* 
 * CS:APP Data Lab 
 * 
 * <BATYR CHARYYEV 2001527>
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

You will provide your solution to the Data Lab by
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

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
	
	return (x>>(n<<3))&255;	
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {

int nn=(!!n) & (!(n & (128<<24)));
int c= x>>n;
int d= (255<<24)>>24;
int ff= (32+(~n))+1;
int result= ~((d<<ff)+!nn);
int result2= c & result;

return result2;	
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	return 2;
  
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	int result=0;
	int tcom=~x+1;
	int birli=(x>>31)|(tcom>>31);
  	result=birli+1;
	return result; 
}
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

return !(((~x & (x>>31))+(x & ~(x>>31))) >> (n+1+(~1)));

}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {

	int bias=(x>>31) & ((1<<n)+(~1)+1);
	return (x+bias)>>n;	
 
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {

	return (~x)+1;  
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	
	return (!!x) & (!(x & (128<<24)));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {

int result=0;
int xr=x>>31;
int yr=y>>31;
int dif=x+(~y)+1;

int esit=!(x^y);
int farklibolge=(!!xr)&(!yr);

int aynibolge= (!(xr^yr)) &  (!!(dif>>31));


result= esit | farklibolge | aynibolge;
return result;

}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	
	int input=x;
	int input2=x;
	int count=0;
	input=input>>16;
	count=(!!input)<<4;
	input2=(input2>>count)&((255<<8)+255);

	input2 = input2>>1;
	count =count + (!!input2);	
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);	
	input2 = input2>>1;
	count =count + (!!input2);	
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);
	input2 = input2>>1;
	count =count + (!!input2);	
return count;

}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	unsigned exp=uf;

	
	exp= 2139095040 & exp;
	
	if(!(exp^2139095040) && (8388607 & uf) )
		return uf;
	else 
		return ((~(uf>>31))<<31) | (uf&2147483647u);
 
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
	
	unsigned wnumber, msb, overall;  
	unsigned number=x;  
	unsigned sign=0;  
	unsigned exp;	
	unsigned counter=0;         
	if (!x) 
		return 0;  

	sign = x & 2147483648u;
	
	if(sign)
		number=2147483648-(2147483647 & x);
		
	else 
		number=x;
    
	wnumber=number;  
	
	while(wnumber)
	{	if(wnumber >= 2147483648u)break;
		counter=counter+1;
		wnumber=wnumber<<1;			
	}
		counter=counter+1;
		wnumber=wnumber<<1;

	if(counter == 32)
		exp=127<<23;
	else
		exp=(127+(32-counter))<<23;
     
	overall= (sign | exp | (wnumber>>9) );
	
	if ((((wnumber<<23)>>23)>256) || (((wnumber<<22)>>22)==768))  
		overall= overall+1 ;	
	
		return overall;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {

/////// 2 NORMALIZED ///////////////////////////////////////// 	
int sign2=0<<31;
unsigned exphelper;
///////////////////////////////////////////////////////////// 
int sign = ((uf>>31)<<31);
int frac = (uf<<9)>>9;
int exp =  (((uf<<1)>>24)<<23);


	sign=sign^sign2;

   if(exp == 0)///////// DENORMALIZED
   {
	exphelper=(exp<<1) & 0x7fffffff;
	if(!!(frac & 0x00400000))
	{
		
		exp=exphelper | 0x00800000;
	}
	else 
	{
		
		exp=exphelper;
	}
	frac=(frac<<1) & 0x007fffff;
 }

   else if(exp == 0x7F800000)//////////////// SPECIAL VALUE
   {
		if(frac == 0 && sign==1) //negative infinity
			return 0xff800000u;
		else if(frac == 0 && sign==0) //positive infinity 
			return 0x7f800000u;
		else if(frac != 0) //NaN
			return uf;	
   } 
   else//	NORMALIZED		E1=exp1-bias	E2=exp2-bias	E1+E2
   {		
	   exp=(exp + 0x800000);
   }
 return ((sign | exp) | frac);
 }