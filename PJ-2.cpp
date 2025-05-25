#include <bits/stdc++.h>

using namespace std;
#define MAXN 100100
#define ll long long
#define ull unsigned long long
int n, m, cnt, dp[MAXN], f[MAXN], cntans;
ull has1[MAXN], has2[MAXN], p1 = 37, mi[MAXN];
int a[MAXN], b[MAXN];
char s1[MAXN], s2[MAXN];
struct pos
{
    int l, r;
};
unordered_map<ull, pos> mp;
struct doge
{
    int l1, r1, l2, r2;
}ans[MAXN];
// ull ghas1(int l, int r)
// {
//     return has1[r] - has1[l-1] * mi[r-l+1];
// }
// ull ghas2(int l, int r)
// {
//     return has2[r] - has2[l-1] * mi[r-l+1];
// }
bool cmp(doge x, doge y)
{
    return x.l1 < y.l1;
}
struct node
{
    int l, r, score;
}G, g[MAXN];
node solve(int L, int R)
{
    int len = R-L+1;
    int cnt=0;
    node G = {0, 0, 0};
    for(int i=1;i<=n;i++)
    {
        if(i+len-1 > n) break;
        cnt=0;
        for(int j=1;j<=len;j++)
        {
            if(a[j+i-1] == b[j+L-1]) cnt++;
            if(j-cnt > (len+9)/10) break;
        }
        if(cnt*10 > len*9 && cnt > G.score)
        {
            G = {i, i+len-1, cnt};
        }
        cnt=0;
        for(int j=1;j<=len;j++)
        {
            if(5-a[i+len-1 - j + 1] == b[j+L-1]) cnt++;
            if(j-cnt > (len+9)/10) break;
        }
        if(cnt*10 > len*9 && cnt > G.score)
        {
            G = {i, i+len-1, cnt};
        }
    }
    return G;
}
int Llen=100, Rlen=100;
int main()
{
    freopen("2.in","r",stdin);
    freopen("2.out","w",stdout);
    scanf("%s%s",s1+1,s2+1);
    n = strlen(s1+1);
    m = strlen(s2+1);
    for(int i=1;i<=n;i++) 
    {
        if(s1[i] == 'A') a[i] = 1;
        if(s1[i] == 'G') a[i] = 2;
        if(s1[i] == 'C') a[i] = 3;
        if(s1[i] == 'T') a[i] = 4;
    }
    for(int i=1;i<=m;i++) 
    {
        if(s2[i] == 'A') b[i] = 1;
        if(s2[i] == 'G') b[i] = 2;
        if(s2[i] == 'C') b[i] = 3;
        if(s2[i] == 'T') b[i] = 4;
    }
    ull w;
    for(int i=1;i<=m;i++)
    {
        if(i < Llen) 
        {
            f[i] = i-1;
            continue;
        }
        f[i] = i-1;
        dp[i] = dp[i-1];
        for(int j=i-Llen;j>=0 && i-j <= Rlen;j--)
        {
            G = solve(j+1, i);
            if(G.score == 0) continue;
            dp[i] = dp[j] + G.score;
            f[i] = j;
            g[i] = G;
        }
    }
    int u = m, sum=0;
    while(u != 0)
    {
        if(f[u] == u-1)
        {
            u--;
            continue;
        }
        ans[++cntans] = (doge){f[u]+1, u, g[u].l, g[u].r};
        sum += u-f[u];
        u = f[u];
    }
    // printf("%d %d %d %d\n",n,m,sum,dp[m]);
    sort(ans+1,ans+cntans+1,cmp);
    // for(int i=1;i<=cntans;i++) flag[i] = 1;
    // for(int i=cntans;i>=1;i--)
    // {
    //     if()
    // }、
    // ans[cntans+1].l1 = m+1;
    // for(int i=1;i<=cntans;i++)
    // {
        // u = (ans[i].r1-ans[i].l1+1)/10;
        // for(int j=ans[i].l1-1;j>=ans[i-1].r1+1;j--)
        // {
        //     if(u <= 0) break;
        //     if(ans[i].l2 <= 1) break;
        //     u--;
        //     ans[i].l1--;
        //     ans[i].l2--;
        // }
        // for(int j=ans[i].r1+1;j<=ans[i+1].l1-1;j++)
        // {
        //     if(u <= 0) break;
        //     if(ans[i].r2 >= n) break;
        //     u--;
        //     ans[i].r1++;
        //     ans[i].r2++;
        // }
    // }
    for(int i=1;i<=cntans;i++) 
    {
        if(i != cntans) printf("(%d,%d,%d,%d),",ans[i].l1-1,ans[i].r1,ans[i].l2-1,ans[i].r2);
        else printf("(%d,%d,%d,%d)\n",ans[i].l1-1,ans[i].r1,ans[i].l2-1,ans[i].r2);
    }


    return 0;
}