/**
\file TablicaAsocjacyjna.cpp
**/

#include "TablicaAsocjacyjna.h"

/**
\brief Zwraca indeks danego klucza.
Wykorzystuje wyszukiwanie binarne, wymaga posortowania wzgledem kluczy.
\param klucz poszukiwany klucz.
\return indeks poszukiwanego klucza. -1 jesli napotkano blad.
**/
int TablicaAsocjacyjna::znajdz_klucz(TYP_KLUCZ klucz) {
	for (int i=0; i<ilosc_elementow(); i++) {
      if (tablica[i].klucz == klucz) {
        return i;
      }
    }
    return -1;
}
/**
\brief Zwraca pare klucz i wartosc na podanym indeksie.
\param indeks indeks pary.
\return para klucz i wartosc na podanym indeksie.
**/
ParaKluczWartosc TablicaAsocjacyjna::element_na(int indeks) {
	if (indeks>=aktualna_ilosc)
		cerr << "Blad: indeks poza zakresem. __FILE__/__LINE__" << endl;
	return tablica[indeks];
}
/**
\brief Tworzy nowa dwukrotnie wieksza tablice.
**/
void TablicaAsocjacyjna::zwieksz_rozmiar_tablicy() {
	nowa_tablica(rozmiar_tablicy * 2);
}
/**
\brief Tworzy nowa dwukrotnie mniejsza tablice.
**/
void TablicaAsocjacyjna::zmniejsz_rozmiar_tablicy() {
	nowa_tablica(rozmiar_tablicy / 2);
}
/**
\brief tworzy nowa tablice o zadanym rozmiarze i kopiuje poprzednie wartosci.
\param nowy_rozmiar nowy rozmiar tablicy
**/
bool TablicaAsocjacyjna::nowa_tablica(int nowy_rozmiar) {
	if (aktualna_ilosc > nowy_rozmiar) {
		return false;
	}
	ParaKluczWartosc *stara_tablica = tablica;
	if (tablica == NULL) {
		cerr << "Blad: wskaznik NULL. __FILE__/__LINE__" << endl;
	}
	tablica = new ParaKluczWartosc[nowy_rozmiar];
	if (tablica == NULL) {
		cerr << "Blad: wskaznik NULL. __FILE__/__LINE__" << endl;
		return false;
	}
	rozmiar_tablicy = nowy_rozmiar;
	for (int i=0; i<aktualna_ilosc; i++) {
		tablica[i] = stara_tablica[i];
	}
	delete[] stara_tablica;
	return true;
}
/**
\brief usuwa wszystkie dane i zmienia tablice na poczatkowa.
**/
void TablicaAsocjacyjna::usun_wszystko() {
	delete[] tablica;
	tablica = new ParaKluczWartosc[1];
	rozmiar_tablicy = 1;
	aktualna_ilosc = 0;
}
/**
\brief Konstruktor kopiujacy.
\param inna kopiowana TablicaAsocjacyjna
**/
TablicaAsocjacyjna::TablicaAsocjacyjna(TablicaAsocjacyjna& inna) {
	tablica = new ParaKluczWartosc[inna.rozmiar_tablicy];
	rozmiar_tablicy = inna.rozmiar_tablicy;
	aktualna_ilosc = inna.aktualna_ilosc;
	for (int i=0; i<inna.aktualna_ilosc; i++) {
		tablica[i] = inna.element_na(i);
	}
}
/**
\brief Dodaje nowa pare klucz i wartosc lub zmienia juz istniejaca.
\param klucz klucz pod jakim bedzie znajdzowac sie nowa wartosc.
\param wartosc wartosc jaka bedzie sie znajdowac pod kluczem.
**/
void TablicaAsocjacyjna::dodaj(TYP_KLUCZ& klucz, TYP_WARTOSC& wartosc) {
  int indeks = znajdz_klucz(klucz);
  if (indeks < 0) {
    if (rozmiar_tablicy <= aktualna_ilosc)
		zwieksz_rozmiar_tablicy();
	tablica[aktualna_ilosc] = ParaKluczWartosc(klucz, wartosc);
	aktualna_ilosc++;
  } else {
    tablica[indeks] = ParaKluczWartosc(klucz, wartosc);
  }
}
/**
\brief Usuwa dany element, przesuwa wszystkie elementy za nim o jedno miejsce do tylu.
\param klucz klucz pod jakim znajduje sie para.
**/
void TablicaAsocjacyjna::usun(TYP_KLUCZ& klucz) {
  int indeks = znajdz_klucz(klucz);
  if (indeks < 0) {
    return;
  } else {
    for (int i=indeks+1; i<ilosc_elementow(); i++) {
      tablica[i-1] = tablica[i];
    }
    aktualna_ilosc--;
  }
}
/**
\brief Zmienia juz istniejaca pare klucz i wartosc.
\param klucz klucz pod jakim bedzie znajdzowac sie nowa wartosc.
\param wartosc wartosc jaka bedzie sie znajdowac pod kluczem.
**/
void TablicaAsocjacyjna::zmien(TYP_KLUCZ& klucz, TYP_WARTOSC& wartosc) {
  int indeks = znajdz_klucz(klucz);
  if (indeks < 0) {
    return;
  } else {
    tablica[indeks] = ParaKluczWartosc(klucz, wartosc);
  }
}
/**
\brief Pobiera wartosc spod klucza lub wartosc zero jesli nie istenieje.
\param klucz klucz pod jakim bedzie znajdowac sie wartosc.
**/
const TYP_WARTOSC TablicaAsocjacyjna::pobierz(const TYP_KLUCZ& klucz) {
  int indeks = znajdz_klucz(klucz);
  if (indeks < 0) {
    return WARTOSC_ZERO;
  } else {
    return tablica[indeks].wartosc;
  }
}
/**
\brief zwraca ilosc elementow w tablicy.
\return ilosc elementow.
**/
const int TablicaAsocjacyjna::ilosc_elementow() {
	return aktualna_ilosc;
}
/**
\brief Sprawdza czy tablica nie zawiera zadnej pary klucz i wartosc.
\return
-true - tablica pusta
-false - tablica zawiera co najmniej jedna pare
**/
const bool TablicaAsocjacyjna::czy_pusta() {
	return (aktualna_ilosc < 1);
}

void TablicaAsocjacyjna::wypisz_wszystko() {
  for (int i=0; i<aktualna_ilosc; i++) {
    cout << tablica[i].klucz << " -> " << tablica[i].wartosc << endl;
  }
}
/**
\brief Przepisuje wybrana ilosc elementow ze struktury do tablicy.
\param dane zrodlowa struktura danych.
\param ile ilosc elementow do przepisania.
**/
void TablicaAsocjacyjna::przepisz_strukture(StrukturaDanych& dane, int ile) {
  usun_wszystko();
  if (ile < dane.ilosc_elementow())
    ile = dane.ilosc_elementow();
  for (int i=0; i<ile; i++) {
    string klucz = dane.element_na(i);
    dodaj(klucz, i);
  }
}