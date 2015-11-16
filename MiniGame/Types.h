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

struct EulerAngle{
	float32 y;
	float32 p;
	float32 r;

	EulerAngle(float32 y, float32 p, float32 r) : y(y), p(p), r(r) {};
	EulerAngle(){};
};

#endif // TYPES_H