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
int T,L,R,l,r,a[100];
ll pw[40][100];

ll solve(int x,int base){
	if(x == 0) return 0;
	int len=0;
	int n = x;
	while(n) a[len++] = n % base , n /= base;
	int to = len / 2;
	int cnt = 0;
	rep(i,1,len) cnt += (base - 1) * pw[base][(i + 1) / 2 - 1];
	for(int i=len-1;i>=to;--i){
		cnt += (i == len - 1 ? a[i] - 1 : a[i]) * pw[base][i - to];
	}
	bool ok = 1;
	for(int i=to;i<=len-1;++i) {
		if(a[i] < a[len-1-i]) break;
		else if(a[i] > a[len-1-i]){
			ok = 0;
			break;
		}
	}
	cnt += ok;
	return 1ll * cnt * base + (x - cnt);
}

int bf(int x,int base){
	int len=0;
	while(x) a[len++]=x%base,x/=base;
	bool ok = 1;
	rep(i,0,len/2) if(a[i]!=a[len-1-i]){
		ok=0;
		break;
	}
	return ok?base:1;
}

ll solve(){
	scanf("%d%d%d%d",&L,&R,&l,&r);
	ll ans=0,tmp=0;
	/*	
	rep(j,L,R) if(bf(j,l) != solve(j,l)-solve(j-1,l)){
		cerr<<j<<endl;
		cerr<<bf(j,l)<<endl;
		cerr<<solve(j,l)<<endl;
		cerr<<solve(j-1,l)<<endl;
		exit(0);
	}
	*/
	/*
	rep(j,l,r+1) {
		de(j);
		rep(i,L,R+1)
			tmp+=bf(i,j);
		de(j);de(tmp);
	}
	*/
	// 27955586
	rep(i,l,r+1) {
		ans += solve(R , i) - solve(L - 1 , i);
	}
	return ans;
}

int main() {
	rep(i,0,40){
		pw[i][0] = 1;
		rep(j,1,100) pw[i][j] = pw[i][j-1] * i;
	}
	scanf("%d",&T);
	rep(i,1,T+1) printf("Case #%d: %lld\n",i,solve());
	return 0;
}
