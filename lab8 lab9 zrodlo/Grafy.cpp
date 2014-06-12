
/**
\file Grafy.cpp
**/

#include "Grafy.h"

/**
\brief zapisuje dane do pliku .csv
dane zawieraja:
1 kolumna: wielkosc problemu
2 kolumna: czas potrzebny do zrealizowanego danego problemu
\param *nazwa_pliku nazwa pliku do zapisu
\param *col_rozmiar_problemu tablica z 1 kolumna
\param *col_czas druga kolumna
\param rozmiar rozmiar obu tablic
\return
- true sukces
- false blad
**/
bool zapisz_dane(const char *nazwa_pliku, int *col_rozmiar_problemu, double *col_czas, int rozmiar) {
  ofstream plik;
  plik.open(nazwa_pliku, ios::out | ios::trunc);
  if (!plik.good())
    return false;
  for (int i=0; i<rozmiar;) {
    int aktualny_rozmiar_problemu = col_rozmiar_problemu[i];
    int powtorzen = 0;
    double suma_czasow = 0.0;
    while(aktualny_rozmiar_problemu == col_rozmiar_problemu[i]) {
      suma_czasow += col_czas[i];
      powtorzen++;
      i++;
    }
    plik << aktualny_rozmiar_problemu << "," << powtorzen << "," << suma_czasow/powtorzen << endl;
  }
  plik.close();
  cout << "Zapisano do: " << nazwa_pliku << endl;
  return true;
}
/**
\brief wykonuje testy czasu algorytmu dla przygotowanych parametrow
zmierzone czasu zapisuje do pliku
\param double(*algorytm) funkcja z algorytmem do testowania
\param *tablica dane dla algorytmu
\param rozmiar rozmiar tablicy
\param *plik_wyjsciowy nazwa pliku do zapisu zmierzonych czasow
**/
void testuj_algorytm(bool(*algorytm)(Graf& graf, int W1, int W2, list<int>& sciezka), const char *plik_wyjsciowy) {
  Graf graf;
  int tab_wielkosci[] = WIELKOSCI_PROBLEMU;

  int liczba_col = LICZBA_POWTORZEN * LICZBA_WIELKOSCI;
  int col_rozmiar_problemu[LICZBA_POWTORZEN * LICZBA_WIELKOSCI];
  double col_czas[LICZBA_POWTORZEN * LICZBA_WIELKOSCI];

  int aktualny_rozmiar = 0;
  double czas_start = 0;
  double czas_koniec = 0;

  srand(clock());
  cout << "Postep: ";
  for(int i=0; i<LICZBA_WIELKOSCI; i++) {
    aktualny_rozmiar = tab_wielkosci[i];
    graf.generuj_graf(aktualny_rozmiar);
    for(int j=0; j<LICZBA_POWTORZEN; j++) {
      int index = i*LICZBA_POWTORZEN + j;

      col_rozmiar_problemu[i*LICZBA_POWTORZEN + j] = aktualny_rozmiar;

      double czas_koniec;
      bool sukces;
      list<int> sciezka;
      do {
        int w1 = graf.znajdz_losowy_wierzcholek();
        int w2 = graf.znajdz_losowy_wierzcholek();
        double czas_start = (double)clock()/CLOCKS_PER_SEC;
        sukces = algorytm(graf, w1, w2, sciezka);
        czas_koniec= (double)clock()/CLOCKS_PER_SEC;
      } while (!sukces);

      col_czas[i*LICZBA_POWTORZEN + j] = czas_koniec - czas_start;

      cout << "\r";
      cout << "Postep: ";
      cout.width(4);
      cout << (i*LICZBA_POWTORZEN+j+1) << "/" << (LICZBA_POWTORZEN * LICZBA_WIELKOSCI);
    }
  }
  cout << endl;
  zapisz_dane(plik_wyjsciowy, col_rozmiar_problemu, col_czas, liczba_col);
}
int main() {
  srand( time( NULL ) );
  testuj_algorytm(BreadthSearch::szukaj, "Breadth.csv");
  testuj_algorytm(DepthSearch::szukaj, "Depth.csv");
  testuj_algorytm(AStar::szukaj, "AStar.csv");


  cout << "Gotowe:";
  cin.get();
  return 0;
}