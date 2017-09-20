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

const int N = 10 , M = 10000;
int n , cnt[M];
string s[N];

void surreal(string&s){
    int i=0,j=0;
    for(;i<sz(s)&&s[i]==s[0];++i) cnt[0]+=s[i]=='1'?1:-1;
    for(;i<sz(s);++i) cnt[++j]+=s[i]=='1'?1:-1;
}
int surrealsgn(){
    per(i,1,M){
        int t=cnt[i]/2;cnt[i]-=t*2;
        cnt[i-1]+=t;
    }
    //rep(i,0,10) printf("%d%c",cnt[i]," \n"[i==9]);
    rep(i,0,M/2) if(cnt[i]) {
        int iszero = true;
        rep(j,1,M/2) iszero &= cnt[i + j] + cnt[i] == 0;
        if(iszero) return 0;
        return cnt[i] > 0 ? 1 : -1;
    }
    return 0;
}

int main(){
    while(cin >> n){
        rep(i,0,n) cin >> s[i];
        int infinity = 0;
        rep(i,0,n) if(s[i].find('(') != string::npos) {
            int left = s[i].find('(') , right = s[i].find(')');
            bool same = true;
            rep(j,0,right) if(j != left) same&=s[i][j]==s[i][left+1];
            if(same) {
                infinity += s[i][left + 1] == '1' ? 1 : -1;
                s[i] = s[i].substr(right + 1);
            }
        }
        if(infinity) printf("%d wins\n",infinity > 0);
        else {
            rep(i,0,M) cnt[i] = 0;
            rep(i,0,n){
                if(s[i].find('(') != string::npos){
                    int left = s[i].find('(') , right = s[i].find(')');
                    string A = s[i].substr(0,left) , B = s[i].substr(left+1,right-left-1);
                    while(sz(B) && sz(A) + sz(B) < M) A += B;
                    surreal(A);
                } else {
                    surreal(s[i]);
                }
            }
            int sgn = surrealsgn();
            if(sgn != 0) printf("%d wins\n",sgn > 0);
            else {
                rep(i,0,M) cnt[i] = 0;
                rep(i,0,n){
                    if(s[i].find('(') != string::npos){
                        int left = s[i].find('(') , right = s[i].find(')');
                        string C = s[i].substr(right+1);
                        bool same=true;
                        rep(j,left+1,right) same&=s[i][j]==s[i][left+1];
                        if(same) C = string(1,s[i][left+1]^('0'^'1')) + C;
                        surreal(C);
                    }
                }
                int sgn = surrealsgn();
                if(sgn != 0) printf("%d wins\n",sgn > 0);
                else printf("tie\n");
            }
        }
    }
    return 0;
}
