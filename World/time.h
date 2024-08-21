#pragma once



class Clock
{
	unsigned int ticks = 0;

public:

	void update() { ticks++; }
	void time() { return ticks; }
};