#pragma once
using namespace std;

struct Edge
{
public:
	int edge_start, edge_end;
	int weight;
};
// Disjoint-Set
class DS_node
{
public:
	int reprezentant, stopien;
};

class DS_struct
{
public: 
	vector<DS_node> wierzcholki;
	DS_struct(int ilosc_wierzcholkow);
	void Make_set(int v);
	int Find(int v);
	void Union(Edge e);
};
DS_struct::DS_struct(int ilosc_wierzcholkow)
{
	vector<DS_node> _temp(ilosc_wierzcholkow);
	wierzcholki = _temp;             // stworz tablice na wierzcholki
}
void DS_struct::Make_set(int v)
{
	wierzcholki[v].reprezentant = v; //reprezentant zbioru z jednym elementem to on sam
	wierzcholki[v].stopien = 0; // ranga(ilosc elementow w zbiorze)
}
int DS_struct::Find(int v)
{
	/*cout << "Wchodze do finda" << endl;
	cout << "v: " << v << " rep_v: " << wierzcholki[v].reprezentant << endl;*/
	if (wierzcholki[v].reprezentant != v) wierzcholki[v].reprezentant = Find(wierzcholki[v].reprezentant);
	return wierzcholki[v].reprezentant; // zwroc reprezentanta zbioru
}
void DS_struct::Union(Edge e)
{
	int rep_u, rep_v;
	rep_u = Find(e.edge_start);             // wyznaczamy korzen drzewa z wezlem u
	rep_v = Find(e.edge_end);             //wyznaczamy korzen drzewa z wezlem v
	if (rep_u != rep_v)                    // korzenie musza byc rozne, inaczej to ten sam zbior
	{
		if (wierzcholki[rep_u].stopien > wierzcholki[rep_v].stopien)   // porownujemy stopnie drzew
			wierzcholki[rep_v].reprezentant = rep_u;              // rep_u wieksze, dolaczamy rep_v
		else
		{
			wierzcholki[rep_u].reprezentant = rep_v;              // rowne lub rep_v wieksze, dolaczamy ru
			if (wierzcholki[rep_u].stopien == wierzcholki[rep_v].stopien) wierzcholki[rep_v].stopien++;
		}
	}
}