#include "newgraphics.h"
#include <iostream>


int main(int argc, char* argv[]) {

	int gd, gm;
	detectgraph(&gd, &gm);
	initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

	// boundary
	setcolor(BLUE);
	rectangle(10, 30, 30, 50);
	setcolor(RED);
	floodfill(16, 36, BLUE);

	setcolor(WHITE);
	rectangle(110, 30, 130, 50);
	setcolor(RED);
	floodfill(115, 40, WHITE);

	setcolor(GREEN);
	circle(70, 150, 50);
	//floodfill(70, 150, GREEN);

	setfillstyle(0, 0);

	std::cin.get();
	closegraph();
	return 0;
}
