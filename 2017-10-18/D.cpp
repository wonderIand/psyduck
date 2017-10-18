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

const int N = 7 , M = 40404;
int n , f[N][N];
int a[N][N][M],top[N][N];
inline void add(int x,int y,int num){
    int&top=::top[x][y];
    a[x][y][top++]=num;
}
inline int del(int x,int y){
    int&top=::top[x][y];
    return a[x][y][--top];
}
inline void out(int x,int y,char ch,int num){
    printf("%d %d %c %d\n",7-x,7-y,ch,num);
}
void move(int x,int y,int tx,int ty){
    while(x!=tx) {
        out(x,y,'D',1);
        add(x-1,y,del(x,y));
        --x;
    }
    while(y!=ty) {
        out(x,y,'R',1);
        add(x,y-1,del(x,y));
        --y;
    }
}
int gox[M],goy[M];
void solve(int x,int y,int l,int r){
    //cout << "=====> "  << x << " " << y << " " << l << " " << r << endl;
    //rep(i,0,top[x][y]) printf("%d%c",a[x][y][i]," \n"[i+1==top[x][y]]);
    if(x + y == 3) {
        if(l == r) move(x , y , 1 , 1);
        else if(a[x][y][top[x][y]-1]==r) {
            rep(i,0,2) move(x , y , 1 , 1);
        } else {
            out(x,y,"RD"[x==2],2);
            int a=del(x,y),b=del(x,y);
            add(1,1,b);add(1,1,a);
        }
        return;
    }
    int cnt[7][7],s[7][7];
    memset(cnt,0,sizeof(cnt));
    int c=l;
    rep(i,1,x+1) rep(j,1,y+1) if(i!=1||j!=1){
        int can=f[i][j];
        if(c<r) s[i][j]=c;
        for(;c<r&&can--;++c) gox[c]=i,goy[c]=j;
    }
    gox[r]=1,goy[r]=1;
    int times=r-l+1;
    rep(i,0,times) {
        int num=a[x][y][top[x][y]-1];
        cnt[gox[num]][goy[num]]++;
        move(x , y , gox[num] , goy[num]);
    }
    per(i,1,x+1) per(j,1,y+1) if((i!=1||j!=1)&&cnt[i][j]){
        solve(i , j , s[i][j] , s[i][j] + cnt[i][j] - 1);
    }
}

int main(){
    f[1][1] = 1;
    f[1][2] = f[2][1] = 2;
    rep(i,1,7) rep(j,1,7) if(f[i][j]==0){
        int&x=f[i][j];
        rep(ii,1,i+1) rep(jj,1,j+1) if(ii!=i||jj!=j)
            x+=f[ii][jj];
    }
    scanf("%d",&n);
    int x;
    rep(i,0,n) scanf("%d",&x),add(6,6,x);
    solve(6,6,1,n);
    //rep(i,0,top[1][1]) printf("%d\n",a[1][1][i]);
    return 0;
}
