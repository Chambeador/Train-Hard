#include<bits/stdc++.h>


using namespace std;


signed main(){
    int n,k; cin>>n>>k;
    vector<vector<int>> dp(n, vector<int>(k, -1));
    vector<int> a(n);
    for(auto &x: a) cin>>x;

    for(int i = 0; i<  k; i++){
        dp[0][i] = a[i];
    }

    for(int i = 1; i < n; i++){
        for(int k = 0; k < n; k++){
            if(k == 0){
                dp[i][k] = dp[i-1][k] + a[i];
            }else{
                
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < k; i++){
        if(dp[n-1][i] != -1)ans = max(ans, dp[n-1][i]);
    }
    cout<<ans<<endl;
}