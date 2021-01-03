#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

#define victory 100000000
#define DEFEAT -100000000
#define OPPONENT_WINS 200000000
#define ILLEGAL -200000000
#define failgame -500000000
#define WIN 1
#define LOSE -1
#define continue 2
#define CORNER 1
#define EDGE 2
#define MY true
#define OPPONENT false


int weightedcount(int row, int col, Board board, Player player);
int run_game(Board board, Player player);
int critical_cells(int row, int col, Board board, char player);
int cell_classify(int row, int col);
int critical_cells_linked(int row, int col, Board board, char player, bool record[][COL]);
int minimax(int row, int col, Board board, Player player, Player enemy, bool turn, int depth,int MAX_depth, int a, int b);
int critical_condition(Board board, int row, int col);
    

void algorithm_A(Board board, Player player, int index[])
{
    srand(time(NULL));
    int row, col;
    char color = player.get_color();
    char enemy_color;
    int score = ILLEGAL;
    int a = -1000000000;
    int b = 1000000000;
    if (color == RED)   enemy_color = BLUE;
    else enemy_color = RED;
    Player enemy(enemy_color);

    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
        {
            int new_score;
            if (score < (new_score = minimax(i, j, board, player, enemy, OPPONENT, 0, 2, a, b)) && new_score != failgame)
            {
                    score = new_score;
                    index[0] = i;
                    index[1] = j;
                   
            }
            if (a < new_score)  a = new_score;
            if (b <= a)  return;    
        }
}

bool place_legal(int row, int col, Board board, Player player)
{
    if (board.get_cell_color(row, col) != player.get_color() && board.get_cell_color(row, col) != 'w')
        return false;
    else return true;
}


int minimax(int row, int col, Board board, Player player, Player enemy, bool turn, int depth, int MAX_depth, int a, int b)
{
    int score = ILLEGAL;
    if (depth == MAX_depth)
    {
        if (place_legal(row, col, board, enemy))   board.place_orb(row, col, &enemy);
        else return failgame;
        if (run_game(board, player) == WIN)  return victory;
        else if (run_game(board, player) == LOSE)  return DEFEAT;
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
            {
                int new_score;
                if (score < (new_score = weightedcount(i, j, board, player)))  score = new_score;   
            }
        return score;
    }
    if (turn == MY)
    {
        if (place_legal(row, col, board, enemy))   board.place_orb(row, col, &enemy);
        else return failgame;

        if (run_game(board, player) == WIN)  return victory;
        else if (run_game(board, player) == LOSE)  return DEFEAT;

        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
            {
                int new_score = minimax(i, j, board, player, enemy, !turn, depth + 1, MAX_depth, a, b);
                if (score < new_score && new_score != failgame) score = new_score;
                if (a < new_score)  a = new_score;
                if (b <= a)  return score;
            }
        return score;
    
    }
    if (turn == OPPONENT)
    {
        if (place_legal(row, col, board, player))   board.place_orb(row, col, &player);
        else return failgame;
        if (run_game(board, player) == WIN)  return victory;
        else if (run_game(board, player) == LOSE)  return DEFEAT;
        score = OPPONENT_WINS;
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
            {
                int new_score = minimax(i, j, board, player, enemy, !turn, depth + 1, MAX_depth, a, b);
                if (score > new_score && new_score >= ILLEGAL)
                {
                    score = new_score;
                }
                if (b > new_score && new_score > ILLEGAL)  b = new_score;
                if (b <= a)  return score;
            }
        return score;
    
    }
    return score;
}

