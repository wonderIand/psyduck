#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define de(x) cout << #x << " = " << x << endl
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
//-------

const int N = 3e5 + 10;

struct Seg{
    static const int N = ::N << 2;
    ll a[N] , tag[N] , n;
    void build(int c,int l,int r,ll*x){
        tag[c] = 0;
        if(l == r) a[c]=x[l];
        else {
            int mid=(l+r)>>1;
            build(c<<1,l,mid,x);
            build(c<<1|1,mid+1,r,x);
            a[c]=min(a[c<<1],a[c<<1|1]);
        }
    }
    void ins(int c,int l,int r,int L,int R,int d){
        if(L <= l && r <= R){
            tag[c] += d;
            a[c] += d;
        } else {
            int mid=(l+r)>>1;
            if(L <= mid) ins(c<<1,l,mid,L,R,d);
            if(R > mid) ins(c<<1|1,mid+1,r,L,R,d);
            a[c] = tag[c] + min(a[c<<1] , a[c<<1|1]);
        }
    }
    ll query(int c,int l,int r,int L,int R){
        if(L <= l && r <= R){
            return a[c];
        } else {
            int mid=(l+r)>>1;
            ll res=1ll<<60;
            if(L <= mid) res=min(res,query(c<<1,l,mid,L,R));
            if(R > mid) res=min(res,query(c<<1|1,mid+1,r,L,R));
            return res + tag[c];
        }
    }
    ll query(int l,int r){
        return query(1,0,n,l,r);
    }
    void ins(int l,int r,int d){
        ins(1,0,n,l,r,d);
    }
    void init(int _n,ll*x){
        n=_n;
        build(1,0,n,x);
    }
};


struct LCARMQ{
    static const int N = ::N << 1;
    int a[20][N] , lft[N] , dep[N] , lg[N] , L;
    int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
    void add(int x){ a[0][L++] = x;}
    void dfs(int c,int fa,const vi g[]){
        lft[c]=L;add(c);
        for(auto t : g[c]) if(t!=fa) dep[t]=dep[c]+1,dfs(t,c,g),add(c);
    }
    void Build(const vi g[]){
        dep[1] = 1;
        L=0;dfs(1,-1,g);
        rep(i,2,L) lg[i]=lg[i-1]+(i==(i&-i));
        rep(i,1,20){
            int lim=L+1-(1<<i);
            rep(j,0,lim) a[i][j]=rmin(a[i-1][j] , a[i-1][j+(1<<i>>1)]);
        }
    }
    int lca(int x,int y){
        x=lft[x],y=lft[y];
        if(x > y) swap(x , y);
        int i=lg[y-x+1];
        return rmin(a[i][x],a[i][y+1-(1<<i)]);
    }
} lca;
Seg seg;
int n,K,a[N];
vi g[N];
ll dp[N] , pd[N];
vector<pii> st;

int main() {
    while(~scanf("%d%d",&n,&K)){
        rep(i,1,n+1) scanf("%d",a + i) , g[i].clear();
        rep(i,1,n){
            int u,v;
            scanf("%d%d",&u,&v);
            g[u].pb(v);
            g[v].pb(u);
        }
        lca.Build(g);
        //rep(i,1,n+1) rep(j,i,n+1) cout << i << " " << j << " " << lca.lca(i , j) << endl;
        dp[0] = 0;
        rep(i,1,n+1) dp[i] = 1ll<<50;
        rep(times,0,K){
            seg.init(n,dp);
            st.clear();
            rep(i,1,n+1){
                int c=a[i],lft=i;
                int top = -1;
                while(sz(st)){
                    pii tmp=st.back();
                    int node = lca.lca(tmp.se , c);
                    if(node != tmp.se){
                        //cout << tmp.fi  << " " << lft - 1 << endl;;
                        //cout << lca.dep[c] - lca.dep[tmp.se] << endl;
                        seg.ins(tmp.fi-1,lft-2,-lca.dep[tmp.se]);
                        top = node;
                        st.pop_back();
                        lft=tmp.fi;
                    } else break;
                }
                if(top != -1){
                    seg.ins(lft-1,i-2,lca.dep[top]);
                    st.pb(mp(lft,top));
                }
                seg.ins(i-1,i-1,lca.dep[c]);
                st.pb(mp(i,c));
                pd[i] = seg.query(0,i-1);
            }
            rep(i,1,n+1) dp[i]=pd[i];
            rep(i,0,times+1) dp[i]=1ll<<50;
            //rep(i,0,n+1) printf("%lld%c",dp[i]," \n"[i==n]);
        }
        printf("%lld\n",dp[n]);
    }
    return 0;
}
