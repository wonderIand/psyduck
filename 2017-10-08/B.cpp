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
ll encode(int a[]) {
	ll ret = 0, p;
	rep(i, 0, 9) {
		ret = ret * 10 + a[i];
		if (!a[i]) p = i;
	}
	return ret * 10 + p;	
}
void decode(ll val, int a[]) {
	for (int i = 8; i >= 0; --i)
		a[i] = val % 10, val /= 10;
}
int s[10], t[10], a[10];
map<ll, int> R[2];
const int dx[] = { -1, 0, 1, 0, 1 , -1 };
const int dy[] = { 0, 1, 0, -1, -1 , 1};
int bfs(ll S, ll T) {
	rep(i, 0, 2) R[i].clear();
	queue<ll> que;
	R[0][S] = 0, que.push(S << 1);
	R[1][T] = 0, que.push(T << 1 | 1);
	while (!que.empty()) {
		int t = que.front() & 1;
		ll val = que.front() >> 1;
		int step = R[t][val];
		if (R[t ^ 1].count(val)) return step + R[t ^ 1][val];
		int p = val % 10;
		decode(val / 10, a);
		que.pop();
//		rep(i, 0, 9) printf("%d",a[i]);puts("");
		int sx = p / 3, sy = p % 3;
		rep(i, 0, 6) {
			if (i == 4 && t == 1) continue;
			if (i == 5 && t == 0) continue;
			int x = sx + dx[i];
			int y = sy + dy[i];
			if (x < 0 || x >= 3 || y < 0 || y >= 3) continue;
			int np = x * 3 + y;	
			swap(a[p], a[np]);
			ll nval = encode(a);
			if (!R[t].count(nval)) {
				R[t][nval] = step + 1;
				que.push(nval << 1 | t);
			}
			swap(a[p], a[np]);
		}
	}
	return -1;
}
int main() {
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		rep(i, 0, 9) scanf("%d", s + i);	
		rep(i, 0, 9) scanf("%d", t + i);
		int ans = bfs(encode(s), encode(t));
		printf("%d\n", ans);
	}
	return 0;
}
