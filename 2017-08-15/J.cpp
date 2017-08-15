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
const int MAX_N = 7 + 200000;
int a[MAX_N];
int b[MAX_N];
int n, m;
int lowbit(int d) { return d&-d; }
void work(int m) {
	rep(i, 1, n + 1) if (i > m) b[i] = a[i] ^ b[i - m]; else b[i] = a[i];
	rep(i, 1, n + 1) a[i] = b[i];
	//rep(i, 1, n + 1) de(a[i]);
}
int main() {
	
	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///read
		cin >> n >> m;
		rep(i, 1, n + 1) scanf("%d", &a[i]);
		///
		for (; m; m-=lowbit(m)) work(lowbit(m));
		rep(i, 1, n + 1) {
			if (i > 1) printf(" ");
			printf("%d", a[i]);
		}
		printf("\n");

	}


	return 0;
}
