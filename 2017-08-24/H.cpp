#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef double db;
#define fi frist
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e5 + 10;
int par[N] , n , K , sz[N];

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


int main() {
	int T;T = io.xuint();
	rep(i,0,T){
		n = io.xuint(); K = io.xuint();
		rep(i,2,n+1) par[i] = io.xuint();
		rep(i,1,n+1) sz[i] = 1;
		int cnt = 0;
		per(i,1,n+1) {
			if(sz[i] >= 2) sz[i] = 0 , ++cnt;
			sz[par[i]] += sz[i];
		}
		if(K <= 2 * cnt) printf("%d\n",(K + 1) / 2);
	else printf("%d\n",K - cnt);
	}
	return 0;
}

