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

const int N = 7 , M = 5005;
int n , m , K;
int ban[1 << N][1 << N] , dp[M][1 << N] , opt[M] , combo[M] , cnt1[1 << N];
int scorestarisk[M] , scorehash[M] , lefthash[M] , mask[M] , maskasterisk[M];
string g[M];
bool canstart[M];
inline void Update(int &x,int d) {x = max(x , d);}

int main(){
    while(cin >> n >> m >> K){
        rep(i,0,1<<n) rep(j,0,1<<n) ban[i][j] = 0;
        rep(i,0,1<<n) cnt1[i] = __builtin_popcount(i);
        rep(i,1,m+1) combo[i] = i * (i + 1) / 2 - 1;
        rep(i,0,K){
            string a,b;
            cin >> a >> b;
            auto toint = [&](string a){
                int res=0;
                for(auto ch:a)res=res*2+ch-'0';
                return res;
            };
            ban[toint(a)][toint(b)] = 1;
        }
        rep(i,1,m+1) {
            cin >> g[i];
            scorehash[i] = scorestarisk[i] = mask[i] = maskasterisk[i] = 0;
            opt[i] = -1;
            rep(j,0,n) scorestarisk[i] += 5 * (g[i][j] == '*');
            rep(j,0,n) mask[i] |= (g[i][j] != '.') << (n - 1 - j);
            rep(j,0,n) maskasterisk[i] |= (g[i][j] == '*') << (n - 1 - j);
        }
        opt[0] = 0;
        rep(i,0,n) lefthash[i] = -1;
        rep(i,0,1<<n) rep(j,0,1<<n) if(ban[i][j]){
            rep(k,0,n)  ban[i|1<<k][j] = 1;
            rep(k,0,n)  ban[i][j|1<<k] = 1;
        }
        rep(i,1,m+1) {
            canstart[i] = true;
            if(i != 1) rep(j,0,n) canstart[i] &= !(g[i][j] == '#' && g[i-1][j] == '#');
        }
        rep(i,0,m+1) rep(j,0,1<<n) dp[i][j] = -1;
        int ans=0;
        rep(i,1,m+1) {
            rep(j,0,n) if(g[i][j] == '#'){
                if(lefthash[j] == -1) lefthash[j] = i;
                if(lefthash[j] != -1 && (i == m || g[i+1][j] != '#'))
                    scorehash[lefthash[j]] += (i - lefthash[j] + 1) * 10 , lefthash[j] = -1;
            }
            int score = 0;
            per(j,1,i+1){
                if(j != i && ban[mask[j]][mask[j+1]]) break;
                score += scorehash[j] + scorestarisk[j];
                if(canstart[j] && opt[j - 1] != -1){
                    Update(dp[i][mask[i]] , opt[j-1] + score + combo[i - j + 1]);
                }
            }
            if(i == 1){
                rep(j,0,1<<n) Update(dp[i][j] , 5 * cnt1[j & maskasterisk[i]]);
            } else {
                rep(j,0,1<<n) rep(k,0,1<<n) if(!ban[j][k] && dp[i-1][j] != -1) {
                    Update(dp[i][k] , dp[i-1][j] + 5 * cnt1[k & maskasterisk[i]]);
                }
            }
            if(i != m) {
                rep(j,0,1<<n) if(!ban[j][mask[i+1]]) Update(opt[i] , dp[i][j]);
            }
            //rep(j,0,1<<n) printf("%d%c",dp[i][j]," \n"[j+1==(1<<n)]);
            rep(j,0,1<<n) Update(ans , dp[i][j]);
        }
        printf("%d\n",ans);
    }
    return 0;
}

