#include <bits/stdc++.h>
#define Mo 110119
#define M 2000
typedef long long LL;
using namespace std;
LL f[1000], N, T;

int main(){
	f[1] = 1;f[2] = 1; f[3] = 1; f[4] = 2; f[5] = 2;
	for(int i = 6; i <= 100; i++) f[i] = f[i-1]+f[i-5];
	cin >> T;
	for(int i = 1; i <= T; i++){
		cin >> N;
		cout << f[N] << endl;
	}
}
