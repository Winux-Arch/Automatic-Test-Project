#ifndef PPM_FORMAT_HPP
#define PPM_FORMAT_HPP

#include <string>
#include <vector>
#include "Farbe.hpp"
class PPM_File
{
private:
    int width;
    int height;
    std::string filename;
    std::vector<std::vector<Farbe>> pixelData;

public:
    static constexpr const int KLEIN = 0;
    static constexpr const int MEDIUM = 1;
    static constexpr const int GROSS = 2;
    static constexpr const int DIM[3][2]{
        {200, 150},
        {400, 300},
        {600, 450}};

    PPM_File()
        : width{1}, height{1}, filename{""}, pixelData(1, std::vector<Farbe>(1)) {}
    PPM_File(int preset)
        : width{DIM[preset][0]}, height{DIM[preset][1]}, filename{""}, pixelData(height, std::vector<Farbe>(width)) {}
    PPM_File(const std::string &filename, int width, int height)
        : width{width}, height{height}, filename{filename}, pixelData(height, std::vector<Farbe>(width)) {}
    PPM_File(const char *filename, int width, int height)
        : width{width}, height{height}, filename{filename}, pixelData(height, std::vector<Farbe>(width)) {}
    PPM_File(const std::string &filename, int width)
        : width{width}, height{width}, filename{filename}, pixelData(height, std::vector<Farbe>(width)) {}
    PPM_File(const char *filename, int width)
        : width{width}, height{width}, filename{filename}, pixelData(height, std::vector<Farbe>(width)) {}
    PPM_File(const std::string &filename, int width, int zähler, int nenner)
        : width{width}, height{width * nenner / zähler}, filename{filename}, pixelData(height, std::vector<Farbe>(width)) {}

    int getWidth() const;
    int getHeight() const;
    std::string getFilename() const;

    Farbe getPixel(int x, int y) const;

    void set(int x, int y, const Farbe &color);
    void setRow(int y, const std::vector<Farbe> &colors);
    void setColumn(int x, const std::vector<Farbe> &colors);

    const PPM_File &erzeuge_dat() const;
    static void ausgabe(const PPM_File &bild);
};

#endif // PPM_FORMAT_HPP
