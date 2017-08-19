#include<bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b-1); i>=(a); i--)
#define de(x) cout << #x << " => " << x << endl
using namespace std;

#define fi first
#define se second
#define mp make_pair
typedef pair<int,int> pii;

#define pb push_back
typedef vector<int> vi;

typedef long long ll;
typedef long double ld;

///----------------------------------------------

int main() {

    ///freopen("xx.in", "r", stdin);

    int tcase = 0; scanf("%d", &tcase);
    rep(icase, 0, tcase) {
        ///read
        int n, m; cin >> n >> m;
        int k; cin >> k;
        int sum[2] = {0, 0};
        rep(i, 0, k) {
            int a, b, c; scanf("%d%d%d", &a, &b, &c);
            sum[(a + b) & 1] ^= c;
        }
        int t; cin >> t;
        int pos1 = 0;
        rep(i, 0, t) {
            int x, y; scanf("%d%d", &x, &y);
            pos1 = (x + y) & 1;
        }
        int s; cin >> s;
        int pos2 = 0;
        rep(i, 0, s) {
            int x, y; scanf("%d%d", &x, &y);
            pos2 = (x + y) & 1;
        }
        ///work
        if (sum[pos1] == 0) printf("lose\n");
            else printf("win\n");
    }



}








