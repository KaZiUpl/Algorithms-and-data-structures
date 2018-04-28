#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Edge
{
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

bool Weight_compare(Edge a,Edge b) {return a.weight<b.weight;}

int main()
{
    int sum_of_weights = 0;

    vector<Edge> edges;
    vector<Edge> minimum_spanning_tree;
    int number_of_edges,number_of_vertexes,edge_start,edge_end,edge_weight;
    cin>>number_of_vertexes>>number_of_edges;

    DS_struct universe(number_of_vertexes);
    int i;
    for(i = 0; i < number_of_vertexes; i++)
    {
        universe.MakeSet(i);
    }
    // sort all elements
    for(i=0;i<number_of_edges;++i)
    {
        Edge _temp;
        cin>>edge_start>>edge_end>>edge_weight;
        _temp.edge_start = edge_start;
        _temp.edge_end = edge_end;
        _temp.weight = edge_weight;
        edges.push_back(_temp);
    }
    sort(edges.begin(),edges.end(),Weight_compare);
    /*
    for(i=0;i<edges.size();++i)
    {
        cout<<"Edge "<<i+1<<": "<<edges[i].edge_start<<" "<<edges[i].edge_end<<" "<<edges[i].weight<<endl;
    }
    */
    i=1;
    while(i<number_of_edges)
    {
        Edge curr_edge;
        do
        {
            if(i>=number_of_edges) break;
            curr_edge = edges[i]; // podbranie kolejnych krawedzi
            i++;

        } while(universe.FindSet(curr_edge.edge_start) == universe.FindSet(curr_edge.edge_end)); // dopoki tworza cykl to pobieraj nowe
        minimum_spanning_tree.push_back(curr_edge);                 // dodawanie krawedzi do minimalnego drzewa rozpinajacego
        universe.UnionSets(curr_edge);               // laczenie zbiorow ze soba
        sum_of_weights += curr_edge.weight;
    }

    cout<<"Sum of weights: "<<sum_of_weights<<endl;
    cout<<"Min spanning tree:"<<endl;
    for(i=0;i<minimum_spanning_tree.size();++i)
    {
        cout<<"Edge "<<i+1<<": "<<minimum_spanning_tree[i].edge_start<<" "<<minimum_spanning_tree[i].edge_end<<" "<<minimum_spanning_tree[i].weight<<endl;
    }

    return 0;
    /* Dane testowe
11 20
1 4 2
8 7 3
10 0 3
10 2 5
8 0 6
4 6 6
10 1 7
7 6 7
9 10 8
5 6 8
0 1 8
0 6 9
2 3 9
0 7 10
2 1 10
5 4 10
9 8 10
9 0 12
3 5 12
4 3 13
    */
}
