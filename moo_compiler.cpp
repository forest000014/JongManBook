#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
using namespace std;
#define LIT 1
#define VAR 2
#define EXP 3

struct NODE{
    int lit;
    char var[10];
    int type;
    vector <NODE> exp;
};
char tokens[17500][15];
int c;
map <string, int> varTable;
int varCnt;
vector <int> vars;

void lex(char tmp[]){
    int p = 0;
    int tp = 0;
    while(tmp[p]){
        if(tmp[p] == ' '){
            c++;
            p++;
            tp = 0;
        }
        else {
            tokens[c][tp] = tmp[p];
            p++;
            tp++;
        }
    }
}

int parseVar(int cc){ // index in vars[]
    if(!varTable.find(tokens[cc])){ // string?
        varTable.insert(tokens[cc], varCnt++);
        vars.push_back(-1);
    }

    return varTable.find(tokens[cc]);
}

NODE parseLit(int cc){
    NODE ret;
    int p = 0;
    ret.lit = 0;
    while(tokens[cc] != '\0'){
        ret.lit = ret.lit * 10 + (tokens[cc][p] - '0');
        p++;
    }
    ret.type = LIT;

    return ret;
}

NODE parseExp(int cc){
    NODE ret;
    char tmp[15];
    int p = 0;
    while(tokens[cc][p] != '\0'){
        tmp[p] = tokens[cc][p];
        p++;
    }

    if(tmp[0] >= '0' && tmp[0] <= '9'){
        ret = parseLit(cc);
    }
    else {
        ret = parseVar(cc);
    }
    return ret;
}

void parseSta(void){
    c = 0;
    while(tokens[c][0] != ''){
        if(tokens[c][0] == '='){
            
            int varIdx = parseVar(c - 1);
            vars[varIdx] = parseExp(c + 1).lit;
        }
        else if(!strcmp(tokens[c], "RETURN")){
            parseVar();
        }
        else{

        }


        c++;
    }
}

int main(void){
    char tmp[355];
    while(scanf("%s", tmp) != EOF){
        lex(tmp);
    };

    parseSta();


    return 0;
}