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

const int N = 303 , P = 1e9 + 7;
int n , g[N][N] , layer[N] , vis[N] , comb[N][N] = {{1}};
int prefix[N] , suffix[N][N] , way[N][N];
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}

int main(){
    scanf("%d",&n);
    rep(i,0,n) rep(j,0,n) scanf("%d",g[i]+j),--g[i][j];
    rep(c,0,n) {
        rep(i,0,n) if(!vis[i]) {
            int col=-1,cnt=0;
            rep(j,0,n) if((i!=j)&&!vis[j]&&(col==-1||g[i][j]==col)) col=g[i][j],++cnt;
            if(cnt==n-1-c) {
                layer[c]=col;
                vis[i]=true;
                break;
            }
        }
    }
    rep(i,1,n+1) rep(j,0,i+1) comb[i][j]=j?(comb[i-1][j-1]+comb[i-1][j])%P:1;
    rep(i,0,N) rep(j,0,n) way[i][j]=1;
    int ans=n;
    rep(c,2,n+1){
        rep(i,0,n) suffix[N-1][i]=1,prefix[i]=1;
        per(i,0,N-1) rep(j,0,n) suffix[i][j]=(ll)suffix[i+1][j]*way[i+1][j]%P;
        rep(i,0,N) {
            int cnt=0;
            rep(j,0,n){
                if(cnt>=c-1){
                    pp(ans,(ll)c*comb[cnt][c-1]%P*prefix[j]%P*suffix[i][j]%P);
                    pp(way[i][j],comb[cnt][c-1]);
                }
                prefix[j]=(ll)prefix[j]*way[i][j]%P;
                if(layer[j]==i) ++cnt;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
