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
// definicje do wektorow
#define SIZE(x) (int)x.size()
#define PB(x) push_back(x)



double odleglosc(Punkt, Punkt);
bool porownaj_krawedzie(Krawedz, Krawedz);

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
	// tworzenie krawedzi grafu pelnego zlozonego z podanych wierzcholkow, jest in n(n-1)/2
	vector<Krawedz> graf_pelny;
	FOR(i, 0, SIZE(wierzcholki))
	{
		FOR(j, i + 1, SIZE(wierzcholki))
		{
			graf_pelny.PB(stworz_krawedz(wierzcholki[i], wierzcholki[j]));
		}
	}

	cout << "Tworzenie krawedzi zakonczone, wcisnij Enter" << endl;

	// sortowanie krawedzi wedlug dlugosci
	sort(graf_pelny.begin(), graf_pelny.end(), porownaj_krawedzie);
	/*FOR(i, 0, SIZE(graf_pelny))
	{
		cout << "ODL: " << graf_pelny[i].odleglosc << "\t\t";
		cout << "ID1: " << graf_pelny[i].pierwszy.identyfikator << ", " << graf_pelny[i].pierwszy.x << " " << graf_pelny[i].pierwszy.y << "\t";
		cout << "ID2: " << graf_pelny[i].drugi.identyfikator << ", " << graf_pelny[i].drugi.x << " " << graf_pelny[i].drugi.y << endl;
	}*/
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// tworzenie struktury zbiorow rozlacznych zawierajacej wszystkie wierzcholki
	cout << "Przed DS" << endl;
	DS_struct zbior_rozlaczny(liczba_wierzcholkow + 1);
	FOReq(i, 1, liczba_wierzcholkow + 1)
	{
		zbior_rozlaczny.Make_set(i);
	}
	// tworzenie minimalnego drzewa rozpinajacego
	vector<Krawedz> MST;

	// wyznaczanie minimalnego drzewa rozpinajacego
	cout << "Po DS.Make_set" << endl;
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
			curr_edge.edge_start = graf_pelny[i].pierwszy.identyfikator;
			curr_edge.edge_end = graf_pelny[i].drugi.identyfikator;
			/*cout << "Egde_start: " << curr_edge.edge_start << "\tEgde_end: " << curr_edge.edge_end << endl;*/
			i++;
		} while (zbior_rozlaczny.Find(curr_edge.edge_start) == zbior_rozlaczny.Find(curr_edge.edge_end)); // dopoki tworza cykl to pobieraj nowe

		if (do_not_add) break;
		MST.PB(graf_pelny[i]);					// dodawanie krawedzi do minimalnego drzewa rozpinajacego
		zbior_rozlaczny.Union(curr_edge);       // laczenie zbiorow ze soba

	}
	cout << "MST stworzone, wypisuje:" << endl;
	_getch();


	FOR(i, 0, SIZE(MST))
	{
		cout << MST[i].pierwszy.identyfikator << " ------> " << MST[i].drugi.identyfikator << endl;
	}



	int cos;
	cin >> cos;
	return 0;
	/*
	wypisz krawedzie grafu pelnego
	FOR(i, 0, SIZE(graf_pelny))
	{
		graf_pelny[i].wypisz_krawedz();
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