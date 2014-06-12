/**
\file Graf.cpp
**/

#include "Graf.h"

using namespace std;
/**
\brief Zwraca wierzcholek o danym indeksie.
\param index index wierzcholka.
\param wynik znaleziony wierzcholek.
\return Sukces.
**/
/*bool Graf::wez_wierzcholek(int index, Wierzcholek& wynik) {
  if (index<tab_wierzcholkow.size() && index >= 0) {
    wynik = tab_wierzcholkow[index];
    return true;
  }
  return false;
}*/
/**
\brief Konstruktor kopiujacy.
\param inny kopiowany graf.
**/
Graf::Graf(const Graf& inny) {
  for (int i=0; i<inny.tab_wierzcholkow.size(); i++) {
    tab_wierzcholkow.push_back(inny.tab_wierzcholkow[i]);
  }
}
/**
\brief Zwraca wierzcholek o podanym indeksie.
\param W indeks wierzcholka.
**/
Wierzcholek& Graf::wierzcholek(int W) {
  return tab_wierzcholkow[W];
}
/**
\brief Tworzy nowy wierzcholek bez zadnych krawedzi.
\return indeks dodanego wierzcholka.
**/
int Graf::dodaj_wierzcholek() {
  Wierzcholek& w = Wierzcholek();
  tab_wierzcholkow.push_back(w);
  return tab_wierzcholkow.size()-1;
}
/**
\brief Tworzy nowy wierzcholek bez zadnych krawedzi, z ustawionymi wspolrzednymi.
\return indeks dodanego wierzcholka.
**/
int Graf::dodaj_wierzcholek(int x, int y) {
  Wierzcholek& w = Wierzcholek(x, y);
  tab_wierzcholkow.push_back(w);
  return tab_wierzcholkow.size()-1;
}
/**
\brief Zwraca ilosc wszystkich wierzcholkow.
**/
int Graf::ilosc_wierzcholkow() {
  return tab_wierzcholkow.size();
}
/**
\brief Dodaje krawedz miedzy dwoma wierzcholkami.
\param W1 indeks pierwszego wierzcholka.
\param W2 indeks drugiego wierzcholka.
\param koszt koszt/waga krawedzi.
\return Sukces.
**/
bool Graf::dodaj_krawedz(int W1, int W2, TYP_KOSZTU koszt) {
  if (W1 >= 0 && W2 >= 0 && W1 < tab_wierzcholkow.size() && W2 < tab_wierzcholkow.size()) {
    tab_wierzcholkow[W1].dodaj_krawedz(W2, koszt);
    tab_wierzcholkow[W2].dodaj_krawedz(W1, koszt);
    return true;
  }
  return false;
}
/**
\brief Usuwa wierzcholek i krawedzie ktore z niego wychodza.
\param W indeks wierzcholka.
\return Sukces.
**/
bool Graf::usun_wierzcholek(int W) {
  //usuwanie krawedzi
  vector<int> lista_sasiadow;
  tab_wierzcholkow[W].sasiedztwo(lista_sasiadow);
  for (int i=0; i<lista_sasiadow.size(); i++) {
    tab_wierzcholkow[lista_sasiadow[i]].usun_krawedz(W);
  }
  tab_wierzcholkow[W].usun_wszystkie_krawedzie();
  tab_wierzcholkow[W].usun();
  return true;
}
/**
\brief Usuwa krawedz miedzy dwoma wierzcholkami.
\param W1 indeks pierwszego wierzcholka.
\param W2 indeks drugiego wierzcholka.
**/
bool Graf::usun_krawedz(int W1, int W2) {
  return tab_wierzcholkow[W1].usun_krawedz(W2);
  return tab_wierzcholkow[W2].usun_krawedz(W1);
}
/**
\brief Sprawdza czy istnieje krawedz miedzy dwoma wierzcholkami.
\param W1 indeks pierwszego wierzcholka.
\param W2 indeks drugiego wierzcholka.
**/
bool Graf::czy_polaczone(int W1, int W2) {
  return ( tab_wierzcholkow[W1].czy_polaczone(W2) && tab_wierzcholkow[W2].czy_polaczone(W1) );
}

