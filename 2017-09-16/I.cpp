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
const int Q = 3e4 + 7;
const int V = 2e6 + 7;
const int M = 26;
const int B = 33427;
const int P = 1e9 + 7;
int n;
int rt, tot, head[V], cnt[V], ne[V][M];
struct Edge {
	int v, nxt;
	Edge() {}
	Edge(int _v, int _nxt) {
		v = _v, nxt = _nxt;
	}
} e[V];
int et;
void ins(int L, char *str, int id) {	
	int p = rt;
	rep(i, 0, L) {
		int x = str[i] - 'a';
		if (ne[p][x] == -1) {
			cnt[tot] = 0, head[tot] = -1;
			memset(ne[tot], -1, sizeof(ne[tot]));
			ne[p][x] = tot++;
		}
		p = ne[p][x];
		++cnt[p];
		e[et] = Edge(id, head[p]), head[p] = et++;
	}
}
int get(int L, char *str) {
	int p = rt;
	rep(i, 0, L) {
		int x = str[i] - 'a';
		if (ne[p][x] == -1) return -1;
		p = ne[p][x];
	}
	return p;
}
int pw[V], p[Q], len[Q], hs[V];
char s[V], a[V], b[V], c[V], d[V];
int geths(int l, int r) {
	return (hs[r] - 1ll * hs[l - 1] * pw[r - l + 1] % P + P) % P;
}
int la, lb, lc, ld;
int ha, hb, hc, hd;
int geths(int L, char *str) {
	int ret = str[0];
	rep(i, 1, L)
		ret = (1ll * ret * B + str[i]) % P;
	return ret;
}
int solve(int t) {
	if (t == -1) return 0; 
	hb = geths(lb, b);
	hc = geths(lc, c);
	hd = geths(ld, d);
	int ret = 0;
	for (int i = head[t]; ~i; i = e[i].nxt) {
		int id = e[i].v;
//		if (len[i] < la + lb + lc + ld) continue;	
		if (len[id] / 2 < la + lb || len[id] / 2 < lc + ld) continue;
//		de(id);
		int l1 = len[id] / 2;		
		int r = p[id] + l1 - 1;	
		if (!(geths(r - lb + 1, r) == hb)) continue;
		if (!(geths(r + 1, r + 1 + lc - 1) == hc)) continue;	
		r += l1;
		if (!(geths(r - ld + 1, r) == hd)) continue;
		++ret;
	}
	return ret;
}
int main() {
	pw[0] = 1;
	rep(i, 1, V) pw[i] = 1ll * pw[i - 1] * B % P;
	int T;
	scanf("%d", &T);
	rep(cas, 0, T) {
		rt = 0, tot = 1;
		cnt[rt] = 0, memset(ne[rt], -1, sizeof(ne[rt]));	
		scanf("%d", &n);
		int L = 1, m = 0;
		et = 0;
		rep(i, 0, n) {
			int op;
			scanf("%d", &op);
			if (op == 1) {	
				scanf(" %s", s + L);
				p[i] = L, len[i] = strlen(s + L);
				rep(j, L, L + len[i])
					hs[j] = (1ll * hs[j - 1] * B + s[j]) % P;
				ins(len[i] >> 1, s + L, i);
				L += len[i];
			} else {
				scanf(" %s %s %s %s", a, b, c, d);
				la = strlen(a), lb = strlen(b), lc = strlen(c), ld = strlen(d);
				int p = get(la, a);	
				printf("%d\n", solve(p));
			}
		}
	}
	return 0;
}
