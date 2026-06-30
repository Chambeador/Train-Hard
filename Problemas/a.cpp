#include<bits/stdc++.h>
#define int long long
using namespace std;



//res 2 o 1 

// string construir(vector<bool> &use, string s){
//     string ans;
//     for(int i = 0; i < s.size(); i++){
//         if(use[i] == 0) ans.push_back(s[i]);
//     }
//     return ans;
// }
// void solve(){
//     int n; cin>>n;
//     string s; cin>>s;

//     while(1){
//         vector<bool> use(s.size(), 0);
//         string nS;
//         for(int i = 1; i < s.size(); i++){
//             if(s[i] == s[i-1]){
//                 use[i] = 1;
//             }
//         }

//         s = construir(use, s);
//         cout<<"s despues de 1 "<<s<<endl;
//         vector<bool> use2(s.size(), 0);
//         for(int i = 2; i < s.size(); i++){
//             if((s[i-2] == '0' and s[i-1] == '1' and s[i] == '0') or
//                (s[i-2] == '1' and s[i-1] == '0'  and s[i] == '1')){
//                 use2[i-1] = 1;
//                 break;
//             }
//         }
//         s = construir(use2, s);
//         cout<<"s despues de 2 "<<s<<endl;
//         if(s.size() == 1){
//             cout<<1<<endl;
//             return;
//         }else if(s.size() == 2){
//             if(s == "01" or s == "10"){
//                 cout<<2<<endl;
//                 return;
//             }
//         }
//     }

// }


void solve(){
    int n; cin>>n;
    string s; cin>>s;
    int c0,c1;
    c0 = c1 = 0;
    for(auto x: s){
        if(x == '0') c0++;
        else c1++;
    }

    if(c0 != 0 and c1 != 0){
        int cant = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == s[0]) cant++;
            else{
                int contador = c0;
                if(s[0] == '1') contador = c1;
                if(cant == contador){
                    cout<<2<<endl;
                    return;
                }
                break;
            }

        }
    }
    if(s == "101" or s == "010"){
        cout<<1<<endl;
    }else{
        if(c1 == 0 or c0 == 0){
            cout<<1<<endl;
        }else{
            if(c1 == 1 or c0 == 1){
                cout<<2<<endl;
            }else cout<<1<<endl;
        }
    }

}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t; while(t--)
    solve();
}