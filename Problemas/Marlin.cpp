#include<bits/stdc++.h>


using namespace std;


signed main(){
    int m,k; cin>>m>>k;
    int n = 4;
    vector<vector<char>> mat(n, vector<char>(m, '.'));
    int j1 = 1, j2 = m-2;
    while(j1 != j2 and k >= 2){
        mat[1][j1] = mat[1][j2] = '#';
        k-=2;
        j1++,j2--;
    }
    j1 = 1, j2 = m-2;
    while(j1 != j2 and k >= 2){
        mat[2][j1] = mat[2][j2] = '#';
        k-=2;
        j1++,j2--;
    }

    if(k == 1){
        mat[1][m/2] = '#';
    }else if(k == 2){
        mat[1][m/2] = '#';
        mat[2][m/2] = '#';
    }
    cout<<"YES"<<"\n";
    for(auto x: mat){
        for(auto y: x) cout<<y;
        cout<<endl;
    }

}