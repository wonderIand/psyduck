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
//-------
int main() {

    int n; ll k;
    for (int icase=0; ~scanf("%d",&n); ) {
        printf("Case #%d: ",++icase);
        cin>>k;
        ll bas = (k-1)/(n-1)+1;
        ll lef = (k-1)%(n-1)+1;
        if (bas==1) cout << lef << endl;
        else if (bas&1) {
            if (lef==1) cout << n-1 << endl;
                else cout << lef-1 << endl;
        }
        else {
            if (lef==1) cout << n << endl;
                else cout << lef-1 << endl;
        }
    }

    return 0;
}
