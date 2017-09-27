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
#define setIO(x) freopen(x".in","r", stdin);freopen(x".out","w",stdout);
//-------
const int N = 107;
int n, l, r;
char s[N];
int main() {
	setIO("brackets");
	scanf("%d%d%d", &n, &l, &r);	
	int L = 0;
	for (int i = l, j = r; i < j; ++i, --j) {
		L += 2;
		s[i] = '[', s[j] = ']';
	}
	for (int i = l - 1, j = r + 1; i > 0 && j <= n; --i, ++j) {
		L += 2;
		s[i] = '(', s[j] = ')';
		l = i, r = j;
	}
	if (l == 1) {
		for (int i = r + 1, j = n; i < j; ++i, --j)
			s[i] = '(', s[j] = ')';
	} else {
		for (int i = 1, j = l - 1; i < j; ++i, --j)
			s[i] = '(', s[j] = ')';
	}
	rep(i, 1, n + 1) putchar(s[i]);

	return 0;
}
