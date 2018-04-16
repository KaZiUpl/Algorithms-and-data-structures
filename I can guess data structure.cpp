#include<iostream>
#include<stack>
#include<queue>
using namespace std;

int main()
{
	int ile_komend, komenda, element;
	bool czy_stos = true,
		czy_kolejka = true,
		czy_priorytet = true;

	while (cin >> ile_komend)
	{
		int i;
		stack <int> stos;
		queue <int> kolejka;
		priority_queue <int> priorytet;
		czy_stos = true;
		czy_kolejka = true;
		czy_priorytet = true;
		for (i = 0; i < ile_komend; ++i)
		{
			cin >> komenda >> element;
			if (komenda == 1)
			{
				stos.push(element);
				kolejka.push(element);
				priorytet.push(element);
			}
			else
			{
				if (!stos.empty() && stos.top() == element) stos.pop();
				else czy_stos = false;
				if (!kolejka.empty() && kolejka.front() == element) kolejka.pop();
				else czy_kolejka = false;
				if (!priorytet.empty() && priorytet.top() == element) priorytet.pop();
				else czy_priorytet = false;
			}
			//cout << czy_stos << czy_kolejka << czy_priorytet << endl;
		}
		if (czy_stos && !(czy_kolejka || czy_priorytet)) cout << "stack" << endl;
		else if (czy_kolejka && !(czy_stos || czy_priorytet)) cout << "queue" << endl;
		else if (czy_priorytet && !(czy_kolejka || czy_stos)) cout << "priority queue" << endl;
		else if ((czy_stos?1:0)+(czy_kolejka?1:0)+(czy_priorytet?1:0) > 1) cout << "not sure" << endl;
		else cout << "impossible" << endl;
	}

	system("pause");
	return 0;
}