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
} io;


const int limit = 1e9;
int cnt[1 << 17] , mask = (1 << 17) - 1;
int a[(1 << 17) + 1];
int w[18][1 << 17];

void gen(ll a,ll b,ll c){
//	if(c > limit) return;
//	if(a > b) ++cnt[a & mask];
//	else ++cnt[b & mask];
	a > b ? ++cnt[a & mask] : ++cnt[b & mask];
	ll x = (a + c - b) << 1 , y = (a + b + c) << 1 , z = (b + c - a) << 1;	
	if (x + c <= limit) gen(x - a , x + b , x + c);
	//gen(a - (b << 1) + (c << 1), ((a + c) << 1) - b , ((c + a - b) << 1) + c);
	if (y + c <= limit) gen(y - a , y - b , y + c);
	//gen(a + ((b + c) << 1) , ((a + c) << 1) + b , ((a + b + c) << 1) + c);
	if (z + c <= limit) gen(z + a , z - b , z + c);
	//gen(-a + ((b + c) << 1) , -(a << 1) + b + (c << 1) , ((c + b - a) << 1) + c);
}

/*
const int N = 1e5 + 7;
struct Node {
	short x;
	ll a, b, c;
} st[N];
int top;
void gao() {
	top = 0;
	++top;
	st[top].x = 0;
	st[top].a = 3, st[top].b = 4, st[top].c = 5;
	ll a, b, c;
	while (top > 0) {
		if (st[top].x >= 3 || st[top].c > limit) {
			--top;
			continue;
		}
		a = st[top].a, b = st[top].b, c = st[top].c;	
		switch(st[top].x++) {
			case 0: ++cnt[max(a, b) & mask];
				++top;
				st[top].x = 0;
				st[top].a = a - (b << 1) + (c << 1);
				st[top].b = ((a + c) << 1) - b;
				st[top].c = 2 * a - 2 * b + 3 * c;
				break;
			case 1:
				++top;
				st[top].x = 0;
				st[top].a = a + ((b + c) << 1);
				st[top].b = ((a + c) << 1) + b;
				st[top].c = ((a + b + c) << 1) + c;
				break;
			case 2:
				++top;
				st[top].x = 0;
				st[top].a = -a + ((b + c) << 1);
				st[top].b = -(a << 1) + b + (c << 1);
				st[top].c = -(a << 1) + (b << 1) + 3 * c;
				break;
		}
	}
}
*/

/*
int x[1 << 25] , y[1 << 25] , z[1 << 25];

int l,r;
inline void gen(ll a,ll b,ll c){
	if(c > limit) return;
	cnt[max(a , b) & mask]++;
	x[r] = a , y[r] = b , z[r++] = c;
	if(r >> 25) r = 0;
}
void bfs(){
	l = r = 0;
	gen(3 , 4 , 5);
	while(l != r){
		ll a = x[l] , b = y[l] , c = z[l++];
		if(l >> 25) l = 0;
		gen(a - (b << 1) + (c << 1), ((a + c) << 1) - b , 2 * a - 2 * b + 3 * c);
		gen(a + ((b + c) << 1) , ((a + c) << 1) + b , ((a + b + c) << 1) + c);
		gen(-a + ((b + c) << 1) , -(a << 1) + b + (c << 1) , -(a << 1) + (b << 1) + 3 * c);
	}
}
*/

int T;
int main() {
	gen(3 , 4 , 5);
//	rep(k, 1, 17 + 1) {
//		int mk = (1 << k) - 1;
//		rep(i, 0, 1 << 17) w[k][i & mk] += cnt[i];	
//	}
	//bfs();
//	gao();
//	scanf("%d",&T);
	T = io.xuint();
	rep(i,0,T) {
		int k;
//		scanf("%d",&k);
		k = io.xuint();
		ll ans = 0;
		rep(i, 0, 1 << k) {
//			int ai = io.xuint();
//			ans += 1ll * w[k][i] * ai;
			a[i] = io.xuint();
		}
//		rep(i,0,1<<k) a[i] = io.xuint();
//		ll ans = 0;
		rep(i,0,1<<17) ans += 1ll * cnt[i] * a[i & ((1 << k)-1)];
		printf("%lld\n",ans);
	}
	return 0;
}
