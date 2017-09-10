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
int T;

vector<vector<pii> > trans;
int d[8][27] = {
    1 , 3 , 4 , 9 , 8 , 7 , 5 , 6 , 2 ,
    19 , 10 , 12 , 11 , 15 , 14 , 54 , 41 , 42 , 43 , 44 , 45 , 68 , 36 , 35 , 31 , 30 , 28 ,
    10 , 12 , 13 , 18 , 17 , 16 , 14 , 15 , 11 ,
    28 , 19 , 21 , 20 , 24 , 23 , 63 , 50 , 51 , 52 , 53 , 54 , 41 , 9 , 8 , 4 , 3, 1,
    19 , 21 , 22 , 27 , 26 , 25 , 23 , 24 , 20 ,
    28 , 30 , 29 , 33 , 32 , 72 , 59 , 60 , 61 , 62 , 63 , 50 , 18 , 17 , 13 , 12 , 10 , 1,
    28 , 30 , 31 , 36 , 35 , 34 , 32 , 33 , 29 ,
    45 , 5 , 6 , 2 , 3 , 1 , 10 , 19 , 21 , 22 , 26 , 27 , 59 , 72 , 71 , 70 , 69 , 68, // error
    37 , 39 , 40 , 45 , 44 , 43 , 41 , 42 , 38 ,
    5 , 6 , 7 , 8 , 9 , 14 , 54 , 53 , 49 , 48 , 46 , 55 , 64 , 66 , 65 , 69 , 68 , 36,
    46 , 48 , 49 , 54 , 53 , 52 , 50 , 51 , 47 ,
    37 , 39 , 38 , 42 , 41 , 9 , 14 , 15 , 16 , 17 , 18 , 23 , 63 , 62 , 58 , 57  , 55 , 64,
    55 , 57 , 58 , 63 , 62 , 61 , 59 , 60 , 56 ,
    37 , 46 , 48 , 47 , 51 , 50 , 18 , 23 , 24 , 25 , 26 , 27 , 32 , 72 , 71 , 67 , 66 , 64,
    64 , 66 , 67 , 72 , 71 , 70 , 68 , 69 , 65 ,
    5 , 45 , 44 , 40 , 39 , 37 , 46 , 55 , 57 , 56 , 60 , 59 , 27 , 32 , 33 , 34 ,35 , 36
};

int f[4][18] = {
    34 , 33 , 29 , 22 , 21 , 20 , 13 , 17 , 16 , 52 , 53 , 49 , 38 , 39 , 40 , 65 , 69 , 70 ,
    2 , 6 , 7 , 43 , 42 , 38 , 49 , 48 , 47 , 58 , 62 , 61 , 25 , 26 , 22 , 29 , 30 , 31 ,
    2 , 3 , 4 , 11 , 15 , 16 , 52 , 51 , 47 , 58 , 57 , 56 , 67 , 71 , 70 , 34 , 35 , 31 ,
    25 , 24 , 20 , 13 , 12 , 11 , 4 , 8 , 7 , 43 , 44 , 40 , 65 , 66 , 67 , 56 , 60 , 61
};

void prepare(){
    for(int l=9,r=26;l<=r;++l,--r) swap(d[3][l] , d[3][r]);
    rep(i,0,8){
        rep(j,0,27) d[i][j]--;
        vector<pii> go;
        rep(j,0,3){
            int x = d[i][j];
            int y = d[i][j + 3];
            int z = d[i][j + 6];
            go.pb({x,y});go.pb({y,z});go.pb({z,x});
        }
        rep(j,0,6){
            int x = d[i][9+j];
            int y = d[i][15+j];
            int z = d[i][21+j];
            go.pb({x,y});go.pb({y,z});go.pb({z,x});
        }
        trans.pb(go);
    }
    rep(i,0,4){
        rep(j,0,18) f[i][j]--;
        vector<pii> go;
        rep(j,0,6){
            int x = f[i][j];
            int y = f[i][j+6];
            int z = f[i][j+12];
            go.pb({x,y});go.pb({y,z});go.pb({z,x});
        }
        trans.pb(go);
    }
    vector<vector<pii> > rtrans;
    for(auto e : trans){
        vector<pii> go = e;
        rep(i,0,sz(go)) swap(go[i].fi , go[i].se);
        rtrans.pb(go);
    }
    for(auto e : rtrans) trans.pb(e);
}

int a[81] , b[81] , c[81];
bool check(){
    rep(i,0,8){
        bool ok = true;
        rep(j,0,9) ok &= b[i*9+j] == b[i*9];
        if(!ok) return false;
    }
    return true;
}
void GO(int x){
    rep(i,0,72) c[i] = b[i];
    for(auto e : trans[x]) c[e.se] = b[e.fi];
    rep(i,0,72) b[i] = c[i];
}

bool solve(){
    rep(i,0,72) scanf("%d",a + i) , b[i] = a[i];
    if(check()) return true;
    rep(i,0,24) {
        rep(i,0,72) b[i] = a[i];
        GO(i);
        if(check()) return true;
    }
    rep(i,0,24) rep(j,0,24){
        rep(i,0,72) b[i] = a[i];
        GO(i);
        GO(j);
        if(check()) return true;
    }
    rep(i,0,24) rep(j,0,24) rep(k,0,24){
        rep(i,0,72) b[i] = a[i];
        GO(i);
        GO(j);
        GO(k);
        if(check()) return true;
    }
}

int main() {
    prepare();
    scanf("%d",&T);
    rep(i,0,T) puts(solve() ? "YES" : "NO");
    return 0;
}
