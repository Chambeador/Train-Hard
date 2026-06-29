#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m;
vector<vector<int>> izq,der,arr,aba;
vector<vector<char>> mat;

void f(){
    izq.assign(n, vector<int> (m, -1));
    der.assign(n, vector<int> (m, -1));
    arr.assign(n, vector<int> (m, -1));
    aba.assign(n, vector<int> (m, -1));
    //n fila y m columnas
    for(int i = 0; i < n; i++){
        int vi = -1, vd = -1;
        for(int j = 0; j < m; j++){
            izq[i][j] = vi;
            der[i][m-j-1] = vd;
            if(mat[i][j] != '.') vi = j;
            if(mat[i][m-j-1] != '.') vd = m-j-1;
        }
    }

    for(int j = 0; j < m; j++){
        int va = -1, vb = -1;
        for(int i = 0; i < n; i++){
            arr[i][j] = va;
            aba[n-i-1][j] = vb;
            if(mat[i][j] != '.') va = i;
            if(mat[n-i-1][j] != '.') vb = n-i-1;
        }
    }
}

vector<vector<int>> enCola;
bool bloqueado(int i, int j){
    char c = mat[i][j];
    if(enCola[i][j] == 1) return 1;
    if(c == 'R') return der[i][j] != -1;
    if(c == 'L') return izq[i][j] != -1;
    if(c == 'U') return arr[i][j] != -1;
    if(c == 'D') return aba[i][j] != -1;
    return 0;
}
void solve(){
    cin>>n>>m;
    int canti = 0;
    mat.resize(n, vector<char>(m));
    enCola.resize(n, vector<int>(m, 0));
    for(auto &x: mat) for(auto &y: x) cin>>y;
    f();

    queue<pair<int,int>> cola;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] != '.'){
                canti++;
                if(!bloqueado(i,j)){
                    enCola[i][j] = 1;
                    cola.push({i,j});
                }
            }
        }
    }
    vector<pair<int, int>> ans;
    while(!cola.empty()){
        auto [i,j] = cola.front(); cola.pop();
        int left1 = izq[i][j];  int rigth1 = der[i][j];
        int up1 = arr[i][j]; int down1 = aba[i][j];
        ans.push_back({i,j});
        char c = mat[i][j];

        if(left1 != -1)der[i][left1] =rigth1;
        if(rigth1 != -1) izq[i][rigth1] = left1;
        if(down1 != -1)arr[down1][j] = up1;
        if(up1 != -1)aba[up1][j] = down1;
        mat[i][j] = '.';

        //vecinos?
        if(left1 != -1 and !bloqueado(i, left1)){
             cola.push({i, left1}); enCola[i][left1] = 1;
        }
        if(rigth1 != -1 and !bloqueado(i, rigth1)){
             cola.push({i, rigth1});  enCola[i][rigth1] = 1;
        }
        if(down1 != -1 and !bloqueado(down1, j)){
            cola.push({down1, j});  enCola[down1][j] = 1;
        }
        if(up1 != -1 and !bloqueado(up1, j)){
             cola.push({up1, j});  enCola[up1][j] = 1;
        }

    }

    if((int)ans.size() == canti){
        for(auto [i,j]: ans){
            cout<<i+1<<" "<<j+1<<"\n";
        }
    }else cout<<-1<<"\n";
}


signed main(){
    solve();
}