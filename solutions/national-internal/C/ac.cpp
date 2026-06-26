#include<bits/stdc++.h>
using namespace std;
char a[100005],b[100005];
int c[100005];
int main() {
    int n,m;
    scanf("%d",&n);
    scanf("%s",a);
    scanf("%s",b);
    for(int i = 0;a[i];i++) {
        c[i] = abs(a[i] - b[i]);
    }
    int use = 0,pv = 0;
    for(int i = 0;a[i];i++) {
        if(pv == 0 && c[i]) use++;
        pv = c[i];
    }
    printf("%d",use);
}