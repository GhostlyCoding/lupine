#ifndef LUPINE_COLOR_H_INCLUDED
#define LUPINE_COLOR_H_INCLUDED

#include <cmath> // floor()
#include <algorithm> // transform()
#include <string> // substr

class Color {
    public:
	int r;
	int g;
	int b;
	int a;
	std::string hexCode;
	Color(int r, int g, int b, float a);
	Color(int r, int g, int b, int a);
	Color(std::string hexCode, float a);
	Color(std::string hexCode, int a);
    private:
	void errorChecking();
};

#endif
