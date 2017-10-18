#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a);i<(b);i++)
using namespace std;
const int N = 1e3 + 7;
const int M = 1e2 + 7;
const int MOD = 10000000;
void inc(int &a, int b) { if ((a += b) >= MOD) a -= MOD; }
///------
int dp[N][M], sum[M], n, m;
///------
int solve() {
    //read
    scanf("%d%d", &n, &m);
    if (n == 1) return 1;
    if (n == 2) return (m + 1) * (m + 2) / 2;
    //prework
    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));
    dp[0][0] = sum[0] = 1;
    rep(j, 1, m + 1) dp[1][j] = sum[j] = 1;
    int tmp = m;
    rep(i, 2, n) {
        rep(j, 0, m + 2) {
            dp[i][j] = tmp;
            inc(dp[i][j], MOD - dp[i - 1][j]);
            inc(dp[i][j], MOD - 1ll * dp[i - 2][j] * m % MOD);
        }
        tmp = 1ll * tmp * tmp % MOD;
    }
    rep(i, 2, n) rep(j, 0, m + 2) inc(sum[j], dp[i][j]);
    sort(sum, sum + m + 2);
    //work
    int ans = 0;
    rep(i, 0, m + 2) inc(ans, 1ll * sum[i] * (m + 2 - i) % MOD);
    return ans;
}

///----
int main() {

    //freopen("xx.in", "r", stdin);
    int tcase = 0; scanf("%d", &tcase);
    rep(icase, 0, tcase) printf("%d\n", solve());
    return 0;
}

