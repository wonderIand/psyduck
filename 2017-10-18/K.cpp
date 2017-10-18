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
const int N = 3e5 + 7;
int n;
char s[N];
void flip(int x) {
	s[x] = '0' ^ '1' ^ s[x];
	s[x + 1] = '0' ^ '1' ^ s[x + 1];
}
int main() {
	scanf(" %s", s);
	n = strlen(s) / 3;
	vi ans;
	rep(i, 0, n - 1) {
		int x = 3 * i;
		int y = 3 * (i + 1);
		if (s[x + 2] == s[y]) {
			if (s[x] == s[x + 1] || s[x + 1] != s[x + 2]) {
				flip(x + 1), ans.pb(x + 1);
			} else {
				flip(x + 2), ans.pb(x + 2);
			}
		} else {
			if (s[x + 1] == s[x + 2]) {
				flip(x + 2), ans.pb(x + 2);
			}
		}
	}
	int x = 3 * (n - 1);
	if (s[x] == s[x + 1] && s[x] == s[x + 2]) 
		flip(x + 1), ans.pb(x + 1);
//	rep(i, 0, sz(ans)) flip(ans[i]), flip(ans[i] + 1);
//	int cnt = 1;
//	rep(i, 0, 3 * n - 1) cnt += s[i] != s[i + 1];
//	assert(cnt >= 2 * n);
	printf("%d\n", sz(ans));	
	rep(i, 0, sz(ans))
		printf("%d%c", ans[i] + 1, " \n"[i == sz(ans) - 1]);
	return 0;
}
