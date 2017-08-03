#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
//-------
const int N = 50000 + 10;
int T,n,m,K,lens,lent,lenp;
int pre[N][101] , suf[N][101] , nt[N] , ns[N];
char s[N],t[N],p[N];

void kmp(char *s,int *ns,char *t,int *nt){
	nt[0]=-1;
	int lens=strlen(s);
	int lent=strlen(t);
	for(int i=0,j=-1;i<lens;++i){
		while(j >= 0 && s[i] != t[j + 1]) j = nt[j];
		if(s[i] == t[j + 1]) ++j;
		ns[i] = j;
		if(j + 1 == lent) j = nt[j];
	}
}
ll A[N] , B[N];

void solve(){
	scanf("%d%d%d",&n,&m,&K);
	scanf("%s",s);
	scanf("%s",t);
	lens=strlen(s);
	lent=strlen(t);
	rep(i,1,lent+1) {
		rep(j,0,i) p[j] = t[j];
		p[i] = 0;
		kmp(p+1,nt+1,p,nt);
		kmp(s,ns,p,nt);
		rep(j,0,lens) pre[j][i] = (j ? pre[j-1][i] : 0) + (ns[j] + 1 == i);
	}
	reverse(s , s + lens);
	reverse(t , t + lent);
	rep(i,1,lent+1) {
		rep(j,0,i) p[j] = t[j];
		p[i] = 0;
		kmp(p+1,nt+1,p,nt);
		kmp(s,ns,p,nt);
		rep(j,0,lens) suf[j][i] = (j ? suf[j-1][i] : 0) + (ns[j] + 1 == i);
	}
	rep(i,0,lens) A[i] = (i ? A[i-1] : 0) + pre[i][lent];
	rep(i,0,lens) B[i] = (i ? B[i-1] : 0) + suf[i][lent];
	int l,r;
	ll ans=0;
	rep(i,0,K){
		scanf("%d%d",&l,&r);
		--l,--r;
		ll ans = 1ll * A[l] * (lens - r) + 1ll * B[lens-1-r] * (l + 1);
		rep(i,1,lent) ans += 1ll * pre[l][i] * suf[lens-1-r][lent-i];
		printf("%lld\n",ans);
	}
}

int main() {
	scanf("%d",&T);
	rep(i,0,T) solve();
	return 0;
}
