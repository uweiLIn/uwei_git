#include <iostream>
#include <fstream>
using namespace std;



int** typeMatrix(char *a) {
   int sign[4][4] = {0};
   if (a[0] == 'T' && a[1] == 1) {
       sign[2][0] = 1;
       sign[2][1] = 1;
       sign[2][2] = 1;
       sign[3][1] = 1;
   }
   if (a[0] == 'T' && a[1] == 2) {
       sign[2][0] = 1;
       sign[2][1] = 1;
       sign[1][1] = 1;
       sign[3][1] = 1;
   }
   if (a[0] == 'T' && a[1] == 3) {
       sign[3][0] = 1;
       sign[2][1] = 1;
       sign[3][2] = 1;
       sign[3][1] = 1;
   }
   if (a[0] == 'T' && a[1] == 4) {
       sign[1][0] = 1;
       sign[2][0] = 1;
       sign[2][1] = 1;
       sign[3][0] = 1;
   }
   if (a[0] == 'L' && a[1] == 1) {
       sign[1][0] = 1;
       sign[2][0] = 1;
       sign[3][0] = 1;
       sign[3][1] = 1;
   }
   if (a[0] == 'L' && a[1] == 2) {
       sign[2][0] = 1;
       sign[2][1] = 1;
       sign[2][2] = 1;
       sign[3][0] = 1;
   }
   if (a[0] == 'L' && a[1] == 3) {
       sign[1][0] = 1;
       sign[1][1] = 1;
       sign[2][1] = 1;
       sign[3][1] = 1;
   }
   if (a[0] == 'L' && a[1] == 4) {
       sign[3][0] = 1;
       sign[3][1] = 1;
       sign[2][2] = 1;
       sign[3][2] = 1;
   }
   if (a[0] == 'J' && a[1] == 1) {
       sign[1][1] = 1;
       sign[2][1] = 1;
       sign[3][0] = 1;
       sign[3][1] = 1;
   }
   if (a[0] == 'J' && a[1] == 2) {
       sign[2][0] = 1;
       sign[2][1] = 1;
       sign[3][0] = 1;
       sign[3][2] = 1;
   }
   if (a[0] == 'J' && a[1] == 3) {
       sign[1][0] = 1;
       sign[1][1] = 1;
       sign[2][0] = 1;
       sign[3][0] = 1;
   }
   if (a[0] == 'J' && a[1] == 4) {
       sign[2][0] = 1;
       sign[2][1] = 1;
       sign[2][2] = 1;
       sign[3][2] = 1;
   }
   if (a[0] == 'I' && a[1] == 1) {
       sign[0][0] = 1;
       sign[1][0] = 1;
       sign[2][0] = 1;
       sign[3][0] = 1;
   }
   if (a[0] == 'I' && a[1] == 2) {
       sign[3][0] = 1;
       sign[3][1] = 1;
       sign[3][2] = 1;
       sign[3][3] = 1;
   }
   if (a[0] == 'S' && a[1] == 1) {
       sign[3][0] = 1;
       sign[2][1] = 1;
       sign[2][2] = 1;
       sign[3][1] = 1;
   }
   if (a[0] == 'S' && a[1] == 2) {
       sign[1][0] = 1;
       sign[2][0] = 1;
       sign[3][0] = 1;
       sign[3][1] = 1;
   }
   if (a[0] == 'Z' && a[1] == 1) {
       sign[2][0] = 1;
       sign[2][1] = 1;
       sign[3][2] = 1;
       sign[3][1] = 1;
   }
   if (a[0] == 'Z' && a[1] == 2) {
       sign[2][0] = 1;
       sign[1][1] = 1;
       sign[2][1] = 1;
       sign[3][0] = 1;
   }
   if (a[0] == 'O') {
       sign[2][0] = 1;
       sign[2][1] = 1;
       sign[3][0] = 1;
       sign[3][1] = 1;
   }
   return *sign; // bug 
}

void line_check(int m, int n, int** &target) {
    int rowsum;
    int row, column;

    row = 0;
    while(row < m) {
        rowsum = 0;
        for (int j = 0; j < n; j++) {
            if (target[row][j]) rowsum++;
            if (rowsum == n) {
                for (int j = 0; j < n; j++) {
                    target[row][j] = 0;
                }
                for (int k = row; k >= 0; k--) {
                    for (int j = 0; j < n; j++) {
                        target[k][j] = target[k - 1][j]; 
                    }
                }
            } 
        }
        row++;
    }        
}

void move(int shift, int m, int n, int refpt, int** &target, int** addmatrix) {
    for (int i = 0; i < m - 1; i++) {
        if ((target[i + 1][refpt - 1] || target[i + 1][refpt] || target[i + 1][refpt + 1] || 
            target[i + 1][refpt + 2]) == 1) {
                
            }
    }


}

int main(int argc, char* argv[]) {
    int refpt;
    int shiftv;
    char command[20];
    int m, n;
    ifstream infile(argv[1]);     
    if (!infile) {
        cout << "Can not open file!\n";
        return 1;
    }
    
    while () {
        for(int i = 0; command[i] != '\n' || i < 20; i++) {
            command[i] = getchar();
        }
        typeMatrix(command);

        
    }
  
   return 0;
}