// #include {{{
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <bitset>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
// }}}
// #define {{{
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define de(x) cout << #x << "=" << x << endl
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
// }}}

const int N = 3030;
int n;
struct P{
    short x,y;
    void read(){int a,b;scanf("%d%d",&a,&b);x=a,y=b;}
    void show(){printf("(%d,%d)\n",x,y);}
    int qua() const {return (x>=0)^(1<<(y<0));}
    P(){} P(int x,int y):x(x),y(y){}
    P operator - (const P&b) const {return P(x-b.x,y-b.y);}
    int operator ^ (const P& b) const {return x*b.y-y*b.x;}
    void rot() {swap(x,y);}
    bool operator < (const P&b) const{
        if(qua() != b.qua()) return qua() < b.qua();
        return (*this ^ b) > 0;
    }
}p[N],temp_p[N];
P norm(const P& a){
    P r=a;
    if(r.y<=0) r.y=-r.y,r.x=-r.x;
    if(r.y==0&&r.x<0) r.x=-r.x,r.y=-r.y;
    return r;
}
P np[N];
inline bool cmp(const int a,const int b){
    return (np[a] ^ np[b]) > 0;
}
inline bool Less(const P&a,const P&b){
    if(a.x!=b.x) return a.x < b.x;
    return a.y < b.y;
}
int to[N][N] , sz[N] , num[N][N] , id[N] , tmp[N];
int ans[N * N] , _;
int vis[N][N];
int q[10101];

void solve(){
    scanf("%d",&n);
    rep(i,0,n) p[i].read() , p[i].rot() , temp_p[i] = p[i];
    rep(i,0,n) rep(j,0,n) num[i][j] = -1;
    rep(s,0,n){
        int tot = 0;
        rep(i,0,n) if(i != s) id[tot++] = i , p[i] = p[i] - p[s] , np[i] = norm(p[i]);
        p[s] = P(0,0);
        sort(id,id+tot,cmp);
        //rep(i,0,tot) p[id[i]].show();
        int cnt = 0;
        for(int i=0,j=0;i<tot;i=j){
            int _ = 0;
            for(j=i;j<tot&&(p[id[i]]^p[id[j]])==0;++j){
                tmp[_++]=id[j] , num[s][id[j]] = cnt;
            }
            tmp[_++] = s;
            int K = 0;
            rep(k,i,j) if(Less(p[id[k]] , p[s])) ++K;
            K = _ - 1 - K;
            nth_element(tmp,tmp+K,tmp+_,[&](int a,int b){return Less(p[a],p[b]);});
            //cout << s + 1 << " " << tmp[kk] + 1<< endl;
            to[s][cnt] = tmp[K];
            ++cnt;
        }
        sz[s] = cnt;
        rep(i,0,n) p[i] = temp_p[i];
    }
    int Q;scanf("%d",&Q);
    int Mx = 0;
    rep(i,0,Q) scanf("%d",q + i);
    rep(i,0,Q) Mx = max(Mx , q[i]);
    if(Mx == 0) return;
    rep(i,0,n) rep(j,0,sz[i]) vis[i][j] = 0;
    int c = 0;
    rep(i,0,n) if(p[i].x == 0 && p[i].y == 0) c = i;
    int dir = sz[c] - 1;
    _ = 0;
    vis[c][dir] = _;
    ans[_] = c;
    ++_;
    int left = 0 , right = 0;
    int g , ndir;
    for(;;){
        g = to[c][dir];
        ndir = num[g][c];
        if(g == c){
            dir = (dir - 1 + sz[c]) % sz[c];
        } else {
            dir = (num[g][c] - 1 + sz[g]) % sz[g];
            c = g;
            if(vis[c][dir]){
                left = vis[c][dir];
                right = _;
                break;
            } else {
                vis[c][dir] = _;
                ans[_] = c;
                ++_;
            }
        }
        if(_ > Mx) break;
    }
    //cout << left << " " << right << endl;
    rep(i,0,Q){
        int x = q[i] , t;
        if(x < _) t = ans[x];
        else t = ans[left + (x - left) % (right - left)];
        printf("%d %d\n",(int)p[t].y,(int)p[t].x);
    }
}

int main() {
    int T;
    scanf("%d",&T);
    rep(i,0,T) solve();
    return 0;
}
