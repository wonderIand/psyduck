#include<bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b-1); i>=(a); i--)
#define de(x) cout << #x << " => " << x << endl
using namespace std;

#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii;

#define pb push_back
typedef vector<int> vi;

typedef long long ll;
typedef long double ld;

///----------------------------------------------
int main() {

	int n = 30;
	vector<pii> E;
	rep(i, 1, n + 1) E.pb(mp(i, n + i));
	
	vi v;
	int tot = 2 * n;
	rep(i, 1, n + 1) v.pb(i);
	rep(i, 2, n + 1) {
		per(j, 0, sz(v) / i) {
			++tot;
			rep(k, j * i, (j + 1) * i) {
				E.pb(mp(v[k], tot));
			}
		}
	}
	
	printf("%d %d\n", tot, sz(E));
	//de(tot - n);
	//de(3 * n);
	rep(i, 0, sz(E)) printf("%d %d\n", E[i].fi, E[i].se);
	printf("%d\n", n); 
	rep(i, 1, n + 1) printf("%d\n", i);


}
