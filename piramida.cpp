#include<iostream>
#include<vector>
using namespace std;
int zachlannie_gora_dol(vector<vector<int>> piramida)
{
	int pietro = 0, element = 0;
	int suma = piramida[0][0];
	while (pietro < piramida.size() - 1)
	{
		if (piramida[pietro + 1][element] > piramida[pietro + 1][element + 1])
		{
			suma += piramida[pietro + 1][element];
			pietro++;
		}
		else
		{
			suma += piramida[pietro + 1][element + 1];
			pietro++;
			element++;
		}
	}
	return suma;
}
int max(vector<int> pietro)
{
	int iterator = 0, max_el = pietro[0];
	int i;
	if (pietro.size() == 0) return iterator;
	for (i = 1; i < pietro.size(); ++i)
	{
		if (pietro[i] > max_el)
		{
			iterator = i;
			max_el = pietro[i];
		}
	}
	return iterator;
}
int zachlannie_dol_gora(vector<vector<int>> piramida)
{
	int pietro = piramida.size() - 1;
	int element = max(piramida[pietro]);
	int suma = piramida[pietro][element];
	int i;
	while (pietro > 0)
	{
		if (element == piramida[pietro].size() - 1)
		{
			suma += piramida[pietro - 1][element - 1];
			pietro--;
			element--;
		}
		else if (element == 0)
		{
			suma += piramida[pietro - 1][0];
			pietro--;
		}
		else if (piramida[pietro - 1][element] >= piramida[pietro - 1][element - 1])
		{
			suma += piramida[pietro - 1][element];
			pietro--;
		}
		else
		{
			suma += piramida[pietro - 1][element - 1];
			pietro--;
			element--;
		}
	}
	return suma;
}
int dynamicznie(vector<vector<int>>piramida)
{
	int pietro = piramida.size() - 2;
	while (pietro >= 0)
	{
		int i;
		for (i = 0; i < piramida[pietro].size(); ++i)
		{
			if (piramida[pietro + 1][i] > piramida[pietro + 1][i + 1])
			{
				piramida[pietro][i] += piramida[pietro + 1][i];
			}
			else
			{
				piramida[pietro][i] += piramida[pietro + 1][i + 1];
			}
		}
		pietro--;
	}

	return piramida[0][0];
}
int main()
{
	int liczba_elementow;
	cin >> liczba_elementow;
	vector <vector<int>> piramida;
	int i = 0, j, ilosc_w_wierszu = 1, pietro = 0, liczba;

	while (i < liczba_elementow)
	{
		vector<int> temp;
		for (j = 0; j < ilosc_w_wierszu; ++j)
		{
			cin >> liczba;
			temp.push_back(liczba);
			i++;
		}
		piramida.push_back(temp);
		pietro++;
		ilosc_w_wierszu++;
	}

	cout << endl;
	cout << "Zachlannie od gory do dolu: " << zachlannie_gora_dol(piramida) << endl;
	cout << "Zachlannie od dolu do gory: " << zachlannie_dol_gora(piramida) << endl;
	cout << "Dynamicznie: " << dynamicznie(piramida) << endl << endl;
	cout << "Zlozonosc metod zachlannych to O(n), gdzie n to ilosc poziomow piramidy." << endl;
	cout << "Zlozonosc metody dynamicznej to rowniez O(n) jednak wzgledem ilosci elementow w piramidzie." << endl;
	cout << "Piramida, dla ktora pokazuje nieoptymalnosc metod zachlannych to np. 1 2 1 1 5 35 20 1 1 1." << endl;
	cout << "Metody zachlanne daja w niej wyniki nie bedace najwieksza suma wag w piramidzie."<<endl;
	cout << endl;
	return 0;
}