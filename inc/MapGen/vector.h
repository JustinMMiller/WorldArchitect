#ifndef VECTORDEF
#define VECTORDEF
typedef struct _POINT
{
	int x, y;
}Point;
typedef struct _VECTOR
{
	Point point;
	Point direction;
} Vector;
#endif
