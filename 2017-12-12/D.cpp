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
const int P = (int)1e9 + 7 , N = 1000 * 1000 * 10 + 7;
int Pow(int a,int b){int r=1;for(;b;b>>=1,a=ll(a)*a%P)if(b&1)r=ll(r)*a%P;return r;}
int n , fac[N] = {1}, ifac[N];
void pp(int &a,int b){if((a+=b)>=P)a-=P;}
int mul(int a,int b){return ll(a)*b%P;}
int comb(int a,int b){
    if(a<b||a<0||b<0) return 0;
    return ll(fac[a])*ifac[b]%P*ifac[a-b]%P;
}
int cal(int n,int k){
    if(n == 0 && k == 0)
        return 1;
    int res = 0;
    rep(i,0,n+1) {
        int r=k-i*10;
        if(r<0) continue;
        pp(res , mul(i&1?P-1:1 , mul(comb(n,i) , comb(n-1+r,n-1))));
    }
    return res;
}

int main(){
    cin >> n;
    int tot = n * 10;
    fac[0] = 1;
    rep(i,1,tot) fac[i] = ll(fac[i-1]) * i % P;
    ifac[tot - 1] = Pow(fac[tot - 1] , P - 2);
    per(i,1,tot) ifac[i-1] = ll(ifac[i]) * i % P;
    if(~n & 1) {
        cout << Pow(10 , n / 2) << endl;
    } else {
        int half_n = n >> 1 , left = half_n >> 1;
        int ans = 0;
        rep(d,0,5) pp(ans,cal(half_n,d+left*9));
        cout << ans << endl;
    }
    return 0;
}

