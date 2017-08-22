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
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
int m;
multiset<int> S;
int main() {
	while (~scanf("%d", &m)) {
		S.clear();
		rep(i, 0, m) {
			int x; scanf("%d", &x);
			S.insert(x);
		}
		vector<int> a;
		a.pb(*S.begin());
		S.erase(S.begin());
		while (!S.empty()) {
			int x = *S.begin();
			S.erase(S.begin());
			rep(i, 0, sz(a)) {
				S.erase(S.find(a[i] + x));
			}
			a.pb(x);
		}
		printf("%d\n", sz(a));
		rep(i, 0, sz(a)) printf("%d%c", a[i], " \n"[i == sz(a) - 1]);
	}
	return 0;
}
