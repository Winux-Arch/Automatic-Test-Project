#include "PPM_Datei.hpp"
#include <fstream>

int PPM_Datei::getWidth() const
{
    return format.getWidth();
}

int PPM_Datei::getHeight() const
{
    return format.getHeight();
}

std::string PPM_Datei::getFilename() const
{
    return filename;
}

Farbe PPM_Datei::getPixel(int x, int y) const
{
    return format.getPixel(x, y);
}

void PPM_Datei::set(int x, int y, const Farbe &color)
{
    format.setPixel(x, y, color);
}

void PPM_Datei::setRow(int y, const std::vector<Farbe> &colors)
{
    format.setRow(y, colors);
}

void PPM_Datei::setColumn(int x, const std::vector<Farbe> &colors)
{
    format.setColumn(x, colors);
}

// diese Methode kontrolliert nur ob geschrieben werden kann
bool PPM_Datei::read()
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }
    // Implement file reading logic
    file.close();
    return true;
}

bool PPM_Datei::write() const
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "Bild konnte nicht abgespeichert werden";
        return false;
    }
    format.write(file, formatType);
    file.close();
    return true;
}

bool PPM_Datei::erzeuge_dat() const
{
    return PPM_Datei::write();
}

std::ostream &operator<<(std::ostream &out, const PPM_Datei &ppmDatei)
{
    ppmDatei.format.write(out, ppmDatei.formatType);
    return out;
}

void copyData(PPM_Datei &dest, const PPM_Format &src)
{
    dest.format = src;
}
