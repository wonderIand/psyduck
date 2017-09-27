#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<(b);i++)
using namespace std;
typedef long long ll;
///-----
struct P { int a, b, c; void read() { scanf("%d%d%d", &a, &b, &c); } };
int ned(const P &p1, const P &p2) {
    int a1 = p1.a;
    int b1 = p1.a + p1.b;
    int c1 = p1.a + p1.b + p1.c;
    int a2 = a1 + p2.a;
    int b2 = max(a2, b1) + p2.b;
    int c2 = max(b2, c1) + p2.c;
    return c2;
}
bool cmp(const P &p1, const P &p2) {
    return ned(p1, p2) < ned(p2, p1);
}
///-----
const int N = 1e5 + 7;
int n;
P p[N];
int main() {

    ///freopen("xx.in", "r", stdin);

    for (; scanf("%d", &n) && n; ) {
        ///read
        rep(i, 0, n) p[i].read();
        ///prework
        sort(p, p + n, cmp);
        ///work
        ll cura = 0, curb = 0, curc = 0;
        rep(i, 0, n) {
            cura += p[i].a;
            curb = max(curb, cura) + p[i].b;
            curc = max(curc, curb) + p[i].c;
        }
        cout << curc << endl;
    }


    return 0;
}
