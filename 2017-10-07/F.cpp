#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define per(i,a,b) for (int i = (b) - 1; i >= (a); i--)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define fi first
#define se second
#define mp make_pair
#define pb push_back
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 110;
const db inf = 1e50;
struct ele{
	db A,L,P,a,b;
	void read(){
		scanf("%lf%lf%lf",&A,&L,&P);
		P /= 100. , L /= 100.;L = 1 - L;
		a = P + (1 - P) * L , b = A * P;
	}
	bool operator < (const ele&y){
		return y.a * b + y.b > a * y.b + b;
	}
}e[N];
db f[N];
int n , K , x0;
int main() {
	while(~scanf("%d%d%d",&n,&K,&x0)){
		if(n == 0 && K == 0 && x0 == 0) break;
		rep(i,0,n) e[i].read();
		sort(e , e + n);
		rep(i,0,K+1) f[i] = -inf;
		f[0] = x0;
		rep(i,0,n){
			per(j,0,K) f[j+1] = max(f[j+1] , f[j] * e[i].a + e[i].b);
		}
		printf("%.2f\n",f[K] + 1e-8);
	}
	return 0;
}
