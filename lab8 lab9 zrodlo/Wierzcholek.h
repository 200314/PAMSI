#ifndef WIERZCHOLEK
#define WIERZCHOLEK

/**
\file Wierzcholek.h
**/

#include "Definicje.h"

using namespace std;

/**
\brief Struktura wierzcholka grafu.
**/
class Wierzcholek {
private:
  vector<int> lista_sasiadow;
  vector<int> lista_kosztow;
  bool istnieje;

public:
  int x, y;
  bool odwiedzono;
  int poprzedni_wierzcholek;
  int koszt_sciezki;
  int szacowany_koszt;

  Wierzcholek() : istnieje(true), x(0), y(0), odwiedzono(false), poprzedni_wierzcholek(-1), koszt_sciezki(0), szacowany_koszt(0) {};
  Wierzcholek(int x, int y) : istnieje(true), lista_sasiadow(), x(x), y(y), odwiedzono(false), poprzedni_wierzcholek(-1), koszt_sciezki(0), szacowany_koszt(0) {};
  Wierzcholek(const Wierzcholek& inny);

  void dodaj_krawedz(int W, TYP_KOSZTU koszt);
  bool usun_krawedz(int W);
  bool usun_wszystkie_krawedzie();
  void usun() {istnieje = false;}
  bool czy_istnieje() {return istnieje;}
  bool czy_polaczone(int W);
  void sasiedztwo(vector<int>& l_sasiadow) { l_sasiadow=lista_sasiadow; }
  void sasiedztwo(vector<int>& l_sasiadow, vector<int>& l_kosztow) { l_sasiadow=lista_sasiadow; l_kosztow=lista_kosztow; }
};
#endif