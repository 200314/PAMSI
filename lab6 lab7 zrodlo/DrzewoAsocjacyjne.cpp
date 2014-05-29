/**
\file DrzewoAsocjacyjne.cpp
**/

#include "DrzewoAsocjacyjne.h"

/**
\brief Pobiera nastepny wierzcholek z lewej strony. Jesli nie istenieje to tworzy.
**/
Wierzcholek& Wierzcholek::lewy() {
  if (syn_lewy == NULL)
    syn_lewy = new Wierzcholek(this);
  return *syn_lewy;
}
/**
\brief Pobiera nastepny wierzcholek z prawej strony. Jesli nie istenieje to tworzy.
**/
Wierzcholek& Wierzcholek::prawy() {
  if (syn_prawy == NULL)
    syn_prawy = new Wierzcholek(this);
  return *syn_prawy;
}
/**
\brief Wypisuje elementy w wierzcholku i potomkach na podany strumien.
**/
void Wierzcholek::wypisz_rekurencyjnie() {
  if (czy_lewy())
    lewy().wypisz_rekurencyjnie();
  if (para.czy_istnieje())
    cout << para.klucz << " -> " << para.wartosc << endl;
  if (czy_prawy())
    prawy().wypisz_rekurencyjnie();
}
/**
\brief Pobiera pare o danym kluczu. Jesli nie istenieje to zwraca pare o kluczu zerowym.
\param klucz Poszukiwany klucz.
\return Znaleziona para, moze byc pusta.
**/
ParaKluczWartosc& DrzewoAsocjacyjne::znajdz_klucz(TYP_KLUCZ klucz) {
  Wierzcholek* aktualny = &korzen;
  while(klucz != aktualny->para.klucz && aktualny->para.czy_zajety()) {
    if(aktualny->para.klucz > klucz) {
      aktualny = &(aktualny->lewy());
    }else{
      aktualny = &(aktualny->prawy());
    }
  }
  return aktualny->para;
}

/**
\brief Usuwa wszystkie elementy.
**/
void DrzewoAsocjacyjne::usun_wszystko() {
  korzen.usun();
  korzen.para = ParaKluczWartosc();
  aktualna_ilosc = 0;
}
/**
\brief Dodaje pare o okreslonym kluczu i wartosci.
\param klucz Nowy lub juz istniejacy klucz.
\param wartosc Nowa wartosc.
**/
void DrzewoAsocjacyjne::dodaj(TYP_KLUCZ& klucz, TYP_WARTOSC& wartosc) {
  ParaKluczWartosc& para = znajdz_klucz(klucz);
  if (!para.czy_istnieje()) {
    para.klucz = klucz;
    aktualna_ilosc++;
  }
  para.wartosc = wartosc;
}
/**
\brief Zmienia wartosc na o okreslonym kluczu na wartosc zerowa.
\param klucz Klucz do usuniecia wartosci.
**/
void DrzewoAsocjacyjne::usun(TYP_KLUCZ klucz) {
  ParaKluczWartosc& para = znajdz_klucz(klucz);
  para.wartosc = WARTOSC_ZERO;
}
/**
\brief Zmienia pare o okreslonym kluczu i wartosci, jesli istnieje.
\param klucz Juz istniejacy klucz.
\param wartosc Nowa wartosc.
**/
void DrzewoAsocjacyjne::zmien(TYP_KLUCZ& klucz, TYP_WARTOSC& wartosc) {
  ParaKluczWartosc& para = znajdz_klucz(klucz);
  if (para.czy_istnieje()) {
    para.wartosc = wartosc;
  }
}
/**
\brief Pobiera wartosc na okreslonym kluczu.
\param klucz Juz istniejacy klucz.
\return Odnaleziona wartosc.
**/
const TYP_WARTOSC DrzewoAsocjacyjne::pobierz(const TYP_KLUCZ& klucz) {
  return znajdz_klucz(klucz).wartosc;
}
/**
\brief Podaje ilosc elementow znajdujacych sie na drzewie
\return Ilosc elementow.
**/
const int DrzewoAsocjacyjne::ilosc_elementow() {
  return aktualna_ilosc;
}
/**
\brief Podaje czy drzewo jest puste.
\return true - brak elementow.
false - istnieja elementy.
**/
const bool DrzewoAsocjacyjne::czy_pusta() {
  return (aktualna_ilosc <= 0);
}
/**
\brief Wypisuje wszystkie elementy na drzewie na standardowe wyjscie.
**/
void DrzewoAsocjacyjne::wypisz_wszystko() {
  korzen.wypisz_rekurencyjnie();
}
/**
\brief Przepisuje wybrana ilosc elementow ze struktury do tablicy.
\param dane zrodlowa struktura danych.
\param ile ilosc elementow do przepisania.
**/
void DrzewoAsocjacyjne::przepisz_strukture(StrukturaDanych& dane, int ile) {
  usun_wszystko();
  if (ile < dane.ilosc_elementow())
    ile = dane.ilosc_elementow();
  for (int i=0; i<ile; i++) {
    string klucz = dane.element_na(i);
    dodaj(klucz, i);
  }
}