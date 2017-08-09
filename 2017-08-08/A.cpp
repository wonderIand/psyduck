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
const int N = 50000;
int n, m, q, b[N + 7];
pair<int, int> w[N + 7];
bool ans[N + 7];
bitset<N + 1> A, B, R;
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d%d%d", &n, &m, &q);
		A.reset(), B.reset();
		rep(i, 0, n) {
			int x;scanf("%d", &x);
			A[x] = 1;
		}
		rep(i, 0, m) scanf("%d", b + i);
		rep(i, 0, q) {
			int x;scanf("%d", &x);
			w[i] = mp(x, i);
		}
		sort(w, w + q);
		for (int i = q - 1, j = m - 1; i >= 0; --i) {
			while (j >= 0 && b[j] > w[i].fi) {
				for (int k = b[j]; k <= N; k += b[j])
					B[k].flip();
				--j;
			}
			int c = 0;
			if (A[w[i].fi] && b[m - 1] > w[i].fi) {
				int p = upper_bound(b, b + m, w[i].fi) - b;
				c += m - p;
			}
//			dd(w[i].fi), dd(c), de(B);
			ans[w[i].se] = (((A >> w[i].fi) & B).count() + c) & 1;
		}
		rep(i, 0, q) printf("%d\n", ans[i]);
	}

	return 0;
}
