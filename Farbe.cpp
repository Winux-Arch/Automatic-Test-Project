#include "Farbe.hpp"

bool Farbe::LONG_OUTPUT = true;

void Farbe::ausgabe() const
{
    if (LONG_OUTPUT)
        ausgabergba();
    else
        std::cout << toString();
}

std::string Farbe::toString() const
{
    std::ostringstream oss;
    oss << static_cast<int>(rgba[ROT_INDEX]) << ' '
        << static_cast<int>(rgba[GRUEN_INDEX]) << ' '
        << static_cast<int>(rgba[BLAU_INDEX]) << ' ';
    return oss.str();
}

void Farbe::ausgabergba() const
{
    std::cout << "(" << std::setw(3) << std::setfill('0') << static_cast<int>(rgba[ROT_INDEX]) << ","
              << static_cast<int>(rgba[GRUEN_INDEX]) << ","
              << static_cast<int>(rgba[BLAU_INDEX]) << ")" << "\n";
    std::cout << RGBA_ROT << ": " << static_cast<int>(rgba[ROT_INDEX]) << "\n";
    std::cout << RGBA_GRUEN << ": " << static_cast<int>(rgba[GRUEN_INDEX]) << "\n";
    std::cout << RGBA_BLAU << ": " << static_cast<int>(rgba[BLAU_INDEX]) << std::setfill(' ') << "\n";
}

std::ostream &operator<<(std::ostream &os, const Farbe &f)
{
    if (Farbe::LONG_OUTPUT)
    {
        f.ausgabergba();
    }
    else
    {
        os << f.toString();
    }
    return os;
}

Farbe operator+(const Farbe &farbe1, const Farbe &farbe2)
{
    Farbe res;
    res[0] = (farbe1[0] + farbe2[0]) % 256;
    res[1] = (farbe1[1] + farbe2[1]) % 256;
    res[2] = (farbe1[2] + farbe2[2]) % 256;
    return res;
}
