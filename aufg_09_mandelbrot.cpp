// Habe für Linux noch eog als viewer hinzugefügt ( Gnome STandard)

#include <cassert>
#include <complex>
#include <cstdlib> // fuer system(..)
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

// Include der Headerdatei der eigenen Klasse "Farbe":
// ...

#include "Farbe.hpp"

using namespace std;

using Komplex = complex<double>;

const bool DEBUG = false;
// const bool DEBUG = true;

const double XMIN = -2.25;      // kleinster x-Wert in Mandelbrotmenge
const double XMAX = 0.75;       // groesster x-Wart in Mandelbrotmenge
const double YMIN = -1.5;       // kleinster y-Wert in Mandelbrotmenge
const double YMAX = 1.5;        // groesster y-Wert in Mandelbrotmenge
const int MAX_ITERATIONS = 150; // Anzahl der Iterationen zur Berechnung der Mandelbrotmenge
const double M = 2.0;           // maximaler Betrag der komplexen Iterierten

const int ANZ_FARBEN = 17;
const Farbe JET_RGB[ANZ_FARBEN] = {Farbe(0, 0, 0),
                                   Farbe(0, 0, 191),
                                   Farbe(0, 0, 255),
                                   Farbe(0, 64, 255),
                                   Farbe(0, 128, 255),
                                   Farbe(0, 191, 255),
                                   Farbe(0, 255, 255),
                                   Farbe(64, 255, 191),
                                   Farbe(128, 255, 128),
                                   Farbe(191, 255, 64),
                                   Farbe(255, 255, 0),
                                   Farbe(255, 191, 0),
                                   Farbe(255, 128, 0),
                                   Farbe(255, 64, 0),
                                   Farbe(255, 0, 0),
                                   Farbe(191, 0, 0),
                                   Farbe(128, 0, 0)};

/* so detailiert war das nicht noetig fuer die ZP */
// Taugt nicht für gnome eog fehlte
const int ANZ_LINUX_PROGS = 6;
const string LINUX_PROGS[ANZ_LINUX_PROGS] = {"eog", "gwenview", "xview", "xv", "gnome-open", "kde-open"};
const int ANZ_MAC_PROGS = 2;
const string MAC_PROGS[ANZ_MAC_PROGS] = {"open /Applications/Preview.app/Contents/MacOS/Preview", "open"};

using namespace std;

/*
   Berechnen der Mandelbrotmenge.
*/
void berechne_mandelbrot(const string &name, int w, int h);

/*
   Hauptmenue des Programms.
*/
void eingabe(int &width, int &height);
void starte_viewer(const string &name);

/*
   Hauptprogramm.
*/
int main(int argn, char **argv)
{
  int width, height;
  string dat_name = "mandelbrot.ppm";

  if (argn != 4)
    eingabe(width, height);
  else
  {
    width = atoi(argv[1]);
    height = atoi(argv[2]);
  }

  berechne_mandelbrot(dat_name, width, height);
  starte_viewer(dat_name);

  return 0;
}

void berechne_mandelbrot(const string &name, int w, int h)
{
  int farb_nr, sp_in_zeile;
  ofstream fout(name);

  Farbe::LONG_OUTPUT = false;

  // Headerinfos der PPM-Datei
  fout << "P3" << endl;
  fout << w << " " << h << endl;
  fout << 255 << endl;

  // Schleifen
  for (int i = 0; i < h; i++)
  {
    sp_in_zeile = 0;

    for (int j = 0; j < w; j++)
    {
      // Real- und Imaginaerteil
      double real = XMIN + j * (XMAX - XMIN) / (w - 1);
      double imag = YMIN + i * (YMAX - YMIN) / (h - 1);
      Komplex z;

      // Parameter c setzen
      Komplex c(real, imag);
      int k;

      // Schleife und Abbruch
      for (k = 0; k < MAX_ITERATIONS && abs(z) <= M; k++)
      {
        // Iteration
        z = pow(z, 2);
        z += c;
      }

      // Farbnummer setzen
      if (k < MAX_ITERATIONS)
        farb_nr = (k % (ANZ_FARBEN - 1)) + 1;
      else
        farb_nr = 0;

      fout << JET_RGB[farb_nr].toString();
      sp_in_zeile += 3 * 4; // 3 int-Werte mit max. 3 Zeichen und einem Leerzeichen
      cout << sp_in_zeile << " .. ";
      if (j < w - 1 && sp_in_zeile + 3 * 4 < 70)
        fout << " ";
      else
      {
        fout << endl;
        cout << endl;
        sp_in_zeile = 0;
      }
    }
  }

  fout.close();
}

void eingabe(int &width, int &height)
{
  cout << "Image resolution (width height): ";
  cin >> width >> height;
}

void starte_viewer(const string &name)
{
  int status, wahl;
  string kommando, prog;

  /* so detailiert war das nicht noetig fuer die ZP */
  cout << "Auswahl des Betriebssystems:" << endl;
  cout << "(1) Linux oder (2) Mac: ";
  cin >> wahl;

  switch (wahl)
  {
  case 1:
    cout << "Auswahl des Programmes:" << endl;
    cout << "(1) eog" << endl;
    cout << "(2) gwenview" << endl;
    cout << "(3) xv" << endl;
    cout << "(4) xview" << endl;
    cout << "(5) gnome-open (Standardprogramm fuer PPM-Dateien unter Gnome)" << endl;
    cout << "(6) kde-open (Standardprogramm fuer PPM-Dateien unter KDE)" << endl;
    cin >> wahl;
    assert(wahl >= 1 && wahl <= ANZ_LINUX_PROGS);
    prog = LINUX_PROGS[wahl - 1];
    break;
  case 2:
    cout << "Auswahl des Programmes:" << endl;
    cout << "(1) open mit Preview-App" << endl;
    cout << "(2) open (Standardprogramm fuer PPM-Dateien unter Mac)" << endl;
    cin >> wahl;
    assert(wahl >= 1 && wahl <= ANZ_MAC_PROGS);
    prog = MAC_PROGS[wahl - 1];
    break;
  default:
    cerr << "Fehlerhafte Auswahl " << wahl << ", nur 1-2 erlaubt!" << endl;
    cerr << "Abbruch!" << endl;
    exit(1);
  }

  kommando = prog + " " + name;
  status = system(kommando.c_str());

  if (status == 0)
    cout << "Start des Programmes war erfolgreich!" << endl;
  else
    cerr << "Start des Programmes ergab den Fehlerstatus " << status << "!" << endl;
}
