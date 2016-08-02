#include <cstdio>
 
using namespace std;
const int mod = 9999991;
 
int i, n;
long long x = 1;
 
int main() {
    scanf("%d\n", &n);
    for (i = 1; i < n - 1; ++i)
        (x *= n) %= mod;
    for (i = 1; i < n; ++i)
        (x *= i) %= mod;
    printf("%lld\n", x);
    return 0;
}
