#include "field.h"

/** @file field.c
 *  @brief You will modify this file and implement five functions
 *  @details Your implementation of the functions defined in field.h.
 *  You may add other function if you find it helpful. 
 * <p>
 * @author <b>Your name</b> goes here
 */

/** @todo Implement in field.c based on documentation contained in field.h */
int getBit (int value, int position) {
	
    return (value >> position)& 0x1;

}

/** @todo Implement in field.c based on documentation contained in field.h */
int setBit (int value, int position) {
	
    return (0x1 << position)| value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int clearBit (int value, int position) {
	
    return ~(0x1 << position) & value;
}

/** @todo Implement in field.c based on documentation contained in field.h */
int getField (int value, int hi, int lo, int sign) {
	int result;
	result = ((1 << (hi-lo+1))-1) & (value >> lo);
	if(sign)
	{
		result = ~result + 1;
	}
    return result;
}
