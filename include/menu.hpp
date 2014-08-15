#ifndef MENU_HPP
#define MENU_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <map>

namespace Suidao {

class TextBox {
	int width, height;
	int x, y;
	bool draw_background;
	Uint8 colR, colG, colB;
	std::string text;
	Uint8 textR, textG, textB;
	TTF_Font *font;

public:
	TextBox();
	TextBox(int width, int height, int x, int y, bool draw_background,
			Uint8 colR, Uint8 colG, Uint8 colB, std::string text,
			Uint8 textR, Uint8 textG, Uint8 textB,
			std::string font_loc, int font_size);
	void Draw(SDL_Renderer *renderer);
	bool inBox(int qx, int qy);
};

class Menu {
	int backgroundR, backgroundG, backgroundB;

public:
	std::map<std::string, TextBox> boxes;

	Menu();
	void Init();
	void Draw(SDL_Renderer *renderer);
};

}

#endif // MENU_HPP