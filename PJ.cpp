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
ull ghas1(int l, int r)
{
    return has1[r] - has1[l-1] * mi[r-l+1];
}
ull ghas2(int l, int r)
{
    return has2[r] - has2[l-1] * mi[r-l+1];
}
bool cmp(doge x, doge y)
{
    return x.l1 < y.l1;
}
  
int Llen=30, Rlen=60;
int main()
{
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
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
    mi[0] = 1;
    for(int i=1;i<=max(n, m);i++) mi[i] = mi[i-1] * p1;
    for(int i=1;i<=n;i++)
    {
        has1[i] = has1[i-1] * p1 + a[i];
        if(i >= Llen)
        {
            for(int j=i-Llen+1;j >= 1 && i-j+1 <= Rlen; j--)
            {
                mp[ghas1(j, i)] = (pos){j, i};
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        has1[i] = has1[i-1] * p1 + 5-a[n-i+1];
        if(i >= Llen)
        {
            for(int j=i-Llen+1;j >= 1 && i-j+1 <= Rlen; j--)
            {
                mp[ghas1(j, i)] = (pos){n-i+1, n-j+1};
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        has2[i] = has2[i-1] * p1 + b[i];
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
            w = ghas2(j+1, i);
            if(mp[w].l != 0 || mp[w].r != 0)
            {
                // if(i >= 200 && i <= 350)
                // {
                //     printf("%d %d \n",j,i);
                // }   
                if(dp[j] + i-j > dp[i])
                {
                    f[i] = j;
                    dp[i] = dp[j] + i-j;
                }
            }
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
        w = ghas2(f[u]+1, u);
        ans[++cntans] = (doge){f[u]+1, u, mp[w].l, mp[w].r};
        sum += u-f[u];
        u = f[u];
    }
    // printf("%d %d %d %d\n",n,m,sum,dp[m]);
    // sort(ans+1,ans+cntans+1,cmp);
    // for(int i=1;i<=cntans;i++) flag[i] = 1;
    // for(int i=cntans;i>=1;i--)
    // {
    //     if()
    // }、
    // ans[cntans+1].l1 = m+1;
    // for(int i=1;i<=cntans;i++)
    // {
    //     // u = (ans[i].r1-ans[i].l1+1)/10;
    //     // for(int j=ans[i].l1-1;j>=ans[i-1].r1+1;j--)
    //     // {
    //     //     if(u <= 0) break;
    //     //     if(ans[i].l2 <= 1) break;
    //     //     u--;
    //     //     ans[i].l1--;
    //     //     ans[i].l2--;
    //     // }
    //     // for(int j=ans[i].r1+1;j<=ans[i+1].l1-1;j++)
    //     // {
    //     //     if(u <= 0) break;
    //     //     if(ans[i].r2 >= n) break;
    //     //     u--;
    //     //     ans[i].r1++;
    //     //     ans[i].r2++;
    //     // }
    // }
    for(int i=1;i<=cntans;i++) 
    {
        if(i != cntans) printf("(%d,%d,%d,%d),",ans[i].l1-1,ans[i].r1,ans[i].l2-1,ans[i].r2);
        else printf("(%d,%d,%d,%d)\n",ans[i].l1-1,ans[i].r1,ans[i].l2-1,ans[i].r2);
    }


    return 0;
}