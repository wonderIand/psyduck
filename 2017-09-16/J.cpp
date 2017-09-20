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
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
struct FastIO {
	static const int S = 1310720;
	int wpos;
	char wbuf[S];
	FastIO() :
			wpos(0) {
	}
	inline int xchar() {
		static char buf[S];
		static int len = 0, pos = 0;
		if (pos == len)
			pos = 0, len = fread(buf, 1, S, stdin);
		if (pos == len)
			return -1;
		return buf[pos++];
	}
	inline int xuint() {
		int c = xchar(), x = 0;
		while (c <= 32)
			c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar())
			x = x * 10 + c - '0';
		return x;
	}
	inline int xint() {
		int s = 1, c = xchar(), x = 0;
		while (c <= 32)
			c = xchar();
		if (c == '-')
			s = -1, c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar())
			x = x * 10 + c - '0';
		return x * s;
	}
	inline void xstring(char *s) {
		int c = xchar();
		while (c <= 32)
			c = xchar();
		for (; c > 32; c = xchar())
			*s++ = c;
		*s = 0;
	}
	inline void wchar(int x) {
		if (wpos == S)
			fwrite(wbuf, 1, S, stdout), wpos = 0;
		wbuf[wpos++] = x;
	}
	inline void wint(int x) {
		if (x < 0)
			wchar('-'), x = -x;
		char s[24];
		int n = 0;
		while (x || !n)
			s[n++] = '0' + x % 10, x /= 10;
		while (n--)
			wchar(s[n]);
	}
	inline void wstring(const char *s) {
		while (*s)
			wchar(*s++);
	}
	~FastIO() {
		if (wpos)
			fwrite(wbuf, 1, wpos, stdout), wpos = 0;
	}
};
//-------
const int N = (1e7 + 7) + (8e6);
const int MAXQ = 1e5 + 7;
const int MAXN = 1e6 + 7;
struct Node {
	int ls, rs, siz;
	int mv, val;
	short d;
	void clr() {
		ls = rs = 0, siz = 1;
		d = 0, mv = val = -1;
	}
} a[N];
int rt[MAXQ], val[MAXN];
inline bool le(int x, int y) {
	if (x < 0) return false;
	if (y < 0) return true;
	return x >= 0 && x <= y;
}
int cnt, path[N];
struct Treap {
	int tot;
	void init() {
		tot = 0, srand(time(NULL));
		a[0].clr();
		a[0].siz = 0;
	}
	inline int _rand() {
		return (((ll) rand() << 14) ^ ((ll) rand()));
	}
	inline int newnode() {
		++tot, a[tot].clr();
		return tot;
	}
	void up(int t) {
		a[t].siz = 1 + a[a[t].ls].siz + a[a[t].rs].siz;
		a[t].mv = a[t].val, a[t].d = 0;	
		if (a[t].ls && le(a[a[t].ls].mv, a[t].mv)) a[t].mv = a[a[t].ls].mv, a[t].d = 1;
		if (a[t].rs && le(a[a[t].rs].mv, a[t].mv)) a[t].mv = a[a[t].rs].mv, a[t].d = 2;
	}
	int build(int l, int r) {
		int m = (l + r) >> 1;
		int t = newnode();
		a[t].val = val[m];
		if (l < m) a[t].ls = build(l, m - 1);
		if (m < r) a[t].rs = build(m + 1, r);
		up(t);
		return t;
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
	int get(int rt, int l, int r) {
		int L, R;
		split(rt, r, L, R);
		split(L, l - 1, L, R);
		return R;
	}	
	inline int getk(int t, int k) {
		while (true) {
			if (a[a[t].ls].siz + 1 == k)
				return a[t].val;
			if (k <= a[a[t].ls].siz)
				t = a[t].ls;
			else k -= a[a[t].ls].siz + 1, t = a[t].rs;
		}
		return -1;
	}
	pii qry(int x) {
		cnt = 0;
		int t = rt[x], rk = 1, d;
		while (true) {
			int nt = newnode();	
			a[nt] = a[t];
			path[++cnt] = nt;
			if (cnt > 1)
				(d == 1 ? a[path[cnt - 1]].ls : a[path[cnt - 1]].rs) = nt;
			if (!a[t].d) {
				rk += a[a[t].ls].siz;
				break;
			}
			d = a[t].d;
			if (a[t].d == 1) {
				t = a[t].ls;
			} else {
				rk += 1 + a[a[t].ls].siz;
				t = a[t].rs;
			}
		}
		pii ret = mp(a[path[cnt]].val, rk);
		rt[x] = path[1];
		a[path[cnt]].val = -1;
		for (int i = cnt; i > 0; --i) up(path[i]);
		return ret;	
	}
} T;
struct Seq {
	ll sum;
	int pos;
	Seq() {}
	Seq(ll _sum, int _pos) {
		sum = _sum, pos = _pos;
	}
	bool operator<(const Seq &p) const {
		return sum > p.sum;
	}
};
int main() {
//	freopen("J.out", "w", stdout);
	int TT;
	scanf("%d", &TT);
	rep(cas, 0, TT) {
		int Q, m = 0;
		scanf("%d", &Q);
		T.init();
		rep(q, 0, Q) {
			int op;
			scanf("%d", &op);
			if (op == 1) {
				int n;
				scanf("%d", &n);
				rep(i, 0, n) scanf("%d", val + i);
				rt[++m] = T.build(0, n - 1);
			} else if (op == 2) {
				int x, l1, r1, y, l2, r2;
				scanf("%d%d%d%d%d%d", &x, &l1, &r1, &y, &l2, &r2);
				rt[++m] = T.merge(T.get(rt[x], l1, r1), T.get(rt[y], l2, r2));
			} else {
				int x, k, qs, _rt, _tot = T.tot;
				scanf("%d%d", &x, &k);
				_rt = rt[x];
				qs = min(a[rt[x]].siz, k);
				priority_queue<Seq> que;
				rep(i, 0, qs) {
					pii now = T.qry(x);
					que.push(Seq(now.fi, now.se));
				}
				rt[x] = _rt, T.tot = _tot;	
				rep(i, 0, k) {
					if (que.empty()) assert(false);
					Seq now = que.top();
					que.pop();
					printf("%lld\n", now.sum);
					if (now.pos + 1 <= a[rt[x]].siz) {
						now.sum += T.getk(rt[x], ++now.pos);
						que.push(now);
					}
				}
			}
		}
	}
	return 0;
}
