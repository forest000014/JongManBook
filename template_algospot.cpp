#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;


const int MAX_N = 1000;

int T, tc, N;
int ans;


void init(void){

}


void inputData(void){
    scanf("%d", &N);
    init();
}


void solve(void){
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
