#pragma once
using namespace std;

//----------------------------------------------- //
class Punkt
{
public:
	double x, y;
	int identyfikator;
	void wypisz_punkt();
};
// wypisuje wspolrzedne punktu i jego identyfikator
void Punkt::wypisz_punkt()
{
	cout << "ID: " << this->identyfikator << " X,Y: " << this->x << " " << this->y << endl;
}
bool operator==(Punkt lewy, Punkt prawy)
{
	return lewy.identyfikator == prawy.identyfikator;
}
bool operator!=(Punkt lewy, Punkt prawy)
{
	return lewy.identyfikator != prawy.identyfikator;
}

//----------------------------------------------- //

// zwraca punkt o zadanym id oraz wspolrzednych
Punkt stworz_punkt(int id, double a, double b)
{
	Punkt _temp;
	_temp.x = a;
	_temp.y = b;
	_temp.identyfikator = id;
	return _temp;
}
