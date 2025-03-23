#include <bits/stdc++.h> 

using namespace std;
#define MAXN 3100
#define maxn 5000100
#define ull unsigned long long
int n, m, cnt, dp[MAXN][MAXN];
char s1[MAXN], s2[MAXN], s3[MAXN];
ull has1[MAXN], has2[MAXN], has3[MAXN], p1 = 131, mi[MAXN];
vector<int> a[maxn];
struct doge
{
	ull has;
	int id;
}p[maxn];
int cntp;
bool cmp(doge x, doge y)
{
	if(x.has != y.has) return x.has < y.has;
	return x.id < y.id;
}
ull ghas1(int l, int r)
{
	return has1[r] - has1[l-1] * mi[r-l+1];
}
ull ghas2(int l, int r)
{
	return has2[r] - has2[l-1] * mi[r-l+1];
}
ull ghas3(int l, int r)
{
	return has3[r] - has3[l-1] * mi[r-l+1];
}
struct node
{
	int l, r;
	char flag;
}f[MAXN][MAXN], ans[MAXN];
int cntans;
map<ull, int> rk;
int main()
{
	scanf("%s%s",s1+1,s2+1);
	n = strlen(s1+1); m = strlen(s2+1);
	mi[0] = 1;
	for(int i=1;i<=n;i++) mi[i] = mi[i-1] * p1;
	for(int i=1;i<=n;i++)
		has1[i] = has1[i-1] * p1 + s1[i];
	for(int i=1;i<=m;i++)
		has2[i] = has2[i-1] * p1 + s2[i];
	for(int i=1;i<=m;i++)
	{
		if(s2[i] == 'A') s3[m-i+1] = 'T';
		if(s2[i] == 'T') s3[m-i+1] = 'A';
		if(s2[i] == 'C') s3[m-i+1] = 'G';
		if(s2[i] == 'G') s3[m-i+1] = 'C';
	}
	for(int i=1;i<=m;i++)
		has3[i] = has3[i-1] * p1 + s3[i];
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			p[++cntp] = (doge){ghas1(i, j), j};
		}
	}
	sort(p+1,p+cntp+1,cmp);
	rk[p[1].has] = 1;
	for(int i=2;i<=cntp;i++)
	{
		if(p[i].has != p[i-1].has) rk[p[i].has] = rk[p[i-1].has] + 1;
	}
	int u, v, len;
	for(int i=1;i<=cntp;i++)
	{
		u = rk[p[i].has];
		a[u].push_back(p[i].id);
	}
	dp[0][0] = 1;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(s2[i] == s1[j] && dp[i-1][j-1] == 1)
			{
				dp[i][j] = 1;	
			} 
		}
		for(int j=i;j>=1;j--)
		{
			ull w = ghas2(j, i);
			len = i-j+1;
			if(rk[w] != 0)
			{
				u = rk[w];
				for(int k=0;k<a[u].size();k++)
				{
					if(dp[i-len][a[u][k]] == 1) dp[i][a[u][k]] = 1, f[i][a[u][k]] = {a[u][k]-len+1, a[u][k], '+'};
				}
			}
            w = ghas3(m-i+1, m-j+1);
			len = i-j+1;
			if(rk[w] != 0)
			{
				u = rk[w];
				for(int k=0;k<a[u].size();k++)
				{
					if(dp[i-len][a[u][k]] == 1) dp[i][a[u][k]] = 1, f[i][a[u][k]] = {a[u][k]-len+1, a[u][k], '-'};
				}
			}
		}
	}
	u = m; v = n;
	while(u != 0)
	{
		if(f[u][v].l == 0)
		{
			u--;
			v--;
			continue;
		}
		ans[++cntans] = f[u][v];
		len = f[u][v].r-f[u][v].l+1;
		ans[++cntans] = {u-len+1, u};
		printf("s1:: %d %d %c\n",f[u][v].l,f[u][v].r,f[u][v].flag);
		printf("s2:: %d %d\n",u-len+1,u);
		u -= len;
	}
