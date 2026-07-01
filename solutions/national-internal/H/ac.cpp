#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

const ll INF = (ll)1e18;
const int STATES = 8;
const int MAT_SIZE = STATES * STATES;

int N, Q, segSize;
ll (*tree)[MAT_SIZE];
vector<ll> cost;

inline void buildLeafMatrix(ll x, ll *m) {
    for (int i = 0; i < MAT_SIZE; i++) m[i] = INF;

    m[0 * STATES + 3] = 0;
    m[1 * STATES + 4] = 0;
    m[2 * STATES + 5] = 0;
    m[3 * STATES + 6] = 0;
    m[4 * STATES + 7] = 0;

    m[1 * STATES + 0] = x;
    m[2 * STATES + 0] = x;
    m[3 * STATES + 1] = x;
    m[5 * STATES + 1] = x;
    m[6 * STATES + 2] = x;
    m[7 * STATES + 2] = x;
}

inline void buildIdentityMatrix(ll *m) {
    for (int i = 0; i < MAT_SIZE; i++) m[i] = INF;
    for (int i = 0; i < STATES; i++) m[i * STATES + i] = 0;
}

inline const ll *getMatrix(int idx, ll *buf) {
    if (idx < segSize) return tree[idx];
    int pos = idx - segSize + 1;
    if (pos <= N) buildLeafMatrix(cost[pos], buf);
    else buildIdentityMatrix(buf);
    return buf;
}

inline void multiplyMatrices(const ll *a, const ll *b, ll *c) {
    for (int i = 0; i < MAT_SIZE; i++) c[i] = INF;
    for (int i = 0; i < STATES; i++) {
        const ll *aRow = a + i * STATES;
        ll *cRow = c + i * STATES;
        for (int k = 0; k < STATES; k++) {
            ll val = aRow[k];
            if (val >= INF) continue;
            const ll *bRow = b + k * STATES;
            for (int j = 0; j < STATES; j++) {
                ll candidate = val + bRow[j];
                if (candidate < cRow[j]) cRow[j] = candidate;
            }
        }
    }
}

void build() {
    ll leftBuf[MAT_SIZE], rightBuf[MAT_SIZE];
    for (int i = segSize - 1; i >= 1; i--) {
        multiplyMatrices(getMatrix(2 * i, leftBuf), getMatrix(2 * i + 1, rightBuf), tree[i]);
    }
}

void update(int pos, ll newCost) {
    cost[pos] = newCost;
    ll leftBuf[MAT_SIZE], rightBuf[MAT_SIZE];
    for (int i = (segSize + pos - 1) / 2; i >= 1; i >>= 1) {
        multiplyMatrices(getMatrix(2 * i, leftBuf), getMatrix(2 * i + 1, rightBuf), tree[i]);
    }
}

ll query(int l, int r) {
    ll state[STATES];
    for (int i = 0; i < STATES; i++) state[i] = INF;
    state[0] = state[1] = state[2] = cost[l];

    if (l < r) {
        int lo = segSize + l, hi = segSize + r;
        int leftNodes[48], rightNodes[48], leftCount = 0, rightCount = 0;
        while (lo < hi) {
            if (lo & 1) leftNodes[leftCount++] = lo++;
            if (hi & 1) rightNodes[rightCount++] = --hi;
            lo >>= 1;
            hi >>= 1;
        }

        ll matBuf[MAT_SIZE], nextState[STATES];
        auto applyMatrix = [&](int idx) {
            const ll *m = getMatrix(idx, matBuf);
            for (int j = 0; j < STATES; j++) nextState[j] = INF;
            for (int i = 0; i < STATES; i++) {
                ll val = state[i];
                if (val >= INF) continue;
                const ll *mRow = m + i * STATES;
                for (int j = 0; j < STATES; j++) {
                    ll candidate = val + mRow[j];
                    if (candidate < nextState[j]) nextState[j] = candidate;
                }
            }
            for (int j = 0; j < STATES; j++) state[j] = nextState[j];
        };

        for (int t = 0; t < leftCount; t++) applyMatrix(leftNodes[t]);
        for (int t = rightCount - 1; t >= 0; t--) applyMatrix(rightNodes[t]);
    }

    return min({state[0], state[1], state[2]});
}

int main() {
    scanf("%d %d", &N, &Q);
    segSize = 1;
    while (segSize < N) segSize <<= 1;

    cost.assign(N + 1, 0);
    tree = new ll[segSize][MAT_SIZE];
    for (int p = 1; p <= N; p++) scanf("%lld", &cost[p]);

    build();

    while (Q--) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(l, r));
        } else {
            int a;
            ll b;
            scanf("%d %lld", &a, &b);
            update(a, b);
        }
    }

    return 0;
}
