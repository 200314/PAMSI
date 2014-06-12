
/**
\file Wierzcholek.cpp
**/

#include "Wierzcholek.h"

using namespace std;

/**
\brief Konstruktor kopiujacy.
\param inny Kopiowany wierzcholek
**/
Wierzcholek::Wierzcholek(const Wierzcholek& inny) {
  for (int i=0; i<inny.lista_sasiadow.size(); i++) {
    lista_sasiadow.push_back(inny.lista_sasiadow[i]);
  }
  for (int i=0; i<inny.lista_kosztow.size(); i++) {
    lista_kosztow.push_back(inny.lista_kosztow[i]);
  }
  istnieje = inny.istnieje;
  x = inny.x;
  y = inny.y;
  odwiedzono = inny.odwiedzono;
  poprzedni_wierzcholek = inny.poprzedni_wierzcholek;
  koszt_sciezki = inny.koszt_sciezki;
  szacowany_koszt = inny.szacowany_koszt;
}

/**
\brief Dodaje nowa krawedz miedzy tym wierzcholkiem a podanym.
\param W docelowy wierzcholek.
\param koszt koszt/waga krawedzi.
**/
void Wierzcholek::dodaj_krawedz(int W, TYP_KOSZTU koszt) {
  if(!czy_polaczone(W)) {
    lista_sasiadow.push_back(W);
    lista_kosztow.push_back(koszt);
  }
}
/**
\brief Usuwa krawedz z list tylko tego wierzchola.
\param W docelowy wierzcholek.
**/
bool Wierzcholek::usun_krawedz(int W) {
  for (int i=0; i<lista_sasiadow.size(); i++) {
    int drugi = lista_sasiadow[i];
    if (W == drugi) {
      lista_sasiadow.erase(lista_sasiadow.begin() + i);
      lista_kosztow.erase(lista_kosztow.begin() + i);
      return true;
    }
  }
  return false;
}
/**
\brief Usuwa wszystkie krawedzie miedzy tym wierzcholkiem a wszystkimi sasiadami.
**/
bool Wierzcholek::usun_wszystkie_krawedzie() {
  lista_sasiadow.clear();
  lista_kosztow.clear();
  return true;
}
/**
\brief Sprawdza czy wierzcholki sa polaczone.
\param W docelowy wierzcholek.
**/
bool Wierzcholek::czy_polaczone(int W) {
  for (int i=0; i<lista_sasiadow.size(); i++) {
    if (lista_sasiadow[i] == W) {
      return true;
    }
  }
  return false;
}
