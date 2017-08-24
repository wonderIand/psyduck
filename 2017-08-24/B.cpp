#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef double db;
#define fi frist
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 100;
ll h[N] = {2,3,6};
ll f[N];

int main2() {
	rep(i,3,N) h[i] = 4*h[i-1]+17*h[i-2]-12*h[i-3]-16;
	rep(i,2,13){
		int n=i;
		ll x=3*h[n+1]*h[n]+9*h[n+1]*h[n-1]+9*h[n]*h[n]+27*h[n]*h[n-1]-18*h[n+1]-126*h[n]-81*h[n-1]+192;
		ll y = sqrt(pow(4,n)+x);
		ll t = sqrt(x);
		f[i] = t;
		cout<<i<<" "<<x<<" "<< t << " "<< y << endl;
	}
	rep(i,2,13) {
		int a = f[i-1] * 6;
		int b = a + f[i-2] * 2;
		int c = b + f[i-3] * 2;
		int d = c + f[i-4] * 2;
		int s = 0;
		rep(j,1,i-1) s += f[j];
		s *= 2;
		cout << i << " " << f[i] << " " << f[i] - a << " " << f[i] - b << " " << f[i] - c << " " << f[i] - d << " " << f[i] - (s + a) << endl;
	}
	return 0;
}
const int P = 1e9 + 7;
int ans[] = {0,0,30,196,1255};
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}

typedef vector<vi> MM;
MM operator * (const MM a,const MM b){
	int L=sz(a);MM r(L,vi(L,0));
	rep(i,0,L) rep(j,0,L) rep(k,0,L) pp(r[i][j] , 1ll * a[i][k] * b[k][j] % P);
	return r;
}
MM operator ^ (MM a,ll t){
	int L=sz(a);MM r(L,vi(L,0));
	rep(i,0,L) r[i][i] = 1;
	for(;t;t>>=1,a=a*a) if(t&1) r=r*a;
	return r;
}

int main(){
	main2();
	int T;scanf("%d",&T);
	rep(i,0,T){
		ll x;
		scanf("%lld",&x);
		if(x == 2) printf("%d\n",ans[x] + 1);
		else if(x == 3) printf("%d\n",ans[x] + 1);
		else if(x == 4) printf("%d\n",ans[x]);
		else {
			MM a(3,vi(3,0));
			a[0] = {1,2,0};
			a[1] = {1,6,15};
			a[2] = {0,0,1};
			a = a ^ (x - 4);
			int res = 0;
			vi v = {2 * (ans[2] + ans[3]) , ans[4] , 1};
			//rep(i,0,3) cout << v[i] << " ";cout << endl;
			rep(i,1,2) rep(j,0,3) pp(res , 1ll * a[i][j] * v[j] % P);
			printf("%d\n",res);
		}
	}
	return 0;
}
