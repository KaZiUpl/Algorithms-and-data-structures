#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

#define FOR(i,a,b) for(i=a;i<b;++i)
#define FORd(i,a,b) for(i=a;i>b;--i)
#define FOReq(i,a,b) for(i=a;i<=b;++i)
#define FORdeq(i,a,b) for(i=a;i>=b;--i)

struct Punkt
{
    double x,y;
};
struct Krawedz
{

};
Punkt stworz_punkt(int a,int b)
{
    Punkt _temp;
    _temp.x = a;
    _temp.y = b;
    return _temp;
}
double odleglosc(Punkt pierwszy,Punkt drugi) {return sqrt( pow(drugi.y-pierwszy.y,2) + pow(drugi.x-pierwszy.x,2) );}


int main()
{
    int liczba_wierzcholkow;
    int num_wierzcholka,wspol_x,wspol_y;

    cin >> liczba_wierzcholkow;
    vector<Punkt> punkty(liczba_wierzcholkow+1);


    int i;
    FOReq(i,1,liczba_wierzcholkow)
    {
        cin>> num_wierzcholka >>wspol_x >> wspol_y;
        punkty[num_wierzcholka] = stworz_punkt(wspol_x,wspol_y);
    }


    /*
    FOReq(i,1,liczba_wierzcholkow)
    {
        cout<<i<<": "<<punkty[i].x<<" "<<punkty[i].y<<endl;
    }
    */
    return 0;
}
