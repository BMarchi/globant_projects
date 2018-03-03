#include <iostream>
#include <SDL.h>
using namespace std;

const int Hilbert_Size = 4;
const int widthH = 512;
int x = 0;
int y = 0;
int x0 = 0;
int y00 = 0;
int h = 0;

void A(int i, SDL_Renderer *renderer);
void B(int i, SDL_Renderer *renderer);
void C(int i, SDL_Renderer *renderer);
void D(int i, SDL_Renderer *renderer);
void DrawLine(SDL_Renderer *renderer, int xs_point, int ys_point, int xt_point, int yt_point) {
	SDL_RenderDrawLine(renderer, xs_point, ys_point, xt_point, yt_point);
}


int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		int i = 1;
		h = widthH;
		x0 = h / 2;
		y00 = x0;
		bool done = false;
		if (SDL_CreateWindowAndRenderer(1024, 768, 0, &window, &renderer) == 0) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			while (i <= Hilbert_Size) {
				A(i, renderer);
				++i;
				h = h / 2;
				x0 = x0 + (h / 2);
				y00 = y00 + (h / 2);
				x = x0;
				y = y00;

			}
			SDL_RenderPresent(renderer);

			while (!done) {
				SDL_Event event;
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
	SDL_Quit();
	return 0;
	return 0;
}

void A(int i, SDL_Renderer *renderer) {
	if (i > 0) {
		D(i - 1, renderer);
		x = x - h;
		DrawLine(renderer, x0, y00, x, y);
		A(i - 1, renderer);
		y = y - h;
		DrawLine(renderer, x0, y00, x, y);
		A(i - 1, renderer);
		x = x + h;
		DrawLine(renderer, x0, y00, x, y);
		B(i - 1, renderer);
	}
}

void B(int i, SDL_Renderer *renderer) {
	if (i > 0) {
		C(i - 1, renderer);
		y = y + h;
		DrawLine(renderer, x0, y00, x, y);
		B(i - 1, renderer);
		x = x + h;
		DrawLine(renderer, x0, y00, x, y);
		B(i - 1, renderer);
		y = y - h;
		DrawLine(renderer, x0, y00, x, y);
		A(i - 1, renderer);
	}
}

void C(int i, SDL_Renderer *renderer) {
	if (i > 0) {
		B(i - 1, renderer);
		x = x + h;
		DrawLine(renderer, x0, y00, x, y);
		C(i - 1, renderer);
		y = y + h;
		DrawLine(renderer, x0, y00, x, y);
		C(i - 1, renderer);
		x = x - h;
		DrawLine(renderer, x0, y00, x, y);
		D(i - 1, renderer);
	}
}

void D(int i, SDL_Renderer *renderer) {
	if (i > 0) {
		A(i - 1, renderer);
		y = y - h;
		DrawLine(renderer, x0, y00, x, y);
		D(i - 1, renderer);
		x = x - h;
		DrawLine(renderer, x0, y00, x, y);
		D(i - 1, renderer);
		y = y + h;
		DrawLine(renderer, x0, y00, x, y);
		C(i - 1, renderer);
	}
}