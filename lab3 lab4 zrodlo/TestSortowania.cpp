
/**
\file TestSortowania.cpp
**/

#include "TestSortowania.h"

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
	TYP temp;
	plik >> rozmiar;
	while (plik >> temp) {
		StrukturaDanych::dodaj_element(tablica, temp);
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
	for (int i=0; i<WIELKOSC_GENEROWANYCH_DANYCH; i++) {
		plik << rand() % 100000 << endl;
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
void testuj_algorytm(void(*algorytm)(StrukturaDanych& dane), StrukturaDanych &dane, const char *plik_wyjsciowy) {
	int tab_wielkosci[] = WIELKOSCI_PROBLEMU;
	
	int liczba_col = LICZBA_POWTORZEN * LICZBA_WIELKOSCI;
	int col_rozmiar_problemu[LICZBA_POWTORZEN * LICZBA_WIELKOSCI];
	double col_czas[LICZBA_POWTORZEN * LICZBA_WIELKOSCI];

	int aktualny_rozmiar = 0;
	double czas_start = 0;
	double czas_koniec = 0;

	cout << "Postep: ";
	for(int i=0; i<LICZBA_WIELKOSCI; i++) {
		aktualny_rozmiar = tab_wielkosci[i];
		if (aktualny_rozmiar > dane.ilosc_elementow()) {
			cerr << "Za malo danych dla wyznaczonych wielkosci problemu" << endl;
			continue;
		}
		for(int j=0; j<LICZBA_POWTORZEN; j++) {
			int index = i*LICZBA_POWTORZEN + j;
			
			col_rozmiar_problemu[i*LICZBA_POWTORZEN + j] = aktualny_rozmiar;
			StrukturaDanych aktualne_dane;
			StrukturaDanych::kopiuj_wycinek(dane, aktualne_dane, 0, aktualny_rozmiar -1);

			double czas_koniec;
			double czas_start = (double)clock()/CLOCKS_PER_SEC;
			algorytm(aktualne_dane);
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
StrukturaDanych sprawdz_poprawnosc(void(*algorytm)(StrukturaDanych& dane), StrukturaDanych& dane, int ile_liczb) {
	StrukturaDanych do_sprawdzenia;
	StrukturaDanych::kopiuj_wycinek(dane, do_sprawdzenia, 0, ile_liczb -1);
	StrukturaDanych::wypisz_wszystko(do_sprawdzenia);
	algorytm(do_sprawdzenia);
	StrukturaDanych::wypisz_wszystko(do_sprawdzenia);
	return do_sprawdzenia;
}
/**
\brief funkcja main
**/
int main() {
	generuj_dane(PLIK_DANYCH);
	StrukturaDanych dane;
	wczytaj_dane(PLIK_DANYCH, dane);

	//StrukturaDanych po_szybkim = sprawdz_poprawnosc(SortowanieSzybkie::sortuj, dane, 50);
	//StrukturaDanych po_szybkim2 = sprawdz_poprawnosc(SortowanieSzybkie2::sortuj, dane, 50);
	//StrukturaDanych po_scalaniu = sprawdz_poprawnosc(SortowanieScalanie::sortuj, dane, 50);
	//StrukturaDanych po_kopcowaniu = sprawdz_poprawnosc(SortowanieKopcowanie::sortuj, dane, 50);
	//cout << "sortowania rowne? => " << (po_szybkim == po_szybkim2) << endl;
	
	//testuj_algorytm(SortowanieSzybkie::sortuj, dane, "wyjscie4 quicksort.csv");
	//testuj_algorytm(SortowanieScalanie::sortuj, dane, "wyjscie4 mergesort.csv");
	//testuj_algorytm(SortowanieKopcowanie::sortuj, dane, "wyjscie4 heapsort.csv");
	StrukturaDanych dane_posortowane = dane;
	SortowanieSzybkie::sortuj(dane_posortowane);


	testuj_algorytm(SortowanieSzybkie::sortuj, dane, "wyjscie5 quicksort zwykly.csv");
	testuj_algorytm(SortowanieSzybkie::sortuj, dane_posortowane, "wyjscie5 quicksort najgorszy przypadek.csv");
	testuj_algorytm(SortowanieSzybkie2::sortuj, dane, "wyjscie5 quicksort2 zwykly.csv");
	testuj_algorytm(SortowanieSzybkie2::sortuj, dane_posortowane, "wyjscie5 quicksort2 najgorszy przypadek.csv");

	cout << "Gotowe:";
	cin.get();
	return 0;
}