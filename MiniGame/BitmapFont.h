#ifndef BITMAP_FONT_H
#define BITMAP_FONT_H

class CBitmapFont
{
public:
	CBitmapFont();
	~CBitmapFont();

	void Render();
	void LoadFont(const char* path);
};

#endif

