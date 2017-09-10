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
const int N = 2e4 + 7;
const int M = 150;
const int INF = INT_MAX;
int n, v[N], s[N], f[2][N][M];
inline int get(int i, int j) {
    return s[n - i + j] - s[n - i];
}
int dfs(int t, int i, int j) {
    if (i <= 0 || i < j) return 0;
    if (f[t][i][j] != -INF) return f[t][i][j];
    if (t == 0) { // max
        f[0][i][j] = dfs(1, i - j, j) + get(i, j);
        if (i >= j + 1)
            f[0][i][j] = max(f[0][i][j], dfs(1, i - j - 1, j + 1) + get(i, j + 1));
    } else { // min
        f[1][i][j] = dfs(0, i - j, j) - get(i, j);
        if (i >= j + 1)
            f[1][i][j] = min(f[1][i][j], dfs(0, i - j - 1, j + 1) - get(i, j + 1));
    }
    return f[t][i][j];
}
int main() {
    int T;
    scanf("%d", &T);
    rep(cas, 0, T) {
        scanf("%d", &n);
        rep(t, 0, 2) rep(i, 0, n + 1) rep(j, 0, M) f[t][i][j] = 0;
        rep(i, 1, n + 1) scanf("%d", v + i);
        rep(i, 1, n + 1) s[i] = s[i - 1] + v[i];
        rep(i, 0, n + 1) rep(j, 0, min(M, i + 1)) {
            f[0][i][j] = f[1][i - j][j] + get(i, j);
            if (j + 1 <= i)
                f[0][i][j] = max(f[0][i][j], f[1][i - j - 1][j + 1] + get(i, j + 1));

            f[1][i][j] = f[0][i - j][j] - get(i, j);
            if (i >= j + 1)
                f[1][i][j] = min(f[1][i][j], f[0][i - j - 1][j + 1] - get(i, j + 1));
        }
        printf("%d\n", f[0][n][1]);
    }

    return 0;
}