int weightedcount(int row, int col, Board board, Player player)
{
    int score = 0;
    char player_color = player.get_color();
    char enemy_color;
    bool record[ROW][COL] = {0};
    int result = run_game(board, player);
    if (player_color == RED)   enemy_color = BLUE;
    else enemy_color = RED;
    
    if (board.get_cell_color(row, col) == enemy_color) return ILLEGAL;
    board.place_orb(row, col, &player);
    
    
    if (result == WIN) score += victory;
    else if (result == LOSE) score += DEFEAT;

    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
        {
            int temp;
            if (player_color == board.get_cell_color(i,j))
            {
                score += board.get_orbs_num(i, j);
                temp = critical_cells(i, j, board, player_color);
                score += temp;
                if (temp == 0)
                {
                    if (cell_classify(i, j) == CORNER) score += 3;
                    else if (cell_classify(i, j) == EDGE) score += 2;
                    
                    if (critical_condition(board, i, j))
                        score += 2;
                }
                else if (critical_condition(board, i, j))
                {
                    score += critical_cells_linked(i, j, board, player_color, record);
                }                 
            }      
        }

    return score;
}

int run_game(Board board, Player player)
{
    char player_color = player.get_color();
    int me = 0;
    int opoponent = 0;

    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            if(board.get_cell_color(i,j) == player_color) me++;
            else if (board.get_cell_color(i,j) != 'w') opoponent++;
        }
    }
    if (opoponent == 0 && me != 0) return WIN;
    if (opoponent != 0 && me == 0) return LOSE;
    return continue; 
}

int critical_cells(int row, int col, Board board, char player)
{
    int score = 0;
    char enemy_color;
    char player_color = player;
    
    if (player_color == RED)   enemy_color = BLUE;
    else enemy_color = RED;
    
    if (row > 0)    
        if (board.get_cell_color(row - 1, col) == enemy_color)
            if (critical_condition(board, row - 1, col))
                score += board.get_capacity(row - 1, col) - 5;
                            
    if (col > 0)    
        if (board.get_cell_color(row, col - 1) == enemy_color)
            if (critical_condition(board, row, col - 1))

                score += board.get_capacity(row, col - 1) - 5;
    if (row < ROW - 1)   
        if (board.get_cell_color(row + 1, col) == enemy_color)
            if (critical_condition(board, row + 1, col))
                score += board.get_capacity(row + 1, col) - 5;        

    if (col < COL - 1) 
        if (board.get_cell_color(row, col + 1) == enemy_color)
            if (critical_condition(board, row, col + 1))
                score += board.get_capacity(row, col + 1) - 5;  

    return score;
}


int critical_cells_linked(int row, int col, Board board, char player, bool record[][COL])
{
    int number = 0;
                             
    if (row > 0)    
        if (board.get_cell_color(row - 1, col) == player)
            if (critical_condition(board, row - 1, col) && !record[row - 1][col])
            {
                number++;
                record[row - 1][col] = 1;
            }
                         
    if (col > 0)    
        if (board.get_cell_color(row, col - 1) == player)
            if (critical_condition(board, row, col - 1) && !record[row][col - 1])
            {
                number++;
                record[row][col - 1] = 1;
            }
    if (row < ROW - 1)    
        if (board.get_cell_color(row + 1, col) == player)
            if (critical_condition(board, row + 1, col) && !record[row + 1][col])
            {
                number++;
                record[row + 1][col] = 1;
            }
                                      
    if (col < COL - 1) 
        if (board.get_cell_color(row, col + 1) == player)
            if (critical_condition(board, row, col + 1) && !record[row][col + 1])
            {
                number++;
                record[row][col + 1] = 1;
            }     

    return 5 * number;
}

int cell_classify(int row, int col)
{
    if (row == 0 || col == 0 || row == ROW - 1 || col == COL - 1)
    {
        if (row == 0 && col == 0 || row == 0 && col == COL - 1 || row == ROW - 1 && col == 0 || row == ROW - 1 && col == COL - 1)     
            return CORNER;
        else return EDGE;           
    }
    return 0;
}

int critical_condition(Board board, int row, int col) {
    if (board.get_orbs_num(row, col) == board.get_capacity(row, col) - 1) return true;
    else return false;
}