#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
 
using namespace std;
 
const int X = 20;
#define esp 1e-8
 
double dp[X][X];
double a[X][X],b[X][X];
double f[X];
int n;
 
double gauss(){
    for(int i=1;i<=n;i++){
        int x = i;
        for(int j=i+1;j<=n;j++)
            if(fabs(a[j][i]-a[x][i])>esp)
                x = j;
        if(x!=i)
            for(int j=1;j<=n+1;j++)
                swap(a[i][j],a[x][j]);
        for(int j=i+1;j<=n;j++)
            if(fabs(a[j][i])>esp){
                double temp = a[j][i] / a[i][i];
                for(int k=i;k<=n+1;k++)
                    a[j][k] -= temp*a[i][k];
            }
    }
    for(int i=n;i;i--){
        double temp = a[i][n+1];
        for(int j=i+1;j<=n;j++)
            temp -= f[j]*a[i][j];
        f[i] = temp / a[i][i];
    }
}
 
int main(){
    cin>>n;
    for(int i=1;i<n+2;i++)
        for(int j=1;j<=n;j++)
            scanf("%lf",&b[i][j]);
    for(int i=1;i<=n;i++){
        double temp = 0;
        for(int j=1;j<=n;j++){
            temp += b[i+1][j]*b[i+1][j]-b[i][j]*b[i][j];
            a[i][j] = 2*(b[i+1][j]-b[i][j]);
        }
        a[i][n+1] = temp;
    }
    gauss();
    for(int i=1;i<n;i++)
        printf("%.3lf ",f[i]);
    printf("%.3lf\n",f[n]);
    return 0;
}
