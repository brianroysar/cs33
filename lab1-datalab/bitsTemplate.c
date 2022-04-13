/* 
 * CS:APP Data Lab 
 * 
 * <BRIAN ROYSAR 205394798>
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
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
    /* Using an approach I did on 4-bit bit sequences, I realised that the XOR bitwise operation is useful in determining whether or not the bit collection has an odd or even number of 0s in total. When we XOR two bit sequences, we get two possible results:
     1. Odd #0's ^ Odd #0's -> even number of 0s (e.g. 1000 ^ 0100 = 1100)
     2. Even #0's ^ Even #0's -> even number of 0s (e.g. 0101 ^ 0011 = 0110)
     3. Odd #0's ^ Even #0's -> odd number of 0s (e.g. 1011 ^ 0011 = 1000)
     This means that if we have the 32-bit number x, and we keep XOR-ing its two halves until we get to 1 bit, we can determine whether or not the whole number has a total of odd or even number of 0s. At the end, we will get x = ......1 if it has an odd number of 1s and 0s, and x = .......0 if it has an even number of 1s and 0s. By anding it with 1, we only get the LSB which is either 1 or 0
     */
    int result;
    x = x ^ (x >> 16);
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);
    result = (x & 1);
    return result;
}

/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
    /*
     In temp, the function will store x right shifted n times in temp. I have designed the mask so that the bit sequence of the mask will be filled with ones from the least significant bit to the bit in the (32 - n)th spot. This will take care of negative numbers and streamline their appearance with positive number. The add will conssit of the bits that we lost due to the rotation, multiplied accordingly to the right scale factor. Finally, we simply add this with temp, and we get the funal result.
     */
    int temp, mask, add, negativeone, negativeN;
    negativeN = ~n + 1;
    temp = x >> n;
    negativeone = ~1 + 1;
    mask = (1 << (32 + negativeN)) + (negativeone);
    temp = temp & mask;
    add = (x << (32 + negativeN)) + temp;
    return add;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    /* My funciton attempts to get two integers, x and newX, in a manner which when we do x | newX, we get the byteSwap value: this is because I set x as the original x, with the nth and mth bytes removed (e.g. if x = 12345678 and n = 0 and 2, x would now be 12005600, and newX would an integer that contains the nth and mth bytes in the appropriate positions (newX in this case would be 00780034). Thus, we are left to OR the bytes bitwise, and we get the byteswap value.
     */
    int nShift, byteAtN, mShift, byteAtM, newX;
    nShift = n << 3;
    byteAtN = ((x >> nShift) & 255);
    x = x + ((~byteAtN + 1) << nShift);
    mShift = m << 3;
    byteAtM = ((x >> mShift) & 255);
    x = x + ((~byteAtM + 1) << mShift);
    newX = 0;
    newX = newX + (byteAtN << mShift) + (byteAtM << nShift);
    return (newX | x);
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
    /* We can split this into two cases:
     * 1. x < 0: we know x will only fit if x >> 15 strictly produces a bit sequence of 1s (111...1)
     * 2. x > 0: we know x will only fir if x >> 15 strictly produces a bit sequence of 0s (000...0)
     * To streamline the two cases, we have the variable, isNegative, that acts as a bias, so if it is negative, it will add 1 to the bit sequence of 1s (111...1) and it will result in a bit sequence of 0s, just like case number 2 where x > 0. So, finally, we ! the sequence to get 1 if it fits, and 0 in any other case.
     */
    int isNegative, fit;
    isNegative = (x >> 31) & 1; // isNegative = 1 if x is negative, isNegative = 0 if x is positive
    fit = !((x >> 15) + isNegative);
    return fit;
}
/*
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    /* ~x and ~y will replace all the 0s with 1s. We know in an and, 0s would cause and to give out 0, so by doing an or of ~x and ~y, we get a 1 in every bit position where there is a 0 in the original x and y. Thus, by flipping all of this, we get 0s in those 1 positions and 1s in where there were originally 1s in the same index position in x and y. */
    return (~((~x) | (~y)));
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
    /* The two cases where x-y will cause overflow is when:
     * 1. x < 0, y > 0 --> x-y > 0
     * 2. x > 0, y < 0 --> x-y < 0
     From this, we have two variables that determine whether x and y is negative or positive. Then we also check is x-y will be positive or negative. Then, we can figure out that the function should return 0 (when it causes overflow) in the two cases below:
     * 1. isXNegative = 0, isYNegative = 1, isResultNegative = 1
     * 2. isXNegative = 1, isYNegative = 0, isResultNegative = 0
     So, using the last logic statement, I got the function to return 0 in the cases above where overflow occurs, and the function will return 1 in any other case (where there is no overflow)
     */
    int isXNegative, isYNegative, result, isResultNegative;
    isXNegative = (x >> 31) & 1; // 1 if x is negative, 0 if x is positive
    isYNegative = (y >> 31) & 1; // 1 if y is negative, 0 if y is positive
    result = x + (~y+1); // x - y
    isResultNegative = (result >> 31) & 1;
    return !((isXNegative ^ isYNegative) & (isXNegative ^ isResultNegative));
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
    /* For this function, I decided to split it into two cases:
     * 1. x and y have the same sign (both negative or both positive): In this case we can use a subtraction to figure out whether x or y is greater.
     * 2. x and y have different signs: For this, since we are guranteed that x and y will have different signs, the only case where x > y is if x's m.s.b = 0. (implying that y's m.s.b = 1, making y negative)
     Because of the nature of the variables samesigncheck and differentsigncheck, these two variables will never be the same since one involves anding with signcheck and the other ands with !signcheck. Thus, we can use an XOR (^) to determine whether either one is true - signifying that one of the two cases mentioned above are true.
     */
    int signcheck, sub, subcheck, samesigncheck, differentsigncheck;
    signcheck = !((x>>31)^(y>>31)); //will be 1 if x and y have same signs, will be 0 if x and y have different signs
    sub = !!(x + (~y+1)); // will be 0 if x == y, will be 1 if anything else
    subcheck = !((x + (~y+1)) >> 31); //will be 1 if x>y, will be 0 if x < y
    samesigncheck = signcheck & subcheck & sub;
    differentsigncheck = ((!signcheck) & !(x>>31));
    return (samesigncheck ^ differentsigncheck);
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
    /* We can break x into two cases: when x is positive and when x is negative. When x is positive, we know it will fit in an n-byte TC system when everything from the nth bit from the right are all 0s. When x is negative, we know it will fit in an n-byte TC system when everything from the nth bit from the right are all 1s. Right shifting both cases by (n-1) will produce 0 in the positive case and -1 in the negative case. To make sure they are the same, in the case it is negative, we add a positve one bias so both equals 0 if they can fit, else, it will be a  non-zero value. By ! this result, we get the output we want: 1 if x fits in a n bits TC system, else 0. */
    int canfit, isNegative;
    isNegative = (x>>31) & 1; // 1 if negative, 0 if positive
    canfit = !((x >> (n+(~0))) + isNegative); // 1 if can fit, else doesnt fit
    return canfit;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    /* From the definition of how to negate a twos complement number: flip the bits and add one */
    return (~x + 1);
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    /* TMax+1 will result in Tmin, and Tmax ^ Tmin will produce a sequence of 1s for its bit sequence. I also realised that if x = -1, it will produce the same behaviour as x = Tmax, as -1 ^ 0 will produce a sequence of 1s as well. That is why there is a second part (!!(x+1)) to ensure that we dont take into account x = -1 and only return 1 if x = Tmax.
     */
    return !((x ^ (x+1)) + 1) & !!(x+1);
}
