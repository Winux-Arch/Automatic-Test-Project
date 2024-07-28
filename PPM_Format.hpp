#ifndef PPM_FORMAT_HPP
#define PPP_FORMAT_HPP

#include <vector>
#include "Farbe.hpp"

enum class PPM_FormatType
{
    ASCII,
    Binary
};

class PPM_Format
{
protected:
    int width;
    int height;
    std::vector<std::vector<Farbe>> pixelData;

public:
    PPM_Format();
    PPM_Format(int width, int height);

    int getWidth() const;
    int getHeight() const;
    Farbe getPixel(int x, int y) const;

    void setPixel(int x, int y, const Farbe &color);
    void setRow(int y, const std::vector<Farbe> &colors);
    void setColumn(int x, const std::vector<Farbe> &colors);

    void write(std::ostream &out, PPM_FormatType format) const;
    friend std::ostream &operator<<(std::ostream &out, const PPM_Format &PPM_Format);
};

#endif // PPM_FORMAT_HPP
