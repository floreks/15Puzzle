#include <iostream>
#include <vector>
#include <queue>

/* Adam Kopaczewski 165443
 * Sebastian Florek 165397
 * Marcin Maciaszczyk 165466 */

using namespace std;

typedef vector< vector <int> > vector2d;

#define BIALY 0
#define SZARY 1
#define CZARNY 2

void explore(int n, vector<int>&v, vector<int>&p, vector2d &l, int end)
{
    vector<int>s(l[n]);
    if(v[n] == BIALY)
    {
        cout << n << ' ';
        if(n == end)
        {
            for(int i=0;i<v.size();i++)
                v[i] = SZARY;
        return;
        }
    }
    v[n] = SZARY;
    for(int i=0;i<s.size();i++)
    {
        int j = s[i];
        if(v[j] == BIALY)
        {
            p[j] = n;
            explore(j,v,p,l,end);
        }
    }
    v[n] = CZARNY;
}

int main()
{
    vector2d list;
    int v,e,v0,v1;
    cin >> v >> e;
    list.resize(v);
    vector<int>visited(v);
    vector<int>poprzednik(v);
    for(int i=0;i<visited.size();i++)
    {
        visited[i] = BIALY;
        poprzednik[i] = -1;
    }
    while(e--)
    {
        cin >> v0 >> v1;
        list[v0].push_back(v1);
    }
    cin >> v0 >> v1;

    explore(v0,visited,poprzednik,list,v1);
    if(!visited[v1])
    {
        cout << "\rBRAK                            \n";
        return 0;
    }
    else
    {
        cout << endl;
//        int cur;
//        vector<int> path;
//        cur = v1;
//        path.push_back(cur);
//        while(poprzednik[cur] != -1 && cur != v0)
//        {
//            cur = poprzednik[cur];
//            path.push_back(cur);
//        }
//        cout << path.size() << endl;
//        for(int i=path.size()-1;i>=0;i--)
//            cout << path[i] << ' ';
//        cout << endl;
    }
    return 0;
}
