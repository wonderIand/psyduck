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
const int P = 1e9 + 7;
ll Pow(ll x,ll t){
    ll r=1l;
    for(;t;t>>=1,x=x*x%P){
        if(t&1) r=r*x%P;
    }
    return r;
}

int main() {
    ll n,K;
    int t=0;
    while(~scanf("%lld%lld",&n,&K)){
        printf("Case #%d: %d\n",++t,(int)Pow(n%P,K));
    }
    return 0;
}