//	for(int i=cntans;i>=1;i--) printf("%d %d\n",ans[i].l,ans[i].r);
	
	return 0;
}
/*
CTGCAACGTTCGTGGTTCATGTTTGAGCGATAGGCCGAAACTAACCGTGCATGCAACGTTAGTGGATCATTGTGGAACTATAGACTCAAACTAAGCGAGCTTGCAACGTTAGTGGACCCTTTTTGAGCTATAGACGAAAACGGACCGAGGCTGCAAGGTTAGTGGATCATTTTTCAGTTTTAGACACAAACAAACCGAGCCATCAACGTTAGTCGATCATTTTTGTGCTATTGACCATATCTCAGCGAGCCTGCAACGTGAGTGGATCATTCTTGAGCTCTGGACCAAATCTAACCGTGCCAGCAACGCTAGTGGATAATTTTGTTGCTATAGACCAACACTAATCGAGACTGCCTCGTTAGTGCATCATTTTTGCGCCATAGACCATAGCTAAGCGAGCCTTACCATCGGACCTCCACGAATCTGAAAAGTTTTAATTTCCGAGCGATACTTACGACCGGACCTCCACGAATCAGAAAGGGTTCACTATCCGCTCGATACATACGATCGGACCTCCACGACTCTGTAAGGTTTCAAAATCCGCACGATAGTTACGACCGTACCTCTACGAATCTATAAGGTTTCAATTTCCGCTGGATCCTTACGATCGGACCTCCTCGAATCTGCAAGGTTTCAATATCCGCTCAATGGTTACGGACGGACCTCCACGCATCTTAAAGGTTAAAATAGGCGCTCGGTACTTACGATCGGACCTCTCCGAATCTCAAAGGTTTCAATATCCGCTTGATACTTACGATCGCAACACCACGGATCTGAAAGGTTTCAATATCCACTCTATA
CTGCAACGTTCGTGGTTCATGTTTGAGCGATAGGCCGAAACTAACCGTGCATGCAACGTTAGTGGATCATTGTGGAACTATAGACTCAAACTAAGCGAGCTTGCAACGTTAGTGGACCCTTTTTGAGCTATAGACGAAAACGGACCGAGGCTGCAAGGTTAGTGGATCATTTTTCAGTTTTAGACACAAACAAACCGAGCCATCAACGTTAGTCGATCATTTTTGTGCTATTGACCATATCTCAGCGAGCCTGCAACGTGAGTGGATCATTCTTGAGCTCTGGACCAAATCTAACCGTGCCAGCAACGCTAGTGGATAATTTTGTTGCTATAGACCAACACTAATCGAGACTGCCTCGTTAGTGCATCATTTTTGCGCCATAGACCATAGCTAAGCGAGCCTGCCTCGTTAGTGCATCATTTTTGCGCCATAGACCATAGCTAAGCGAGCCTGCCTCGTTAGTGCATCATTTTTGCGCCATAGACCATAGCTAAGCGAGCCTGCCTCGTTAGTGCATCATTTTTGCGCCATAGACCATAGCTAAGCGAGCCTGCCTCGTTAGTGCATCATTTTTGCGCCATAGACCATAGCTAAGCGAGCTAGACCAACACTAATCGAGACTGCCTCGTTAGTGCATCATTTTTGCGCCATAGACCATAGCTAAGCGAGCTAGACCAACACTAATCGAGACTGCCTCGTTAGTGCATCATTTTTGCGCCATAGACCATAGCTAAGCGAGCTAGACCAACACTAATCGAGACTGCCTCGTTAGTGCATCATTTTTGCGCCATAGACCATAGCTAAGCGAGCGCTCGCTTAGCTATGGTCTATGGCGCAAAAATGATGCACTAACGAGGCAGTCTCGATTAGTGTTGGTCTATAGCAACAAAATTATCCACTAGCGTTGCTGGCTCGCTTAGCTATGGTCTATGGCGCAAAAATGATGCACTAACGAGGCAGTCTCGATTAGTGTTGGTCTATAGCAACAAAATTATCCACTAGCGTTGCTGCTTACCATCGGACCTCCACGAATCTGAAAAGTTTTAATTTCCGAGCGATACTTACGACCGGACCTCCACGAATCAGAAAGGGTTCACTATCCGCTCGATACATACGATCGGACCTCCACGACTCTGTAAGGTTTCAAAATCCGCACGATAGTTACGACCGTACCTCTACGAATCTATAAGGTTTCAATTTCCGCTGGATCCTTACGATCGGACCTCCTCGAATCTGCAAGGTTTCAATATCCGCTCAATGGTTACGGACGGACCTCCACGCATCTTAAAGGTTAAAATAGGCGCTCGGTACTTACGATCGGACCTCTCCGAATCTCAAAGGTTTCAATATCCGCTTGATACTTACGATCGCAACACCACGGATCTGAAAGGTTTCAATATCCACTCTATA
*/
