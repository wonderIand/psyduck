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
const int N = 1e5 + 7;
int n, tot, f[N], s[N], ls[N], rs[N];
int p;
char str[N];
int expr() {
	if ('0' <= str[p] && str[p] <= '9')	{
		while ('0' <= str[p] && str[p] <= '9') ++p;
		++tot;
		f[tot] = s[tot] = 1, ls[tot] = rs[tot] = 0;
		return tot;
	} else {
		int t = ++tot;	
		++p, ls[t] = expr(), ++p;
		char op = str[p++];
		++p, rs[t] = expr(), ++p;
		s[t] = s[ls[t]] + s[rs[t]];
		if (op == 'U') {
			f[t] = max(f[ls[t]], f[rs[t]]);
		} else {
			f[t] = s[t];
			f[t] = min(f[t], f[ls[t]] + s[rs[t]]);		
			f[t] = min(f[t], s[ls[t]] + f[rs[t]]);
		}
		return t;
	}
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		scanf(" %d %s", &n, str);
		p = 0, tot = 0;	
		int root = expr();
		printf("%d\n", f[root]);
	}
	return 0;
}
