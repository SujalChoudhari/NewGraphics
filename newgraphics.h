/**
* =============================================================================
* MIT License
*
* Copyright (c) 2024 Sujal Choudhari
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* =============================================================================
*/


/**
* =============================================================================
* Notes:
* - This library is still under development
* - Texts and stylings are not implemented
* - Use the SDL2.dll based on what device you are running the code on.
* - Library was only tested with the x64 version of SDL2.dll
* =============================================================================
*/

/**
* =============================================================================
* Imports and Macros:
* - SDL library
* - All 15 colors from graphics.h are supported
* - Color order is same as graphics.h
* =============================================================================
*/

#pragma once
#include <SDL.h>

enum _colors {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
	LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

// The various graphics drivers
enum graphics_drivers {
	DETECT, CGA, MCGA, EGA, EGA64, EGAMONO, IBM8514, HERCMONO,
	ATT400, VGA, PC3270
};


/**
* =============================================================================
* Global variables
* - current window
* - current renderer
* - current selected color for drawing
* - list of rgb of color
* - background color
* - current x coords
* - current y coords
* - window width as max x
* - window height as max y
* =============================================================================
*/
static SDL_Window* _window;
static SDL_Renderer* _renderer;
static SDL_Color _colors[16] = {
	{0, 0, 0, 255},			// BLACK
	{0, 0, 255, 255},		// BLUE
	{0, 255, 0, 255},		// GREEN
	{0, 255, 255, 255},		// CYAN
	{255, 0, 0, 255},		// RED
	{255, 0, 255, 255},		// MAGENTA
	{165, 42, 42, 255},		// BROWN
	{192, 192, 192, 255},	// LIGHTGRAY
	{169, 169, 169, 255},	// DARKGRAY
	{173, 216, 230, 255},	// LIGHTBLUE
	{144, 238, 144, 255},	// LIGHTGREEN
	{224, 255, 255, 255},	// LIGHTCYAN
	{255, 182, 193, 255},	// LIGHTRED
	{255, 105, 180, 255},	// LIGHTMAGENTA
	{255, 255, 0, 255},		// YELLOW
	{255, 255, 255, 255}	// WHITE
};

static int _current_color = 15;
static int _bk_color;
static int _current_x;
static int _current_y;
static int _max_x;
static int _max_y;
static int _window_width = 600;
static int _window_height = 600;

/**
* =============================================================================
* Declarations:
* Functions from graphics.h are declared here
* Most of the functions are implemented, but some are remaining
* =============================================================================
*/
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


/**
* =============================================================================
* Definations:
* Most of the declared functions are defined here, 
* Unimplemented functions give errors
* =============================================================================
*/
void detectgraph(int* gdriver, int* gmode) {
	*gdriver = 0;
	*gmode = 0;
}

void initgraph(int* gdriver, int* gmode, const char* path) {
	SDL_Init(SDL_INIT_VIDEO);

	Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	_window = SDL_CreateWindow(path, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _window_width, _window_height, windowFlags);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetWindowAlwaysOnTop(_window, SDL_TRUE);
	_max_x = _window_width - 1;
	_max_y = _window_height - 1;

	SDL_SetRenderDrawColor(_renderer, _colors[_bk_color].r, _colors[_bk_color].g, _colors[_bk_color].b, _colors[_bk_color].a);
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);

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
	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
	SDL_RenderDrawLines(_renderer, points, num_segments + 1);
	SDL_RenderPresent(_renderer);
}

void bar(int left, int top, int right, int bottom) {
	SDL_Rect rect = { left, top, right - left, bottom - top };
	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
	SDL_RenderFillRect(_renderer, &rect);
	SDL_RenderPresent(_renderer);
}

void bar3d(int left, int top, int right, int bottom, int depth, int topflag) {
	// Simplified 3D bar (topflag determines shading)
	SDL_Rect rect = { left, top, right - left, bottom - top };
	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
	SDL_RenderFillRect(_renderer, &rect);
	// For 3D effects, you'll need to draw additional lines and rectangles to simulate depth
	SDL_RenderPresent(_renderer);
}

void circle(int x, int y, int radius) {
	const int num_segments = 108;
	const double step = 2 * M_PI / num_segments;
	SDL_Point points[num_segments + 1];  // +1 to include the closing point
	for (int i = 0; i < num_segments; ++i) {
		double angle = i * step;
		points[i].x = static_cast<int>(x + radius * cos(angle));
		points[i].y = static_cast<int>(y + radius * sin(angle));
	}
	// Closing the circle by connecting the last point to the first point
	points[num_segments] = points[0];

	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
	SDL_RenderDrawLines(_renderer, points, num_segments + 1);  // Draw the complete circle
	SDL_RenderPresent(_renderer);
}


void cleardevice() {
	SDL_SetRenderDrawColor(_renderer, _colors[_bk_color].r, _colors[_bk_color].g, _colors[_bk_color].b, _colors[_bk_color].a

	);
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);
}

void closegraph() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void drawpoly(int num_points, int* points) {
	SDL_Point* sdl_points = new SDL_Point[num_points];
	for (int i = 0; i < num_points; ++i) {
		sdl_points[i].x = points[i * 2];
		sdl_points[i].y = points[i * 2 + 1];
	}
	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
	SDL_RenderDrawLines(_renderer, sdl_points, num_points);
	SDL_RenderPresent(_renderer);
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
	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
	SDL_RenderDrawLines(_renderer, points, num_segments + 1);
	SDL_RenderPresent(_renderer);
}

