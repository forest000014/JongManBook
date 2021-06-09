#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;


const int MAX_N = 10;

int T, tc, N, M;
bool areFriends[MAX_N + 5][MAX_N + 5];
bool selected[MAX_N + 5];
int pairs[MAX_N / 2 + 5][2];
int ans;


void init(void){
    for(int i = 0; i < MAX_N; ++i){
        selected[i] = false;
        for(int j = 0; j < MAX_N; ++j){
            areFriends[i][j] = false;
        }
    }
    ans = 0;
}


void inputData(void){
    scanf("%d %d", &N, &M);
    init();
    for(int i = 1, a, b; i <= M; ++i){
        scanf("%d %d", &a, &b);
        areFriends[a][b] = areFriends[b][a] = true;
    }
}


void printPairs(void){
    printf("    === pairs ===\n");
    for(int i = 1; 2 * i <= N; ++i){
        printf("(%d, %d) ", pairs[i][0], pairs[i][1]);
    }
    printf("\n");
}


void dfs(int now, int cnt){
    if(cnt == N){
        ans++;
        //printPairs(); // [DEBUG]
        return;
    }

    while(selected[now] && now <= N) now++;
    if(now > N){
        // [ERROR]
        return;
    }

    selected[now] = true;
    for(int i = now + 1; i < N; ++i){
        if(selected[i]) continue;
        if(!areFriends[now][i]) continue;
        selected[i] = true;
        //pairs[cnt / 2 + 1][0] = now; pairs[cnt / 2 + 1][1] = i; // [DEBUG]
        dfs(now + 1, cnt + 2);
        selected[i] = false;
    }
    selected[now] = false;
}


void solve(void){
    selected[0] = true;
    for(int i = 1; i < N; ++i){
        if(!areFriends[0][i]) continue;
        selected[i] = true;
        //pairs[1][0] = 0; pairs[1][1] = i; // [DEBUG]
        dfs(1, 2);
        selected[i] = false;
    }
}


void printAns(void) {
    printf("%d\n", ans);
}

int main(void){
    freopen("picnic_input.txt", "rb", stdin);
    freopen("picnic_output.txt", "wb", stdout);
    
    scanf("%d", &T);
    for(tc = 1; tc <= T; ++tc){
        inputData();
        solve();
        printAns();
    }

    return 0;
}
