#ifndef TEXTDATA_H
#define TEXTDATA_H

#include <unordered_map>
#include <string>

struct CharData final
{
	int x = 0, y = 0;
	int width = 0, height = 0;
	int xoffset = 0, yoffset = 0;
	int xadvance = 0;
};
struct TextData final
{
    std::unordered_map<int, CharData> fontData;
    std::string textureName;
    int lineHeight;
};

#endif
