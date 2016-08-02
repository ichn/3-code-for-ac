#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	freopen("3156.in","w",stdout);
	srand((int)time(NULL));
	int n=1000000;
	printf("%d\n",n);
	for(int i=1;i<=n;++i) {
		printf("%d ",(rand()%203)+1);
	}
	puts("");
	return 0;
}
