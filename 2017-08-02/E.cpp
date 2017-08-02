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
#define de(x) cout << #x << " = " << x << endl;
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
//-------
const int N = 1e6 + 10;
int n , K , q[N] , fa[N] , h[N] , w[N << 1] , ne[N << 1] , to[N << 1] , e;
void link(int u,int v,int c){
    to[e] = v;
    ne[e] = h[u];
    w[e] = c;
    h[u] = e++;
}
int sz[N];

int main() {
    while(~scanf("%d%d",&n,&K)){
        e = 0;
        rep(i,1,n+1) h[i] = -1 , fa[i] = -1 , sz[i] = 1;
        int u,v,c;
        rep(i,1,n){
            scanf("%d%d%d",&u,&v,&c);
            link(u , v , c);
            link(v , u , c);
        }
        int _ = 0;q[_++] = 1;
        fa[1] = 0;
        rep(i,0,_){
            int c = q[i];
            for(int k=h[c];~k;k=ne[k]){
                int t=to[k];
                if(fa[t] == -1){
                    fa[t] = c;
                    q[_++] = t;
                }
            }
        }
        ll ans = 0;
        per(i,0,n){
            int c = q[i];
            sz[fa[c]] += sz[c];
            for(int k=h[c];~k;k=ne[k]){
                int t=to[k];
                if(fa[t] == c)
                    ans += 1ll * min(sz[t] , K) * w[k];
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
