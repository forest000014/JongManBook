#define DEBUG_MODE 01
#define DEBUG if(DEBUG_MODE)

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
using namespace std;

#define ASSG 1
#define ITER 2
#define RETN 3
#define LIT  1
#define VAR  2
#define EPE  3


class Expr{
public:
    int type;
                // 1 : literal
                // 2 : variable
                // 3 : (E) + (E)
    int eval;
    string var;
    Expr *left, *right;
};

class Stat{
public:
    int type;
                // 1 : assignment
                // 2 : iteration
                // 3 : return
    Stat *next;
    int loop;
    Stat *iterStat;
    Expr *expr;
    string var;
};

vector <string> tokens;
Stat root;
map <string, int> varTable;
const int MOD = (int)(1e9 + 7);


void printTokens(void){ // [DEBUG]
    cout << "   === tokens[] ===" << endl;
    for(int i = 0; i < tokens.size(); ++i){
        cout << "[i = " << setw(2) << i << "]    " << tokens[i] << "    " << endl;
    }
}


void printExpr(int tp, Expr *now){ // [DEBUG]
    printf("tokens[%2d] : Expr\n", tp);
    printf("   type : %d, ", now->type);
    if(now->type == LIT) {
        printf("value : %d\n", now->eval);
    }
    else if(now->type == VAR) {
        printf("value : %s\n", now->var.c_str());
    }
    else if(now->type == EPE) {
        printf("\n");
        //printExpr(tp + 1, now->left);
        //printExpr(tp + 2, now->right);
    }
    printf("\n");
}


void printStat(int tp, Stat *now){ // [DEBUG]
    printf("tokens[%2d] : Stat\n", tp);
    printf("    type : %d, ", now->type);
    if(now->type == ASSG){
        printf("var : %s, expr : ...\n", now->var.c_str());
        printExpr(tp + 2, now->expr);
    }
    else if(now->type == ITER){
        printf("loop : %d, stat : ...\n", now->loop);
        printStat(tp + 3, now->iterStat);
    }
    else if(now->type == RETN){
        printf("return var : %s\n", now->var.c_str());
    }
    printf("\n");
}


void lex(void){
    string tmp;
    while(!cin.eof()){
        cin >> tmp;
        tokens.push_back(tmp);
    }
    DEBUG printTokens();
}


int parseExpr(int tp, Expr *now){
    if(tokens[tp].at(0) >= '0' && tokens[tp].at(0) <= '9'){
        now->type = LIT;
        now->eval = stoi(tokens[tp]);
        DEBUG printExpr(tp, now);
    }
    else if(tokens[tp].at(0) >= 'a' && tokens[tp].at(0) <= 'z'){
        now->type = VAR;
        now->var = tokens[tp];
        DEBUG printExpr(tp, now);
    }
    else if(tokens[tp].at(0) == '('){
        now->type = EPE;
        now->left = new Expr();
        DEBUG printExpr(tp, now);
        tp = parseExpr(tp + 1, now->left);
        now->right = new Expr();
        tp = parseExpr(tp + 3, now->right);
    }
    else {} // [ERROR]

    return tp + 1;
}


int parseStat(int tp, Stat *now){ // tp : 현재 파싱해야할 token의 index
    int tmp = tp; // [DEBUG]
    DEBUG printf("      === parseStat(%d) ===\n", tp);

    if(tokens[tp].at(0) >= 'a' && tokens[tp].at(0) <= 'z'){ // assignment statement
        now->type = ASSG;
        now->var = tokens[tp];
        now->expr = new Expr();
        tp = parseExpr(tp + 2, now->expr);
        DEBUG printStat(tmp, now);
    }
    else if(tokens[tp].at(0) >= '0' && tokens[tp].at(0) <= '9'){ // iteration statement
        now->type = ITER;
        now->loop = stoi(tokens[tp]);
        now->iterStat = new Stat();
        tp = parseStat(tp + 3, now->iterStat);
        DEBUG printStat(tmp, now);
    }
    else if(tokens[tp].at(0) == 'R'){ // return statement
        now->type = RETN;
        ++tp;
        now->var = tokens[tp];
        DEBUG printStat(tp - 1, now);
        ++tp;
    }
    else {} // [ERROR EXCEPTION]

    if(tp < tokens.size() && tokens[tp].at(0) == '}') return tp + 1; // end of iteration statement

    if(tp < tokens.size()){
        now->next = new Stat();
        tp = parseStat(tp, now->next);
    }

    return tp;
}


void compileExpr(Expr *now){
    if(now->type == LIT){} // nothing to do
    else if(now->type == VAR){
        now->eval = varTable[now->var];
    }
    else if(now->type == EPE){
        compileExpr(now->left);
        compileExpr(now->right);
        now->eval = (now->left->eval + now->right->eval) % MOD;
    }
}


void compileStat(Stat *now){
    if(now->type == ASSG){
        compileExpr(now->expr);
        varTable[now->var] = now->expr->eval;
    }
    else if(now->type == ITER){
        for(int i = 1; i <= now->loop; ++i){
            compileStat(now->iterStat); // Q. 백준 시간 제한 2초까지 어떻게 줄일 것인가? (~2억번 이내 연산. but 100,000 * 100,000 > 20,000,000)
        }
    }
    else if(now->type == RETN){
        cout << varTable[now->var] << endl;
        return;
    }

    if(now->next != NULL){
        compileStat(now->next);
    }
}


int main(void){
    freopen("moo_input.txt", "r", stdin);

    lex();
    parseStat(0, &root);
    compileStat(&root);

    return 0;
}