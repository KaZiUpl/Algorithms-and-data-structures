#include<iostream>
#include<vector>
using namespace std;
#define FOR(x,a,b) for(x = a;x<(b);++x)

struct Point
{
    int x,y;
};
int orientation(Point x, Point y, Point z)
{
    int value = (y.y - x.y)*(z.x - y.x) - (z.y - y.y)*(y.x - x.x);
    if(value == 0) return 0;
    if(value > 0 ) return 1;
    return -1;
}
vector<Point> find_convex_hull(vector<Point> points)
{
    vector<Point> convex_hull;
    if((int) points.size() < 3) return convex_hull;
    int leftmost_point = 0;
    int i;
    FOR(i,1,(int)points.size())
    {
        if(points[i].x < points[leftmost_point].x) leftmost_point = i;
    }
    cout<<"Leftmost point: "<<points[leftmost_point].x<<" "<<points[leftmost_point].y<<endl;
    int next_point = leftmost_point,candidate;
    do
    {
        int j;
        convex_hull.push_back(points[next_point]);
        candidate = (next_point+1)%points.size();
        cout<<"Candidate: "<<points[candidate].x<<" "<<points[candidate].y<<endl;
        FOR(j,0,(int)points.size())
        {
            cout<<"\tpoints[next_point]: "<<points[next_point].x<<" "<<points[next_point].y<<endl;
            cout<<"\tpoints[j]: "<<points[j].x<<" "<<points[j].y<<endl;
            cout<<"\tpoints[candidate]: "<<points[candidate].x<<" "<<points[candidate].y<<endl;
            cout<<"\tOrientation: "<<orientation(points[next_point],points[j],points[candidate])<<endl<<endl;
            if(orientation(points[next_point],points[j],points[candidate]) == -1)
            {
                candidate = j;
                cout<<"ble"<<endl;
            }
        }
        next_point = candidate;
    }while(candidate != leftmost_point);
}

int main()
{
    int test_cases,number_of_points;
    char character;
    vector<Point> convex_hull;
    cin>>test_cases;
    while(test_cases--)
    {
        int i;
        cin>>number_of_points;
        vector<Point> points;
        FOR(i,0,number_of_points)
        {
            Point _temp;
            cin>>_temp.x>>_temp.y>>character;
            points.push_back(_temp);
        }
        convex_hull = find_convex_hull(points);
        int j;
        cout<<"Convex hull"<<endl;
        FOR(j,0,(int)convex_hull.size())
        {
            cout<<convex_hull[j].x<<" "<<convex_hull[j].y<<endl;
        }

    }

    return 0;
}
