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

const int N = 1e5 + 10 , P = 1e9 + 7;
int T,n,Q;
char s[N];
inline void pp(int &x,int d){if((x+=d)>=P)x-=P;}

struct ele{
	int a[2][4],has[2];
	ele(){rep(i,0,2) rep(j,0,4) a[i][j]=0;has[0]=has[1]=0;}
	ele(int x){rep(i,0,2) rep(j,0,4) a[i][j]=0;a[x][0]=1;has[x]=1,has[x^1]=0;}
	void rev(){
		rep(i,0,2) swap(a[i][1],a[i][2]);
		rep(i,0,4) swap(a[0][i],a[1][i]);
		swap(has[0],has[1]);
	}
	ele operator + (const ele&b) const{
		ele r;
		rep(i,0,2) r.has[i]=has[i]|b.has[i];
		rep(i,0,2){
			if(!has[i]) rep(j,0,4) r.a[i][j]=b.a[i][j];
			else {
				if(a[i][0]){
					rep(j,0,2) if(b.has[j]){
						rep(k,0,4) pp(r.a[i][k] , 1ll*a[i][0]*b.a[j][k]%P);
					}
					if(b.has[0]&&b.has[1]) pp(r.a[i][3],a[i][0]);
					else if(b.has[0]) pp(r.a[i][1],a[i][0]);
					else if(b.has[1]) pp(r.a[i][2],a[i][0]);
				}
				if(a[i][1]){
					if(b.has[1]){
						rep(k,0,4) pp(r.a[i][k] , 1ll*a[i][1]*b.a[1][k]%P);
						pp(r.a[i][3],a[i][1]);
					} else pp(r.a[i][1],a[i][1]);
				}
				if(a[i][2]){
					if(b.has[0]){
						rep(k,0,4) pp(r.a[i][k] , 1ll*a[i][2]*b.a[0][k]%P);
						pp(r.a[i][3],a[i][2]);
					} else pp(r.a[i][2],a[i][2]);
				}
				if(a[i][3]){
					pp(r.a[i][3],a[i][3]);
				}
			}
		}
		return r;
	}
	int sum(){
		int r=0;
		rep(i,0,2) rep(j,0,4) pp(r,a[i][j]);
		return r;
	}
	void show(){
		rep(i,0,2) rep(j,0,4) printf("%d%c",a[i][j]," \n"[j==3]);
	}
}a[N << 2];

struct SegTree {
	#define ls ((t)<<1)
	#define rs ((t)<<1|1)
	int tag[N << 2];
	inline void up(int t) {
		a[t] = a[t<<1] + a[t<<1|1];
	}
	inline void down(int t) {
		if(tag[t]){
			tag[t]=0;
			tag[t<<1]^=1;
			tag[t<<1|1]^=1;
			a[t<<1].rev();
			a[t<<1|1].rev();
		}
	}
	void build(int t, int l, int r) {
		tag[t] = 0;
		if (l == r) {
			a[t] = ele(s[l] - '0');
		} else {
			int z = (l + r) >> 1;
			build(ls, l, z), build(rs, z + 1, r);
			up(t);
		}
	}
	void upd(int t, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			tag[t]^=1;
			a[t].rev();
			return;
		}
		down(t);
		int z = (l + r) >> 1;
		if (L <= z) upd(ls, l, z, L, R);
		if (z < R) upd(rs, z + 1, r, L, R);
		up(t);
	}
	ele qry(int t, int l, int r, int L, int R) {
		if (L <= l && r <= R) return a[t];
		down(t);
		int z = (l + r) >> 1;
		if (R <= z) return qry(ls, l, z, L, R);
		else if (L > z) return qry(rs, z + 1, r, L, R);
		else return qry(ls, l, z, L, R) + qry(rs, z + 1, r, L, R);
	}
}seg;

int main() {
	scanf("%d",&T);
	rep(i,0,T){
		scanf("%d%d",&n,&Q);
		scanf("%s",s + 1);
		int op,l,r;
		seg.build(1,1,n);
		rep(i,0,Q){
			scanf("%d%d%d",&op,&l,&r);
			if(op==1) seg.upd(1,1,n,l,r);
			else printf("%d\n",seg.qry(1,1,n,l,r).sum());
		}
	}
	return 0;
}
