// #include {{{
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <bitset>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
// }}}
// #define {{{
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define de(x) cout << #x << "=" << x << endl
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
// }}}

const int N = 505 , P = 1e9 + 7;
int T,n,K,dp[N][1<<8],pd[N][1<<8];
int vis[N],rmap[N],_,mask[N],belong[N];
vi v[N];
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}

int main(){
    memset(rmap,-1,sizeof(rmap));
    rep(i,2,N) {
        if(!vis[i]) rmap[i]=_++;
        for(int j=i+i;j<N;j+=i) vis[j]=1;
    }
    rep(i,1,N){
        belong[i] = -1;
        map<int,int> times;
        int x=i,mask=0,p=1;
        for(int i=2;i*i<=x;++i) if(x%i==0){
            if(~rmap[i] && rmap[i]<=7) mask|=1<<rmap[i];
            else p*=i;
            while(x%i==0) x/=i,times[i]++;
        }
        if(~rmap[x] && rmap[x]<=7) mask|=1<<rmap[x];
        else p*=x;
        if(x>=1) times[x]++;
        bool ok=1;for(auto e : times) if(e.se>1) ok=0;
        if(ok) belong[i]=p,::mask[i]=mask;
    }
    scanf("%d",&T);
    rep(i,0,T){
        scanf("%d%d",&n,&K);
        rep(i,0,N) v[i].clear();
        rep(i,1,n+1) if(~belong[i]) v[belong[i]].pb(i);
        rep(i,0,K+1) rep(j,0,1<<8) dp[i][j]=0;
        dp[0][0]=1;
        for(auto e : v[1]) {
            per(i,0,K) per(j,0,1<<8) if(dp[i][j]&&((j&mask[e])==0))
                pp(dp[i+1][j|mask[e]] , dp[i][j]);
        }
        rep(k,2,n+1) if(sz(v[k])){
            per(i,0,K) per(j,0,1<<8) if(dp[i][j]) for(auto e : v[k]) if((j&mask[e])==0)
                pp(dp[i+1][j|mask[e]] , dp[i][j]);
        }
        int ans=0;
        rep(i,1,K+1) rep(j,0,1<<8) pp(ans,dp[i][j]);
        printf("%d\n",ans);
    }
    return 0;
}
