#include <iostream>
#include <fstream>
using namespace std;

int** target;
int count = 1;
void move (char, int, int, int, int, int);
void clr(int, int);

int main(int argc, char* argv[]) {
    int refpt;
    int shift;
    int type;
    int m, n;
    
    char firstlet;
    ifstream infile(argv[1]);     
    if (!infile) {
        cout << "Can not open file!\n";
        return 1;
    }
    infile >> m >> n;
    target = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++){
        target[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            target[i][j] = 0;
        }
    }
    infile >> firstlet;
    while (firstlet != 'E') {                                                  
        infile >> type >> refpt >> shift;       
        move(firstlet, type, m, n, refpt, shift);
        clr(m, n);
        infile >> firstlet;
    }
    for(int i = m -1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            cout << target[i][j] <<' ';
        }
        cout << endl;
    }

   return 0;
}

void move (char a, int type, int m, int n, int refpt, int shift) {
    
    int i;
    int position[4][2];
    int height, flag;
    refpt--;
    if (a == 'T') {
        switch (type) {
        case 1: 
            position[0][0] = 1;
            position[0][1] = 0 + refpt;
            position[1][0] = 1;
            position[1][1] = 1 + refpt;
            position[2][0] = 0;
            position[2][1] = 1 + refpt;
            position[3][0] = 1;
            position[3][1] = 2 + refpt;
            height = 2;
            break;
        case 2: 
            position[0][0] = 0;
            position[0][1] = 1 + refpt;
            position[1][0] = 1;
            position[1][1] = 1 + refpt;
            position[2][0] = 2;
            position[2][1] = 1 + refpt;
            position[3][0] = 1;
            position[3][1] = 0 + refpt;
            height = 3;
            break;
        case 3: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 0;
            position[1][1] = 1 + refpt;
            position[2][0] = 0;
            position[2][1] = 2 + refpt;
            position[3][0] = 1;
            position[3][1] = 1 + refpt;
            height = 2;
            break;
        case 4: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 1;
            position[1][1] = 0 + refpt;
            position[2][0] = 2;
            position[2][1] = 0 + refpt;
            position[3][0] = 1;
            position[3][1] = 1 + refpt;
            height = 3;
            break;
        }
    } else if (a == 'L') {
        switch (type) {
        case 1: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 0;
            position[1][1] = 1 + refpt;
            position[2][0] = 1;
            position[2][1] = 0 + refpt;
            position[3][0] = 2;
            position[3][1] = 0 + refpt;
            height = 3;
            break;
        case 2: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 1;
            position[1][1] = 0 + refpt;
            position[2][0] = 1;
            position[2][1] = 1 + refpt;
            position[3][0] = 2;
            position[3][1] = 1 + refpt;
            height = 2;
            break;
        case 3: 
            position[0][0] = 2;
            position[0][1] = 0 + refpt;
            position[1][0] = 0;
            position[1][1] = 1 + refpt;
            position[2][0] = 1;
            position[2][1] = 1 + refpt;
            position[3][0] = 2;
            position[3][1] = 1 + refpt;
            height = 3;
            break;
        case 4: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 0;
            position[1][1] = 1 + refpt;
            position[2][0] = 0;
            position[2][1] = 2 + refpt;
            position[3][0] = 1;
            position[3][1] = 2 + refpt;
            height = 2;
            break;
        }
    } else if (a == 'J') {
        switch (type) {
        case 1: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 0;
            position[1][1] = 1 + refpt;
            position[2][0] = 1;
            position[2][1] = 1 + refpt;
            position[3][0] = 2;
            position[3][1] = 1 + refpt;
            height = 3;
            break;
        case 2: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 1;
            position[1][1] = 0 + refpt;
            position[2][0] = 0;
            position[2][1] = 1 + refpt;
            position[3][0] = 0;
            position[3][1] = 2 + refpt;
            height = 2;
            break;
        case 3: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 1;
            position[1][1] = 0 + refpt;
            position[2][0] = 2;
            position[2][1] = 0 + refpt;
            position[3][0] = 2;
            position[3][1] = 1 + refpt;
            height = 3;
            break;
        case 4: 
            position[0][0] = 0;
            position[0][1] = 2 + refpt;
            position[1][0] = 1;
            position[1][1] = 0 + refpt;
            position[2][0] = 1;
            position[2][1] = 1 + refpt;
            position[3][0] = 1;
            position[3][1] = 2 + refpt;
            height = 2;
            break;
        }
    } else if (a == 'S') {
        switch (type) {
        case 1: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 0;
            position[1][1] = 1 + refpt;
            position[2][0] = 1;
            position[2][1] = 1 + refpt;
            position[3][0] = 1;
            position[3][1] = 2 + refpt;
            height = 2;
            break;
        case 2: 
            position[0][0] = 0;
            position[0][1] = 1 + refpt;
            position[1][0] = 1;
            position[1][1] = 0 + refpt;
            position[2][0] = 1;
            position[2][1] = 1 + refpt;
            position[3][0] = 2;
            position[3][1] = 0 + refpt;
            height = 3;
            break;
        }
    } else if (a == 'Z') {
        switch (type) {
        case 1: 
            position[0][0] = 0;
            position[0][1] = 1 + refpt;
            position[1][0] = 0;
            position[1][1] = 2 + refpt;
            position[2][0] = 1;
            position[2][1] = 0 + refpt;
            position[3][0] = 1;
            position[3][1] = 1 + refpt;
            height = 2;
            break;
        case 2: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 1;
            position[1][1] = 0 + refpt;
            position[2][0] = 1;
            position[2][1] = 1 + refpt;
            position[3][0] = 2;
            position[3][1] = 1 + refpt;
            height = 3;
            break;
        }
    } else if (a == 'I') {
        switch (type) {
        case 1: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 2;
            position[1][1] = 0 + refpt;
            position[2][0] = 1;
            position[2][1] = 0 + refpt;
            position[3][0] = 3;
            position[3][1] = 0 + refpt;
            height = 4;
            break;
        case 2: 
            position[0][0] = 0;
            position[0][1] = 0 + refpt;
            position[1][0] = 0;
            position[1][1] = 1 + refpt;
            position[2][0] = 0;
            position[2][1] = 2 + refpt;
            position[3][0] = 0;
            position[3][1] = 3 + refpt;
            height = 1;
            break;
        }
    } else if (a == 'O') {
        position[0][0] = 0;
        position[0][1] = 0 + refpt;
        position[1][0] = 0;
        position[1][1] = 1 + refpt;
        position[2][0] = 1;
        position[2][1] = 0 + refpt;
        position[3][0] = 1;
        position[3][1] = 1 + refpt;
        height = 2;
    }
    flag = 1;
    for (i = m - height; i >= 0 && flag; ) { 
        for (int j = 0; j < 4; j++) {
            if (target[position[j][0] + i][position[j][1]] != 0) {
                flag = 0;
            }
        }
        if (flag == 1){
            i--;
        }
    }
    for (int j = 0; j < 4; j++) {    
        target[position[j][0] + i + 1][position[j][1] + shift] = count;
        
    }
    count++;
    return;
}

void clr(int m, int n){
    int flag = 1;

    for (int i = 0; i < m; i++){
        flag = 1;
        for (int j = 0; j < n; j++){
            
            if (target[i][j] == 0){
                flag = 0;
            }
        }
        if (flag == 1){
            for (int k = i; k < m - 1; k++){
                for (int l = 0; l < n; l++){
                    target[k][l] = target[k + 1][l];
                }
            }
            for (int l = 0; i < n; i++){
                target[m - 1][l] = 0;
            }
        }
    }
    return;
}