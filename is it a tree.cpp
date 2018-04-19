#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

bool czy_jest(vector<int>kierunki,int wartosc)
{
    for(int i=0;i<kierunki.size();++i)
    {
        if(kierunki[i] == wartosc) return true;
    }
    return false;
}

int main()
{
    int case_number = 1,
        first_point, second_point;
    vector<vector <int> > vertex_vec;

    while(cin>>first_point>>second_point && (first_point>0 && second_point>0))
    {
        bool jest = false;
        vector<int> kierunki;

        while(first_point != 0 || second_point != 0)
        {
            cout<<first_point<<" "<<second_point<<endl;
            int i;
            for(int i=0; i<vertex_vec.size();++i)
            {
                if(vertex_vec[i][0] == first_point) vertex_vec[i].push_back(second_point);
                else
                {
                    vector<int> new_vec;
                    new_vec.push_back(first_point);
                    new_vec.push_back(second_point);
                    vertex_vec.push_back(new_vec);
                }
            }
            for(int g=0;g<vertex_vec.size();++g)
            {
                cout<<"Start: "<<vertex_vec[g][0]<<" ends: ";
                for(int h=1;h<vertex_vec[g].size();++h)
                {
                    cout<<vertex_vec[g][h]<<" ";
                }
                cout<<endl;
            }
            cin>>first_point>>second_point;
        }

        cout<<"Case "<<case_number++;
        if(jest) cout<<" is not a tree"<<endl;
        else cout<<" is  a tree"<<endl;
    }


    return 0;
}
