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
const int N = 1e6 + 10 , P = 1e9 + 7;
char s[N] , t[N];
int T,lens,lent,ns[N],nt[N];

void kmp(char *s,int *ns,char *t,int *nt){
	int lens=strlen(s);
	int lent=strlen(t);
	nt[0] = -1;
	for(int i=0,j=-1;i<lens;++i){
		while(j>=0&&s[i]!=t[j+1])j=nt[j];
		if(s[i]==t[j+1])++j;
		ns[i] = j;
		if(j + 1 == lent) j = nt[j];
	}
}
ll cnt[N];

int main() {
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%s%s",s,t);
		lens=strlen(s);
		lent=strlen(t);
		reverse(s,s+lens);
		reverse(t,t+lent);
		kmp(t+1,nt+1,t,nt);
		kmp(s,ns,t,nt);
		rep(i,0,lent) cnt[i]=0;
		rep(i,0,lens) if(ns[i]!=-1) cnt[ns[i]]++;
		per(i,0,lent) if(nt[i]!=-1) cnt[nt[i]]+=cnt[i];
		ll ans=0;
		rep(i,0,lent) ans+=1ll*(i+1)*cnt[i];
		printf("%d\n",(int)(ans%P));
	}
	return 0;
}
