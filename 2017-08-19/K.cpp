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

typedef unsigned int ui;
const int N = 10 * 64 * 56 * 56 * 4;
char s[N];
int numin,channelin,hin,win;
int numw,channelw,hw,ww;
int stridew,strideh;
ll I[10][64][56] , W[64][64][11];

int main(){
    scanf("%d%d%d%d",&numin,&channelin,&hin,&win);gets(s);
    gets(s);
    ll dig=0,a=0,b=0,c=0,d=0;
    for(int i=0;s[i];){
        if(s[i]==' ') {++i;continue;}
        if(s[i]=='1') dig=0,++i;
        else dig=1,i+=3;
        I[a][b][c] |= dig<<d;
        ++d==win&&(d=0,++c==hin)&&(c=0,++b==channelin)&&(b=0,++a);
    }
    scanf("%d%d%d%d",&numw,&channelw,&hw,&ww);gets(s);
    gets(s);
    dig=0,a=0,b=0,c=0,d=0;
    for(int i=0;s[i];){
        if(s[i]==' ') {++i;continue;}
        if(s[i]=='1') dig=0,++i;
        else dig=1,i+=3;
        W[a][b][c] |= dig<<d;
        ++d==ww&&(d=0,++c==hw)&&(c=0,++b==channelw)&&(b=0,++a);
    }
    ui ans = 0;
    ll mask = (ll(1) << 62) - 1;
    int mask2 = (1<<ww)-1;
    __int128 mask3 = (__int128(1) << (ww*hw)) - 1;
    int szb = ww * hw;
    int hout = hin-hw+1;
    int wout = win-ww+1;
    rep(n,0,numin) rep(m,0,numw) rep(c,0,channelin) {
        __int128 Y = 0 , X , Z;
        ui weight = ((ui)n * numw + m) * hout;
        rep(k,0,hw) Y = Y << ww | W[m][c][k];
        rep(y,0,wout) {
            X = 0;
            rep(x,0,hin){
                X = X << ww | (I[n][c][x] >> y & mask2);
                X &= mask3;
                if(x >= hw - 1){
                    Z = X ^ Y;
                    int cnt1 = __builtin_popcountll((ll)(Z & mask)) + __builtin_popcountll((ll)(Z >> 62));
                    int cnt0 = szb - cnt1;
                    ans += (cnt0 - cnt1) * ((weight + x - hw + 1) * wout + y);
                }
            }
        }
    }
    scanf("%d%d",&stridew,&strideh);
    printf("%d %d %d %d\n",numin,numw,hout,wout);
    printf("%u\n",ans);
    return 0;
}
