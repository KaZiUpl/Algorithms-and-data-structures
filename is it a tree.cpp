#include<iostream>
#include<vector>
#include<queue>
#include<set>
using namespace std;

class Node
{
public:
    int start;
    vector<int> ends;
};
int wyszukaj_poczatek(vector<Node>graf,int start) /// zwraca indeks wierzcholka w grafie lub -1
{
    int i;
    for(i=0;i<graf.size();++i)
    {
        if(start == graf[i].start) return i;
    }
    return -1;
}
int znajdz_korzen(vector<Node>graf,set<int>wierzcholki)
{
    int korzen=0;
    set <int> konce;
    std::set<int>::iterator it;
    int i,j;
    for(i=0;i<graf.size();++i)
    {
        for(j=0;j<graf[i].ends.size();++j)
        {
            konce.insert(graf[i].ends[j]);
        }
    }
    for (it=wierzcholki.begin(); it!=wierzcholki.end(); ++it)
    {
        if(konce.find(*it) == konce.end()) korzen = *it;
    }

    return korzen;
}
void DFS_odwiedz(int wierzcholek, queue <int> &kolejka, vector<bool> &sprawdzone,vector<Node> graf)
{
    int i;
    for(i = 0;i<graf[wierzcholek].ends.size();++i) // dla kazdego dziecka danego wierzcholka
    {
        if(wyszukaj_poczatek(graf,graf[wierzcholek].ends[i]) != -1)
        {
            //cout<<"jestem przed ifem, szukam "<<graf[wierzcholek].ends[i]<<endl;
            if(!sprawdzone[ wyszukaj_poczatek(graf,graf[wierzcholek].ends[i]) ])
            {
                //cout<<"jestem w ifie"<<endl;
                kolejka.push( wyszukaj_poczatek(graf,graf[wierzcholek].ends[i]) );
            }
        }

    }
    sprawdzone[wierzcholek] = true;
    kolejka.pop();
}
void DFS(vector<bool> &sprawdzone,vector<Node> graf,int korzen)
{
    queue <int> kolejka;
    int i;
    kolejka.push(korzen);
    while(!kolejka.empty())
    {
        DFS_odwiedz(kolejka.front(),kolejka,sprawdzone,graf);
    }
}

int main()
{
    int case_number = 1,
        first_point, second_point,
        arc_count;


    while(cin>>first_point>>second_point && (first_point>=0 && second_point>=0))
    {
        bool jest = true;
        vector< Node > graf;
        vector<bool> sprawdzone;
        set<int>wierzcholki;
        arc_count = 0;

        while(first_point != 0 || second_point != 0)
        {
            if(first_point == second_point) jest = false;
            //cout<<first_point<<" "<<second_point<<endl;
            if(wyszukaj_poczatek(graf,first_point) == -1)
            {
                Node temp;
                temp.start = first_point;
                temp.ends.push_back(second_point);
                graf.push_back(temp);
                sprawdzone.push_back(false);
                arc_count++;
                wierzcholki.insert(first_point);
                wierzcholki.insert(second_point);
            }
            else
            {
                graf[wyszukaj_poczatek(graf,first_point)].ends.push_back(second_point);
                wierzcholki.insert(second_point);
                arc_count++;
            }
            //cout<<"graf:"<<endl;
            for(int g=0;g<graf.size();g++)
            {
                /*
                cout<<"Start: "<<graf[g].start<<endl;
                for(int h=0;h<graf[g].ends.size();++h)
                {
                    cout<<graf[g].ends[h]<<" ";
                }
                cout<<endl;
                */
            }
            //cout<<"vertex,arc: "<<wierzcholki.size()<<" "<<arc_count<<endl;
            cin>>first_point>>second_point;
        }
        if(wierzcholki.size()-1 != arc_count) jest = false;
        else
        {
            DFS(sprawdzone,graf,wyszukaj_poczatek(graf,znajdz_korzen(graf,wierzcholki)));
            int j;
            for(j=0;j<sprawdzone.size();++j)
            {
                jest = jest && sprawdzone[j];
            }
        }

        cout<<"Case "<<case_number++;
        if(jest || wierzcholki.empty()) cout<<" is a tree."<<endl;
        else cout<<" is not a tree."<<endl;
    }


    return 0;
}
