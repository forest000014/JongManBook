// ~35분
#include <stdio.h>
#include <string.h>


const int MAX_R = 5;
const int MAX_C = 5;
const int MAX_S = 10;
const int dr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };


int T, tc, N, L;
char board[MAX_R + 5][MAX_C + 5];
char word[MAX_S + 5];
bool hasAlphabet[27];
bool ans;


void inputData(void){
    for(int i = 1; i <= 26; ++i){
        hasAlphabet[i] = false;
    }
    for(int i = 1; i <= MAX_R; ++i){
        scanf("%s", board[i] + 1);
        for(int j = 1; j <= MAX_C; ++j){
            hasAlphabet[board[i][j] - 'A' + 1] = true;
        }
    }
    scanf("%d", &N);
}

void dfs(int r, int c, int p){
    if(p == L){
        ans = true;
        return;
    }
    for(int i = 0; i < 8; ++i){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if(nr < 1 || nr > MAX_R || nc < 1 || nc > MAX_C) continue;
        if(board[nr][nc] != word[p + 1]) continue;
        dfs(nr, nc, p + 1);
    }
}

void solve(void){
    ans = false;
    scanf("%s", word + 1);
    L = strlen(word + 1);
    for(int i = 1; i <= L; ++i){
        if(!hasAlphabet[word[i] - 'A' + 1]) return;
    }
    for(int i = 1; i <= MAX_R; ++i){
        for(int j = 1; j <= MAX_C; ++j){
            if(board[i][j] != word[1]) continue;
            dfs(i, j, 1);
            if(ans) return;
        }
    }
}

void printAns(void) {
    if(ans) printf("%s YES\n", word + 1);
    else printf("%s NO\n", word + 1);
}

int main(void){
    freopen("boggle_input.txt", "rb", stdin);
    freopen("boggle_output.txt", "wb", stdout);
    
    scanf("%d", &T);
    for(tc = 1; tc <= T; ++tc){
        inputData();
        for(int i = 1; i <= N; ++i){
            solve();
            printAns();
        }
    }

    return 0;
}
