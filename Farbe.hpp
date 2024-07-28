/*Für Farbpaletten empfehle ich einfach ein Array geordnet nach Helligkeit anzulegen.
dann kann mit Palette[Farbeton][Farbkomponente] zugreifenund ändern oder
mit Palette[Farbton].toString() eine String für PPM bekommen
  */
#ifndef FARBE_H
#define FARBE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <stdexcept> // Include for std::out_of_range

class Farbe
{
private:
    unsigned char rgba[3];

    static constexpr const int ROT_INDEX = 0;
    static constexpr const int GRUEN_INDEX = 1;
    static constexpr const int BLAU_INDEX = 2;
    static constexpr const unsigned char MAX_DECKKRAFT = 255;
    static constexpr const unsigned char MIN_DECKKRAFT = 0;
    static constexpr const char *RGBA_ROT = "Rotanteil";
    static constexpr const char *RGBA_GRUEN = "Grünanteil";
    static constexpr const char *RGBA_BLAU = "Blauanteil";

public:
    static bool LONG_OUTPUT;

    inline Farbe(unsigned char r = MAX_DECKKRAFT, unsigned char g = MAX_DECKKRAFT, unsigned char b = MAX_DECKKRAFT) : rgba{r, g, b}
    {
    }

    inline unsigned char &operator[](int index)
    {
        if (index < 0 || index > 2)
        {
            throw std::out_of_range("Index out of range");
        }
        return rgba[index];
    }

    inline const unsigned char &operator[](int index) const
    {
        if (index < 0 || index > 2)
        {
            throw std::out_of_range("Index out of range");
        }
        return rgba[index];
    };

    void ausgabe() const;
    std::string toString() const;

    void ausgabergba() const;

    friend std::ostream &operator<<(std::ostream &os, const Farbe &f);
    friend Farbe operator+(const Farbe &farbe1, const Farbe &farbe2);
};

#endif // FARBE_H
