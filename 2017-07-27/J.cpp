// #include {{{
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <ctime>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <bitset>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
// }}}
// #define {{{
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> vi;
#define de(x) cout << #x << "=" << x << endl
#define rep(i,a,b) for(int i=a;i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define fi first
#define se second
// }}}

const int N = 1e5 + 10;
char s[N],t[N];
int T,lens,lent,val[N];
struct SAM{
    static const int N = ::N<<1 , M = 26;
    int par[N] , l[N] , ne[N][M];
    int rt , last , L;
    int rid[N] , id[N];
    void add(int c,int num){
        int p = last , np = ++L;
        fill(ne[np] , ne[np] + M , 0);
        l[np] = l[p] + 1;
        last = np;
        while(p && !ne[p][c]) ne[p][c] = np , p = par[p];
        if(!p) par[np] = rt;
        else{
            int q = ne[p][c];
            if(l[q] == l[p] + 1) par[np] = q;
            else{
                int nq = ++L;
                l[nq] = l[p] + 1;
                copy(ne[q] , ne[q] + M , ne[nq]);
                par[nq] = par[q];
                par[q] = par[np] = nq;
                while(p && ne[p][c] == q) ne[p][c] = nq , p = par[p];
            }
        }
        id[num] = last;
        rid[last] = num;
    }
    void ini(){
        rt = last = L = 1;
        fill(ne[rt] , ne[rt] + M , 0);
        l[0] = -1;
    }
    int b[N],t[N],fa[18][N],lft[N],rgt[N],sz[N],acc[N];
    static const int NODE=N*30;// ???
    int h[N],sum[NODE],ls[NODE],rs[NODE],_;
    int newnode(){++_;ls[_]=rs[_]=sum[_]=0;return _;}
    void update(int &c,int l,int r,int pos,int x){
        if(!c) c=newnode();
        sum[c]+=x;
        if(l!=r){
            int m=(l+r)>>1;
            if(pos<=m) update(ls[c],l,m,pos,x);
            else update(rs[c],m+1,r,pos,x);
        }
    }
    int query(int c,int l,int r,int L,int R){
        if(!c) return 0;
        if(L <= l && r <= R) return sum[c];
        int m=(l+r)>>1;
        int ret=0;
        if(L<=m) ret+=query(ls[c],l,m,L,R);
        if(R>m) ret+=query(rs[c],m+1,r,L,R);
        return ret;
    }
    void ins(int num,int val){
        for(int i=lft[id[num]];i<=L;i+=i&(-i))
            update(h[i],0,lens-1,num,val);
    }
    int query(int x,int l,int r){
        int ret=0;
        for(;x;x&=x-1) ret+=query(h[x],0,lens-1,l,r);
        return ret;
    }
    int go[N];
    int shrink(int a,int b){
        int c=go[b];int len=b-a+1;
        if(l[c]<len) return -1;
        per(i,0,18) if(l[fa[i][c]]>=len) c=fa[i][c];
        return c;
    }
    void run(){
        int c=rt;
        rep(i,0,lent){
            int ch=::t[i]-'a';
            while(c!=rt&&!ne[c][ch]) c=par[c];
            if(ne[c][ch]) c=ne[c][ch];
            go[i]=c;
        }
    }
    int query(int a,int b,int c,int d){
        c+=b-a;
        if(c>d) return 0;
        int x=shrink(a,b);
        if(x==-1) return 0;
        return query(rgt[x],c,d) - query(lft[x]-1,c,d);
    }
    void preparetree(){
        rep(i,0,L+1) b[i]=0;
        rep(i,1,L+1) b[l[i]]++;
        rep(i,1,L+1) b[i]+=b[i-1];
        rep(i,1,L+1) t[b[l[i]]--]=i,sz[i]=1,acc[i]=0,rgt[i]=0;
        per(i,1,L+1){
            int c=t[i];
            sz[par[c]]+=sz[c];
        }
        rep(i,1,L+1){
            int c=t[i];
            lft[c]=lft[par[c]]+acc[par[c]]+1;
            if(par[c]) acc[par[c]]+=sz[c];
            fa[0][c]=par[c];
            rep(j,1,18) fa[j][c]=fa[j-1][fa[j-1][c]];
        }
        per(i,1,L+1){
            int c=t[i];
            rgt[c]=max(rgt[c],lft[c]);
            rgt[par[c]]=max(rgt[par[c]],rgt[c]);
        }
        _=0;
        rep(i,1,L+1) h[i]=0;
        rep(i,0,lens) ins(i,val[i]);
    }
}sam;

void Init(){
    sam.ini();
    rep(i,0,lens) sam.add(s[i]-'a',i);
    sam.preparetree();
    sam.run();
}


int main(){
    scanf("%d",&T);
    rep(i,0,T){
        int pastans=0;
        scanf("%s%s",s,t);
        lens=strlen(s);
        lent=strlen(t);
        rep(i,0,lens) scanf("%d",val+i);
        int Q;scanf("%d",&Q);
        int op,a,b,c,d;
        Init();
        rep(i,0,Q){
            scanf("%d%d%d",&op,&a,&b);
            a^=pastans,b^=pastans;
            if(op==2){
                scanf("%d%d",&c,&d);
                c^=pastans,d^=pastans;
                printf("%d\n",pastans=sam.query(a,b,c,d));
            } else {
                sam.ins(a,b-val[a]);val[a]=b;
            }
        }
    }
    return 0;
}