/**
\brief Zwraca indeks losowego wierzcholka z grafu.
**/
int Graf::znajdz_losowy_wierzcholek() {
  int indeks;
  do {
    indeks = (rand()%tab_wierzcholkow.size());
  } while (!tab_wierzcholkow[indeks].czy_istnieje());
  return indeks;
}
/**
\brief Resetuje zmienne pomocnicze wszystkich wierzcholkow.
**/
void Graf::reset_zmiennych_pomocniczych() {
  for (int i = 0; i<tab_wierzcholkow.size(); i++) {
    tab_wierzcholkow[i].poprzedni_wierzcholek = -1;
    tab_wierzcholkow[i].odwiedzono = false;
    tab_wierzcholkow[i].koszt_sciezki = 0;
    tab_wierzcholkow[i].szacowany_koszt = 0;
  }
}
/**
\brief Tworzy liste ktora prowadzi od podanego wierzcholka do wierzcholka bez nastepnego wyboru.
\return lista indeksow sciezki.
**/
list<int> Graf::zrekonstruuj_sciezke(int W) {
  list<int> sciezka;
  int aktualny = W;
  while (tab_wierzcholkow[aktualny].poprzedni_wierzcholek >= 0) {
    sciezka.push_back(aktualny);
    aktualny = tab_wierzcholkow[aktualny].poprzedni_wierzcholek;
  } 
  sciezka.push_back(aktualny);
  return sciezka;
}
/**
\brief Czysci graf i generuje nowy o zblizonym ksztalcie do kwadratu.
\param rozmiar bok kwadratu.
**/
void Graf::generuj_graf(int rozmiar) {
  tab_wierzcholkow.clear();
  for (int i = 0; i<rozmiar; i++) {
    for (int j = 0; j<rozmiar; j++) {
      int ten = dodaj_wierzcholek(j, i);
      if (i>0)
        dodaj_krawedz(ten, ten - rozmiar, 1);
      if (j>0)
        dodaj_krawedz(ten, ten - 1, 1);
      if (i>0 && j>0)
        dodaj_krawedz(ten, ten - rozmiar - 1, 1);
      if (i>0 && j<rozmiar-1)
        dodaj_krawedz(ten, ten - rozmiar + 1, 1);
    }
  }
  for (int i = 0; i<tab_wierzcholkow.size(); i++) {
    if (rand()%100 < 40)
      usun_wierzcholek(i);
  }
}
/**
\brief Rysuje graf na standardowym wyjsciu.
**/
void Graf::rysuj_graf() {
  //wyswietlanie:
  int x = 0;
  int y = 0;
  for (int i = 0; i<tab_wierzcholkow.size(); i++) {
    if (y<tab_wierzcholkow[i].y) {
      cout << endl;
      x = 0;
      y++;
    }
    if (tab_wierzcholkow[i].czy_istnieje()) {
      if (tab_wierzcholkow[i].odwiedzono) {
        cout << 'O';
      } else {
        cout << 'X';
      }
    } else {
      cout << ' ';
    }
    x++;
  }
  cout << endl;
}
/**
\brief Zwraca tekst opisujacy wspolrzedne danego wierzcholka.
\param W wierzcholek.
\return tekst postaci (x, y)
**/
void Graf::wspolrzedne_wierzcholka(int W) {
  cout << "(" << tab_wierzcholkow[W].x << ", " << tab_wierzcholkow[W].y << ")";
}
/**
\brief Oblicza heurystyke dla drogi pomiedzy dwoma wierzcholkami.
\param W1 wierzcholek 1.
\param W2 wierzcholek 2.
\return Heurystyka
**/
int Graf::heurystyka(int W1, int W2) {
  return (abs(tab_wierzcholkow[W1].x - tab_wierzcholkow[W2].x) + abs(tab_wierzcholkow[W1].y - tab_wierzcholkow[W2].y));
}