#include<bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b-1); i>=(a); i--)
#define de(x) cout << #x << " => " << x << endl
using namespace std;

#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii;

#define pb push_back
typedef vector<int> vi;

typedef long long ll;
typedef long double ld;

int n;
int pos1, tot, out;
///----------------------------------------------
vector<pair<pii,int> > ans;
bool vis[1000][2];
void build(int dep, int u, int &dig) {
    if (dep>n) return;
    int dir = (dig >> (n-dep)) & 1;
    if (!vis[u][dir]) {
        vis[u][dir] = true;
        if (dir == 1) {
            ///to right
            int rson = u<<1|1;
            pair<pii,int> tmp;
            tmp.fi.fi = dep;
            tmp.fi.se = u + tot;
            tmp.se = rson + tot;
            ans.pb(tmp);
        }
        else {
            ///to left
            int lson = u<<1;
            pair<pii,int> tmp;
            tmp.fi.fi = dep + 2 + n;
            tmp.fi.se = u + tot;
            tmp.se = lson + tot;
            ans.pb(tmp);
        }
    }
    build(dep+1, u<<1|dir, dig);
}

///----
int val[1000];
int mac[1000];
void ioxor(int a,int b,int &c) { /*printf("%d %d %d\n",a,b,c);*/ c^=a&b; }
void show() {
    //rep(i,1,n+1+1+(1<<(n+1))+1) printf("%d ",mac[i]); printf("\n");
}
int work( ) {
    rep(i,0,sz(ans)) {
        show();
        ioxor(mac[ans[i].fi.fi], mac[ans[i].fi.se], mac[ans[i].se]);
    }
    show();
    return mac[n+1];
}
void check( ) {
    rep(i,0,1<<n) {
        //init
        memset(mac,0,sizeof(mac));
        rep(j,0,n) mac[j+1] = (i>>(n-1-j))&1;
        mac[n+1] = out;
        rep(j,n+2,n+2+n+2) mac[j] = 1;
        //
        int ret = work();
        if (ret != val[i]) {
            de("WA");
            exit(0);
        }
    }
    de("AC");
}
///----
int main() {

    #define ONLINE_JUDGE TRUE
    // freopen ( "xx.in" , "r" , stdin );

    #ifdef ONLINE_JUDGE
    for (; ~scanf("%d",&n); ) {
    #endif // ONLINE_JUDGE
        ///init
        memset(vis,false,sizeof(vis));
        ans.clear();

        ///read
        #ifndef ONLINE_JUDGE
            n = 8;
            srand((unsigned)time(0));
        #else
            if (n<=0) continue;
        #endif // ONLINE_JUDGE
        tot = n + 2 + n;
        pos1 = n + 2;
        rep(i,0,n) {
            pair<pii,int> tmp;
            tmp.fi.fi = pos1;
            tmp.fi.se = i + 1;
            tmp.se = n + 3 + i;
            ans.pb(tmp);
        }

        ///read 2
        vi ned;
        int num1 = 0;
        rep(i,0,1<<n) {
            int pos = 0;
            #ifndef ONLINE_JUDGE
                pos = (1<<n)-1-i;
                val[pos] = rand()&1;
            #else
                rep(j,0,n) {
                    int bit; char c; scanf(" %c",&c); bit = c=='1';
                    pos = pos<<1 | bit;
                }
                scanf("%d",&val[pos]);
            #endif // ONLINE_JUDGE
            num1 += val[pos];
        }

        ///prework2
        out = num1*2 >= (1<<n) ? 0 : 1;
        rep(i,0,1<<n) {
            if (val[i] == out) continue;
            build(1,1,i);
            ned.pb(tot + (1<<n) + i);
        }

        ///work
        rep(i,0,sz(ned)) {
           pair<pii,int> tmp;
           tmp.fi.fi = ned[i];
           tmp.fi.se = pos1;
           tmp.se = n + 1;
           ans.pb(tmp);
        }

        ///print
        #ifndef ONLINE_JUDGE
            de(sz(ans));
            check();
        #else
            printf("%d\n",out);
            int t = n+(1<<(n+1));
            if (t>800 || sz(ans)>800) for(;;);
            printf("%d\n",t);
            rep(i,0,n+2) printf("1\n");
            rep(i,n+2,t) printf("0\n");
            printf("%d\n",sz(ans));
            rep(i,0,sz(ans)) {
                printf("%d %d %d\n",ans[i].fi.fi,ans[i].fi.se,ans[i].se);
            }
        #endif // ONLINE_JUDGE

    #ifdef ONLINE_JUDGE
    }
    #endif // ONLINE_JUDGE

    return 0;

}








