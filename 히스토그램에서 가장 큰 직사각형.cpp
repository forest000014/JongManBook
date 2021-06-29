// 10:44
// BOJ 6549
#define TEST_MODE 0
#define TEST if(TEST_MODE)


#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;


typedef long long ll;
const int MAX_N = 100000;
const int MAX_T = 262144;
struct INFO{
    int i, h;
};


int N, L;
INFO info[MAX_N + 5];
int maxTree[MAX_T + 5], minTree[MAX_T + 5];
queue <int> q;
ll ans;


void init(void){
    for(L = 1; L < N; L <<= 1);
    for(int i = (L << 1) - 1; i; --i){
        maxTree[i] = 0;
        minTree[i] = N + 1;
    }
    while(!q.empty()) q.pop();
    ans = 0LL;
}


void inputData(void){
    scanf("%d", &N);
    init();
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &info[i].h);
        info[i].i = i;
    }
}


bool compare(const INFO a, const INFO b){
    return a.h < b.h;
}


void updateMax(int idx, int v){
    int i = L + idx - 1;
    maxTree[i] = v;
    i >>= 1;
    while(i){
        maxTree[i] = max(maxTree[i << 1], maxTree[(i << 1) + 1]);
        i >>= 1;
    }
}


void updateMin(int idx, int v){
    int i = L + idx - 1;
    minTree[i] = v;
    i >>= 1;
    while(i){
        minTree[i] = min(minTree[i << 1], minTree[(i << 1) + 1]);
        i >>= 1;
    }
}


int queryMax(int l, int r){ // return max value (which is actually rightmost index that has been updated) in [l, r]
    int i = L + l - 1;
    int j = L + r - 1;
    int ret = 0; //
    while(i <= j){
        if(i & 0x1) ret = max(ret, maxTree[i++]);
        if(!(j & 0x1)) ret = max(ret, maxTree[j--]);
        i >>= 1;
        j >>= 1;
    }
    return ret;
}

/*
1. i = 4인데, [1, 4]에 지금까지 업데이트 된 적이 없어서, max가 0인 경우
  -> return은 0이며, l = 1이 타당함.
2. i = 1이어서, [1, 1]에 지금까지 업데이트 된 적이 없어서, max가 0인 경우
  -> return은 0이며, l = 1이 타당함.

3. i = 4인데, [4, 8]에 지금까지 업데이트 된 적이 없어서, min이 N+1인 경우
  -> return은 N+1이며, r = N이 타당함.
4. i = 8이어서, [4, 8]에 지금까지 업데이트 된 적이 없어서, min이 N+1인 경우
  -> return은 N+1이며, r = N이 타당함.

*/


int queryMin(int l, int r){
    int i = L + l - 1;
    int j = L + r - 1;
    int ret = N + 1; //
    while(i <= j){
        if(i & 0x1) ret = min(ret, minTree[i++]);
        if(!(j & 0x1)) ret = min(ret, minTree[j--]);
        i >>= 1;
        j >>= 1;
    }
    return ret;
}


void solve(void){
    sort(info + 1, info + N + 1, compare);

    for(int i = 1; i <= N; ++i){
        int l = queryMax(1, info[i].i) + 1;
        int r = queryMin(info[i].i, N) - 1;
        ll area = (ll)(r - l + 1) * info[i].h;

        TEST printf("[i = %2d] l = %d, r = %d, area = %d * %d = %lld\n", i, l, r, (r - l + 1), info[i].h, area);
        if(ans < area){
            ans = area;
        }

        q.push(info[i].i);
        if(i == N || info[i].i != info[i + 1].i){
            while(!q.empty()){
                int now = q.front();
                q.pop();
                updateMax(now, now);
                updateMin(now, now);
            }
        }
    }
}


void printAns(void) {
    printf("%lld\n", ans);
}


int main(void){
    freopen("6549_input.txt", "rb", stdin);
    freopen("6549_output.txt", "wb", stdout);
    
    while(1){
        inputData();
        if(N == 0) return 0;
        solve();
        printAns();
    }

    return 0;
}
