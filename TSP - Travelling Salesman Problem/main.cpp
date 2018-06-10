#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
#include<algorithm>
#include<conio.h>
#include"punkt.hpp"
#include"krawedz.hpp"
#include"union_find.hpp"
using namespace std;

#define FOR(i,a,b) for(i=a;i<b;++i)
#define FORd(i,a,b) for(i=a;i>b;--i)
#define FOReq(i,a,b) for(i=a;i<=b;++i)
#define FORdeq(i,a,b) for(i=a;i>=b;--i)
// zmienne
#define PI (2*acos(0))
// definicje do wektorow
#define SIZE(x) (int)x.size()
#define PB(x) push_back(x)

double odleglosc(Punkt, Punkt);
bool porownaj_krawedzie(Krawedz, Krawedz);
double kat_pomiedzy(Punkt pierwszy, Punkt drugi, Punkt trzeci);


int main()
{
	// zmienne
	int liczba_wierzcholkow;
	int num_wierzcholka, wspol_x, wspol_y;
	// zmienne iteracyjne
	int i, j;

	// podawanie liczby wierzcholkow w grafie, tworzenie wektora na wierzcholki
	cin >> liczba_wierzcholkow;
	vector<Punkt> wierzcholki(liczba_wierzcholkow);
	// podawanie wsporzednych wierzcholkow
	FOR(i, 0, liczba_wierzcholkow)
	{
		cin >> num_wierzcholka >> wspol_x >> wspol_y;
		wierzcholki[num_wierzcholka - 1] = stworz_punkt(num_wierzcholka, wspol_x, wspol_y);

	}
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// tworzenie krawedzi grafu pelnego zlozonego z podanych wierzcholkow, jest ich n(n-1)/2
	vector<Krawedz> graf_pelny;
	FOR(i, 0, SIZE(wierzcholki))
	{
		FOR(j, i + 1, SIZE(wierzcholki))
		{
			graf_pelny.PB(stworz_krawedz(wierzcholki[i], wierzcholki[j]));
		}
	}

	/*cout << "Tworzenie krawedzi zakonczone, wcisnij Enter aby stworzyc MST" << endl;
	_getch();*/

	// sortowanie krawedzi wedlug dlugosci
	sort(graf_pelny.begin(), graf_pelny.end(), porownaj_krawedzie);
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// tworzenie struktury zbiorow rozlacznych zawierajacej wszystkie wierzcholki
	DS_struct zbior_rozlaczny(liczba_wierzcholkow + 1);

	FOR(i, 1, liczba_wierzcholkow + 1)
	{
		zbior_rozlaczny.Make_set(i);
	}
	// tworzenie minimalnego drzewa rozpinajacego
	vector<Krawedz> MST;

	// wyznaczanie minimalnego drzewa rozpinajacego
	i = 0;
	while (i < SIZE(graf_pelny))
	{
		Edge curr_edge;
		bool do_not_add = false;
		do
		{
			if (i >= SIZE(graf_pelny))
			{
				do_not_add = true;
				break;
			}
			// pobranie kolejnej krawedzi
			curr_edge.edge_start = graf_pelny[i].pierwszy.identyfikator, curr_edge.edge_end = graf_pelny[i].drugi.identyfikator;
			i++;
		} while (zbior_rozlaczny.Find(curr_edge.edge_start) == zbior_rozlaczny.Find(curr_edge.edge_end)); // dopoki tworza cykl to pobieraj nowe
		if (do_not_add) break;
		MST.PB(graf_pelny[i]);					// dodawanie krawedzi do minimalnego drzewa rozpinajacego
		zbior_rozlaczny.Union(curr_edge);       // laczenie zbiorow ze soba
	}
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //

	cout << endl << "MST stworzone, wcisnij dowolny klawisz, aby wypisac MST i skasowac graf pelny" << endl;
	_getch();

	// kasowanie grafu pelnego
	vector<Krawedz>().swap(graf_pelny);

	FOR(i, 0, SIZE(MST))
	{
		cout << MST[i].pierwszy.identyfikator << " <-----> " << MST[i].drugi.identyfikator << endl;
	}

	_getch();
	return 0;


	/*
	wypisz krawedzie grafu pelnego
	FOR(i, 0, SIZE(graf_pelny))
	{
		cout << "ODL: " << graf_pelny[i].odleglosc << "\t\t";
		cout << "ID1: " << graf_pelny[i].pierwszy.identyfikator << ", " << graf_pelny[i].pierwszy.x << " " << graf_pelny[i].pierwszy.y << "\t";
		cout << "ID2: " << graf_pelny[i].drugi.identyfikator << ", " << graf_pelny[i].drugi.x << " " << graf_pelny[i].drugi.y << endl;
	}

	wypisz punkty
	FOReq(i,1,liczba_wierzcholkow)
	{
		wierzcholki[i].wypisz_punkt();
	}

	wypisz MST
	FOR(i, 0, SIZE(MST))
	{
		cout << MST[i].pierwszy.identyfikator << " ------> " << MST[i].drugi.identyfikator << endl;
	}

	*/
}

double odleglosc(Punkt pierwszy, Punkt drugi)
{
	return sqrt(pow(drugi.y - pierwszy.y, 2) + pow(drugi.x - pierwszy.x, 2));
}
bool porownaj_krawedzie(Krawedz pierwsza, Krawedz druga)
{
	if (druga.odleglosc > pierwsza.odleglosc) return 1;
	else return 0;
}
double kat_pomiedzy(Punkt pierwszy, Punkt drugi, Punkt trzeci)
{
	double wynik = (atan2(drugi.y - pierwszy.y, drugi.x - pierwszy.x) - atan2(trzeci.y - drugi.y, trzeci.x - drugi.x)) * 180 / PI;
	if (wynik > 180) return wynik - 360;
	return wynik;
}
/*
zasada dzialania kat_pomiedzy:
zwraca wartosc kata alfa e(-180,180) lezacego pomiedzy AB i BC (kat wewnetrzny)

Punkt pierwszy = stworz_punkt(0, 5, 0);
Punkt drugi = stworz_punkt(0, 1, 0);
Punkt trzeci = stworz_punkt(0, 1, -4);

cout << "KAT ROWNY: " << kat_pomiedzy(pierwszy, drugi, trzeci) << endl;

for (double h = 0; h < 2 * PI; h += PI / 180)
{
trzeci.x = 5 * cos(h);
trzeci.y = 5 * sin(h);
cout << "KAT ROWNY: " << kat_pomiedzy(pierwszy, drugi, trzeci) << " h: " << h * 180 / PI << "\t";
cout << trzeci.x << " " << trzeci.y << endl;
}

*/