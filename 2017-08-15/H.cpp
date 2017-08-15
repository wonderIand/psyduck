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
const int N = 5e4 + 7;
struct Node {
	ll x, y;
	int val, zone;
	void in() {
		scanf("%lld%lld%d", &x, &y, &val);
		zone = (x >= 0) ^ (1 << (y < 0));
	}
	ll operator^(const Node &p) const {
		return x * p.y - y * p.x;
	}
} a[N];
#define sqr(x) ((x)*(x))
bool cmp(const Node &p, const Node &q) {
	if (p.zone != q.zone) return p.zone < q.zone;
	if ((p ^ q) != 0) return (p ^ q) > 0;
	return sqr(p.x) + sqr(p.y) < sqr(q.x) + sqr(q.y);
}
int n;
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf("%d", &n);
		ll sum = 0;
		rep(i, 0, n) a[i].in(), sum += a[i].val;
		sort(a, a + n, cmp);
		if (n == 1) {
			puts("0");
			continue;
		}
		if (n == 2) {
			printf("%lld\n", 1ll * a[0].val * a[1].val);
			continue;
		}

//		rep(i, 0, n) printf("%lld %lld\n", a[i].x, a[i].y);

		ll ans = 0, tmp = a[0].val;
		for (int i = 0, j = 1; i < n; ++i) {	
			while (j != i && (a[i] ^ a[j]) >= 0) {
				tmp += a[j].val;
				j = (j + 1) % n;
			}
//			dd(i), dd(j), de(tmp);
			ans = max(ans, tmp * (sum - tmp));
			tmp -= a[i].val;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
