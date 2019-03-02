#ifndef _MYMATH_H_
#define _MYMATH_H_

#include <stdint.h>

#define ABS(x) ( (x)>0?(x):-(x) )
#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define TAN_MAP_RES     0.003921569f     /* (smallest non-zero value in table) */
#define RAD_PER_DEG     0.017453293f
#define TAN_MAP_SIZE    256
#define PI_FLOAT       3.14159f
#define HALFPI_FLOAT  1.570796f
#define ONE_PI   (3.14159265)
#define TWO_PI   (2.0 * 3.14159265)
#define ANGLE_UNIT (TWO_PI/10.0) 


float fast_atan2(float y, float x);
float mAtan(float x, float y);
float mPow(float a);
float mSqrt(float number); 
double mx_sin(double rad);
double mSin(double rad);
float mCos(double rad);

float getDeathzoom_float(float x,float zoom);
int16_t getDeathzoom_int16(int16_t x,int16_t zoom);
float to180Degrees(float x);
#endif