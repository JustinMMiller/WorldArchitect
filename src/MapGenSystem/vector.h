#ifndef VECTORDEF
#define VECTORDEF

/// Pair of (x, y) with equivalence operator.
typedef struct _POINT
{
	int x, y;
	bool operator==(const _POINT& a) const
	{
		return (x == a.x && y == a.y);
	}
}Point;

/// Vector of origin and direction
typedef struct 
{
	Point point;
	Point direction;
} Vector;
#endif
