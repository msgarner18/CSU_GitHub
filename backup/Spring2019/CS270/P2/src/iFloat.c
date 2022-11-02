#include "Debug.h"
#include "iFloat.h"

/** @file iFloat.c
 *  @brief You will modify this file and implement nine functions
 *  @details Your implementation of the functions defined in iFloat.h.
 *  You may add other function if you find it helpful. Added function
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 *  <p>
 *  @author <b>Your name</b> goes here
 */

/* declaration for useful function contained in testFloat.c */
const char* getBinary (iFloat_t value);

iFloat_t floatAbs(iFloat_t x);

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetSign (iFloat_t x) {
  return  x>>(BITS-1); /* implement this */
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetExp (iFloat_t x) {
  return (floatAbs(x)>>(BITS_MANT))-EXP_BIAS; /* implement this */
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatGetVal (iFloat_t x) {
  int value = x<< (BITS_EXP+1);
  if(floatGetSign(x) == -1)//if number is negative
  {
    value = ~value+1;
  }
  return value;
}

/** @todo Implement based on documentation contained in iFloat.h */
void floatGetAll(iFloat_t x, iFloat_t* sign, iFloat_t* exp, iFloat_t* val) {
  *sign = floatGetSign(x);
  *exp = floatGetExp(x);
  *val = floatGetVal(x); 
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatLeftMost1 (iFloat_t bits) {
  int value = -1;
  for(int i = 15; i >= 0 ; i--)
  {
    if(floatGetSign(bits) == 0)
    {
      bits = bits<<1;
    }
    else
    {
      value = i;
    }
  }
  return value;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAbs (iFloat_t x) {
  return (~(1<<(BITS-1))) & x;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatNegate (iFloat_t x) {
  int value;
  if(floatGetSign(x) == -1)
  {
    value = floatAbs(x);
  }
  else
  {
    value = (1<<(BITS-1)) | x;
  }
  return value;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatAdd (iFloat_t x, iFloat_t y) {
  int xexp = floatGetExp(x);
  int yexp = floatGetExp(y);

  int xMant = floatGetVal(x);
  int yMant = floatGetVal(y);

  int value;

  if(xexp <= yexp)
  {
    value = ((xMant*2^(xexp-yexp)) + yMant) *2^yexp;
  }
  else
  {
    value = ((yMant*2^(yexp-xexp)) + xMant)*2^xexp;  
  }
  return value;
}

/** @todo Implement based on documentation contained in iFloat.h */
iFloat_t floatSub (iFloat_t x, iFloat_t y) {
  return x-y;
}
