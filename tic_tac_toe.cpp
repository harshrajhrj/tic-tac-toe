#include <bits/stdc++.h>
using namespace std;

#define EMPTY '-'
#define PLAYER_1 'X'
#define PLAYER_0 '0'

/**
 * Conventions of return value from check_winner() function
 * 'X' - Player 'X' wins
 * '0' - Player '0' wins
 * 'T' - Game tied
 * 'N' - No one has won yet
 * /
/** Board */
vector<char> board(9, EMPTY);

/** Print board */
void print_board(vector<char> board)
{
    for (int i = 0; i < 3; i++)
    {
        cout << board[i * 3] << " " << board[i * 3 + 1] << " " << board[i * 3 + 2];
        cout << endl;
    }
    cout << endl;
}

/** Check winner */
char check_winner(vector<char> board)
{
    vector<vector<int>> possible_wins = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

    /** Check who is the winner */
    for (auto wins : possible_wins)
    {
        if (board[wins[0]] == board[wins[1]] && board[wins[1]] == board[wins[2]] && board[wins[0]] != EMPTY)
            return board[wins[0]];
    }

    /** If none are winner then, check if all cells are full or not */
    bool isBlank = false;
    for (auto cell : board)
        if (cell == EMPTY)
        {
            isBlank = true;
            break;
        }
    if (isBlank == false) /** No cell is empty*/
        return 'T';

    return 'N';
}

/** Agent winning status check */
int agent_winning_status(vector<char> board)
{
    char win_status = check_winner(board);

    if (win_status == PLAYER_0)
        return 1;
    else if (win_status == PLAYER_1)
        return -1;
    else
        return 0;
}

/** Minimax (alpha-beta) pruning */
int alphabeta(vector<char> board, int depth, int alpha, int beta, bool isMaximizing)
{
    if (check_winner(board) != 'N' || depth == 0)
        return agent_winning_status(board);

    if (isMaximizing)
    {
        int max_score = INT_MIN;
        for (int i = 0; i < 9; i++)
            if (board[i] == EMPTY)
            {
                board[i] = PLAYER_0;
                int eval_score = alphabeta(board, depth - 1, alpha, beta, false);
                board[i] = EMPTY;
                max_score = max(max_score, eval_score);
                alpha = max(alpha, eval_score);
                if (beta <= alpha)
                    break;
            }
        return max_score;
    }
    else
    {
        int min_score = INT_MAX;
        for (int i = 0; i < 9; i++)
            if (board[i] == EMPTY)
            {
                board[i] = PLAYER_1;
                int eval_score = alphabeta(board, depth - 1, alpha, beta, true);
                board[i] = EMPTY;
                min_score = min(min_score, eval_score);
                beta = min(beta, eval_score);
                if (beta <= alpha)
                    break;
            }
        return min_score;
    }
}

/** Heuristic function to find best move */
int find_best_move(vector<char> board)
{
    int best_score = INT_MIN;
    int best_move = -1;

    for (int i = 0; i < 9; i++)
    {
        if (board[i] == EMPTY)
        {
            board[i] = PLAYER_0;

            /** Maximizing player: minimize the chances of opponent i.e. us*/
            int move_score = alphabeta(board, 9, INT_MIN, INT_MAX, false);
            board[i] = EMPTY;

            if (move_score > best_score)
            {
                best_score = move_score;
                best_move = i;
            }
        }
    }

    return best_move;
}

int main()
{
    while (true)
    {
        print_board(board);
        char win_status = check_winner(board);
        if (win_status != 'N')
        {
            if (win_status == 'T')
                cout << "Game tied!";
            else
                cout << "Player " << win_status << " wins!";
            break;
        }

        /** Find which player will agent_winning_statusplay the next move */
        int flag_next_move = 0;
        for (auto cell : board)
            if (cell != EMPTY)
                flag_next_move++;
        if (flag_next_move % 2 == 0)
        {
            while (true)
            {
                int move;
                cout << "Enter your(Player X) move(0-8): ";
                cin >> move;

                /** Check whether the move is valid or invalid */
                if (board[move] == EMPTY)
                {
                    board[move] = PLAYER_1;
                    break;
                }
                else
                    cout << "Invalid move, please try again!" << endl;
            }
        }
        else
        {
            int move = find_best_move(board);
            board[move] = PLAYER_0;
            cout << "Player_0 used " << move << " move" << endl;
        }
    }
}
