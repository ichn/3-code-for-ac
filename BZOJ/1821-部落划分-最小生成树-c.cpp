#include <cmath>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAX 1010
using namespace std;
 
struct Point{
    double x,y;
     
    void Read() {
        scanf("%lf%lf",&x,&y);
    }
}point[MAX];
 
inline double Calc(const Point &a,const Point &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
 
struct Edge{
    int x,y;
    double len;
     
    Edge(int _,int __,double ___):x(_),y(__),len(___) {}
    Edge() {}
    bool operator <(const Edge &a)const {
        return len < a.len;
    }
}edge[MAX * MAX];
 
int points,edges,k;
int father[MAX];
 
int Find(int x)
{
    if(father[x] == x)  return x;
    return father[x] = Find(father[x]);
}
 
int main()
{
    cin >> points >> k;
    for(int i = 1; i <= points; ++i)
        point[i].Read(),father[i] = i;
    for(int i = 1; i <= points; ++i)
        for(int j = i + 1; j <= points; ++j)
            edge[++edges] = Edge(i,j,Calc(point[i],point[j]));
    sort(edge + 1,edge + edges + 1);
    int added = 0;
    for(int i = 1; i <= edges; ++i) {
        int fx = Find(edge[i].x);
        int fy = Find(edge[i].y);
        if(fx != fy) {
            father[fx] = fy;
            if(++added == points - k + 1) {
                cout << fixed << setprecision(2) << edge[i].len << endl;
                return 0;
            }
        }
    }
    return 0;
}
