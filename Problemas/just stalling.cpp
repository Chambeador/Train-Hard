#include<bits/stdc++.h>
#define int long long
using namespace std;


signed main(){
    int t; cin>>t; while(t--){
    int n; cin>>n; int c; cin>>c;
    vector<int> a(n), b(n);
    int sum = 0;
    for(auto &x: a){
         cin>>x;
        sum +=x;
    }

    for(auto &x: b){
        cin>>x;
        sum-=x;
    }

    bool sePuede = 1;
    vector<int> aa = a;
    vector<int> bb = b;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(int i = 0; i < n; i++){
        if(b[i] > a[i]){
            cout<<"-1"<<endl;
            sePuede = 0;
            break;
        }
    }
    int sum2 = 0;
    for(int i = 0; i < n; i++){
        sum2 += aa[i]-bb[i];
        if(bb[i]  > aa[i]) sum2 = -10000000000;
    }
    if(sePuede){
        if(sum2 == sum){
            cout<<sum<<endl;
        }else{
            cout<<sum+c<<endl;
        }
    }

    }


}