#include<bits/stdc++.h>
using namespace std;
char a[3][100005],b[3][100005];
int tar[4][100005],use[3][100005];
int cnt;

struct Node {
    int cnt = 0;
    Node *l, *r;
    void cal() {
        cnt = 0;
        if(l->cnt != NULL) cnt += l->cnt;
        if(r->cnt != NULL) cnt += r->cnt;
    }
} root[3], range[3];

void build(int st,int ed,Node *cur,int r) {
    if(st == ed) {
        cur->cnt ^= use[r][st];
        return;
    }
    if(cur->l == NULL) cur->l = new Node();
    if(cur->r == NULL) cur->r = new Node();
    int md = (st+ed)>>1;
    build(st,md,cur->l,r);
    build(md+1,ed,cur->r,r);
    cur->cal();
}

int qy_point(int st,int ed,Node *cur,int pos) {
    if(st > pos || ed < pos) return 10;
    if(st == ed) return cur->cnt;
    int md = (st+ed)>>1;
    int val = cur->cnt;
    if(md >= pos) val ^= qy_point(st,md,cur->l,pos);
    else val ^= qy_point(md+1,ed,cur->r,pos);
    return val;
}

void build_point(int st,int ed,Node *cur,int r) {
    if(st == ed) {
        cur->cnt ^= tar[r][st];
        return;
    }
    if(cur->l == NULL) cur->l = new Node();
    if(cur->r == NULL) cur->r = new Node();
    int md = (st+ed)>>1;
    build_point(st,md,cur->l,r);
    build_point(md+1,ed,cur->r,r);
}

void up(int st,int ed,Node *cur,int pos) {
    if(st > pos || ed < pos) return;
    if(st == pos && ed == pos) {
        cur->cnt ^= 1;
        return;
    }
    int md = (st+ed)>>1;
    up(st,md,cur->l,pos);
    up(md+1,ed,cur->r,pos);
    cur->cal();
}

void up_range(int st,int ed,Node *cur,int l,int r) {
    if(st > r || ed < l) return;
    if(st >= l && ed <= r) {
        cur->cnt ^= 1;
        return;
    }
    int md = (st+ed)>>1;
    up_range(st,md,cur->l,l,r);
    up_range(md+1,ed,cur->r,l,r);
}

int qy(int st,int ed,Node *cur,int l,int r) {
    if(st > r || ed < l) return 0;
    if(st >= l && ed <= r) return cur->cnt;
    int md = (st+ed)>>1;
    return qy(st,md,cur->l,l,r) + qy(md+1,ed,cur->r,l,r);
}


void update(int r1,int r2,int c1,int c2,int N) {
    up(0,N,&root[r1-1],c1-1);
    up(0,N,&root[r2],c1-1);
    up(0,N,&root[r1-1],c2);
    up(0,N,&root[r2],c2);

    for(int i = r1;i <= r2;i++) up_range(0,N,&range[i],c1,c2); // original array
}

int ask(int r1,int r2,int c1,int c2,int N) {
    int one = 0;
    for(int i = 2*r1-2;i < 3;i += (3 - 2*(r2-r1))) one += qy(0,N,&root[i],c1,c2-1);
    int ck = 0;
    for(int i = r1;i <= r2;i++) {
        ck = max(ck, qy_point(0,N,&range[i],c1));
    }
    if(r2 > r1) one += 2 * ck;
    else one += ck;
    ck = 0;
    for(int i = r1;i <= r2;i++) {
        ck = max(ck, qy_point(0,N,&range[i],c2));
    }
    if(r2 > r1) one += 2 * ck;
    else one += ck;

    return one;
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
        }
        build(0,n,&root[i],i);
    }
    for(int i = 1;i < 3;i++) {
        build_point(0,n,&range[i],i);
    }
    scanf("%d",&m);
    int ty;
    for(int i = 0;i < m;i++) {
        scanf("%d",&ty);
        int r1,r2,c1,c2;
        scanf("%d%d%d%d",&r1,&r2,&c1,&c2);
        if(ty == 1) {
            update(r1,r2,c1,c2,n);
        }
        else {
            int num = ask(r1,r2,c1,c2,n);
            if(r1 < r2) printf("%d\n",(num+3)/4);
            else printf("%d\n",(num+1)/2);
        }
    }
}