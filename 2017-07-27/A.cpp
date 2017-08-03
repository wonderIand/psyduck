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
const int N = 1e5 + 7;
int n, x, y;
char A[N], B[N];
bool solve(int a, int b) {
    if (abs(x - y) > b) return false;
    if (x + y - 2 * a > b) return false;
    return true;
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d%d%d", &n, &x, &y);
        scanf(" %s %s", A, B);
        int a = 0;
        rep(i, 0, n) a += A[i] == B[i];
        int b = n - a;
        puts(solve(a, b) ? "Not lying" : "Lying");
    }

    return 0;
}
