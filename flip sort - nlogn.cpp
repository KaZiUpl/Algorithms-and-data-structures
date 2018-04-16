#include<iostream>

using namespace std;
int sort(int *tab, int n)
{
	int zamiany = 0;
	bool flaga = true;
	int straznik, ostatnia_wymiana = 0;
	int i, j;
	for (i = 0; i < n - 1; ++i)
	{
		straznik = ostatnia_wymiana;
		for (j = n - 1; j > straznik; --j)
		{
			if (tab[j - 1] > tab[j])
			{
				swap(tab[j - 1], tab[j]);
				flaga = false;
				ostatnia_wymiana = j;
				zamiany++;
			}
		}
		if (flaga) break;
		flaga = true;
	}
	return zamiany;
}

int main()
{
	int n;
	while (cin >> n)
	{
		int *tab = new int[n];
		int i = 0;
		for (i; i < n; ++i)
		{
			cin >> tab[i];
		}
		cout << "Minimum exchange operations : " << sort(tab, n) << endl;

	}
	return 0;
}