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
const int N = 1107;
void out(int *c,int len){
    for (int i = len; i >= 0; --i) {
        if (!c[i]) continue;
        if (c[i] > 0) {
            if (i != len) putchar('+');
            if (c[i] == 1 && !i) putchar('1');
            if (c[i] > 1) printf("%d", c[i]);
        } else {
            if (c[i] == -1) {
                if (!i) printf("-1");
                else putchar('-');
            } else {
                printf("%d", c[i]);
            }
        }
        if (i == 0) {
        } else if (i == 1) putchar('x');
        else printf("x^%d", i);
    }
    puts("");
}
int a[N][N],q[N][N],l[N],id[N],rk[N];
int x[N],len,y[N],nlen;
void output(int p){
    printf("(");
    rep(i,0,l[p]){
        if(a[p][i]>0){
            if(i!=0) putchar('+');
            if(a[p][i]==1&&q[p][i]==0) putchar('1');
            if(a[p][i]>1) printf("%d",a[p][i]);
        } else {
            if(a[p][i]==-1){
                if(q[p][i]==0) printf("-1");
                else putchar('-');
            } else {
                printf("%d",a[p][i]);
            }
        }
        if(q[p][i]==1) putchar('x');
        else if(q[p][i]) printf("x^%d",q[p][i]);
    }
    printf(")");
}
int cmp(int x,int y){
    for(int i=0;i<l[x]&&i<l[y];++i){
        if(q[x][i]!=q[y][i])
            return q[x][i]<q[y][i];
        if(abs(a[x][i])!=abs(a[y][i]))
            return abs(a[x][i])<abs(a[y][i]);
        if(a[x][i]!=a[y][i])
            return a[x][i]<a[y][i];
    }
    return l[x]<l[y];
}
vi fac[N];
int main() {
    int T = 1100;
    rep(i,1,T+1) {
        rep(j,0,i+1) x[j]=0;
        x[i]=1,x[0]=-1;
        len=i;
        rep(j,1,i) if(i%j==0) {
            fac[i].pb(j);
            rep(k,0,len+1) y[k]=0;
            for(int k=len;k>=q[j][0];--k) if(x[k]){
                int mul=x[k]/a[j][0],del=k-q[j][0];
                y[k-q[j][0]]=mul;
                rep(t,0,l[j]) x[del+q[j][t]]-=mul*a[j][t];
            }
            len=len-q[j][0];
            rep(k,0,len+1) x[k]=y[k];
        }
        fac[i].pb(i);
        int &l=::l[i];
        per(j,0,len+1) if(x[j]!=0) a[i][l]=x[j],q[i][l++]=j;
        //per(i,0,len+1) printf("%d%c",x[i]," \n"[i==0]);
    }
    rep(i,1,T+1) id[i] = i;
    sort(id+1,id+T+1,cmp);
    rep(i,1,T+1) rk[id[i]] = i;
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        if(n==1) printf("x-1\n");
        else {
            sort(all(fac[n]),[&](int a,int b){return rk[a]<rk[b];});
            for(auto e : fac[n]) output(e);
            puts("");
        }
    }
    return 0;
}
