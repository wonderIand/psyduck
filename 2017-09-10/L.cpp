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
const int N = 1e6 + 7;
int a[N], b[N];
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
        if (c == -1) return -1;
        while (c <= 32) {
            c = xchar();
            if (c == -1) return -1;
        }
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
int n;
int sign(int d) { return (d > 0) - (d < 0); }
void format(vector<pii> &vu) {
    vector<pii> ret;
    rep(i, 0, sz(vu)) {
        if (!ret.empty() && sign(vu[i].fi) * sign(ret.back().fi) != -1) {
            ret.back().fi += vu[i].fi;
        } else {
            ret.pb(vu[i]);
        }
    }
    //check
    if (sz(ret) > 1) {
        if (sign(ret[0].fi) == -1 && sign(ret.back().fi) == -1) {
            ret.back().fi += ret[0].fi;
            rep(i, 0, sz(ret) - 1) swap(ret[i], ret[i + 1]);
            ret.pop_back();
        }
        else if (sign(ret[0].fi) == 1 && sign(ret.back().fi) == 1) {
            ret.back().fi += ret[0].fi;
            rep(i, 0, sz(ret) - 1) swap(ret[i], ret[i + 1]);
            rep(i, 0, sz(ret) - 2) swap(ret[i], ret[i + 1]);
            ret.pop_back();
        }
        else if (sign(ret[0].fi) == -1 && sign(ret.back().fi) == 1) {
            rep(i, 0, sz(ret) - 1) swap(ret[i], ret[i + 1]);
        }
    }
    //return
    swap(vu, ret);
}
void gao(vector<pii> &vu) {
    //rep(i, 0, sz(vu)) {
    //    printf("(%d %d) ", vu[i].fi, vu[i].se);
    //}
    //printf("\n");

    //push
    vector<pii> tmp;
    //assert(sz(vu) % 2 == 0);
    for (int i = 0; i < sz(vu); i += 2) {
        tmp.pb(mp(vu[i].fi + vu[i + 1].fi, vu[i].se));
    }
    swap(vu, tmp);
}
int main() {

    for (; (n = io.xuint()) != -1; ) {
        ///read
//        rep(i, 0, n) scanf("%d", &a[i]);
//        rep(i, 0, n) scanf("%d", &b[i]);
        rep(i, 0, n) a[i] = io.xuint();
        rep(i, 0, n) b[i] = io.xuint();

        ///prework
        vector<pii> vu;
        rep(i, 0, n) vu.pb(mp(a[i] - b[i], i + 1));
        //rep(i, 0, n) de(vu[i].fi);
        format(vu);

        ///work
        while (sz(vu) > 1) {
            gao(vu);
            format(vu);
        }

        ///print
        printf("%d\n", vu.back().se - 1);
    }


    return 0;
}
