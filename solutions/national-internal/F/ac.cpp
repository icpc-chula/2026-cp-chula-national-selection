#include<bits/stdc++.h>
using namespace std;
char a[3][100005],b[3][100005];
int tar[4][100005],use[3][100005];
int cnt;

void up(int r,int c) {
    cnt += 1 - 2*use[r][c];
    use[r][c] ^= 1;
}

int main() {
    int n,m;
    scanf("%d",&n);
    for(int i = 1;i <= 2;i++) {
        scanf("%s",&a[i][1]);
    }
    for(int i = 1;i <= 2;i++) {
        scanf("%s",&b[i][1]);
        for(int j = 1;j <= n;j++) {
            if(a[i][j] == b[i][j]) tar[i][j] = 0;
            else tar[i][j] = 1;
        }
    }
    for(int i = 0;i < 3;i++) {
        for(int j = 0;j <= n;j++) {
            use[i][j] = (tar[i][j] ^ tar[i][j+1] ^ tar[i+1][j] ^ tar[i+1][j+1]);
            cnt += use[i][j];
        }
    }
    scanf("%d",&m);
    int ty;
    for(int i = 0;i < m;i++) {
        scanf("%d",&ty);
        if(ty == 1) {
            int r1,r2,c1,c2;
            scanf("%d%d%d%d",&r1,&r2,&c1,&c2);
            up(r1-1,c1-1);
            up(r2,c1-1);
            up(r1-1,c2);
            up(r2,c2);
        }
        else {
            printf("%d\n",(cnt+3)/4);
        }
    }
}