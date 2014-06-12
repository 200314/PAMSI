
/**
\file DepthSearch.cpp
**/

#include "DepthSearch.h"
/**
\brief Algorytm przeszukiwania grafy wglab.
\param graf graf w ktorym poszukujemy sciezki.
\param W1 indeks poczatkowego wierzcholka.
\param W2 indeks docelowego wierzcholka.
\param sciezka wynikowa sciezka jesli udalo sie taka znalezc.
\return stan powodzenia funkcji.
**/
bool DepthSearch::szukaj(Graf& graf, int W1, int W2, list<int>& sciezka) {
  stack<int> stos;
  graf.reset_zmiennych_pomocniczych();
  stos.push(W1);
  int aktualny;
  graf.wierzcholek(W1).odwiedzono = true;
  while (!stos.empty()) {
    aktualny = stos.top();
    stos.pop();
    if (aktualny == W2) {
      sciezka = graf.zrekonstruuj_sciezke(aktualny);
      return true;
    }
    vector<int> sasiedzi;
    graf.wierzcholek(aktualny).sasiedztwo(sasiedzi);
    for (int i=0; i<sasiedzi.size(); i++) {
      if (!graf.wierzcholek(sasiedzi[i]).odwiedzono) {
        graf.wierzcholek(sasiedzi[i]).poprzedni_wierzcholek = aktualny;
        graf.wierzcholek(sasiedzi[i]).odwiedzono = true;
        stos.push(sasiedzi[i]);
      }
    }
    //graf.rysuj_graf();
    //cout << "------------------------------------" << endl;
    //cin.get();
  }
  return false;
}