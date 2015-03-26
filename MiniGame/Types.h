#ifndef TYPES_H
#define TYPES_H

/* custom types */
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long int uint64;
typedef float float32;
typedef double float64;


/* math stuff */
#define DEG_TO_RAD(x) x*(3.141592f/180.0f)


/* -- */
struct Rect{
	float32 x;
	float32 y;
	float32 w;
	float32 h;	

	Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h){};
	Rect(){};
};

struct Rect3D{
	float32 x;
	float32 y;
	float32 z;
	float32 w;
	float32 h;

	Rect3D(float x, float y, float z, float w, float h) : x(x), y(y), z(z),w(w), h(h){};
	Rect3D(){};
};

#endif // TYPES_H