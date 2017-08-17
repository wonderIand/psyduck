#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int MAXN = 1e3 + 7;
int n, k, a[MAXN];
char read() {
	char ch = getchar();
	while (!(ch == 'L' || ch == 'D' || ch == 'N')) ch = getchar();
	return ch;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d", &n, &k);	
		int N = 0, L = 0, D = 0;
		rep(i, 0, n) scanf("%d", a + i);
		rep(i, 0, n) {
			char bi = read();
			if (bi == 'N') {
				N += a[i];
			} else if (bi == 'L') {
				L += a[i];
			} else {
				D += a[i];
			}
		}
		if (- N - D <= k && k <= N + L) {
			puts("yes");
		} else {
			puts("no");
		}
	}
	return 0;
}
