#ifndef VECTORDEF
#define VECTORDEF
typedef struct _POINT
{
	float x, y;
}Point;
typedef struct _VECTOR
{
	Point point;
	Point direction;
} Vector;
#endif
