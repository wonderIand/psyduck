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
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
//-------
const int N = 1e6 + 10 , P = 1e9 + 7;
int mu[N],pri[N],_p,vis[N],sum[N],f[N];
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}
int del[N];

int main() {
	mu[1] = 1;
	rep(i,2,N){
		if(!vis[i]) pri[_p++]=i,mu[i]=-1;
		for(int j=0,o=0;j<_p&&(o=pri[j]*i)<N;++j){
			vis[o]=1;
			if(i%pri[j]) mu[o]=-mu[i];
			else {mu[o]=0;break;}
		}
	}
	rep(i,1,N) sum[i]=(sum[i-1]+mu[i]+P)%P;
	rep(i,1,N) for(int j=i;j<N;j+=i) if(j+1<N) del[j+1]++;
	rep(i,1,N) del[i]++;
	int s=0;
	rep(i,1,N){
		pp(s,del[i]);
		f[i]=(f[i-1]+s)%P;
	}
	/*
	rep(i,2,N){
		int x=0;
		for(int d=1;d<=i;){
			int r=(i+d-1)/d;
			int g=0;
			if(r==1) g=i;
			else g=(i-1)/(r-1);
			pp(x,1ll*r*(g-d+1)%P);
			d=g+1;
		}
		f[i]=f[i-1];
		pp(f[i],x);
	}
	*/
	int n;
	while(~scanf("%d",&n)){
		int ans=0;
		for(int d=1;d<=n;){
			int r=n/d;
			int g=n/r;
			int x=(sum[g]-sum[d-1]+P)%P;
			pp(ans,1ll*f[r]*x%P);
			d=g+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
