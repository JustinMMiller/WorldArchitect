#ifndef SETTLEMENT_H
#define SETTLEMENT_H

namespace WorldArchitect
{
	class Settlement
	{
		public:
			Settlement(int lx, int ly);
			int getX() {return this->x;};
			int getY() {return this->y;};
		private:
			int x, y;
	};
}
#endif
