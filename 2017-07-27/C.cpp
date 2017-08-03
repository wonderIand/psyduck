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
typedef long long ll;
typedef pair<ll,ll> pll;
const int MAX_N = 7 + 250000;
const int MOD = 1e9 + 7;
//-------
int b[MAX_N];
int main() {

    for (int n; ~scanf("%d",&n); ) {
        ///read
        priority_queue<pll, vector<pll>, less<pll> > que;
        rep(i,1,n+1) {
            int a; scanf("%d",&a);
            que.push(mp(a-i,i));
        }
        rep(i,1,n+1) scanf("%d",&b[i]);

        ///work
        sort(b+1,b+1+n);
        ll ans=0;
        rep(i,n+1,2*n+1) {
            int pos = b[i-n];
            for (; que.top().se<pos; que.pop());
            ans=(ans+que.top().fi)%MOD;
            if (ans<0) ans+=MOD;
            que.push(mp(que.top().fi-i,i));
        }
        cout << ans << endl;
    }

    return 0;
}
