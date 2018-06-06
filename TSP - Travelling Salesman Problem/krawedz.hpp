#pragma once
using namespace std;

//----------------------------------------------- //
class Krawedz
{
public:
	double odleglosc;
	Punkt pierwszy, drugi;
	void wypisz_krawedz();
};
void Krawedz::wypisz_krawedz()
{
	cout << endl << "Odleglosc:\t" << this->odleglosc << endl;
	cout << "Punkty:" << endl;
	this->pierwszy.wypisz_punkt();
	this->drugi.wypisz_punkt();
}


//----------------------------------------------- //
Krawedz stworz_krawedz(Punkt start, Punkt koniec)
{
	Krawedz _temp;
	_temp.odleglosc = sqrt(pow(koniec.y - start.y, 2) + pow(koniec.x - start.x, 2));
	_temp.pierwszy = start;
	_temp.drugi = koniec;
	return _temp;
}
