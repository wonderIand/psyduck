#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define de(x) cout << #x << " = " << x << endl;
const int MAX_N = 2e5 + 7;
vector<int> G[MAX_N];
//-------
struct Tree {
    static const int Tree_N = MAX_N<<2;
    int sum[Tree_N], n;
    int tag[Tree_N];
    int ls(int o) { return o<<1; }
    int rs(int o) { return o<<1|1; }
    void init(int n) { this->n = n; }
    void update(int o) {
        sum[o] = sum[ls(o)] + sum[rs(o)];
    }
    //---
    void _build(int o,int l,int r) {
        tag[o]=-1;
        if (l==r) sum[o]=1; else {
            int mid=(l+r)>>1;
            _build(ls(o),l,mid);
            _build(rs(o),mid+1,r);
            update(o);
        }
    }
    void build() {
        _build(1,1,n);
    }
    //---
    void pushdown(int o,int l,int r) {
        if (!~tag[o]) return;
        int mid=(l+r)>>1;
        sum[ls(o)] = (tag[ls(o)]=tag[o]) * (mid-l+1);
        sum[rs(o)] = (tag[rs(o)]=tag[o]) * (r-mid);
        tag[o]=-1;
    }
    //---
    void _change(int o, int l, int r, int ql, int qr, int qv) {
        if (ql<=l&&qr>=r) tag[o]=qv,sum[o]=(r-l+1)*qv; else {
            pushdown(o,l,r);
            int mid=(l+r)>>1;
            if (ql<=mid) _change(ls(o),l,mid,ql,qr,qv);
            if (qr> mid) _change(rs(o),mid+1,r,ql,qr,qv);
            update(o);
        }
    }
    void change(int ql,int qr,int qv) {
        _change(1,1,n,ql,qr,qv);
    }
    //---
    int _query(int o,int l,int r,int ql,int qr) {
        if (ql<=l&&qr>=r) return sum[o]; else {
            pushdown(o,l,r);
            int mid=(l+r)>>1, ret=0;
            if (ql<=mid) ret+=_query(ls(o),l,mid,ql,qr);
            if (qr> mid) ret+=_query(rs(o),mid+1,r,ql,qr);
            return ret;
        }
    }
    int query(int ql,int qr) {
        return _query(1,1,n,ql,qr);
    }
}    tree;
//-------
int dep[MAX_N];
int far[MAX_N];
int dfn[MAX_N],tot;
int in[MAX_N], out[MAX_N];
void dfs(int u,int p) {
    dfn[++tot] = u;
    in[u]=tot;
    rep(i,0,sz(G[u])) {
        int v = G[u][i]; if (v==p) continue;
        dep[v] = dep[u] + 1;
        far[v] = u;
        dfs(v, u);
    }
    out[u]=tot;
}
//-------
int col[MAX_N];
pair<pair<int,int>, int> p[MAX_N];
int main() {

    for (int n,icase=0; ~scanf("%d",&n); ) {
        ///read
        rep(i,1,n+1) scanf("%d",&col[i]);
        rep(i,1,n+1) G[i].clear();
        rep(i,1,n) {
            int a,b; scanf("%d%d",&a,&b);
            G[a].pb(b);
            G[b].pb(a);
        }
        ///prework
        tot=0; dep[1]=1; dfs(1,0);
        tree.init(n);
        //rep(i,1,n+1) de(far[i]);
        ///work
        ll ans=0;
        rep(i,1,n+1) p[i]=mp(mp(col[i],-dep[i]), i);
        sort(p+1,p+1+n);
        for (int l=1,r; l<=n; l=r) {
            tree.change(1,n,1);
            for (r=l; r<=n&&p[r].fi.fi==p[l].fi.fi; r++);
            //de(l); de(r);
            vector<int> pos;
            int sum=0;
            rep(i,l,r) {
                int u = p[i].se;
                //de(u);
                rep(j,0,sz(G[u])) {
                    int v = G[u][j]; if (far[v]!=u) continue;
                    int val = tree.query(in[v], out[v]);
                    if (val) {
                        pos.pb(val);
                        sum+=val;
                    }
                }
                tree.change(in[u],out[u],0);
            }
            if (sum+r-l<n) {
                int val = tree.query(1, n);
                //de(val);
                pos.pb(val);
                sum += val;
            }
            //de(sum);
            ///
            ans+=1ll*(r-l)*sum;
            ans+=1ll*(r-l)*(r-l-1)/2;
            rep(i,0,sz(pos)) {
                sum-=pos[i];
                ans+=1ll*pos[i]*sum;
            }
            //de(ans);
        }

        ///print
        cout << "Case #" << ++icase << ": " << ans << endl;


    }



    return 0;
}
