#pragma once
using namespace std;

double kat_pomiedzy(Punkt, Punkt, Punkt);
//----------------------------------------------- //
class Krawedz
{
public:
	double odleglosc;
	Punkt pierwszy, drugi;
	void wypisz_krawedz();
};
// wypisuje odleglosc pomiedzy koncami krawedzi oraz punkty bedace jej koncami
void Krawedz::wypisz_krawedz()
{
	cout << endl << "Odleglosc:\t" << this->odleglosc << endl;
	cout << "Punkty:" << endl;
	this->pierwszy.wypisz_punkt();
	this->drugi.wypisz_punkt();
}

//----------------------------------------------- //

// zwraca krawedz o koncach w zadanych punktach
Krawedz stworz_krawedz(Punkt start, Punkt koniec)
{
	Krawedz _temp;
	_temp.odleglosc = sqrt(pow(koniec.y - start.y, 2) + pow(koniec.x - start.x, 2));
	_temp.pierwszy = start;
	_temp.drugi = koniec;
	return _temp;
}
// zwraca krawedz o poczatku w punkcie drugim i koncu w trzecim, odleglosc jest miara konta pomiedzy wektorami pierwszy-drugi oraz drugi-trzeci
Krawedz stworz_krawedz(Punkt pierwszy, Punkt drugi, Punkt trzeci)
{
	Krawedz _temp;
	_temp.pierwszy = drugi;
	_temp.drugi = trzeci;
	_temp.odleglosc = kat_pomiedzy(pierwszy, drugi, trzeci);
	return _temp;
}
