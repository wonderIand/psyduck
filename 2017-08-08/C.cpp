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
#define dd(x) cerr << #x << " = " << x << ", "
#define de(x) cerr << #x << " = " << x << endl
//-------
const int N = 1e6 + 7;
const int M = 4e5 + 7;
const int B = 1e3 + 7;
struct Node {
	int ls, rs, siz;
	ll w, sum;
	void clr() {
		ls = rs = 0, siz = 1;
	}
} a[N], b[M];
struct Treap {
	int tot;
	void init() {
		tot = 0, srand(time(0));
	}
	inline int _rand() {
		return ((ll) rand() << 14) ^ ((ll) rand());
	}
	inline int newnode() {
		++tot, a[tot].clr();
		return tot;
	}
	void up(int t) {
		a[t].siz = 1 + a[a[t].ls].siz + a[a[t].rs].siz;
		a[t].sum = a[t].w + a[a[t].ls].sum + a[a[t].rs].sum;
	}
	int merge(int t1, int t2) {
		if (!t1 || !t2) {
			if (!t1 && !t2) return 0;
			int nt = newnode();
			a[nt] = a[t1 | t2];
			return nt;
		}
		int nt = newnode();
		if (_rand() % (a[t1].siz + a[t2].siz) < a[t1].siz) {
			a[nt] = a[t1];
			a[nt].rs = merge(a[t1].rs, t2);
		} else {
			a[nt] = a[t2];
			a[nt].ls = merge(t1, a[t2].ls);
		}
		up(nt);
		return nt;
	}
	void split(int t, int k, int &lt, int &rt) {
		if (!t) {
			lt = rt = 0;
			return ;
		}
		int nt = newnode();
		a[nt] = a[t];
		if (a[a[t].ls].siz >= k) {
			rt = nt;
			split(a[t].ls, k, lt, a[nt].ls);
		} else {
			lt = nt;
			split(a[t].rs, k - 1 - a[a[t].ls].siz, a[nt].rs, rt);	
		}
		up(nt);
	}
	int cpow(int A, int b) {
		int r = 0, g = newnode();
		a[g] = a[A];
		while (b > 0) {
			if (b & 1) r = merge(r, g);
			g = merge(g, g), b >>= 1;
		}
		return r;
	}
	void rebuild(int &rt0, int &rt1) {
		static int timestamp = 0;
		if (tot + B < N) return ;
		static int que[M], ts[N], id[N];
		int h = 0, t = 0;
		++timestamp;
		if (rt0)
			++t, que[t] = rt0, id[rt0] = t, ts[rt0] = timestamp, b[t] = a[rt0];	
		if (rt1)
			++t, que[t] = rt1, id[rt1] = t, ts[rt1] = timestamp, b[t] = a[rt1];	
		while (h < t) {
			int u = que[++h];
			if (a[u].ls) {
				if (ts[a[u].ls] != timestamp) {
					id[a[u].ls] = ++t;
					ts[a[u].ls] = timestamp;
					que[t] = a[u].ls, b[t] = a[a[u].ls];
				}
				b[h].ls = id[a[u].ls];
			}
			if (a[u].rs) {
				if (ts[a[u].rs] != timestamp) {
					id[a[u].rs] = ++t;
					ts[a[u].rs] = timestamp;
					que[t] = a[u].rs, b[t] = a[a[u].rs];
				}
				b[h].rs = id[a[u].rs];
			}
		}
		tot = t;
		rep(i, 1, t + 1) a[i] = b[i];
		rt0 = rt0 ? id[rt0] : 0, rt1 = rt1 ? id[rt1] : 0;
	}
} T;
int n, m, root[2];
int main() {
//	freopen("C.out", "w", stdout);
	scanf("%d%d", &n, &m);	
	T.init(), root[0] = root[1] = 0;
	rep(i, 1, n + 1) {
		T.rebuild(root[0], root[1]);
		int x; scanf("%d", &x);
		int t = T.newnode();
		a[t].w = a[t].sum = x;
		root[0] = T.merge(root[0], t);
	}
	root[1] = T.merge(root[0], root[1]);
	rep(_m, 0, m) {
		T.rebuild(root[0], root[1]);
		int op, l, r, k, lt, rt;	
		scanf("%d%d%d", &op, &l, &r);
		if (op == 1) {
			T.split(root[1], r, lt, rt);
			T.split(lt, l - 1, lt, rt);
			printf("%lld\n", a[rt].sum);
			continue;
		}
		if (op == 2) {
			scanf("%d", &k);
			T.split(root[1], l - 1, lt, rt);
			T.split(lt, l - 1 - k, lt, rt);
			int M = T.cpow(rt, (r - l + 1) / k);
			if ((r - l + 1) % k) {
				T.split(root[1], l - k - 1 + (r - l + 1) % k, lt, rt);
				T.split(lt, l - k - 1, lt, rt);
				M = T.merge(M, rt);
			}
			T.split(root[1], r, lt, rt);
			T.split(lt, l - 1, lt, op);
			root[1] = T.merge(lt, M);
			root[1] = T.merge(root[1], rt);
			continue;
		}
		if (op == 3) {
			T.split(root[0], r, lt, rt);
			T.split(lt, l - 1, lt, k);
			T.split(root[1], r, lt, rt);	
			T.split(lt, l - 1, lt, op);	
			root[1] = T.merge(lt, k);
			root[1] = T.merge(root[1], rt);
			continue;
		}
	}
	return 0;
}
