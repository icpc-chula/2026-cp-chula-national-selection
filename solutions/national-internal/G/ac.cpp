#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N, X, Y;
    int K;
    cin >> N >> X >> Y >> K;

    const long long INF = (long long)4e18;
    vector<vector<long long>> dp(K + 1, vector<long long>(K + 1, INF));
    dp[0][0] = 0;

    for (int day = 1; day <= K; ++day) {
        vector<vector<long long>> ndp(K + 1, vector<long long>(K + 1, INF));

        for (int used = 0; used <= day - 1; ++used) {
            for (int streak = 0; streak <= day - 1; ++streak) {
                long long cur = dp[used][streak];
                if (cur == INF) {
                    continue;
                }

                int nextStreak = streak + 1;
                long long gain = (long long)nextStreak * X;
                long long afterGather = cur + gain;
                if (afterGather < N) {
                    ndp[used][nextStreak] = min(ndp[used][nextStreak], afterGather);
                }

                long long afterDisrupt = max(0LL, cur - Y);
                if (afterDisrupt < N) {
                    ndp[used + 1][0] = min(ndp[used + 1][0], afterDisrupt);
                }
            }
        }

        dp.swap(ndp);
    }

    int answer = K;
    for (int used = 0; used <= K; ++used) {
        for (int streak = 0; streak <= K; ++streak) {
            if (dp[used][streak] < INF) {
                answer = min(answer, used);
                break;
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
