#ifndef VECTORDEF
#define VECTORDEF
typedef struct _POINT
{
	int x, y;
	bool operator==(const _POINT& a) const
	{
		return (x == a.x && y == a.y);
	}
}Point;
typedef struct _VECTOR
{
	Point point;
	Point direction;
} Vector;
#endif
