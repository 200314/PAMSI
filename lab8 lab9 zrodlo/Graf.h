#ifndef GRAF
#define GRAF

/**
\file Graf.h
**/

#include "Wierzcholek.h"
#include "Definicje.h"

using namespace std;

/**
\brief Implementacja grafu.
**/
class Graf {
private:
  vector<Wierzcholek> tab_wierzcholkow;
  //Wierzcholek w;
  //bool wez_wierzcholek(int index, Wierzcholek& wynik);

public:
  Graf() {};
  Graf(const Graf& inny);

  Wierzcholek& wierzcholek(int W);
  int dodaj_wierzcholek();
  int dodaj_wierzcholek(int x, int y);
  
  int ilosc_wierzcholkow();
  bool dodaj_krawedz(int W1, int W2, TYP_KOSZTU koszt);
  bool usun_wierzcholek(int W);
  bool usun_krawedz(int W1, int W2);
  bool czy_polaczone(int W1, int W2);
  void sasiedztwo(int W, vector<int> l_sasiadow, vector<int> l_kosztow) { tab_wierzcholkow[W].sasiedztwo(l_sasiadow, l_kosztow); }

  int znajdz_losowy_wierzcholek();
  void reset_zmiennych_pomocniczych();
  list<int> zrekonstruuj_sciezke(int W);
  void generuj_graf(int rozmiar);
  void rysuj_graf();
  void wspolrzedne_wierzcholka(int W);
  int heurystyka(int W1, int W2);
};

#endif