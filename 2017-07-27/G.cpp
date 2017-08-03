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

const int P = 1e9 + 7;
int T,m,p;

int phi(int x){
    int r=1;
    for(int i=2;i*i<=x;++i) if(x%i==0){
        int times=0;
        while(x%i==0) x/=i,times++;
        r*=i-1;
        rep(t,1,times) r*=i;
    }
    if(x>1) r*=x-1;
    return r;
}
void pp(int &x,int d){x += d;if(x >= P)x -= P;}
int cal(int x){
    return (1ll*x*phi(x)+(x==1))/2%P;
}

int solve(){
    scanf("%d%d",&m,&p);
    int ans=0;
    pp(ans,P-1ll*(p-1)*p/2%P);
    --p;
    for(int i=1;i*i<=p;++i) if(p%i==0){
        pp(ans,1ll*i*i%P*cal(p/i)%P);
        if(i*i!=p) pp(ans,1ll*(p/i)*(p/i)%P*cal(i)%P);
    }
    return 1ll*m*ans%P;
}

int main(){
    scanf("%d",&T);
    rep(i,1,T+1) printf("Case #%d: %d\n",i,solve());
    return 0;
}
