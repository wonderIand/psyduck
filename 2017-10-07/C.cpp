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

const int N = 1010;
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int dfn[N*N],low[N*N],out[N*N],st[N*N],_st;
char s[N][N];int id[N][N],x[N*N],y[N*N];
int n,m,tot,vis[N*N][4],pos[N*N*4],dir[N*N*4],can[N*N],mask[N*N],_;
inline int in(int x,int y){return 0<=x&&x<n&&0<=y&&y<m;}
inline void add(int c,int ask){
    //cout<<c/m<<" "<<c%m<<" "<<mask[c]<<" "<<ask<<endl;
    rep(d,0,4) if(ask>>d&1) rep(nd,0,4) if(mask[c]>>nd&1){
        can[c]^=(1<<(d<<2|nd))|(1<<(nd<<2|d));
    }
    mask[c]^=ask;
}
void dfs(int x,int y,int dep){
    int c=id[x][y];st[_st++]=c;
    dfn[c]=low[c]=dep;
    rep(d,0,4){
        int nx=x+dx[d],ny=y+dy[d];
        if(!in(nx,ny)||s[nx][ny]=='o') continue;
        int t=id[nx][ny];
        if(!dfn[t]){
            dfs(nx,ny,dep+1);
            low[c]=min(low[c],low[t]);
            int ask=0;
            if(low[t]>=dfn[c]){
                while(st[--_st]!=t) out[st[_st]]=1;
                out[t]=1;
                rep(d,0,4) if(~mask[c]>>d&1){
                    int t=id[x+dx[d]][y+dy[d]];
                    if(low[t]>=dfn[c]&&out[t])
                        ask|=1<<d;
                }
                add(c,ask);
            }
        } else if(dfn[t]!=dfn[c]-1)
            low[c]=min(low[c],dfn[t]);
    }
}
int sx,sy,rx,ry;
void bfs(){
    rep(i,0,n) rep(j,0,m){
        if(s[i][j]=='s') sx=i,sy=j;
        if(s[i][j]=='r') rx=i,ry=j;
    }
    rep(i,0,tot) vis[i][0]=0;
    _=0;vis[pos[_++]=id[rx][ry]][0]=1;
    rep(i,0,_){
        int x=::x[pos[i]],y=::y[pos[i]];
        rep(d,0,4){
            int nx=x+dx[d],ny=y+dy[d];
            if(!in(nx,ny)||s[nx][ny]=='o'||s[nx][ny]=='s') continue;
            if(!vis[id[nx][ny]][0]) vis[pos[_++]=id[nx][ny]][0]=1;
        }
    }
    int mask=0;
    rep(d,0,4){
        int nx=sx+dx[d],ny=sy+dy[d];
        if(!in(nx,ny)||s[nx][ny]=='o') continue;
        if(vis[id[nx][ny]][0]) mask|=1<<d;
    }
    rep(i,0,tot) rep(j,0,4) vis[i][j]=0;
    _=0;
    rep(d,0,4) if(mask>>d&1) {
        pos[_]=id[sx][sy],dir[_++]=d;
        vis[id[sx][sy]][d]=1;
    }
    rep(i,0,_) {
        int c=pos[i],x=::x[c],y=::y[c],pd=dir[i];
        rep(d,0,4) if(can[c]>>(pd<<2|d)&1){
            if(!vis[c][d]) {
                pos[_]=c,dir[_++]=d;
                vis[c][d]=1;
            }
        }
        x+=dx[pd^2],y+=dy[pd^2];
        if(in(x,y)&&s[x][y]!='o'&&!vis[id[x][y]][pd]){
            pos[_]=id[x][y],dir[_++]=pd;
            vis[id[x][y]][pd]=1;
        }
    }
    int res=0;
    rep(i,0,n) rep(j,0,m){
        bool ok=i==sx&&j==sy;
        rep(d,0,4) ok|=vis[id[i][j]][d];
        res+=ok;
    }
    printf("%d\n",res);
}

extern int main2(void) __asm__ ("main2");
int main2(){
    while(~scanf("%d%d",&n,&m)){
        if(n==0&&m==0) break;
        rep(i,0,n) scanf("%s",s[i]);
        tot=0;
        rep(i,0,n) rep(j,0,m) id[i][j]=tot,x[tot]=i,y[tot++]=j;
        memset(dfn,0,sizeof(int)*tot);
        memset(low,0,sizeof(int)*tot);
        memset(out,0,sizeof(int)*tot);
        memset(mask,0,sizeof(int)*tot);
        memset(can,-1,sizeof(int)*tot);
        _st=0;
        rep(x,0,n) rep(y,0,m) if(s[x][y]!='o') rep(d,0,4){
            int c=id[x][y],nx=x+dx[d],ny=y+dy[d];
            if(!in(nx,ny)||s[nx][ny]=='o') {
                add(c,1<<d);
            }
        }
        rep(i,0,n) rep(j,0,m) if(s[i][j]!='o') dfs(i,j,1);
        rep(i,0,tot) add(i,15^mask[i]);
        bfs();
    }
    exit(0);
}

int main(){
    //main2();
    int size=256<<20;
    char*p=(char*)malloc(size) + size;
    __asm__ __volatile__(
    "movq  %0, %%rsp\n"
    "pushq $exit\n"
    "jmp main2\n"
    :: "r"(p));
    return 0;
}
