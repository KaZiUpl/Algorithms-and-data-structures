#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Edge
{
public:
    int edge_start,edge_end;
    int weight;
};
// Disjoint-Set data structure
class DS_node
{
public:
    int representative,set_rank;
};
class DS_struct
{
private:
    DS_node * nodes;
public:
    DS_struct(int nodes_number);
    ~DS_struct();
    void MakeSet(int v);
    int FindSet(int v);
    void UnionSets(Edge e);
};
DS_struct::DS_struct(int nodes_number)
{
    nodes = new DS_node [nodes_number];             // stworz tablice na wierzcholki
}
DS_struct::~DS_struct()
{
    delete [] nodes;                    // zniszcz tablice
}
void DS_struct::MakeSet(int v)
{
    nodes[v].representative = v; //reprezentant zbioru z jednym elementem to on sam
    nodes[v].set_rank = 0; // ranga(ilosc elementow w zbiorze)
}
int DS_struct::FindSet(int v)
{
    // jesli reprezentantem zbioru danego elementu nie jest on sam to reprezentantem tego zbioru jest reprezentant elementu, pod ktory dany element "podlega"
    if(nodes[v].representative != v) nodes[v].representative = FindSet(nodes[v].representative);
    return nodes[v].representative; // zwroc reprezentanta zbioru
}
void DS_struct::UnionSets(Edge e)
{
  int rep_u,rep_v;

  rep_u = FindSet(e.edge_start);             // wyznaczamy korzen drzewa z wezlem u
  rep_v = FindSet(e.edge_end);             //wyznaczamy korzen drzewa z wezlem v
  if(rep_u != rep_v)                    // korzenie musza byc rozne, inaczej to ten sam zbior
  {
    if(nodes[rep_u].set_rank > nodes[rep_v].set_rank)   // porownujemy rangi drzew
      nodes[rep_v].representative = rep_u;              // rep_u wieksze, dolaczamy rep_v
    else
    {
      nodes[rep_u].representative = rep_v;              // równe lub rep_v wiêksze, dolaczamy ru
      if(nodes[rep_u].set_rank == nodes[rep_v].set_rank) nodes[rep_v].set_rank++;
    }
  }
}

int main()
{
    return 0;
}
