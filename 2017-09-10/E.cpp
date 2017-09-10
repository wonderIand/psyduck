#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef double db;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int P = 998244353;
void fib(ll n, ll &x, ll &y) {
    if (n == 1) {
        x = y = 1;
        return ;
    }
    if (n & 1) {
        fib(n - 1, y, x);
        y = (y + x) % P;
    } else {
        ll a, b;
        fib(n >> 1, a, b);
        y = (a * a + b * b) % P;
        x = (a * b + a * (b - a) % P + P) % P;
    }
}

int main() {
    int n;
    while(~scanf("%d",&n)){
        ll x,y;
        fib(2*n+3,x,y);
        x = (x - 1 + P) % P;
        printf("%d\n",(int)x);
    }
    return 0;
}
