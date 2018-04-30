#include<iostream>
#include<vector>
#include<stack>
using namespace std;

struct Node
{
public:
    int start;
    vector<int> ends;
};

int wyszukaj_poczatek(vector<Node>graf,int start) /// zwraca indeks wierzcholka w grafie lub -1
{
    int i;
    for(i=0;i<(int)graf.size();++i)
    {
        if(start == graf[i].start) return i;
    }
    return -1;
}
void DFS_odwiedz(int wierzcholek, stack <int> &kolejka, vector<bool> &sprawdzone,vector<Node> graf)
{
    int i;
    for(i = 0;i<(int)graf[wierzcholek].ends.size();++i) // dla kazdego dziecka danego wierzcholka
    {
        if(wyszukaj_poczatek(graf,graf[wierzcholek].ends[i]) != -1)
        {
            if(!sprawdzone[ wyszukaj_poczatek(graf,graf[wierzcholek].ends[i]) ])
            {
                kolejka.push( wyszukaj_poczatek(graf,graf[wierzcholek].ends[i]) );
            }
        }

    }
    sprawdzone[wierzcholek] = true;
    kolejka.pop();
}
void DFS(vector<bool> &sprawdzone,vector<Node> graf,int korzen)
{
    stack <int> stos;
    stos.push(korzen);
    while(!stos.empty())
    {
        DFS_odwiedz(stos.top(),stos,sprawdzone,graf);
    }
}
int main()
{


    return 0;
}

