#ifndef TABLICAASOCJACYJNA
#define TABLICAASOCJACYJNA

/**
\file TablicaAsocjacyjna.h
**/

#include <iostream>
#include "definicje.h"
#include "ParaKluczWartosc.h"
#include "StrukturaDanych.h"

using namespace std;

/**
\brief Tablica asocjacyjna.
**/
class TablicaAsocjacyjna {
private:
  /** \brief Tablica z danymi. **/
  ParaKluczWartosc *tablica;
  /** \brief rozmiar zaalakowanej tablicy. **/
  int rozmiar_tablicy;
  /** \brief aktualna ilosc danych zapamietanych. **/
  int aktualna_ilosc;

  int znajdz_klucz(TYP_KLUCZ klucz);
  ParaKluczWartosc element_na(int indeks);
  void zwieksz_rozmiar_tablicy();
  void zmniejsz_rozmiar_tablicy();
  bool nowa_tablica(int nowy_rozmiar);
  void usun_wszystko();
public:
  TablicaAsocjacyjna():
	tablica(new ParaKluczWartosc[1]),
	rozmiar_tablicy(1),
	aktualna_ilosc(0) {};
  TablicaAsocjacyjna(TablicaAsocjacyjna& inna);
  ~TablicaAsocjacyjna() {if (tablica!=NULL) delete[] tablica;};
	
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