void fillellipse(int x, int y, int x_radius, int y_radius) {
	// Fills the ellipse, can be more complex to implement, a simple approach is to draw horizontal lines
	for (int i = -y_radius; i <= y_radius; i++) {
		int height = static_cast<int>(sqrt(x_radius * x_radius - (i * i * x_radius * x_radius) / (y_radius * y_radius)));
		SDL_Rect rect = { x - height, y + i, 2 * height, 1 };
		SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
		SDL_RenderFillRect(_renderer, &rect);
	}
	SDL_RenderPresent(_renderer);
}

void fillpoly(int num_points, int* points) {
	SDL_Point* sdl_points = new SDL_Point[num_points];
	for (int i = 0; i < num_points; ++i) {
		sdl_points[i].x = points[i * 2];
		sdl_points[i].y = points[i * 2 + 1];
	}
	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
	SDL_RenderDrawLines(_renderer, sdl_points, num_points);
	SDL_RenderPresent(_renderer);
	delete[] sdl_points;
}


bool is_within_bounds(int x, int y, int width, int height) {
	return (x >= 0 && x < width && y >= 0 && y < height);
}

bool colors_equal(const SDL_Color& c1, const SDL_Color& c2) {
	return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

void floodfill(int x, int y, int border_color) {
	int plotted_pixel = getpixel(x, y);
	if (plotted_pixel != _current_color && plotted_pixel != border_color) {
		putpixel(x, y, _current_color);
		floodfill(x + 1, y, border_color);
		floodfill(x, y + 1, border_color);
		floodfill(x - 1, y, border_color);
		floodfill(x, y - 1, border_color);
	}
}

void line(int x1, int y1, int x2, int y2) {
	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
	SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
	SDL_RenderPresent(_renderer);
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
	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
	// Text rendering code should be added here
	SDL_RenderPresent(_renderer);
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
	SDL_RenderPresent(_renderer);
}

void putimage(int left, int top, const void* bitmap, int mode) {
	// Implementation depends on the format of the bitmap
	// This is a placeholder for putting an image
	SDL_RenderPresent(_renderer);
}

void getimage(int left, int top, int right, int bottom, void* bitmap) {
	// Implementation depends on the format of the bitmap
	// This is a placeholder for getting an image
	SDL_RenderPresent(_renderer);
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
	// Create a surface from the renderer
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, _window_width, _window_height, 32, SDL_PIXELFORMAT_ARGB8888);
	if (!surface) {
		return -1;
	}

	// Read pixels from the renderer into the surface
	if (SDL_RenderReadPixels(_renderer, NULL, surface->format->format, surface->pixels, surface->pitch) != 0) {
		SDL_FreeSurface(surface);
		return -1;
	}

	// Lock the surface to access the pixel data
	SDL_LockSurface(surface);

	// Get the pixel data at (x, y)
	Uint32* pixels = (Uint32*)surface->pixels;
	Uint32 pixel_value = pixels[(y * surface->w) + x];

	// Unlock the surface
	SDL_UnlockSurface(surface);

	// Convert the pixel value to an RGBA color
	SDL_Color pixel_color;
	SDL_GetRGBA(pixel_value, surface->format, &pixel_color.r, &pixel_color.g, &pixel_color.b, &pixel_color.a);

	// Free the surface
	SDL_FreeSurface(surface);

	// Check if the colors array is valid
	if (_colors == nullptr) {
		return -1;
	}

	// Loop through the colors array to find the closest match
	for (int i = 0; i < 16; ++i) {
		if (pixel_color.r == _colors[i].r && pixel_color.g == _colors[i].g && pixel_color.b == _colors[i].b) {
			return i;
		}
	}

	// If no matching color is found
	return -1;
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
	SDL_SetRenderDrawColor(_renderer, _colors[color].r, _colors[color].g, _colors[color].b, _colors[color].a);
	SDL_RenderDrawPoint(_renderer, x, y);
	SDL_RenderPresent(_renderer);
}

void rectangle(int left, int top, int right, int bottom) {
	SDL_Rect rect = { left, top, right - left, bottom - top };
	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].

		b, _colors[_current_color].a);
	SDL_RenderDrawRect(_renderer, &rect);
	SDL_RenderPresent(_renderer);
}

inline void sector(int x, int y, int start_angle, int end_angle, int radius1, int radius2)
{
	throw "Unimplemented Function";
}

void fillrectangle(int left, int top, int right, int bottom) {
	SDL_Rect rect = { left, top, right - left, bottom - top };
	SDL_SetRenderDrawColor(_renderer, _colors[_current_color].r, _colors[_current_color].g, _colors[_current_color].b, _colors[_current_color].a);
	SDL_RenderFillRect(_renderer, &rect);
	SDL_RenderPresent(_renderer);
}

void setbkcolor(int color) {
	_bk_color = color;
	SDL_SetRenderDrawColor(_renderer, _colors[color].r, _colors[color].g, _colors[color].b, _colors[color].a);
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);
}

inline void setcolor(int color)
{
	_current_color = color;
	SDL_SetRenderDrawColor(_renderer, _colors[color].r, _colors[color].g, _colors[color].b, _colors[color].a);
	SDL_RenderPresent(_renderer);
}

inline void setfillstyle(int pattern, int color)
{
	throw "Unimplemented Function";
}

inline void setlinestyle(int type, int thickness, int size)
{
	throw "Unimplemented Function";
}

inline void settextstyle(int font, int direction, int size)
{
	throw "Unimplemented Function";
}

inline void setviewport(int left, int top, int right, int bottom, int clip)
{
	SDL_Rect clipRect = { left, top, right - left, bottom - top };
	_window_width = right - left;
	_window_height = bottom - top;
	_max_x = _window_width - 1;
	_max_y = _window_height - 1;
	SDL_RenderSetClipRect(_renderer, clip ? &clipRect : NULL);
}


inline int textheight(const char* text)
{
	return 0;
}

inline int textwidth(const char* text)
{
	return 0;
}



