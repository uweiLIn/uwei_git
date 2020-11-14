#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

typedef struct _point
{
    char state;
    int distance;
} point;

void count_dis(int, int, int);
void step(int, int);
void goHome(int, int);

point** map;
int m, n;
int E;
int battery;
queue<int> x_Q;
queue<int> y_Q;

int main(int argc, char* argv[]) {
    int init_x, init_y;
    int x, y;
    int i;

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
    battery++;
    x = init_x;
    y = init_y;
   
    /*for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("%11d", map[i][j].distance);
        }
        cout << endl;
    }*/
    step(init_x, init_y);
    cout << x_Q.size() << endl;
    while (!x_Q.empty()){
        cout << x_Q.front() << ' ' << y_Q.front() << endl;
        x_Q.pop();
        y_Q.pop();
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
    battery--;
    //cout << x << ' ' << y << endl;
    x_Q.push(x);
    y_Q.push(y);
    map[x][y].state = '2';
    if (battery <= map[x][y].distance + 1){
        //cout << "RETURN" << endl;
        goHome(x, y);
        battery = E - map[x][y].distance;
        x_Q.push(x);
        y_Q.push(y);
    }
    if (x + 1 < m){
        if (map[x + 1][y].state == '0'){
            step(x + 1, y);
            battery--;
            if (battery <= map[x][y].distance + 1){
                //cout << "RETURN" << endl;
                x_Q.push(x);
                y_Q.push(y);
                goHome(x, y);
                battery = E - map[x][y].distance;
            } else {
                x_Q.push(x);
                y_Q.push(y);
            }
        }
    }
     if (y + 1 < n){
        //if (map[x][y + 1].state == '0' && map[x][y + 1].distance <= battery - 1){
        if (map[x][y + 1].state == '0'){
            step(x, y + 1);
            battery--;
            if (battery <= map[x][y].distance + 1){
                //cout << "RETURN" << endl;
                x_Q.push(x);
                y_Q.push(y);
                goHome(x, y);
                battery = E - map[x][y].distance;
            } else {
                x_Q.push(x);
                y_Q.push(y);
            }
        }
    }
     if (x > 0){
        //if (map[x - 1][y].state == '0' && map[x - 1][y].dista
        nce <= battery - 1){
        if (map[x - 1][y].state == '0'){
            step(x - 1, y);
            battery--;
            if (battery <= map[x][y].distance + 1){
                //cout << "RETURN" << endl;
                x_Q.push(x);
                y_Q.push(y);
                goHome(x, y);
                battery = E - map[x][y].distance;
            } else {
                x_Q.push(x);
                y_Q.push(y);
            }
        }
    }
     if (y > 0){
        //if (map[x][y - 1].state == '0' && map[x][y - 1].distance <= battery - 1){
        if (map[x][y - 1].state == '0'){
            step(x, y - 1);
            battery--;
            if (battery <= map[x][y].distance + 1){
                //cout << "RETURN" << endl;
                x_Q.push(x);
                y_Q.push(y);
                goHome(x, y);
                battery = E - map[x][y].distance;
            } else {
                x_Q.push(x);
                y_Q.push(y);
            }
        }
    }
}

void goHome(int x, int y)
{
    int *path_x;
    int *path_y;
    int tmp_x, tmp_y;
    int i = 1;
    int dis = map[x][y].distance;
    int d = dis;

    path_x = (int *)malloc((dis + 1) * sizeof(int));
    path_y = (int *)malloc((dis + 1) * sizeof(int));
    path_x[0] = x;
    path_y[0] = y;

    while (dis != 0){
        if (map[x + 1][y].distance == dis - 1){
            tmp_x = x + 1;
            tmp_y = y;
        } else if (map[x][y + 1].distance == dis - 1){
            tmp_x = x;
            tmp_y = y + 1;
        } else if (map[x - 1][y].distance == dis - 1){
            tmp_x = x - 1;
            tmp_y = y;
        } else if (map[x][y - 1].distance == dis - 1){
            tmp_x = x;
            tmp_y = y - 1;
        }

        path_x[i] = tmp_x;
        path_y[i] = tmp_y;
        i++;
        x = tmp_x;
        y = tmp_y;
        dis--;
    }

    for (i = 1; i < d + 1; i++){
        x_Q.push(path_x[i]);
        y_Q.push(path_y[i]);
    }
    for (i = d - 1; i > 0; i--){
        x_Q.push(path_x[i]);
        y_Q.push(path_y[i]);
    }

    return;
}