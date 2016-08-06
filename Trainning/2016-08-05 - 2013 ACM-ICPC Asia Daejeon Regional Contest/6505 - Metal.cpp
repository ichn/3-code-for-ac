#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
int tot, g[2000000], x, T;
int main(){
  for(int i = 1; i <= 2000; i++)
    for(int j = 1; j < i; j++){
      int a = 2*i*j, b = i*i-j*j;
      if (__gcd(a,b) != 1) continue;
      g[++tot] = a+b;
    }
  sort(g+1,g+tot+1);
  cin >> T;
  while (T--) {
    cin >> x;
    LL ret = 0, i;
    for(i = 1; i <= tot; i++) {
      ret += g[i]*2;
      if (ret > x) break;
    }
    cout << i-1 << endl;
  }
return 0;
}
