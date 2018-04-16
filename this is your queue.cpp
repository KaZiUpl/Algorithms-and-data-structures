#include<iostream>
#include<list>
#include<string>
using namespace std;

string uzyskaj_numer(string komenda)
{
	return komenda.substr(2, komenda.size() - 2);
}

int main()
{
	long populacja;
	int komendy, licznik = 1;
	while (cin >> populacja >> komendy && populacja != 0 && komendy != 0)
	{
		if (populacja > 1000) populacja = 1000;
		list<int>kolejka;
		int i;
		// dodawanie ludzi do kolejki
		for (i = 1; i <= populacja; ++i)
		{
			kolejka.push_back(i);
		}
		cout << "Case " << licznik << ":" << endl;
		int numer_pacjenta;
		string komenda;
		for (i = 0; i <= komendy; ++i)
		{
			getline(cin, komenda);
			if (komenda[0] == 'N')
			{
				numer_pacjenta = kolejka.front();
				cout << numer_pacjenta << endl;
				kolejka.pop_front(); //usuwanie pacjenta z przodu kolejki
				kolejka.push_back(numer_pacjenta); //dodanie go do tylu
			}
			else if (komenda[0] == 'E')
			{
				komenda = uzyskaj_numer(komenda); //uzyskanie numeru z komendy
				numer_pacjenta = strtol(komenda.c_str(), NULL, 10); //zamiana numeru ze stringa na liczbe
				kolejka.remove(numer_pacjenta); //usuniecie go z kolejki
				kolejka.push_front(numer_pacjenta); //dodanie na poczatek
			}
		}
		licznik++;
	}

	system("pause");
	return 0;
}