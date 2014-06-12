/**
\file AStar.cpp
**/

#include "AStar.h"

Graf* AStar::gr = NULL;

/**
\brief Algorytm przeszukiwania grafu A*.
\param graf graf w ktorym poszukujemy sciezki.
\param W1 indeks poczatkowego wierzcholka.
\param W2 indeks docelowego wierzcholka.
\param sciezka wynikowa sciezka jesli udalo sie taka znalezc.
\return stan powodzenia funkcji.
**/
bool AStar::szukaj(Graf& graf, int W1, int W2, list<int>& sciezka) {
  gr = &graf;
  graf.reset_zmiennych_pomocniczych();
  int aktualny = W1;
  graf.wierzcholek(W1).odwiedzono = true;
  priority_queue<int, vector<int>, PorownajWierzcholki> kolejka;
  kolejka.push(W1);

  //f_score[start] := g_score[start] + heuristic_cost_estimate(start, goal)
  
  while (!kolejka.empty()) {
    aktualny = kolejka.top();
    kolejka.pop();
    if (aktualny == W2) {
      sciezka = graf.zrekonstruuj_sciezke(aktualny);
      return true;
    }
    vector<int> sasiedzi;
    vector<int> koszta;
    graf.wierzcholek(aktualny).sasiedztwo(sasiedzi, koszta);
    for (int i=0; i<sasiedzi.size(); i++) {
      if (!graf.wierzcholek(sasiedzi[i]).odwiedzono) {
        graf.wierzcholek(sasiedzi[i]).koszt_sciezki = graf.wierzcholek(aktualny).koszt_sciezki + koszta[i];
        graf.wierzcholek(sasiedzi[i]).szacowany_koszt = graf.wierzcholek(sasiedzi[i]).koszt_sciezki + graf.heurystyka(sasiedzi[i], W2);
        graf.wierzcholek(sasiedzi[i]).poprzedni_wierzcholek = aktualny;
        graf.wierzcholek(sasiedzi[i]).odwiedzono = true;
        kolejka.push(sasiedzi[i]);
      }
    }
    //graf.rysuj_graf();
    //cout << "------------------------------------" << endl;
    //cin.get();
  }
  return false;
}

