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
int x , y , m , n;

int main() {
	int T;scanf("%d",&T);
	rep(i,0,T){
		scanf("%d%d%d%d",&x,&y,&m,&n);m++;
		int time = 0;
		while(m > 1 || n){
			if (n) {
				n -= min(n, m);
				time += y;
			} else {
				m = (m + 1) / 2;
				time += x;
			}
		}
		printf("%d\n",time);
	}
	return 0;
}
