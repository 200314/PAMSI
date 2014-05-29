#ifndef TABLICAHASZUJACA
#define TABLICAHASZUJACA

/**
\file TablicaHaszujaca.h
**/

#include <iostream>
#include <vector>
#include "definicje.h"
#include "ParaKluczWartosc.h"
#include "StrukturaDanych.h"

using namespace std;

/**
\brief Tablica haszujaca.
**/
class TablicaHaszujaca {
private:
  /** \brief Tablica list. **/
  vector<ParaKluczWartosc> tablica_list[LICZBA_LIST];
  /** \brief aktualna ilosc danych zapamietanych. **/
  int aktualna_ilosc;

  bool znajdz(TYP_KLUCZ klucz, int& indeks_listy, int& indeks_elementu);
  int hasz(TYP_KLUCZ klucz);
  void usun_wszystko();
public:
  TablicaHaszujaca(void) : aktualna_ilosc(0) {};
  TablicaHaszujaca(TablicaHaszujaca& inna);

  void dodaj(TYP_KLUCZ& klucz, TYP_WARTOSC& wartosc);
  void usun(TYP_KLUCZ& klucz);
  void zmien(TYP_KLUCZ& klucz, TYP_WARTOSC& wartosc);
  const TYP_WARTOSC pobierz(const TYP_KLUCZ& klucz);
  const int ilosc_elementow();
  const bool czy_pusta();

  void wypisz_wszystko();
  void przepisz_strukture(StrukturaDanych& dane, int ile);
};

#endif