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
void Punkt::wypisz_punkt()
{
	cout << "ID: " << this->identyfikator << " X,Y: " << this->x << " " << this->y << endl;
}


//----------------------------------------------- //
Punkt stworz_punkt(int id, int a, int b)
{
	Punkt _temp;
	_temp.x = a;
	_temp.y = b;
	_temp.identyfikator = id;
	return _temp;
}
