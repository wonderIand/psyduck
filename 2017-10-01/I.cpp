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

const int N = 1e5 + 10 , inf = 1<<30;
char s[N];
int n , start[N] , len[N] , m;
int w[N] , b[N] , j[N] , k[N] , firstchar[N] , vis[N];
int l[N] , r[N] , x[N] , y[N];
int dis[N + N] , pre[N + N];
char prechar[N + N];
vector<pii> jumpj[N] , jumpk[N];

int main(){
    scanf("%d",&n);
    rep(i,0,n){
        scanf("%s",s);
        len[i]=strlen(s);
        for(int j=0;s[j];++j){
            if(isalpha(s[j]) && (j==0||s[j-1]=='.'))
                firstchar[m+j]=1;
            x[m+j]=i,y[m+j]=j;
        }
        start[i]=m;
        m+=len[i];
    }
    memset(vis,-1,sizeof(vis));
    for(int i=0,s=-1;i<m;++i){
        b[i]=s==-1?i:s;if(firstchar[i]) s=i;
        k[i]=vis[y[i]];vis[y[i]]=i;
    }
    memset(vis,-1,sizeof(vis));
    for(int i=m-1,s=-1;i>=0;--i){
        w[i]=s==-1?i:s;if(firstchar[i]) s=i;
        j[i]=vis[y[i]];vis[y[i]]=i;
    }
    for(int i=0;i<n;++i){
        for(int &t=l[i]=i;t&&len[i]>len[t-1];t=l[t-1])
            jumpk[start[i]+len[t-1]].pb(mp(start[t-1]+len[t-1]-1,i-t+1));
    }
    for(int i=n-1;i>=0;--i){
        for(int &t=r[i]=i;t!=n-1&&len[i]>len[t+1];t=r[t+1])
            jumpj[start[i]+len[t+1]].pb(mp(start[t+1]+len[t+1]-1,t-i+1));
    }
    int Q;
    scanf("%d",&Q);
    rep(i,0,Q){
        int sx,sy,tx,ty;
        scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
        int s=start[sx-1]+sy-1,t=start[tx-1]+ty-1;
        rep(i,0,m+m) dis[i] = inf;
        priority_queue<pii> Q;
        auto add = [&](int p,int d,int f,char ch){
            if(d<dis[p]) dis[p]=d,pre[p]=f,prechar[p]=ch,Q.push(mp(-d,p));
        };
        add(s,0,-1,'!');int edp=0;
        while(sz(Q)) {
            int c=Q.top().se,d=-Q.top().fi;Q.pop();
            if(c==t||(c==t+m&&prechar[c]!='?')) {edp=c;break;}
            if(d==dis[c]) {
                if(c<m) add(c+m,d,c,'!');
                if(c<m) {
                    if(j[c]!=-1) add(j[c],d+x[j[c]]-x[c],c,'j');
                    if(k[c]!=-1) add(k[c],d+x[c]-x[k[c]],c,'k');
                } else {
                    int t=c-m;
                    if(y[t]) add(c-1,d,c,'?');
                    for(auto e:jumpj[t]) add(e.fi+m,d+e.se,c,'j');
                    for(auto e:jumpk[t]) add(e.fi+m,d+e.se,c,'k');
                }
                if(c>=m&&prechar[c]=='?') continue;
                int t=c<m?c:c-m;
                //de(c);
                //de(t);de(x[t]);de(y[t]);
                add(start[x[t]],d+1,c,'0');
                add(start[x[t]]+len[x[t]]-1,d+1,c,'$');
                add(w[t],d+1,c,'w');
                add(b[t],d+1,c,'b');
                add(y[t]?t-1:t,d+1,c,'h');
                add(y[t]==len[x[t]]-1?t:t+1,d+1,c,'l');
            }
        }
        string ans="";
        for(int c=edp;c!=s;c=pre[c]) {
            //printf("(%d,%d,%d,%c) <-",x[c],y[c],dis[c],prechar[c]);
            rep(i,0,(dis[c]-dis[pre[c]])) ans+=prechar[c];
        }
        //puts("");
        reverse(all(ans));
        cout<<ans<<endl;
    }
    return 0;
}
