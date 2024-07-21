#pragma once
#include <string>

class Font;
class Renderer;
class Color;
class SDL_Texture;

class Text
{
public:
	Text() = default;
	Text(Font* font, bool centered = false) : m_font{ font }, m_centered{ centered } {}
	~Text();

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, int x, int y);

private:
	Font* m_font{ nullptr };
	SDL_Texture* m_texture{ nullptr };
	bool m_centered = false;
};