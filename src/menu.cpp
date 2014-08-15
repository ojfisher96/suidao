#include "SDL2/SDL.h"
#include "suidao.hpp"
#include "menu.hpp"
#include <string>
#include <map>

namespace Suidao {

TextBox::TextBox() {}

// Constructs a text box, including its size, position, text, font and background colour
TextBox::TextBox(int width, int height, int x, int y, bool draw_background,
		Uint8 colR, Uint8 colG, Uint8 colB, std::string text,
		Uint8 textR, Uint8 textG, Uint8 textB,
		std::string font_loc, int font_size) {
	this->width = width; this->height = height;
	this->x = x; this->y = y;
	this->draw_background = draw_background;
	this->colR = colR; this->colG = colG; this->colB = colB;
	this->text = text;
	this->textR = textR; this->textG = textG; this->textB = textB;
	this->font = TTF_OpenFont(font_loc.c_str(), font_size);
}

// Draws the text box onto the screen
void TextBox::Draw(SDL_Renderer *renderer) {
	SDL_Colour colour = {textR, textG, textB, 0};
	SDL_Surface *textSurface = 
		TTF_RenderText_Blended_Wrapped(font, text.c_str(), colour, width);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect rect;
	rect.x = x; rect.y = y;
	rect.w = width; rect.h = height;
	if (draw_background) {
		SDL_SetRenderDrawColor(renderer, colR, colG, colB, 0);
		SDL_RenderFillRect(renderer, &rect);
	}
	SDL_RenderCopy(renderer, textTexture, NULL, &rect);
}

// Checks whether a given point lies within the text box
bool TextBox::inBox(int qx, int qy) {
	return qx >= x && qx <= x + width && qy >= y && qy <= y + height;
}

Menu::Menu() {}

// Sets up the menu, initialising the text boxes
void Menu::Init() {
	this->boxes["title"] = TextBox(150, 75, 245, 75, 0, 0, 0, 0,
			"SUIDAO", 0, 0, 0, "content/font.ttf", 27);
	this->boxes["play"] = TextBox(100, 50, 75, 350, true, 0, 0, 0, 
			"PLAY", 0, 255, 0, "content/font.ttf", 18);
	this->boxes["quit"] = TextBox(100, 50, 465, 350, true, 0, 0, 0,
			"QUIT", 255, 0, 0, "content/font.ttf", 18);
}

// Draws the background of the menu and then its text boxes on top
void Menu::Draw(SDL_Renderer *renderer) {
	SDL_Rect backg;
	backg.x = backg.y = 0;
	backg.w = SCREEN_WIDTH; backg.h = SCREEN_HEIGHT;
	SDL_SetRenderDrawColor(renderer, 192, 192, 192, 0);
	SDL_RenderFillRect(renderer, &backg);

	for (std::map<std::string,TextBox>::iterator it = boxes.begin();
		it != boxes.end(); ++it) {
		it->second.Draw(renderer);
	}
}


}