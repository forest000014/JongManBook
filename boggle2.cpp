#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;


const int MAX_R = 5;
const int MAX_C = 5;
const int MAX_S = 1000;
const int dr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
struct POS{
    int r, c;
};

int T, tc, N, L;
char board[MAX_R + 5][MAX_C + 5];
char word[MAX_S + 5];
bool hasAlphabet[27];
vector <POS> alphabet[27];
queue <POS> toBeUpdated;
int DP[MAX_R + 5][MAX_C + 5];
bool ans;


void inputData(void){
    for(int i = 1; i <= 26; ++i){
        hasAlphabet[i] = false;
        alphabet[i].clear();
    }
    for(int i = 1; i <= MAX_R; ++i){
        scanf("%s", board[i] + 1);
        for(int j = 1; j <= MAX_C; ++j){
            hasAlphabet[board[i][j] - 'A' + 1] = true;
            POS tmp = {i, j};
            alphabet[board[i][j] - 'A' + 1].push_back(tmp);
        }
    }
    scanf("%d", &N);
}

void printDP(void){
    printf("   === DP[][] ===\n");
    for(int i = 1; i <= MAX_R; ++i){
        for(int j = 1; j <= MAX_C; ++j){
            printf("%4d%c", DP[i][j], " \n"[j == MAX_C]);
        }
    }
    printf("\n");
}

void solve(void){
    for(int i = 1; i <= MAX_R; ++i){
        for(int j = 1; j <= MAX_C; ++j){
            DP[i][j] = 0;
        }
    }
    ans = false;
    scanf("%s", word + 1);
    L = strlen(word + 1);
    for(int i = 1; i <= L; ++i){
        if(!hasAlphabet[word[i] - 'A' + 1]) return;
    }

    for(int i = 0; i < alphabet[word[1] - 'A' + 1].size(); ++i){
        DP[alphabet[word[1] - 'A' + 1][i].r][alphabet[word[1] - 'A' + 1][i].c] = 1;
    }
    
    //printDP(); // [DEBUG]

    for(int i = 2; i <= L; ++i){
        bool hasFound = false;
        for(int j = 0; j < alphabet[word[i] - 'A' + 1].size(); ++j){
            int r = alphabet[word[i] - 'A' + 1][j].r;
            int c = alphabet[word[i] - 'A' + 1][j].c;
            for(int k = 0; k < 8; ++k){
                int pr = r + dr[k];
                int pc = c + dc[k];
                if(pr < 1 || pr > MAX_R || pc < 1 || pc > MAX_C) continue;
                if(DP[pr][pc] != i - 1) continue;
                //DP[r][c] = i;
                POS tmp = {r, c};
                toBeUpdated.push(tmp);
                hasFound = true;
                break;
            }
        }
        //printDP(); // [DEBUG]
        if(!hasFound) return;
        while(!toBeUpdated.empty()){
            POS now = toBeUpdated.front(); toBeUpdated.pop();
            DP[now.r][now.c] = i;
        }
    }
    ans = true;
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
