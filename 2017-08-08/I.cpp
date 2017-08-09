#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 5050 , P = 998244353;
int T , f[N] = {1} , a[N];
char L[N] , R[N];
void pp(int &x,int d){
	if((x+=d)>=P) x-=P;
}
int base , dig[N * 10] , _ , tmp[N * 10] , top;
int res , vis[N];

template<class T>
struct Fenwick{
#define lb(x) (x)&(-(x))
	static const int N = 10101;
	int n;T a[N];
	void ini(int _n) {fill_n(a+1,n=_n,0);}
	void add(int x,T d){ for(;x<=n;x+=lb(x)) a[x]+=d;}
	T sum(int x){ T r=0;for(;x>=1;x^=lb(x)) r+=a[x];return r;}
};
Fenwick<int> fen;


void dfs(int c,bool top){
	int up = dig[c];
	if(c == -1){
		pp(res , 1);
		return;
	}
	int t=up - fen.sum(up);
	if(top&&!vis[0]) --t;
	pp(res , 1ll * t * f[c] % P);
	if(!vis[up]){
		vis[up]=1;
		fen.add(up + 1, 1);
		dfs(c - 1 , false);
	}
}

int solve(char *s,int del){
	int len=strlen(s);
	reverse(s,s+len);
	rep(i,0,len) a[i]=s[i]-'0';
	if(del){
		a[0]--;
		for(int i=0,r=0;i<len;++i){
			a[i]+=r;
			r=a[i]/10;
			a[i]%=10;
			if(a[i]<0) a[i]+=10,--r;
		}
		while(len>1&&!a[len-1]) --len;
	}
		fen.ini(base);
	if(len==1&&a[0]==0) return 0;
	res = 0;
	int l = 2 , r = 2000;
	while(l + 1 < r){
		int base = (l + r) >> 1;
		double x = log(base) / log(10) * (base);
		if(x - 1e-6 <= len - 1) l = base;
		else r = base;
//		_ = 0;top = len;
//		rep(i,0,len) tmp[i] = a[i];
//		while(top){
//			int r=0;
//			per(i,0,top){
//				r=r*10+tmp[i];
//				tmp[i]=r/base;
//				r%=base;
//			}
//			while(top&&!tmp[top-1]) --top;
//			dig[_++]=r;
//		}
//		if(_ > base) l = base;
//		else r = base;
	}
	for(base=2;base<l;++base) pp(res,1ll*f[base-1]*(base-1)%P);
	//	de(base);
	for(base=l;;++base){
		_ = 0;top = len;
		rep(i,0,len) tmp[i] = a[i];
		while(top){
			int r=0;
			per(i,0,top){
				r=r*10+tmp[i];
				tmp[i]=r/base;
				r%=base;
			}
			while(top&&!tmp[top-1]) --top;
			dig[_++]=r;
		}
		//cout << base << " : " << endl;
		//rep(i,0,_) cout << dig[i];cout << endl;
		if(_<base) break;
		if(_==base){
			fen.ini(base);
			rep(i,0,base) vis[i]=0;
			dfs(base - 1 , true);
		} else if(_>base){
			pp(res,1ll*f[base-1]*(base-1)%P);
		}
	}
	return res;
}

void solve(){
	scanf("%s%s",L,R);
	//rep(i,0,5000) R[i] = '1';
	int ans = solve(R , false);
	pp(ans , P - solve(L , true));
	printf("%d\n",ans);
}

int main() {
	rep(i,1,N) f[i] = 1ll * f[i-1] * i % P;
	scanf("%d",&T);
	rep(i,0,T) solve();
	return 0;
}
