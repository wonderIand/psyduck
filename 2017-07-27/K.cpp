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
const int N = 507;
const int M = 207;
int n;
bool v[N][N];
struct Node {
    int x, y;
    Node() {
    }
    Node(int _x, int _y) {
        x = _x, y = _y;
    }
    void in() {
        scanf("%d%d", &x, &y);
    }
    Node operator+(const Node &nd) const {
        return Node(x + nd.x, y + nd.y);
    }
    Node operator-(const Node &nd) const {
        return Node(x - nd.x, y - nd.y);
    }
    ll operator*(const Node &nd) const {
        return 1ll * x * nd.x + 1ll * y * nd.y;
    }
    ll operator^(const Node &nd) const {
        return 1ll * x * nd.y - 1ll * y * nd.x;
    }
} a[N];
#define sqr(x) ((x)*(x))
int dis(int i, int j) {
    return sqr(a[i].x - a[j].x) + sqr(a[i].y - a[j].y);
}
bool check(int i, int j, int k) {
    if ((a[j] - a[i]) * (a[k] - a[j])) return false;
    if (dis(i, j) != dis(j, k)) return false;
    Node q = a[i] + (a[k] - a[j]);
    if (q.x < -100 || q.x > 100) return false;
    if (q.y < -100 || q.y > 100) return false;
//    if (v[q.x + 100][q.y + 100])
//        printf("%d %d %d\n", i, j, k);
    return v[q.x + 100][q.y + 100];
}
bool check(int x, int y) {
    if (x < -100 || x > 100) return false;
    if (y < -100 || y > 100) return false;
    return v[x + 100][y + 100];
}
int main() {
    while (~scanf("%d", &n)) {
        rep(i, 0, n) a[i].in();
        rep(i, 0, M) rep(j, 0, M) v[i][j] = false;
        rep(i, 0, n) v[a[i].x + 100][a[i].y + 100] = true;
        ll ans = 0;
        rep(i, 0, n) rep(j, 0, n) {
            if (i == j) continue;
            if (a[i].x < a[j].x && a[i].y <= a[j].y) {
                int dx = a[j].x - a[i].x;
                int dy = a[j].y - a[i].y;
                int nx = a[i].x - dy, ny = a[i].y + dx;
                if (!check(nx, ny)) continue;
                nx = a[j].x - dy, ny = a[j].y + dx;
                if (!check(nx, ny)) continue;
                ++ans;
//                printf("i = %d, j = %d\n", i, j);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
