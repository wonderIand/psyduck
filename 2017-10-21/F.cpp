#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef unsigned long long ull;
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

const int N = 30;
typedef pair<int, ull> keytype;
map<keytype, ull> f;
ll   des;
ull cnt, pown[N];
int  use[N], n;
char ans[N * N];
bool sear(int cur, int pre, int sum, int distinct, ull cnts) {
    ///check
    if (cnt >  des) return false;
    if (cur == n * (n + 1) / 2)
        return (cnt += sum == (2 << n) && distinct == n) == des;

    ///save
    keytype key = mp(cur * 100 + use[pre], cnts);
    if (f.find(key) != f.end() && cnt + f[key] < des) return cnt += f[key], false;

    ///solve
    ull precnt = cnt;
    rep(dig, 0, 26) if (dig != pre && distinct + !use[dig] <= n) {
        int u = use[dig]; if (sum + (1 << u) > (2 << n)) continue;
        ans[cur] = dig + 'a';
        use[dig]++;
        if (sear(cur + 1, dig, sum + (1 << u), distinct + !u, cnts + pown[u])) return true;
        use[dig]--;
    }
    f[key] = cnt - precnt;
    return false;
}

int main() {
    //read
    cin >> n >> des;

    //prework
    pown[0] = 1; rep(i, 1, n + 1) pown[i] = pown[i - 1] * n;

    //work
    if (sear(0, N - 1, 2 + n, 0, 0)){
        ans[n * (n + 1) / 2] = '\0';
        puts(ans);
    } else puts("-1");
}
