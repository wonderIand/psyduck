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
int m;
int main() {
    int cas = 0;
    double lg2 = log(2), lg10 = log(10);
    while (~scanf("%d", &m)) {
        int k = floor(m * lg2 / lg10);
        printf("Case #%d: %d\n", ++cas, k);
    }

    return 0;
}
