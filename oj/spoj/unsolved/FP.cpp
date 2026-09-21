#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
int dp[101][11][101], n, k;
int a[101];

int add (int a, int b) {
    int x=a, y=b;
    
    while (y > 0) {
        x *= 10;
        y /= 10;
    }
    
    x += b;
    return x;
}

bool cmp (int a, int b) {
    int x, q;
    x = add (a, b);
    q = add (b, a);
    return x > q;
}

int solve (int index, int mask, int taken, int sett[], int val) {
    if (taken == k) {
        if (mask == 0) return val;
        return -1;
    }
    
    if (index == n)
        return -1;
    if (dp[index][mask][taken] != -1)
        return dp[index][mask][taken];
    
    int ans1, ans2;
    sett[index] = 0;
    ans1 = solve (index+1, mask, taken, sett, val);
    sett[index] = 1;
    ans2 = solve (index+1, (mask+a[index])%9, taken+1, sett, add (val, a[index]));
    sett[index] = 0;
    dp[index][mask][taken] = max (ans1, ans2);
    return dp[index][mask][taken];
}

int main () {
    int tc;
    scanf ("%d", &tc);
    
    while (tc--) {
        scanf ("%d %d", &n, &k);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        
        memset (dp, -1, sizeof dp);
        sort (a, a+n, cmp);
        int sett[101] = {};
        printf ("%d\n", solve (0, 0, 0, sett, 0));
    }
}