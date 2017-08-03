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
int main() {

    ///read
    int n; cin>>n;
    int ans=0;
    rep(i,0,n) {
        int d; scanf("%d",&d);
        if (d<=35) ans++;
    }
    printf("%d\n",ans);

    return 0;
}
