#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef double db;
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
const int N = 1e5 + 7;
int n;
pii p[N];
int main() {
	int tcase = 0; scanf("%d", &tcase);
	rep(icase, 0, tcase) {
		///read
		int n; cin >> n;
		rep(i, 0, n) scanf("%d%d", &p[i].fi, &p[i].se);
		///prework
		sort(p, p + n);
		///work
		multiset<ll> S;	
		multiset<ll>::iterator it;
		ll sum = 0;
		rep(i, 0, n) {
			it = S.upper_bound(p[i].fi);
			if (it == S.begin()) {
				sum += p[i].se - p[i].fi;
				S.insert(p[i].se);
			} else {
				--it;
				sum += p[i].se - *it;
				S.erase(it);
				S.insert(p[i].se);
			}
		}
		printf("%d %lld\n", sz(S), sum);	
	}
	return 0;
}

