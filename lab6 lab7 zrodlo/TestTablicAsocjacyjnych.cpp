
/**
\file TestSortowania.cpp
**/

#include "TestTablicAsocjacyjnych.h"

void algorytm1(TYP_KLUCZ& klucz) {
  tab1.pobierz(klucz);
}
void algorytm2(TYP_KLUCZ& klucz) {
  tab2.pobierz(klucz);
}
void algorytm3(TYP_KLUCZ& klucz) {
  tab3.pobierz(klucz);
}

void zmien_ilosc_elementow1(StrukturaDanych& dane, int ile) {
  tab1.przepisz_strukture(dane, ile);
}
void zmien_ilosc_elementow2(StrukturaDanych& dane, int ile) {
  tab2.przepisz_strukture(dane, ile);
}
void zmien_ilosc_elementow3(StrukturaDanych& dane, int ile) {
  tab3.przepisz_strukture(dane, ile);
}
/**
\brief wczytuje dane z pliku
\details
Format: \n
liczba_danych \n
dana1 \n
dana2 \n
. \n
\param *nazwa_pliku nazwa pliku z danymi
\param *&tablica tablica docelowa (usuwana w przypadku !=NULL)
\param &rozmiar rozmiar tablicy docelowej
**/
bool wczytaj_dane(const char *nazwa_pliku, StrukturaDanych &tablica) {
  ifstream plik;
  plik.open(nazwa_pliku);
  if (!plik.good())
    return false;
  int rozmiar;
  int wartosc;
  TYP temp;
  plik >> rozmiar;
  while (plik >> temp) {
    StrukturaDanych::dodaj_element(tablica, temp);
    plik >> wartosc;
  }
  plik.close();
  cout << "Wczytano z: " << nazwa_pliku << endl;
  return true;
}
/**
\brief zapisuje dane do pliku .csv
dane zawieraja:
1 kolumna: wielkosc problemu
2 kolumna: czas potrzebny do zrealizowanego danego problemu
\param *nazwa_pliku nazwa pliku do zapisu
\param *col_rozmiar_problemu tablica z 1 kolumna
\param *col_czas druga kolumna
\param rozmiar rozmiar obu tablic
\return
- true sukces
- false blad
**/
bool zapisz_dane(const char *nazwa_pliku, int *col_rozmiar_problemu, double *col_czas, int rozmiar) {
  ofstream plik;
  plik.open(nazwa_pliku, ios::out | ios::trunc);
  if (!plik.good())
    return false;
  for (int i=0; i<rozmiar;) {
    int aktualny_rozmiar_problemu = col_rozmiar_problemu[i];
    int powtorzen = 0;
    double suma_czasow = 0.0;
    while(aktualny_rozmiar_problemu == col_rozmiar_problemu[i]) {
      suma_czasow += col_czas[i];
      powtorzen++;
      i++;
    }
    plik << aktualny_rozmiar_problemu << "," << powtorzen << "," << suma_czasow/powtorzen << endl;
  }
  plik.close();
  cout << "Zapisano do: " << nazwa_pliku << endl;
  return true;
}
/**
\brief Generuje nowe dane do pliku.
**/
void generuj_dane(char *nazwa_pliku) {
  ifstream plik_do_odczytu;
  plik_do_odczytu.open(nazwa_pliku);
  if (plik_do_odczytu.good()) {
    int rozmiar;
    plik_do_odczytu >> rozmiar;
    if (rozmiar == WIELKOSC_GENEROWANYCH_DANYCH) {
      plik_do_odczytu.close();
      return;
    }
  }
  plik_do_odczytu.close();

  ofstream plik;
  plik.open(nazwa_pliku, ios::out | ios::trunc);
  if (!plik.good())
    return;
  plik << WIELKOSC_GENEROWANYCH_DANYCH << endl;
  srand(clock());
  string klucz;
  for (int i=0; i<WIELKOSC_GENEROWANYCH_DANYCH; i++) {
    klucz = "";
    for (int j=0; j<(DLUGOSC_KLUCZA); j++) {
      klucz+= (char)(97 + rand()%25);
    }
    plik << klucz << ' ' << i << endl;
  }
  plik.close();
  cout << "wygenerowano" << endl;
}
/**
\brief wykonuje testy czasu algorytmu dla przygotowanych parametrow
zmierzone czasu zapisuje do pliku
\param double(*algorytm) funkcja z algorytmem do testowania
\param *tablica dane dla algorytmu
\param rozmiar rozmiar tablicy
\param *plik_wyjsciowy nazwa pliku do zapisu zmierzonych czasow
**/
void testuj_algorytm(void(*algorytm)(TYP_KLUCZ& klucz), void(*zmien_ilosc_elementow)(StrukturaDanych& dane, int ile), StrukturaDanych &dane, const char *plik_wyjsciowy) {
  int tab_wielkosci[] = WIELKOSCI_PROBLEMU;

  int liczba_col = LICZBA_POWTORZEN * LICZBA_WIELKOSCI;
  int col_rozmiar_problemu[LICZBA_POWTORZEN * LICZBA_WIELKOSCI];
  double col_czas[LICZBA_POWTORZEN * LICZBA_WIELKOSCI];

  int aktualny_rozmiar = 0;
  double czas_start = 0;
  double czas_koniec = 0;

  srand(clock());
  cout << "Postep: ";
  for(int i=0; i<LICZBA_WIELKOSCI; i++) {
    aktualny_rozmiar = tab_wielkosci[i];
    zmien_ilosc_elementow(dane, aktualny_rozmiar);
    if (aktualny_rozmiar > dane.ilosc_elementow()) {
      cerr << "Za malo danych dla wyznaczonych wielkosci problemu" << endl;
      continue;
    }
    for(int j=0; j<LICZBA_POWTORZEN; j++) {
      int index = i*LICZBA_POWTORZEN + j;

      col_rozmiar_problemu[i*LICZBA_POWTORZEN + j] = aktualny_rozmiar;
      string klucz = dane.element_na(rand()%aktualny_rozmiar);

      double czas_koniec;
      double czas_start = (double)clock()/CLOCKS_PER_SEC;
      algorytm(klucz);
      czas_koniec= (double)clock()/CLOCKS_PER_SEC;

      col_czas[i*LICZBA_POWTORZEN + j] = czas_koniec - czas_start;

      cout << "\r";
      cout << "Postep: ";
      cout.width(4);
      cout << (i*LICZBA_POWTORZEN+j+1) << "/" << (LICZBA_POWTORZEN * LICZBA_WIELKOSCI);
    }
  }
  cout << endl;
  zapisz_dane(plik_wyjsciowy, col_rozmiar_problemu, col_czas, liczba_col);
}
/**
\brief funkcja sprawdza poprawnosc dzialania struktur danych.
\param void(*algorytm)(StrukturaDanych& dane) Wskaznik na wybrany algorytm.
\param dane Dane do obrobki, niezmieniane.
\param ile_liczb Wielkosc problemu do sprawdzenia, niewielka aby dalo sie zobaczyc w konsoli.
\return Zwraca Strukture po wykonaniu algorytmu.
**/
/*StrukturaDanych sprawdz_poprawnosc(void(*algorytm)(StrukturaDanych& dane), StrukturaDanych& dane, int ile_liczb) {
  StrukturaDanych do_sprawdzenia;
  StrukturaDanych::kopiuj_wycinek(dane, do_sprawdzenia, 0, ile_liczb -1);
  StrukturaDanych::wypisz_wszystko(do_sprawdzenia);
  algorytm(do_sprawdzenia);
  StrukturaDanych::wypisz_wszystko(do_sprawdzenia);
  return do_sprawdzenia;
}*/
/**
\brief funkcja main
**/
int main() {
  generuj_dane(PLIK_DANYCH);
  StrukturaDanych dane;
  wczytaj_dane(PLIK_DANYCH, dane);

  /*
  TablicaHaszujaca drzewo;
  srand(clock());
  string klucz;
  for (int i=0; i<30; i++) {
    klucz = "";
    for (int j=0; j<3; j++) {
      klucz+= (char)(97 + rand()%25);
    }
    drzewo.dodaj(klucz, i);
  }
  drzewo.wypisz_wszystko();
  while (klucz != "e") {
    cin >> klucz;
    drzewo.usun(klucz);
    drzewo.wypisz_wszystko();
  }
  */

  //testuj_algorytm(algorytm1, zmien_ilosc_elementow1, dane, "wynik tablica.csv");
  //testuj_algorytm(algorytm2, zmien_ilosc_elementow2, dane, "wynik drzewo.csv");
  testuj_algorytm(algorytm3, zmien_ilosc_elementow3, dane, "wynik haszujaca 100000.csv");

  cout << "Gotowe:";
  cin.get();
  return 0;
}