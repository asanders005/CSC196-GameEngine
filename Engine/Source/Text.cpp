#include "Text.h"
#include "Renderer.h"
#include "Color.h"
#include "Font.h"
#include <SDL_ttf.h>
#include <iostream>
#include <cassert>

Text::~Text()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
	}
}

bool Text::Create(Renderer& renderer, const std::string& text, const Color& color)
{
	// create a surface using the font, text string and color
	SDL_Color c{ Color::ToInt(color.r), Color::ToInt(color.g), Color::ToInt(color.b), Color::ToInt(color.a) };
	SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), c);
	if (surface == nullptr)
	{
		std::cerr << "Could not create surface.\n";
		return false;
	}

	// create a texture from the surface, only textures can render to the renderer
	m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
	if (surface == nullptr)
	{
		SDL_FreeSurface(surface);
		std::cerr << "Could not create texture" << SDL_GetError() << std::endl;
		return false;
	}


	// free the surface, no longer needed after creating the texture
	SDL_FreeSurface(surface);

	return true;
}

void Text::Draw(Renderer& renderer, int x, int y)
{
	assert(m_texture);

	// query the texture for the texture width and height
	int width, height;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);

	// copy the texture onto the renderer
	if (m_centered)
	{
		SDL_Rect rect{ x - (width / 2), y - (height / 2), width, height };
		SDL_RenderCopy(renderer.m_renderer, m_texture, NULL, &rect);
	}
	else
	{
		SDL_Rect rect{ x, y, width, height };
		SDL_RenderCopy(renderer.m_renderer, m_texture, NULL, &rect);
	}
}
