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
const int N = 1e6 + 7;
int p, a, b;
int flag = 0;
int vis[N];
int main() {
	
	scanf("%d", &p);
	while (~scanf("%d", &a)) {
		if (!~scanf("%d", &b)) break;
		if (b == 1) {
			puts("0");
			continue;
		}
		flag++;
		int ans = 0;
		int cur = 1;
		for (; vis[cur] < flag && cur != b; cur = 1ll * cur * a % p) {
			vis[cur] = flag; ans++;
		}
		if (cur == b) printf("%d\n", ans); else puts("0");
	}
	return 0;
}
