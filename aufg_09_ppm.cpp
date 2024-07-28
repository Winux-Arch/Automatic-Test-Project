#include <fstream>
#include <iostream>
#include <string>
// ... weitere Includes ...

#include "Farbe.hpp"
#include "PPM_Datei.hpp"

/*
   PPM-Bild ist zeilenweise aufgebaut (oberste zuerst, dann untere)
   Dimension: BREITE Spalten, HOEHE Zeilen

     dyn_arr[i_y][i_x]: Pixel in i_x. Breite und i_y. Hoehe
*/

using namespace std;

const Farbe GOLD(238, 220, 130), ROT(255, 0, 0), GRUEN(0, 255, 0), BLAU(0, 0, 255), DUNKELGRUEN(0, 128, 0);

void auswahl_format(char &vordef, int &br, int &h_oder_v_zaehler, int &v_nenner);
void test_rahmen(char vordef, int br, int h_oder_v_zaehler, int v_nenner);

int main()
{
  char vordef;
  int breite, hoehe_v_zaehler, v_nenner;

  auswahl_format(vordef, breite, hoehe_v_zaehler, v_nenner);
  test_rahmen(vordef, breite, hoehe_v_zaehler, v_nenner);

  return 0;
}

void auswahl_format(char &vordef, int &br, int &h_oder_v_zaehler, int &v_nenner)
{
  int wahl;
  v_nenner = 1;

  cout << "Auswahl des Bildformats:" << endl;
  cout << "  (1) erstes  vordef. Format " << PPM_Datei::DIM[0][0] << "x" << PPM_Datei::DIM[0][1] << endl;
  cout << "  (2) zweites vordef. Format " << PPM_Datei::DIM[1][0] << "x" << PPM_Datei::DIM[1][1] << endl;
  cout << "  (3) drittes vordef. Format " << PPM_Datei::DIM[2][0] << "x" << PPM_Datei::DIM[2][1] << endl;
  cout << "  (4) eigenes quadratisches Format mit string" << endl;
  cout << "  (5) eigenes rechteckiges  Format mit string" << endl;
  cout << "  (6) eigenes quadratisches Format mit const char *" << endl;
  cout << "  (7) eigenes rechteckiges  Format mit const char *" << endl;
  cout << "  (8) eigenes rechteckiges  Verhaeltnis mit string" << endl;

  cout << "Wahl: ";
  cin >> wahl;

  switch (wahl)
  {
  case 1:
    vordef = PPM_Datei::KLEIN;
    br = PPM_Datei::DIM[0][0];
    h_oder_v_zaehler = PPM_Datei::DIM[0][1];
    break;

  case 2:
    vordef = PPM_Datei::MEDIUM;
    br = PPM_Datei::DIM[1][0];
    h_oder_v_zaehler = PPM_Datei::DIM[1][1];
    break;

  case 3:
    vordef = PPM_Datei::GROSS;
    br = PPM_Datei::DIM[2][0];
    h_oder_v_zaehler = PPM_Datei::DIM[2][1];
    break;

  case 4:
  case 6:
    vordef = (wahl == 4 ? 'Q' : 'q');
    cout << "  Breite: ";
    cin >> br;
    h_oder_v_zaehler = br;
    break;

  case 5:
  case 7:
    vordef = (wahl == 5 ? 'R' : 'r');
    cout << "  Breite: ";
    cin >> br;
    cout << "  Hoehe: ";
    cin >> h_oder_v_zaehler;
    break;

  case 8:
    vordef = 'V';
    cout << "  Breite: ";
    cin >> br;
    cout << "  Zaehler vom Verhaeltnis: ";
    cin >> h_oder_v_zaehler;
    cout << "  Nenner  vom Verhaeltnis: ";
    cin >> v_nenner;
    break;

  default:
    cerr << "fehlerhafte Eingabe " << wahl << endl;
    cerr << "Verwende 1. Standardformat!" << endl;
    vordef = '1';
    br = PPM_Datei::DIM[0][0];
    h_oder_v_zaehler = PPM_Datei::DIM[0][1];
  }
}

void test_rahmen(char vordef, int br, int h_oder_v_zaehler, int v_nenner)
{
  const char *dat_name_old = "rahmen.ppm";
  string dat_name = dat_name_old;

  PPM_Datei bild;

  if (vordef >= PPM_Datei::KLEIN && vordef <= PPM_Datei::GROSS)
    bild = PPM_Datei(vordef, dat_name);
  else if (vordef == 'Q')
    bild = PPM_Datei(dat_name, br);
  else if (vordef == 'q')
    bild = PPM_Datei(dat_name_old, br);
  else if (vordef == 'R')
    bild = PPM_Datei(dat_name, br, h_oder_v_zaehler);
  else if (vordef == 'r')
    bild = PPM_Datei(dat_name_old, br, h_oder_v_zaehler);
  else if (vordef == 'V')
    bild = PPM_Datei(dat_name, br, h_oder_v_zaehler, v_nenner);
  else
    bild = PPM_Datei(dat_name, br, h_oder_v_zaehler);

  int &h = h_oder_v_zaehler;
  // i_y: y-Koordinate, i_x: x-Koordinate
  //   (roter Rahmen, gruenes Innes):
  // 300 x 200 Pixel abgespeichert als 200 x 300-Matrix:

  // i_y: y-Koordinate, i_x: x-Koordinate
  for (int i_x = 0; i_x < br; ++i_x) // durchlaeuft die Breite
  {
    for (int i_y = 0; i_y < h / 6; ++i_y) // durchlaeuft die Hoehe
      bild.set(i_x, i_y, ROT);
    for (int i_y = h - 1 - h / 6; i_y < h; ++i_y)
      bild.set(i_x, i_y, ROT);
  }

  for (int i_y = 0; i_y < h; ++i_y)
  {
    for (int i_x = 0; i_x < h / 6; ++i_x)
      bild.set(i_x, i_y, ROT);
    for (int i_x = br - 1 - h / 6; i_x < br; ++i_x)
      bild.set(i_x, i_y, ROT);
  }

  for (int i_x = br / 3; i_x < 2 * br / 3; ++i_x)
    for (int i_y = h / 3; i_y < 2 * h / 3; ++i_y)
      bild.set(i_x, i_y, DUNKELGRUEN);

  // // bild.setAllPixels(br, h, pixel);
  // bild.setAllPixels(br, h, &pixel[0][0]);

  bild.erzeuge_dat();

  ifstream fin(dat_name);
  string zeile;

  if (fin.fail())
  {
    cerr << "Fehler! Eingabedatei " << dat_name << " nicht vorhanden!" << endl;
    return;
  }

  while (!fin.eof() && !fin.fail())
  {
    getline(fin, zeile);
    cout << zeile << endl;
  }

  fin.close();
}
