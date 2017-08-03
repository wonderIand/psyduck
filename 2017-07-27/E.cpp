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
#define per(i,l,r) for(int i=(r)-1; i>=(l); i--)
#define de(x) //cout << #x << " = " << x << endl;
const int INF = 1e9 + 7;
const int MAX_N = 7 + 3000;
int dig[MAX_N];
int f[MAX_N][MAX_N];
//-------
int solve(int l,int r) {
    //de(l);
    //de(r);
    int ret=0;
    int mi=INF;
    rep(posl,l,r+1) {
        mi=min(mi,dig[posl]);
        if (r+1-mi != posl-l+1) continue;
        vector<int> posr;
        int mx=0;
        per(tmpr,posl+1,r+1) {
            mx=max(mx,dig[tmpr]);
            if (mx-l+1 != r+1-tmpr) continue;
            posr.pb(tmpr);
        }
        //stack<int> sta;
        rep(pos,posl+1,r+1) {
            if (posr.empty()) break;
            if (posr.back()==pos) {
                if (posl+1 <= posr.back()-1)
                    ret=max(ret, f[posl+1][posr.back()-1] +1);
                else
                    ret=max(ret, 1);
                posr.pop_back();
            }
            //for (; !sta.empty() && sta.top()>dig[pos]; ) sta.pop();
            //sta.push(dig[pos]);
        }
    }
    return ret;
}

int main() {

    ///freopen ( "xx.in" , "r" , stdin );


    int tcase=0; scanf("%d",&tcase);
    rep(icase,0,tcase) {
        ///read
        int n; scanf("%d",&n);
        rep(i,1,n+1) scanf("%d",&dig[i]);
        ///
        int flag=0;
        rep(l,1,n+1) {
            int low=dig[l];
            int hig=dig[l];
            int sum=1;
            f[l][l]=1;
            rep(r,l+1,n+1) {
                if (low>dig[r]) {
                    low=dig[r];
                    sum=0;
                }
                hig=max(hig,dig[r]);
                if (hig-low != r-l) continue; else {
                    f[l][r]=++sum;
                }
            }
        }

        ///prework
        int can=0;
        int ans=0;
        int pre=0;
        int mx=0;
        rep(i,1,n+1) {
            mx=max(mx,dig[i]);
            if (mx!=i) continue;
            ans++;
            can=max(can,solve(pre+1,i));
            pre=i;
        }
        cout << ans+can << endl;
    }


    return 0;
}