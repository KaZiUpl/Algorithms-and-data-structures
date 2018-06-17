#include<iostream>
#include<cmath>
#include<vector>
#include<stack>
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
vector<Punkt> najblizszy_sasiad(vector<Punkt>);
vector <Punkt> stworz_poczatkowa_sciezke(vector <vector<Punkt> > &);
void algorytm_2_opt(vector<Punkt> &);

int main()
{
	// zmienne
	int liczba_wierzcholkow;
	int num_wierzcholka, wspol_x, wspol_y;
	// zmienne iteracyjne
	int i, j;
	// podawanie liczby wierzcholkow w grafie, tworzenie wektora na wierzcholki
	cin >> liczba_wierzcholkow;
	// vector wierzcholkow
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
	//graf pelny zlozony z podanych wierzcholkow
	vector<Krawedz> graf_pelny;
	FOR(i, 0, SIZE(wierzcholki))
	{
		FOR(j, i + 1, SIZE(wierzcholki))
		{
			graf_pelny.PB(stworz_krawedz(wierzcholki[i], wierzcholki[j]));
		}
	}

	// sortowanie krawedzi wedlug dlugosci
	sort(graf_pelny.begin(), graf_pelny.end(), porownaj_krawedzie);
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //

	//struktura zbiorow rozlacznych zawierajaca wszystkie wierzcholki
	DS_struct zbior_rozlaczny(liczba_wierzcholkow + 1);
	FOR(i, 1, liczba_wierzcholkow + 1)
	{
		zbior_rozlaczny.Make_set(i);
	}
	//minimalne drzewo rozpinajace
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
			curr_edge.edge_start = graf_pelny[i].pierwszy.identyfikator, curr_edge.edge_end = graf_pelny[i].drugi.identyfikator;
			i++;
		} while (zbior_rozlaczny.Find(curr_edge.edge_start) == zbior_rozlaczny.Find(curr_edge.edge_end)); // dopoki tworza cykl to pobieraj nowe
		if (do_not_add) break;
		MST.PB(graf_pelny[i - 1]);					// dodawanie krawedzi do minimalnego drzewa rozpinajacego, rekompensata za identyfikator (inaczej nie dziala)
		zbior_rozlaczny.Union(curr_edge);       // laczenie zbiorow ze soba
	}
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //

	// kasowanie grafu pelnego
	vector<Krawedz>().swap(graf_pelny);

	// lista sasiedztwa dla MST
	vector<vector<Punkt> > lista_sasiedztwa;
	// pierwszy przebieg dodaje wierzcholki startowe i koncowe
	FOR(i, 0, SIZE(MST)) // dla kazdej krawedzi z drzewa rozpinajacego
	{
		bool czy_jest = false;
		FOR(j, 0, SIZE(lista_sasiedztwa)) // przejdz przez liste sasiedztwa
		{
			if (MST[i].pierwszy == lista_sasiedztwa[j][0]) // jezeli znajdziesz juz taki punkt to nic nie rob
			{
				lista_sasiedztwa[j].PB(MST[i].drugi);
				czy_jest = true;
				break;
			}
		}
		if (!czy_jest) // jezeli nie znalazl takiego wierzcholka poczatkowego, to go dodaj, dodaj tez koniec krawedzi
		{
			vector <Punkt> _temp;
			_temp.PB(MST[i].pierwszy);
			_temp.PB(MST[i].drugi);
			lista_sasiedztwa.PB(_temp);
		}
	}
	// drugi dodaje krawedzie w druga strone
	FOR(i, 0, SIZE(MST))
	{
		bool czy_jest = false;
		FOR(j, 0, SIZE(lista_sasiedztwa))
		{
			if (MST[i].drugi == lista_sasiedztwa[j][0])
			{
				lista_sasiedztwa[j].PB(MST[i].pierwszy);
				czy_jest = true;
				break;
			}
		}
		if (!czy_jest)
		{
			vector<Punkt> _temp;
			_temp.PB(MST[i].drugi);
			_temp.PB(MST[i].pierwszy);
			lista_sasiedztwa.PB(_temp);
		}
	}
	// wypisywanie listy sasiedztwa
	/*FOR(i, 0, SIZE(lista_sasiedztwa))
	{
		cout << lista_sasiedztwa[i][0].identyfikator << ": \t";
		FOR(j, 1, SIZE(lista_sasiedztwa[i]))
		{
			cout << lista_sasiedztwa[i][j].identyfikator << " ";
		}
		cout << endl;
	}*/
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// przeszukiwanie grafu i tworzenie sciezki

	//vector przechowujacy obecny cykl Hamiltona
	vector<Punkt> sciezka;

	sciezka = najblizszy_sasiad(wierzcholki);

	// dlugosc sciezki
	double dlugosc = 0;
	cout << "SCIEZKA POCZATKOWA: ";
	FOR(i, 0, SIZE(sciezka))
	{
		dlugosc += odleglosc(sciezka[i], sciezka[i + 1]);
		cout << sciezka[i].identyfikator << " ";
		if(i%20 == 0) cout<<endl;
	}
	cout << endl;
	dlugosc += odleglosc(sciezka[SIZE(sciezka) - 1], sciezka[0]);
	cout << "DLUGOSC POCZATKOWA = " << dlugosc << endl;
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// -------------------------------------------------------------------------------------- //
	// algorytm 2-opt

	algorytm_2_opt(sciezka);
	dlugosc = 0;
	cout << "SCIEZKA KONCOWA: " << endl;
	// wypisywanie sciezki koncowej
	FOR(i, 0, SIZE(sciezka))
	{
		dlugosc += odleglosc(sciezka[i], sciezka[i + 1]);
		cout << sciezka[i].identyfikator << " ";
		if (i % 21 == 20) cout << endl;
	}
	cout << endl;
	dlugosc += odleglosc(sciezka[SIZE(sciezka) - 1], sciezka[0]);
	cout << "DLUGOSC KONCOWA = " << dlugosc << endl;

	cout << endl << "--------------- Wszystko zrobione ----------------" << endl;
	_getch();
	return 0;
}
// odleglosc pomiedzy dwoma punktami w przestrzeni 2D
double odleglosc(Punkt pierwszy, Punkt drugi)
{
	return sqrt(pow(drugi.y - pierwszy.y, 2) + pow(drugi.x - pierwszy.x, 2));
}
//porownanie dlugosci krawedzi
bool porownaj_krawedzie(Krawedz pierwsza, Krawedz druga)
{
	if (druga.odleglosc > pierwsza.odleglosc) return 1;
	else return 0;
}
//zwraca kat [-180,180] pomiedzy dwoma wektorami
double kat_pomiedzy(Punkt pierwszy, Punkt drugi, Punkt trzeci)
{
	double wynik = (atan2(drugi.y - pierwszy.y, drugi.x - pierwszy.x) - atan2(trzeci.y - drugi.y, trzeci.x - drugi.x)) * 180 / PI;
	if (wynik > 180) return wynik - 360;
	return wynik;
}
// tworzy cykl Hamiltona metoda najblizszego sasiada
vector<Punkt> najblizszy_sasiad(vector<Punkt> wierzcholki)
{
	vector<Punkt> sciezka;
	Punkt najblizszy;
	double minimalna_odleglosc;
	int i, indeks_najblizszego;

	sciezka.PB(wierzcholki[0]);
	wierzcholki.erase(wierzcholki.begin());

	while (SIZE(wierzcholki) > 0)
	{
		najblizszy = wierzcholki[0];
		minimalna_odleglosc = odleglosc(sciezka[SIZE(sciezka) - 1], najblizszy);
		indeks_najblizszego = 0;
		FOR(i, 1, SIZE(wierzcholki))
		{
			if (odleglosc(sciezka[SIZE(sciezka) - 1], wierzcholki[i]) < minimalna_odleglosc)
			{
				najblizszy = wierzcholki[i];
				minimalna_odleglosc = odleglosc(sciezka[SIZE(sciezka) - 1], wierzcholki[i]);
				indeks_najblizszego = i;
			}
		}
		sciezka.PB(najblizszy);
		wierzcholki.erase(wierzcholki.begin() + indeks_najblizszego);
	}
	return sciezka;
}
// tworzy z listy sasiedztwa cykl Hamiltona
vector <Punkt> stworz_poczatkowa_sciezke(vector <vector<Punkt> > &lista_sasiedztwa)
{
	int i, j;
	vector <Punkt> sciezka;
	stack <Krawedz> stos_sasiadow;
	vector<Krawedz> wektor_sasiadow;

	Punkt poprzedni = stworz_punkt(0, 0, 0),
		obecny = lista_sasiedztwa[0][0];
	sciezka.PB(obecny);

	FOR(j, 1, SIZE(lista_sasiedztwa[0]))
	{
		wektor_sasiadow.PB(stworz_krawedz(poprzedni, obecny, lista_sasiedztwa[0][j]));
	}

	lista_sasiedztwa.erase(lista_sasiedztwa.begin());
	FOR(j, 0, SIZE(lista_sasiedztwa))
	{
		FOR(i, 0, SIZE(lista_sasiedztwa[j]))
		{
			if (lista_sasiedztwa[j][i] == obecny) lista_sasiedztwa[j].erase(lista_sasiedztwa[j].begin() + i);
		}
	}

	sort(wektor_sasiadow.begin(), wektor_sasiadow.end(), porownaj_krawedzie);
	FOR(i, 0, SIZE(wektor_sasiadow))
	{
		stos_sasiadow.push(wektor_sasiadow[i]);
	}
	wektor_sasiadow.clear();

	do
	{
		poprzedni = obecny;
		obecny = stos_sasiadow.top().drugi;
		//cout << "NOWY OBECNY:" << endl;
		//obecny.wypisz_punkt();
		//cout << "NOWY POPRZEDNI:" << endl;
		//poprzedni.wypisz_punkt();
		//cout << endl << endl;
		sciezka.PB(obecny);
		stos_sasiadow.pop();

		// wyszukaj gdzie jest opisany obecny wierzcholek
		FOR(i, 0, SIZE(lista_sasiedztwa))
		{
			if (lista_sasiedztwa[i][0] == obecny) break;
		}
		// do wektora sasiadow dodaj nowe krawedzie idace z obecnego do sasiada
		FOR(j, 1, SIZE(lista_sasiedztwa[i]))
		{
			wektor_sasiadow.PB(stworz_krawedz(poprzedni, obecny, lista_sasiedztwa[i][j]));
		}

		lista_sasiedztwa.erase(lista_sasiedztwa.begin() + i);
		FOR(j, 0, SIZE(lista_sasiedztwa))
		{
			FOR(i, 0, SIZE(lista_sasiedztwa[j]))
			{
				if (lista_sasiedztwa[j][i] == obecny) lista_sasiedztwa[j].erase(lista_sasiedztwa[j].begin() + i);
			}
		}

		// posortuj je, wrzuc do stosu, wyczysc wektor sasiadow
		sort(wektor_sasiadow.begin(), wektor_sasiadow.end(), porownaj_krawedzie);
		FOR(i, 0, SIZE(wektor_sasiadow))
		{
			stos_sasiadow.push(wektor_sasiadow[i]);
		}
		wektor_sasiadow.clear();

	} while (!stos_sasiadow.empty());

	return sciezka;
}
// algorytm 2-OPT polepszajacy zadana sciezke
void algorytm_2_opt(vector<Punkt> & sciezka)
{
	int i, j;
	Punkt pierwszy, drugi, trzeci, czwarty;
	bool czy_byla_poprawka = true;
	// przegladanie sciezki w poszukiwaniu kandydata na zamiane
	// wybieranie pierwszego kandydata
	while (czy_byla_poprawka)
	{
		czy_byla_poprawka = false;
		FOR(i, 0, SIZE(sciezka))
		{
			pierwszy = sciezka[i];
			if (pierwszy == sciezka[SIZE(sciezka) - 1]) drugi = sciezka[0];
			else drugi = sciezka[i + 1];
			// wybieranie drugiego kandydata
			FOR(j, i + 2, SIZE(sciezka))
			{
				// jesli drugi krawedz sie nie laczy z kandydatem to wybierz ja
				if (sciezka[j] != pierwszy && sciezka[j] != drugi && sciezka[(j + 1) % SIZE(sciezka)] != pierwszy)
				{
					trzeci = sciezka[j];
					czwarty = sciezka[(j + 1) % SIZE(sciezka)];
				}
				else continue;
				// zobacz, czy sie krzyzuja
				if (odleglosc(pierwszy, drugi) + odleglosc(trzeci, czwarty) > odleglosc(pierwszy, trzeci) + odleglosc(drugi, czwarty))
				{
					czy_byla_poprawka = true;
					// zamiana kolejnosci sciezki
					// ---------------------------
					reverse(sciezka.begin() + i + 1, sciezka.begin() + j + 1);
					/*double dlugosc = 0;
					int h;
					FOR(h, 0, SIZE(sciezka))
					{
						dlugosc += odleglosc(sciezka[h], sciezka[h + 1]);
					}
					dlugosc += odleglosc(sciezka[SIZE(sciezka) - 1], sciezka[0]);
					cout << "Poprawiono dlugosc na " << dlugosc << endl;*/
				}
				else continue;
			}
		}
	}
}