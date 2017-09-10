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
struct SAM {
    static const int N = 101010 << 1, M = 26;
    int par[N], l[N], ne[N][M] , cnt[N];
    int rt, last, L;
    void add(int c) {
        int p = last, np = ++L;
        fill(ne[np], ne[np] + M, 0);cnt[np] = 1;
        l[np] = l[p] + 1;
        last = np;
        while (p && !ne[p][c]) ne[p][c] = np, p = par[p];
        if (!p) par[np] = rt;
        else {
            int q = ne[p][c];
            if (l[q] == l[p] + 1) par[np] = q;
            else {
                int nq = ++L;cnt[nq] = 0;
                l[nq] = l[p] + 1;
                copy(ne[q], ne[q] + M, ne[nq]);
                par[nq] = par[q];
                par[q] = par[np] = nq;
                while (p && ne[p][c] == q) ne[p][c] = nq, p = par[p];
            }
        }
    }
    int t[N] , q[N];
    ll count(int K){
        rep(i,0,L+1) t[i] = 0;
        rep(i,0,L+1) t[l[i]]++;
        rep(i,1,L+1) t[i] += t[i-1];
        rep(i,1,L+1) q[--t[l[i]]] = i;
        ll res = 0;
        per(i,0,L) {
            int c = q[i];
            int fa = par[c];
            cnt[fa] += cnt[c];
            if(cnt[c] == K) res += l[c] - l[fa];
        }
        return res;
    }
    void ini() {
        rt = last = L = 1;
        fill(ne[rt], ne[rt] + M, 0);
        l[0] = -1;
    }
}sam;
const int N = 1e5 + 10;
int T;
int k,n;
char s[N];

ll solve(){
    scanf("%d%s",&k,s);
    n = strlen(s);
    sam.ini();
    rep(i,0,n) sam.add(s[i] - 'a');
    return sam.count(k);
}

int main() {
    scanf("%d",&T);
    rep(i,0,T) printf("%lld\n",solve());
    return 0;
}
