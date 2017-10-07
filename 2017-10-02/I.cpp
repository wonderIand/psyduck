#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
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
const db PI = acos(-1.0);
const db EPS = 1e-7;
inline int sign(db x) {
    if (fabs(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}
struct P {
    db x, y, z;
    P() {}
    P(db _x, db _y, db _z) {
        x = _x, y = _y, z = _z;
    }
    void out() {
        printf("%f %f %f\n", x, y, z);
    }
    db len() {
        return sqrt(x * x + y * y + z * z + EPS);
    }
    bool operator==(const P &p) const {
        return sign(x - p.x) == 0 && sign(y - p.y) == 0 && sign(z - p.z) == 0;
    }
};
P xmult(P u, P v) {
    P ret;
    ret.x = u.y * v.z - v.y * u.z;
    ret.y = u.z * v.x - u.x * v.z;
    ret.z = u.x * v.y - u.y * v.x;
    return ret;
}
db dmult(P u, P v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
P subt(P u, P v) {
    P ret;
    ret.x = u.x - v.x;
    ret.y = u.y - v.y;
    ret.z = u.z - v.z;
    return ret;
}
P pvec(P s1, P s2, P s3) {
    return xmult(subt(s1, s2), subt(s2, s3));
}
struct SP {
    db r;
    P o;
    SP() {}
    SP(P _o, db _r) {
        o = _o, r = _r;
    }
};
struct L {
    P a, b;
    L() {}
    L(P _a, P _b) {
        a = _a, b = _b;
    }
};
struct S {
    P a, b, c;
    S() {}
    S(P _a, P _b, P _c) {
        a = _a, b = _b, c = _c;
    }
};
db angle(P a, P b) {
    return acos((dmult(a, b)) / a.len() / b.len());
}
db cen_angle(db lng1, db lat1, db lng2, db lat2) {
    db dlng = fabs(lng1 - lng2);
    while (dlng >= PI + PI) dlng -= PI + PI;
    if (dlng > PI) dlng = PI + PI - dlng;
    return acos(cos(lat1) * cos(lat2) * cos(dlng) + sin(lat1) * sin(lat2));
}
db shpere_dist(P a, P b, SP sp) {
    return angle(subt(a, sp.o), subt(b, sp.o)) * sp.r;
}
db shpere_dist(db r, db lat1, db lng1, db lat2, db lng2) {
    return r * cen_angle(lng1, lat1, lng2, lat2);
}
// LS
int parallel(P l1, P l2, P s1, P s2, P s3) {
    return sign(dmult(subt(l1, l2), pvec(s1, s2, s3))) == 0;
}
// SS
int parallel(P u1, P u2, P u3, P v1, P v2, P v3) {
    return (xmult(pvec(u1, u2, u3), pvec(v1, v2, v3))).len() < EPS;
}
// LS
P intersection(P l1, P l2, P s1, P s2, P s3) {
    P ret = pvec(s1, s2, s3);
    db t = (ret.x * (s1.x - l1.x) + ret.y * (s1.y - l1.y)
            + ret.z * (s1.z - l1.z)) /
        (ret.x * (l2.x - l1.x) + ret.y * (l2.y - l1.y)
         + ret.z * (l2.z - l1.z));
    ret.x = l1.x + (l2.x - l1.x) * t;
    ret.y = l1.y + (l2.y - l1.y) * t;
    ret.z = l1.z + (l2.z - l1.z) * t;
    return ret;
}
// SS
L intersection(S u, S v) {
    L ret;
    ret.a = parallel(v.a,v.b,u.a,u.b,u.c) ?
        intersection(v.b,v.c,u.a,u.b,u.c) : intersection(v.a,v.b,u.a,u.b,u.c);
    ret.b = parallel(v.c,v.a,u.a,u.b,u.c) ?
        intersection(v.b,v.c,u.a,u.b,u.c) : intersection(v.c,v.a,u.a,u.b,u.c);
    return ret;
}
int LiC(SP cir, L line, P &rp1, P &rp2) {
    P p = cir.o;
    db r = cir.r;
    db a = line.b.y - line.a.y;
    db b = line.a.x - line.b.x;
    db c = line.a.y * line.b.x - line.a.x * line.b.y;
    if (a < 0) a = -a, b = -b, c = -c;
    int res = 0, sga = sign(a), sgb = sign(b);
    c = c + a * p.x + b * p.y;
    if (sga == 0 && sgb == 0) return 0;
    if (sga == 0 || sgb == 0) {
        db tmp = -c / (sga == 0 ? b : a);
        if (r * r < tmp * tmp) res = 0;
        else if (sign(r * r - tmp * tmp) == 0) res = 1, rp1.y = tmp, rp1.x = 0;
        else {
            res = 2;
            rp1.y = rp2.y = tmp;
            rp1.x = sqrt(r * r - tmp * tmp + EPS);
            rp2.x = -rp1.x;
        }
        if (sgb == 0) swap(rp1.x, rp1.y), swap(rp2.x, rp2.y);
    } else {
        db delt = b * b * c * c - (a * a + b * b) * (c * c - a * a * r * r);
        if (sign(delt) < 0) res = 0;
        else if (sign(delt) == 0) {
            res = 1;
            rp1.y = -b * c / (a * a + b * b);
            rp1.x = (-c - b * rp1.y) / a;
        } else {
            res = 2;
            rp1.y = (-b * c + sqrt(delt + EPS)) / (a * a + b * b);
            rp2.y = (-b * c - sqrt(delt + EPS)) / (a * a + b * b);
            rp1.x = (-c - b * rp1.y) / a;
            rp2.x = (-c - b * rp2.y) / a;
        }
    }
    rp1.x += p.x, rp1.y += p.y;
    rp2.x += p.x, rp2.y += p.y;
    return res;
}
P trans(db R, db lat, db lng) {
    return P(R * cos(lat) * cos(lng), R * cos(lat) * sin(lng), R * sin(lat));
}
db R, H, lat0, lng0, lat1, lng1;
db solve() {
    P s = trans(H, lat0, lng0);
    P t = trans(H, lat1, lng1);
    db v = sqrt(H * H - R * R);
    if (sign(lat0 - lat1) == 0) return sign(s.z + v) >= 0;
    L l = intersection(S(P(0, 0, 0), s, t), S(P(0, 0, -v), P(R, 0, -v), P(0, R, -v)));
    if (l.a == l.b)
        l = intersection(S(P(0, 0, -v), P(R, 0, -v), P(0, R, -v)), S(P(0, 0, 0), s, t));
    P p1, p2;
    int pc = LiC(SP(P(0, 0, 0), R), l, p1, p2);
    if (pc < 2) return 1;
    SP sp(P(0, 0, 0), H);
    db dst = shpere_dist(s, t, sp);
    p1.z = p2.z = -v;
    // 2
    db dis = shpere_dist(s, p1, sp) + shpere_dist(p1, p2, sp) + shpere_dist(p2, t, sp);
    if (sign(dst - dis) == 0) return (shpere_dist(s, p1, sp) + shpere_dist(p2, t, sp)) / dst;
    swap(p1, p2);
    dis = shpere_dist(s, p1, sp) + shpere_dist(p1, p2, sp) + shpere_dist(p2, t, sp);
    if (sign(dst - dis) == 0) return (shpere_dist(s, p1, sp) + shpere_dist(p2, t, sp)) / dst;
    // 1
    dis = shpere_dist(s, p1, sp) + shpere_dist(p1, t, sp);
    if (sign(dst - dis) == 0) return shpere_dist(sign(s.z - p1.z) < 0 ? t : s, p1, sp) / dst;
    swap(p1, p2);
    dis = shpere_dist(s, p1, sp) + shpere_dist(p1, t, sp);
    if (sign(dst - dis) == 0) return shpere_dist(sign(s.z - p1.z) < 0 ? t : s, p1, sp) / dst;
    if (sign(s.z - p1.z) < 0 && sign(t.z - p1.z) < 0) return 0;
    return 1;
}
int main() {
    while (~scanf("%lf%lf%lf%lf%lf%lf", &R, &H, &lat0, &lng0, &lat1, &lng1)) {
        H += R;
        lat0 *= -1, lat1 *= -1;
        printf("%.3f\n", solve() * 100);
    }
    return 0;
}
