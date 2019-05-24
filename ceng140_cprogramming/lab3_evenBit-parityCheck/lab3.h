#ifndef LAB3_H
#define LAB3_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************** Specifications *************/
/* You are allowed to use standard headers */

/* Function Prototypes */

/****************************************************************************************/
void execute();

/**
 * Entry point for test code
**/

/****************************************************************************************/
char* encode(char* message);

/**
 * This function encodes the message according to bit-parity rules and returns the encoded
 * message.
 * e.g. : encode("011111101111010001111110") returns the following string:
 * "011111100111101001011111100"
 *
 * Note: It is ensured that the length of the input message will be a multiple of 8.
**/

/****************************************************************************************/
char* decode(char* message);

/**
 * This function decodes the encoded message according to bit-parity rules. If the message
 * doesn't obey the bit-parity rules then it returns the string "error"; otherwise, it 
 * returns the decoded message.
 * e.g. : decode("011111100111101001011111100") returns the following string:
 * "011111101111010001111110"
 * decode("011111110111101001011111100") returns "error" since it doesn't obey the rules.
 *
 * Note: It is ensured that the length of the input message will be a multiple of 9.
**/

/****************************************************************************************/
char* convert(char* message);

/**
 * Each 8 bits in the binary string actually refers to a character and it is the ASCII code
 * of that character actually. This function takes a binary string and converts it to
 * corresponding character string.
 * e.g. : convert("011111100100011101001111010011110100010000100000010011000101010101000011010010110010000101111110")
 * returns the string "~GOOD LUCK!~"  where '~' means BOF/EOF (Beginning/End of File) character.
 * 
 * Note: It is ensured that the length of the input message will be a multiple of 8.
**/

/****************************************************************************************/
int count(char* message);

/**
 * This function calculates the frequency(count) of each different character(8-bit occurrence) 
 * in the message and returns the frequency number of the character with maximum frequency.
 * e.g. : count("0111111001001000010011110100110001001100010110010101011101001111010011110100010001111110")
 * returns 3 , where the binary string in the argument of the function refers to the string 
 * "HOLLYWOOD" where 'O' is the character with the maximum frequency which is 3.
 *
 * Note: (1) Don't calculate the frequency of the BOF/EOF characters. 
 *	 (2) It is ensured that the length of the input message will be a multiple of 8.
**/

/****************************************************************************************/
char** slide(char** messageBox);

/**
 * This function takes an NxM box which includes N messages of length M, and slides the
 * messages by applying the following rule: Do nothing for the 1st message. When you come to
 * 2nd message, start it below the 1st message again but from the line of where the first 
 * character including '1' occurs at the 1st message. In other words, slide the 2nd message
 * till you see the first '1' of the 1st message. Now, apply the same rule for the 2nd and 
 * 3rd messages, and so on. In the end, fill the empty places with '0's and return the slided
 * message.
 * e.g: What is slide(messageBox) where messageBox is the following pointer array:
 * [<pointer>] -> "001011" 
 * [<pointer>] -> "110111"
 * [<pointer>] -> "010101"
 * [<pointer>] -> "110001"
 * [NULL]
 * When you apply the sliding operation, you will obtain the following: 
 * [<pointer>] -> "001011" 
 * [<pointer>] -> "  110111"
 * [<pointer>] -> "  010101"
 * [<pointer>] -> "   110001"
 * [NULL]
 * Now fill the empty places with '0's and return the following pointer array:
 * [<pointer>] -> "001011000"
 * [<pointer>] -> "001101110"
 * [<pointer>] -> "000101010"
 * [<pointer>] -> "000110001"
 * [NULL]
**/

/****************************************************************************************/
char** intersect(char* message1, char* message2, int number);

/**
 * This function searchs for a common substring that occurs in both of the messages which are 
 * message1 and message2, i.e takes the intersection of strings. However, there can be more 
 * than 1 common substrings, so it just looks for the substrings including as many characters as  
 * <number> given in the input. It returns all of such substrings in the intersection, if 
 * there are many.
 * e.g: What is intersect("10001101111010000000100", "11000101", 4) ?
 * It will return the following pointer array:
 * [<pointer>] -> "1000"
 * [<pointer>] -> "0001"
 * [<pointer>] -> "0010"
 * [NULL]
 *
 * Note: (1) The order of substrings that you returned in the result is not important. If a substring
 * in the intersection appears more than once in different parts of the input strings, you have to
 * return that string only once. For instance, the substrings "1000" and "0111" appear twice in
 * intersection (in different parts of the first string), but we show them only once in the input.
 *	 (2) The input messages can have any length.
**/

/****************************************************************************************/
char** split(char* message);

/**
 * Each message starts and ends with the BOF/EOF character, which is 01111110. Also, each
 * message consists of submessages which are seperated by the BOF/EOF character. This function
 * splits each submessage inside the original message with respect to BOF/EOF character, 
 * and returns an array of submessages:
 * e.g. : split("0111111010001101111010000000100011111101100010101111110111000101001111110/")
 * returns the following pointer array:
 * [<pointer>] -> "10001101111010000000100"
 * [<pointer>] -> "11000101"
 * [<pointer>] -> "1110001010"
 * [NULL] 
 *
 * Note: (1) The order of substrings that you returned in the result is IMPORTANT. The indexing must be 
 * in the order in which the substrings occur in the original message.
 *	 (2) The input message can have any length.
**/

#endif
