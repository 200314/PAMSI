#ifndef DRZEWOASOCJACYJNE
#define DRZEWOASOCJACYJNE

/**
\file DrzewoAsocjacyjne.h
**/

#include <iostream>
#include "definicje.h"
#include "ParaKluczWartosc.h"
#include "StrukturaDanych.h"

using namespace std;

/**
\brief Tablica asocjacyjna na drzewie binarnym.
**/
class Wierzcholek {
private:
  Wierzcholek* ojciec;
  Wierzcholek* syn_lewy;
  Wierzcholek* syn_prawy;
public:
  /** \brief Para klucza i wartosci na danym wierzcholku. **/
  ParaKluczWartosc para;

  Wierzcholek(Wierzcholek* p_ojciec):
    ojciec(p_ojciec), syn_lewy(NULL), syn_prawy(NULL) {};
  ~Wierzcholek() {if (syn_lewy != NULL) delete syn_lewy; if (syn_prawy != NULL) delete syn_prawy; }
  void usun() {if (syn_lewy != NULL) delete syn_lewy; syn_lewy=NULL; if (syn_prawy != NULL) delete syn_prawy; syn_prawy=NULL;}
  Wierzcholek& lewy();
  Wierzcholek& prawy();
  bool czy_lewy() {return syn_lewy != NULL;}
  bool czy_prawy() {return syn_prawy != NULL;}

  void wypisz_rekurencyjnie();
};

/**
\brief Tablica asocjacyjna na drzewie binarnym.
**/
class DrzewoAsocjacyjne {
private:
  /** \brief Pierwszy wierzcholek drzewa. **/
  Wierzcholek korzen;
  /** \brief aktualna ilosc danych zapamietanych. **/
  int aktualna_ilosc;

  ParaKluczWartosc& znajdz_klucz(TYP_KLUCZ klucz);
  void usun_wszystko();
public:
  DrzewoAsocjacyjne():
    korzen(NULL), aktualna_ilosc(0) {};

  void dodaj(TYP_KLUCZ& klucz, TYP_WARTOSC& wartosc);
  void usun(TYP_KLUCZ klucz);
  void zmien(TYP_KLUCZ& klucz, TYP_WARTOSC& wartosc);
  const TYP_WARTOSC pobierz(const TYP_KLUCZ& klucz);
  const int ilosc_elementow();
  const bool czy_pusta();

  void wypisz_wszystko();
  void przepisz_strukture(StrukturaDanych& dane, int ile);
};

#endif