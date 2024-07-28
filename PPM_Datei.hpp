#ifndef PPM_DATEI_HPP
#define PPM_DATEI_HPP

#include <string>
#include "PPM_Format.hpp"

class PPM_Datei
{
private:
    std::string filename;
    PPM_Format format;
    PPM_FormatType formatType;

public:
    static constexpr const int KLEIN = 0;
    static constexpr const int MEDIUM = 1;
    static constexpr const int GROSS = 2;
    static constexpr const int DIM[3][2]{
        {200, 150},
        {400, 300},
        {600, 450}};

    // Rule of three oder five wird nicht benötigt da keins dieser elemnte benötigt wird, da alles in containerklassen eingepackt wird.
    // Konstruktoren sind diejenigen vorhanden, die sinnvoll erschiene oder vorgeben durch das aufgabencpp file oder die Beschreibung wraen.
    PPM_Datei(const std::string &filename, const PPM_Format &format, PPM_FormatType formatType = PPM_FormatType::ASCII)
        : filename{filename}, format{format}, formatType{formatType} {}
    PPM_Datei()
        : filename{""}, format{1, 1}, formatType{PPM_FormatType::ASCII} {}
    PPM_Datei(int preset, const std::string &filename, PPM_FormatType formatType = PPM_FormatType::ASCII)
        : filename{filename}, format{DIM[preset][0], DIM[preset][1]}, formatType{formatType} {}
    PPM_Datei(const std::string &filename, int width, int height, PPM_FormatType formatType = PPM_FormatType::ASCII)
        : filename{filename}, format{width, height}, formatType{formatType} {}
    PPM_Datei(const char *filename, int width, int height, PPM_FormatType formatType = PPM_FormatType::ASCII)
        : filename{filename}, format{width, height}, formatType{formatType} {}
    PPM_Datei(const std::string &filename, int width, PPM_FormatType formatType = PPM_FormatType::ASCII)
        : filename{filename}, format{width, width}, formatType{formatType} {}
    PPM_Datei(const char *filename, int width, PPM_FormatType formatType = PPM_FormatType::ASCII)
        : filename{filename}, format{width, width}, formatType{formatType} {}
    PPM_Datei(const std::string &filename, int width, int zähler, int nenner, PPM_FormatType formatType = PPM_FormatType::ASCII)
        : filename{filename}, format{width, width * nenner / zähler}, formatType{formatType} {}

    int getWidth() const;
    int getHeight() const;
    std::string getFilename() const;

    Farbe getPixel(int x, int y) const;
    void set(int x, int y, const Farbe &color);
    void setRow(int y, const std::vector<Farbe> &colors);
    void setColumn(int x, const std::vector<Farbe> &colors);

    bool read();
    bool write() const;
    bool erzeuge_dat() const;

    friend void copyData(PPM_Datei &dest, const PPM_Format &src);
    friend std::ostream &operator<<(std::ostream &out, const PPM_Datei &ppmDatei);
};

#endif // PPM_DATEI_HPP
