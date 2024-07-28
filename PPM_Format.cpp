#include "PPM_Format.hpp"
#include <iostream>

PPM_Format::PPM_Format() : width{1}, height{1}, pixelData(1, std::vector<Farbe>(1)) {}

PPM_Format::PPM_Format(int width, int height) : width{width}, height{height}, pixelData(height, std::vector<Farbe>(width)) {}

int PPM_Format::getWidth() const
{
    return width;
}

int PPM_Format::getHeight() const
{
    return height;
}

Farbe PPM_Format::getPixel(int x, int y) const
{
    return pixelData[y][x];
}

void PPM_Format::setPixel(int x, int y, const Farbe &color)
{
    pixelData[y][x] = color;
}

void PPM_Format::setRow(int y, const std::vector<Farbe> &colors)
{
    pixelData[y] = colors;
}

void PPM_Format::setColumn(int x, const std::vector<Farbe> &colors)
{
    for (int y = 0; y < height; ++y)
    {
        pixelData[y][x] = colors[y];
    }
}

void PPM_Format::write(std::ostream &out, PPM_FormatType format) const
{
    if (format == PPM_FormatType::ASCII)
    {
        out << "P3\n"
            << width << " " << height << "\n255\n";
        for (const auto &row : pixelData)
        {
            for (const auto &pixel : row)
            {
                out << static_cast<int>(pixel[0]) << " "
                    << static_cast<int>(pixel[1]) << " "
                    << static_cast<int>(pixel[2]) << " ";
            }
            out << "\n";
        }
    }
    else if (format == PPM_FormatType::Binary)
    {
        out << "P6\n"
            << width << " " << height << "\n255\n";
        for (const auto &row : pixelData)
        {
            for (const auto &pixel : row)
            {
                out.put(static_cast<char>(pixel[0]));
                out.put(static_cast<char>(pixel[1]));
                out.put(static_cast<char>(pixel[2]));
            }
        }
    }
}

std::ostream &operator<<(std::ostream &out, const PPM_Format &ppmFormat)
{
    ppmFormat.write(out, PPM_FormatType::ASCII);
    return out;
}
