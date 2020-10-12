#include <iostream>
#include <fstream>
using namespace std;

class addmatrix{
public:

private:
    int row;
    int column;
    int value;
    
};
int main(int argc, char* argv[]) {
    
    ifstream infile(argv[1]);     
    if (!infile) {
    cout << "Can not open file!\n";
    return 1;
    }
    else
   
   return 0;
}