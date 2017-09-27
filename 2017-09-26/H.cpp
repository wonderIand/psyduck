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

const int N = 101 , P = 1e9 + 7;
bitset<N> has[N];
int n , m , K , cnt[1 << 18] , vis[1 << 18] , mask[N] , times , comb[N][N] = {{1}};
inline void pp(int &x,int d){
    if((x += d) >= P) x -= P;
}

int main(){
    freopen("separating-sets.in","r",stdin);
    freopen("separating-sets.out","w",stdout);
    rep(i,1,N) rep(j,0,N+1) comb[i][j] = j ? (comb[i-1][j-1] + comb[i-1][j]) % P : 1;
    cin >> n >> m >> K;
    rep(i,0,m) {
        int t;cin >> t;
        rep(j,0,t) {
            int x;cin >> x;
            --x;
            has[i][x] = 1;
            mask[x] |= 1 << i;
        }
    }
    int ans = 0;
    rep(i,1,1<<m) {
        int tmp = 0;
        rep(j,0,n) cnt[mask[j] & i] ++;
        ++times;
        rep(j,0,n) {
            int c = mask[j] & i;
            if(vis[c] == times) continue;
            vis[c] = vis[c ^ i] = times;
            pp(tmp , 1ll * comb[cnt[c]][K] * comb[cnt[c ^ i]][K] % P * 2 % P);
        }
        rep(j,0,n) cnt[mask[j] & i] --;
        if(__builtin_popcount(i) & 1) pp(ans , tmp);
        else pp(ans , P - tmp);
    }
    cout << ans << endl;
    return 0;
}
