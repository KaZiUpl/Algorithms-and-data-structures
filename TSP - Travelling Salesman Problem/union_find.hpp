#pragma once
using namespace std;

struct Edge
{
public:
	int edge_start, edge_end;
	int weight;
};
// struktura zbiorow rozlacznych
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
	~DS_struct();
	void Make_set(int v);
	int Find(int v);
	void Union(Edge e);
};

DS_struct::DS_struct(int ilosc_wierzcholkow)
{
	vector<DS_node> _temp(ilosc_wierzcholkow);
	wierzcholki = _temp;             // stworz tablice na wierzcholki
}
DS_struct::~DS_struct()
{
	vector<DS_node>().swap(this->wierzcholki);
}
// ustala reprezentanta danego elementu na siebie samego
void DS_struct::Make_set(int v)
{
	wierzcholki[v].reprezentant = v; //reprezentant zbioru z jednym elementem to on sam
	wierzcholki[v].stopien = 0; // ranga(ilosc elementow w zbiorze)
}
// zwraca reprezentanta zbioru, do ktorego nalezy zadany element
int DS_struct::Find(int v)
{
	if (wierzcholki[v].reprezentant != v) wierzcholki[v].reprezentant = Find(wierzcholki[v].reprezentant);
	return wierzcholki[v].reprezentant; // zwroc reprezentanta zbioru
}
// laczy zbiory, w ktorych sa poczatek i koniec krawedzi
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