#include<iostream>
#include<string>
using namespace std;

int najmniejszy_okres(string wyraz)
{
	int okres = 1;
	string porownanie = "";
	while (okres <= wyraz.size())
	{
		porownanie = "";
		while (porownanie.size() < wyraz.size())
		{
			porownanie += wyraz.substr(0, okres);
			//cout << "Porownanie: " << porownanie << endl;
		}
		if (porownanie == wyraz)
		{
			//cout << "Takie same, zwracam" << endl;
			return okres;
		}
		else okres++;
	}
}

int main()
{
	string wyraz;
	int ilosc_testow;

	//cout << "Ilosc testow: " << endl;
	cin >> ilosc_testow;
	while (ilosc_testow--)
	{
		//cout << "Podaj wyraz: " << endl;
		cin >> wyraz;
		cout << najmniejszy_okres(wyraz) << endl;
	}

	return 0;
}