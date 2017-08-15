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

ll P;
inline ll mul(ll a,ll b){
    return (a*b-ll((long double)a*b/P+0.5)*P+P)%P;
}
const int N = 1e5 + 10;
ll a[N];
int T,n;

int main() {
    scanf("%d",&T);
    rep(i,0,T){
        scanf("%d%lld",&n,&P);
        rep(i,0,n) scanf("%lld",a + i);
        if(P == 3){
            map<int,int> cnt;
            rep(i,0,n) cnt[a[i]]++;
            printf("%lld\n",1ll*cnt[1]*(cnt[1]-1)/2+1ll*cnt[2]*(cnt[2]-1)/2);
            continue;
        }
        map<ll,int> p3 , cnt;
        ll ans = 0;
        rep(i,0,n) if(a[i]){
            ll pow3=mul(mul(a[i],a[i]),a[i]);
            ans+=p3[pow3]-cnt[a[i]];
            cnt[a[i]]++;
            p3[pow3]++;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

