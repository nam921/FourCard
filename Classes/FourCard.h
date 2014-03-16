#ifndef __FOURCARD_H__
#define __FOURCARD_H__

#include <string>
#include <cstdarg>

using namespace std;

namespace FourCard
{
	extern const int VERSION;

	extern const char* SERVER_IP;
	extern const int SERVER_PORT;

	extern const char* DEFAULT_FONT;
}

string __stringf(const char* format, ...);

#endif // __FOURCARD_H__
