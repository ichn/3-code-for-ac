#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
#define mp make_pair
#define pb push_back
#define x first
#define y second

char str[100003];


int main() {
#ifdef lol
    freopen("5831.in", "r", stdin);
    freopen("5831.out", "w", stdout);
#endif

    int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d\n%s", &n, str);
        int c1 = 0;
        int c2 = 0;
        for (int i = 0; i < n; ++i) {
            char c = str[i];
            if (c == '(') ++c1;
            else ++c2;
        }
        if (c1 != c2) {
            puts("No");
        } else {
			if (c1 == 1) {
				if (str[0] == '(')
					puts("No");
				else puts("Yes");
				goto end;
			}
            c1 = 2;
            for (int i = 0; i < n; ++i) {
                if (str[i] == ')') {
                    if (c1 == 0) {
                        puts("No");
                        goto end;
                    } else {
                        --c1;
                    }
                } else ++c1;
            }
            puts("Yes");
        }
end:;
    }
    return 0;
}
