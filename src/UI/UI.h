#ifndef UI_H
#define UI_H

namespace WorldArchitect
{
	class UI
	{
		virtual int requestInt() = 0;
		virtual char *requestString() = 0;
	};
}
#endif
