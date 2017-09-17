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

int dp[201][801];


int main() {
	for(int h=4;h<=100;++h){
		for(int len=0;len<8*h;++len){
			for(int s=0;s<2*h;++s){
				db &sum = dp[s][len] = 0.;
				// [s , s + len]
				rep(j,0,len+1){
					int boom = (s + j) % (8 * h);
					int left = 3 , right = 3;
					if(boom % (2 * h) == 1) left = 2;
					else if(boom % (2 * h) == 2 * h - 1) right = 2;

				}
			}
		}
	}
	return 0;
}
