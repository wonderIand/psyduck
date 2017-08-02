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
const int N = 1 << 19 , P = 998244353 , BS = 1526;
int A[N] , B[N] , pw[N] = {1} , m , cnt1[N] , pw2[100] = {1};
void pp(int &a,int b){
    a += b;
    if(a >= P) a -= P;
}

int main() {
    rep(i,1,100) pw2[i] = (pw2[i-1]<<1) % P;
    rep(i,1,N) pw[i] = 1ll * pw[i-1] * BS % P;
    rep(i,1,N){
        int lb=i&-i;
        cnt1[i]=cnt1[i^lb]+1;
    }
    while(~scanf("%d",&m)){
        rep(i,0,1<<m) scanf("%d",A + i);
        rep(i,0,1<<m) scanf("%d",B + i);
        rep(i,0,m) rep(j,0,1<<m) if(!(j>>i&1))
            pp(B[j] , 1ll * B[j|1<<i] * pw[1<<i] % P);
        int ans=0;
        rep(i,0,1<<m) pp(ans,1ll*A[i]*B[i]%P*pw2[cnt1[i]]%P);
        printf("%d\n",ans);
    }
    return 0;
}
