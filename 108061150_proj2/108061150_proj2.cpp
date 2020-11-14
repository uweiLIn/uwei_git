#include <iostream>
#include <fstream>
using namespace std;

typedef struct _point
{
    char state;
    int distance;
} point;

void count_dis(int, int, int);
void step(int, int);

point** map;
int m, n;
int E;
int battery;
int path = 0;

int main(int argc, char* argv[]) {
    int init_x, init_y;
    
    ifstream infile(argv[1]);     
    if (!infile) {
        cout << "Can not open file!\n";
        return 1;
    }
    infile >> m >> n >> E;
    map = (point **)malloc(m * sizeof(point *));
    for (int i = 0; i < m; i++){
        map[i] = (point *)malloc(n * sizeof(point));
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            infile >> map[i][j].state;
            if (map[i][j].state == 'R'){
                init_x = i;
                init_y = j;
            }
            map[i][j].distance = 2147483647;
        }
    }
    map[init_x][init_y].distance = 0;
    count_dis(init_x, init_y, 0);
    battery = E;
   
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("%11d", map[i][j].distance);
        }
        cout << endl;
    }
    
   return 0;
}

void count_dis(int x, int y, int dis)
{
    
    if (x + 1 < m){
        if (map[x + 1][y].state == '0' && map[x + 1][y].distance > dis + 1){
            map[x + 1][y].distance = dis + 1;
            count_dis(x + 1, y, dis + 1);
        }
    }
    if (y + 1 < n){
        if (map[x][y + 1].state == '0' && map[x][y + 1].distance > dis + 1){
            map[x][y + 1].distance = dis + 1;
            count_dis(x, y + 1, dis + 1);
        }
    }
    if (x > 0){
        if (map[x - 1][y].state == '0' && map[x - 1][y].distance > dis + 1){
            map[x - 1][y].distance = dis + 1;
            count_dis(x - 1, y, dis + 1);
        }
    }
    if (y > 0){
        if (map[x][y - 1].state == '0' && map[x][y - 1].distance > dis + 1){
            map[x][y - 1].distance = dis + 1;
            count_dis(x, y - 1, dis + 1);
        }
    }
    

    return;
}

void step(int x, int y)
{
    path++;
    battery--;
    cout << x << ' ' << y << endl;
    map[x][y].state = '2';
    if (x + 1 < m){
        if (map[x + 1][y].state == '0' && map[x + 1][y].distance <= battery - 1){
          step(x + 1, y);
        }
    }
     if (y + 1 < n){
        if (map[x][y + 1].state == '0' && map[x][y + 1].distance <= battery - 1){
          step(x, y + 1);
        }
    }
     if (x > 0){
        if (map[x - 1][y].state == '0' && map[x - 1][y].distance <= battery - 1){
          step(x - 1, y);
        }
    }
     if (y > 0){
        if (map[x][y - 1].state == '0' && map[x][y - 1].distance <= battery - 1){
          step(x, y - 1);
        }
    }
}