#include "TablicaHaszujaca.h"


/**
\brief Znajduje dany klucz w tablicy.
\param klucz klucz do odnalezienia.
\param indeks_listy wynikowy indeks listy.
\param indeks_elementu indeks elementy na liscie.
\return Czy odnaleziono.
**/
bool TablicaHaszujaca::znajdz(TYP_KLUCZ klucz, int& indeks_listy, int& indeks_elementu) {
  indeks_listy = hasz(klucz);
  for (indeks_elementu = 0; indeks_elementu < tablica_list[indeks_listy].size(); indeks_elementu++) {
    if ((tablica_list[indeks_listy])[indeks_elementu].klucz == klucz)
      return true;
  }
  return false;
}
/**
\brief Funkcja haszujaca ciagi znakow.
\param klucz klucz do zhaszowania.
**/
int TablicaHaszujaca::hasz(TYP_KLUCZ klucz) {
  int wynik = 0;
  for (int i=0; i<klucz.length(); i++) {
    wynik += (i+1) * klucz[i];
  }
  return wynik % LICZBA_LIST;
}
/**
\brief Usuwa wszystkie elementy.
**/
void TablicaHaszujaca::usun_wszystko() {
  for (int i=0; i<LICZBA_LIST; i++) {
    tablica_list[i] = vector<ParaKluczWartosc>();
  }
}
/**
\brief Konstruktor kopiujacy.
\param inna kopiowana TablicaAsocjacyjna
**/
TablicaHaszujaca::TablicaHaszujaca(TablicaHaszujaca& inna) {
  aktualna_ilosc = inna.aktualna_ilosc;
  for (int i=0; i<LICZBA_LIST; i++) {
    for (int j=0; j<tablica_list[i].size(); j++) {
      dodaj((inna.tablica_list[i])[j].klucz, (inna.tablica_list[i])[j].wartosc);
    }
  }
}
/**
\brief Dodaje nowa pare klucz i wartosc lub zmienia istniejaca.
\param klucz klucz pary.
\param wartosc nowa wartosc.
**/
void TablicaHaszujaca::dodaj(TYP_KLUCZ& klucz, TYP_WARTOSC& wartosc) {
  int indeks_listy, indeks_elementu;
  if (znajdz(klucz, indeks_listy, indeks_elementu)) {
    (tablica_list[indeks_listy])[indeks_elementu].wartosc = wartosc;
  } else {
    tablica_list[indeks_listy].push_back(ParaKluczWartosc(klucz, wartosc));
    aktualna_ilosc++;
  }
}
/**
\brief Usuwa pare o danym kluczu jesli istenieje.
\param klucz klucz pary do usuniecia.
**/
void TablicaHaszujaca::usun(TYP_KLUCZ& klucz) {
  int indeks_listy = hasz(klucz);
  for (vector<ParaKluczWartosc>::iterator iter=tablica_list[indeks_listy].begin(); iter != tablica_list[indeks_listy].end(); iter++) {
    if (iter->klucz == klucz) {
      (tablica_list[indeks_listy]).erase(iter);
      aktualna_ilosc--;
      return;
    }
  }
}
/**
\brief Zmienia pare klucz i wartosc jesli istnieje.
\param klucz klucz pary do zmiany.
\param wartosc nowa wartosc.
**/
void TablicaHaszujaca::zmien(TYP_KLUCZ& klucz, TYP_WARTOSC& wartosc) {
  int indeks_listy, indeks_elementu;
  if (znajdz(klucz, indeks_listy, indeks_elementu)) {
    (tablica_list[indeks_listy])[indeks_elementu].wartosc = wartosc;
  }
}
/**
\brief Zwraca wartosc danej pary.
\param klucz klucz pary.
\return wartosc danej pary.
**/
const TYP_WARTOSC TablicaHaszujaca::pobierz(const TYP_KLUCZ& klucz) {
  int indeks_listy, indeks_elementu;
  if (znajdz(klucz, indeks_listy, indeks_elementu)) {
    return (tablica_list[indeks_listy])[indeks_elementu].wartosc;
  }
  return WARTOSC_ZERO;
}
/**
\brief Zwraca ilosc elementow na tablicy haszujacej.
**/
const int TablicaHaszujaca::ilosc_elementow() {
  return aktualna_ilosc;
}
const bool TablicaHaszujaca::czy_pusta() {
  return (aktualna_ilosc < 1);
}
/**
\brief Wypisuje wszystkie elementy tablicy na standardowe wyjscie.
**/
void TablicaHaszujaca::wypisz_wszystko() {
  for (int i=0; i<LICZBA_LIST; i++) {
    for (int j=0; j<tablica_list[i].size(); j++) {
      cout << (tablica_list[i])[j].klucz << " -> " << (tablica_list[i])[j].wartosc << endl;
    }
  }
}
/**
\brief Przepisuje wybrana ilosc elementow ze struktury do tablicy.
\param dane zrodlowa struktura danych.
\param ile ilosc elementow do przepisania.
**/
void TablicaHaszujaca::przepisz_strukture(StrukturaDanych& dane, int ile) {
  usun_wszystko();
  if (ile < dane.ilosc_elementow())
    ile = dane.ilosc_elementow();
  for (int i=0; i<ile; i++) {
    string klucz = dane.element_na(i);
    dodaj(klucz, i);
  }
}