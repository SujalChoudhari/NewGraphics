#pragma once
// Colors
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#include <SDL.h>



#ifdef __cplusplus
extern "C" {
#endif

	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static SDL_Color colors[16] = {
		{0, 0, 0, 255},    // BLACK
		{0, 0, 255, 255},  // BLUE
		{0, 255, 0, 255},  // GREEN
		{0, 255, 255, 255},// CYAN
		{255, 0, 0, 255},  // RED
		{255, 0, 255, 255},// MAGENTA
		{165, 42, 42, 255},// BROWN
		{192, 192, 192, 255},// LIGHTGRAY
		{169, 169, 169, 255},// DARKGRAY
		{173, 216, 230, 255},// LIGHTBLUE
		{144, 238, 144, 255},// LIGHTGREEN
		{224, 255, 255, 255},// LIGHTCYAN
		{255, 182, 193, 255},// LIGHTRED
		{255, 105, 180, 255},// LIGHTMAGENTA
		{255, 255, 0, 255},// YELLOW
		{255, 255, 255, 255} // WHITE
	};


	// Global graphics state
	static int _current_color = 15;
	static int _bk_color;
	static int _current_x;
	static int _current_y;
	static int _max_x;
	static int _max_y;
	static int _window_width = 600;
	static int _window_height = 600;


	void detectgraph(int* gdriver, int* gmode);
	void initgraph(int* gdriver, int* gmode, const char* path);
	void arc(int x, int y, int start_angle, int end_angle, int radius);
	void bar(int left, int top, int right, int bottom);
	void bar3d(int left, int top, int right, int bottom, int depth, int topflag);
	void circle(int x, int y, int radius);
	void cleardevice();
	void closegraph();
	void drawpoly(int num_points, int* points);
	void ellipse(int x, int y, int start_angle, int end_angle, int x_radius, int y_radius);
	void fillellipse(int x, int y, int x_radius, int y_radius);
	void fillpoly(int num_points, int* points);
	void floodfill(int x, int y, int border_color);
	void line(int x1, int y1, int x2, int y2);
	void lineto(int x, int y);
	void linerel(int x, int y);
	void moveto(int x, int y);
	void moverel(int x, int y);
	void outtext(const char* text);
	void outtextxy(int x, int y, const char* text);
	void pieslice(int x, int y, int start_angle, int end_angle, int radius);
	void putimage(int left, int top, const void* bitmap, int mode);
	void getimage(int left, int top, int right, int bottom, void* bitmap);
	void getarccords(int* x, int* y);
	int getbkcolor();
	int getcolor();
	const char* getdrivername();
	int imagesize(int left, int top, int right, int bottom);
	int getmaxcolor();
	int getmaxx();
	int getmaxy();
	int getpixel(int x, int y);
	int getx();
	int gety();
	void graphdefaults();
	const char* grapherrormsg();
	void putpixel(int x, int y, int color);
	void rectangle(int left, int top, int right, int bottom);
	void sector(int x, int y, int start_angle, int end_angle, int radius1, int radius2);
	void setbkcolor(int color);
	void setcolor(int color);
	void setfillstyle(int pattern, int color);
	void setlinestyle(int type, int thickness, int size);
	void settextstyle(int font, int direction, int size);
	void setviewport(int left, int top, int right, int bottom, int clip);
	int textheight(const char* text);
	int textwidth(const char* text);




	void detectgraph(int* gdriver, int* gmode) {
		*gdriver = 0;
		*gmode = 0;
	}

	void initgraph(int* gdriver, int* gmode, const char* path) {
		SDL_Init(SDL_INIT_VIDEO);

		Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
		window = SDL_CreateWindow(path, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _window_width, _window_height, windowFlags);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetWindowAlwaysOnTop(window, SDL_TRUE);
		_max_x = _window_width - 1;
		_max_y = _window_height - 1;

		SDL_SetRenderDrawColor(renderer, colors[_bk_color].r, colors[_bk_color].g, colors[_bk_color].b, colors[_bk_color].a);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

	}

	void arc(int x, int y, int start_angle, int end_angle, int radius) {
		const int num_segments = 100;
		const double step = (end_angle - start_angle) / static_cast<double>(num_segments);
		SDL_Point points[num_segments + 1];
		for (int i = 0; i <= num_segments; ++i) {
			double angle = start_angle + i * step;
			points[i].x = static_cast<int>(x + radius * cos(angle * M_PI / 180.0));
			points[i].y = static_cast<int>(y + radius * sin(angle * M_PI / 180.0));
		}
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		SDL_RenderDrawLines(renderer, points, num_segments + 1);
		SDL_RenderPresent(renderer);
	}

	void bar(int left, int top, int right, int bottom) {
		SDL_Rect rect = { left, top, right - left, bottom - top };
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);
	}

	void bar3d(int left, int top, int right, int bottom, int depth, int topflag) {
		// Simplified 3D bar (topflag determines shading)
		SDL_Rect rect = { left, top, right - left, bottom - top };
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		SDL_RenderFillRect(renderer, &rect);
		// For 3D effects, you'll need to draw additional lines and rectangles to simulate depth
		SDL_RenderPresent(renderer);
	}

	void circle(int x, int y, int radius) {
		const int num_segments = 100;
		const double step = 2 * M_PI / num_segments;
		SDL_Point points[num_segments];
		for (int i = 0; i < num_segments; ++i) {
			double angle = i * step;
			points[i].x = static_cast<int>(x + radius * cos(angle));
			points[i].y = static_cast<int>(y + radius * sin(angle));
		}
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		SDL_RenderDrawLines(renderer, points, num_segments);
		SDL_RenderPresent(renderer);
	}

	void cleardevice() {
		SDL_SetRenderDrawColor(renderer, colors[_bk_color].r, colors[_bk_color].g, colors[_bk_color].b, colors[_bk_color].a

		);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	void closegraph() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void drawpoly(int num_points, int* points) {
		SDL_Point* sdl_points = new SDL_Point[num_points];
		for (int i = 0; i < num_points; ++i) {
			sdl_points[i].x = points[i * 2];
			sdl_points[i].y = points[i * 2 + 1];
		}
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		SDL_RenderDrawLines(renderer, sdl_points, num_points);
		SDL_RenderPresent(renderer);
		delete[] sdl_points;
	}

	void ellipse(int x, int y, int start_angle, int end_angle, int x_radius, int y_radius) {
		const int num_segments = 100;
		const double step = (end_angle - start_angle) / static_cast<double>(num_segments);
		SDL_Point points[num_segments + 1];
		for (int i = 0; i <= num_segments; ++i) {
			double angle = start_angle + i * step;
			points[i].x = static_cast<int>(x + x_radius * cos(angle * M_PI / 180.0));
			points[i].y = static_cast<int>(y + y_radius * sin(angle * M_PI / 180.0));
		}
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		SDL_RenderDrawLines(renderer, points, num_segments + 1);
		SDL_RenderPresent(renderer);
	}

	void fillellipse(int x, int y, int x_radius, int y_radius) {
		// Fills the ellipse, can be more complex to implement, a simple approach is to draw horizontal lines
		for (int i = -y_radius; i <= y_radius; i++) {
			int height = static_cast<int>(sqrt(x_radius * x_radius - (i * i * x_radius * x_radius) / (y_radius * y_radius)));
			SDL_Rect rect = { x - height, y + i, 2 * height, 1 };
			SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
			SDL_RenderFillRect(renderer, &rect);
		}
		SDL_RenderPresent(renderer);
	}

	void fillpoly(int num_points, int* points) {
		SDL_Point* sdl_points = new SDL_Point[num_points];
		for (int i = 0; i < num_points; ++i) {
			sdl_points[i].x = points[i * 2];
			sdl_points[i].y = points[i * 2 + 1];
		}
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		SDL_RenderDrawLines(renderer, sdl_points, num_points);
		SDL_RenderPresent(renderer);
		delete[] sdl_points;
	}

	void floodfill(int x, int y, int border_color) {
		//// Flood fill using a basic algorithm; more complex implementations are possible
		//SDL_Color target_color;
		//SDL_GetRenderDrawColor(renderer, &target_color.r, &target_color.g, &target_color.b, &target_color.a);
		//SDL_SetRenderDrawColor(renderer, colors[border_color].r, colors[border_color].g, colors[border_color].b, colors[border_color].a);

		//// Stack-based flood fill
		//std::vector<SDL_Point> stack;
		//stack.push_back({ x, y });

		//while (!stack.empty()) {
		//    SDL_Point p = stack.back();
		//    stack.pop_back();

		//    SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		//    SDL_RenderDrawPoint(renderer, p.x, p.y);

		//    // Check surrounding pixels
		//    if (p.x > 0 && SDL_GetRenderDrawColor(renderer, &target_color.r, &target_color.g, &target_color.b, &target_color.a) == target_color) {
		//        stack.push_back({ p.x - 1, p.y });
		//    }
		//    if (p.y > 0 && SDL_GetRenderDrawColor(renderer, &target_color.r, &target_color.g, &target_color.b, &target_color.a) == target_color) {
		//        stack.push_back({ p.x, p.y - 1 });
		//    }
		//    if (p.x < _window_width - 1 && SDL_GetRenderDrawColor(renderer, &target_color.r, &target_color.g, &target_color.b, &target_color.a) == target_color) {
		//        stack.push_back({ p.x + 1, p.y });
		//    }
		//    if (p.y < _window_height - 1 && SDL_GetRenderDrawColor(renderer, &target_color.r, &target_color.g, &target_color.b, &target_color.a) == target_color) {
		//        stack.push_back({ p.x, p.y + 1 });
		//    }
		//}
		//SDL_RenderPresent(renderer);
	}

	void line(int x1, int y1, int x2, int y2) {
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
		SDL_RenderPresent(renderer);
	}

	void lineto(int x, int y) {
		line(_current_x, _current_y, x, y);
		_current_x = x;
		_current_y = y;
	}

	void linerel(int x, int y) {
		lineto(_current_x + x, _current_y + y);
	}

	void moveto(int x, int y) {
		_current_x = x;
		_current_y = y;
	}

	void moverel(int x, int y) {
		_current_x += x;
		_current_y += y;
	}

	void outtext(const char* text) {
		// Simple implementation to render text
		// More advanced text rendering might use SDL_ttf
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		// Text rendering code should be added here
		SDL_RenderPresent(renderer);
	}

	void outtextxy(int x, int y, const char* text) {
		moveto(x, y);
		outtext(text);
	}

	void pieslice(int x, int y, int start_angle, int end_angle, int radius) {
		// Drawing a pie slice is complex; you might use similar logic to the arc function
		// and fill the resulting wedge
		arc(x, y, start_angle, end_angle, radius);
		// Filling the wedge can be done by filling between the edges
		SDL_RenderPresent(renderer);
	}

	void putimage(int left, int top, const void* bitmap, int mode) {
		// Implementation depends on the format of the bitmap
		// This is a placeholder for putting an image
		SDL_RenderPresent(renderer);
	}

	void getimage(int left, int top, int right, int bottom, void* bitmap) {
		// Implementation depends on the format of the bitmap
		// This is a placeholder for getting an image
		SDL_RenderPresent(renderer);
	}

	void getarccords(int* x, int* y) {
		*x = _current_x;
		*y = _current_y;
	}

	int getbkcolor() {
		return _bk_color;
	}

	int getcolor() {
		return _current_color;
	}

	const char* getdrivername() {
		return "SDL2";
	}

	int imagesize(int left, int top, int right, int bottom) {
		// Implement image size calculation here
		return 0;
	}

	int getmaxcolor() {
		return 0;
	}

	int getmaxx() {
		return _max_x;
	}

	int getmaxy() {
		return _max_y;
	}

	int getpixel(int x, int y) {
		Uint32 pixel;
		SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, &pixel, sizeof(pixel));
		return pixel;
	}

	int getx() {
		return _current_x;
	}

	int gety() {
		return _current_y;
	}

	void graphdefaults() {
		_current_color = 0;
		_bk_color = 0;
	}

	const char* grapherrormsg() {
		return SDL_GetError();
	}

	void putpixel(int x, int y, int color) {
		SDL_SetRenderDrawColor(renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a);
		SDL_RenderDrawPoint(renderer, x, y);
		SDL_RenderPresent(renderer);
	}

	void rectangle(int left, int top, int right, int bottom) {
		SDL_Rect rect = { left, top, right - left, bottom - top };
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].

			b, colors[_current_color].a);
		SDL_RenderDrawRect(renderer, &rect);
		SDL_RenderPresent(renderer);
	}

	void fillrectangle(int left, int top, int right, int bottom) {
		SDL_Rect rect = { left, top, right - left, bottom - top };
		SDL_SetRenderDrawColor(renderer, colors[_current_color].r, colors[_current_color].g, colors[_current_color].b, colors[_current_color].a);
		SDL_RenderFillRect(renderer, &rect);
		SDL_RenderPresent(renderer);
	}

	void setbkcolor(int color) {
		_bk_color = color;
		SDL_SetRenderDrawColor(renderer, colors[color].r, colors[color].g, colors[color].b, colors[color].a);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}


#ifdef __cplusplus
}
#endif
