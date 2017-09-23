#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 107;
int n, m, p[N];
bool v[N];
int main() {
	while (~scanf("%d%d", &n, &m)) {
		rep(i, 0, n) scanf("%d", p + i);
		memset(v, true, sizeof(*v) * n);	
		int q;
		scanf("%d", &q);
		rep(i, 0, q) {
			int x;
			scanf("%d", &x);
			v[x] = false;
		}
		pii ans;
		int val = 1e9;
		rep(i, 0, n) if (v[i]) {
			int pos = -1, cnt = 1;	
			rep(j, i + 1, n) {
				if (!v[j]) continue;
				++cnt;
				if (pos == -1 || p[pos] > p[j])
					pos = j;
				if (cnt >= m)
					break;
			}
			if (cnt == m) {
				if (val > p[i] + p[pos]) {
					val = p[i] + p[pos];
					ans = mp(i, pos);
				}
			}
		}
		printf("%d %d\n", ans.fi, ans.se);
	}

	return 0;
}
