#include <bits/stdc++.h>
#define rep(i,a,b) for (int i=(a); i<(b); i++)
#define per(i,a,b) for (int i=(b)-1; i>=(a); i--)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using namespace std;

typedef double db;
typedef long long ll;

#define fi first
#define se second
#define mp make_pair
typedef pair<int, int> pii;

#define pb push_back
typedef vector<int> vi;
///-----------

const int N = 1010;
int T,n,c[N],d[N],b;

int main(){
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%d%d",&n,&b);
		rep(i,0,n) scanf("%d",c + i);
		rep(i,0,n-1) scanf("%d",d + i);
		int cur = 0;
		bool ok = true;
		rep(i,0,n-1){
			cur += c[i];
			if(cur < d[i] * b){
				ok = false;
				break;
			}
			cur -= d[i] * b;
		}
		puts(ok ? "Yes" : "No");
	}
	return 0;
}

