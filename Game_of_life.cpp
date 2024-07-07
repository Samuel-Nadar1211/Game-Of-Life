// C++ Program to implement Game of Life

#include <iostream>
#include <windows.h>

using namespace std;

class Console
{
protected:
    HANDLE console;
    COORD cursor_position;

    Console()
    {
        console = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void setCursorPosition(int x, int y)
    {
        cursor_position.X = x;
        cursor_position.Y = y;
        SetConsoleCursorPosition(console, cursor_position);
    }

    void setCursorInfo(bool visible, DWORD size)
    {
        if (size == 0)
            size = 20;
        CONSOLE_CURSOR_INFO lpCursor;
        lpCursor.bVisible = visible;
        lpCursor.dwSize = size;
        SetConsoleCursorInfo(console, &lpCursor);
    }
};

class Board : protected Console
{
protected:
    int row, col;
    bool **board;

    void printBoard(int gen)
    {
        SetConsoleTextAttribute(console, 245);

        if (gen)
        {
            setCursorPosition(col / 2 - 13, 0);
            cout << "Board After Generation " << gen;
            SetConsoleTextAttribute(console, 180);
        }
        else
        {
            system("cls");
            setCursorPosition(col / 2 - 8, 0);
            cout << "Board Initially\n";
            
            // Frame
            SetConsoleTextAttribute(console, 86);
            for (int i = 0; i <= col + 1; i++)
                cout << '*';

            setCursorPosition(0, row + 2);
            for (int i = 0; i <= col + 1; i++)
                cout << '*';
            
            for (int i = 2; i <= row + 1; i++)
            {
                setCursorPosition(0, i);
                cout << '*';
                setCursorPosition(col + 1, i);
                cout << '*';
            }
        }
        
        for (int i = 1; i <= row; i++)
        {
            setCursorPosition(1, i + 1);
            for (int j = 1; j <= col; j++)
            {
                if (board[i][j])
                    SetConsoleTextAttribute(console, 160);      // Living creature
                else
                    SetConsoleTextAttribute(console, 176);      // Dead creature
                
                cout << ' ';
            }
        }
    }

    Board(int row = 0, int col = 0)
    {
        this->row = row;
        this->col = col;
        board = new bool *[row + 2]();

        for (int i = 0; i < row + 2; i++)
            board[i] = new bool[col + 2]();
    }

    void cleanBoard()
    {
        for (int i = 0; i <= row + 1; i++)
            for (int j = 0; j <= col + 1; j++)
                board[i][j] = 0;
    }

    ~Board()
    {
        for (int i = 0; i < row + 2; i++)
            delete board[i];
        delete[] board;
    }
};

class InputLife : virtual protected Board
{
protected:
    void placeLifeManually()
    {
        int row_pos, col_pos;
        cout << "\n\t\tFor placing the living creature, enter the position of row and column-\n\t\t\t";
        cin >> row_pos >> col_pos;

        if (row_pos > 0 || row_pos <= row || col_pos > 0 || col_pos <= col)
            board[row_pos][col_pos] = true;

        bool choice;
        cout << "\n\t\tPress 0 if you want to place living creature\n\t\tPress 1 if you are done with placing living creature\n\t\t\t";
        cin >> choice;

        if (!choice)
            placeLifeManually();
    }

    void gosperGliderGun()
    {
        board[5][11] = board[5][12] = board[6][11] = board[6][12] = board[5][21] = board[6][21] = board[7][21] = board[4][22] = board[8][22] = board[3][23] = board[9][23] = board[3][24] = board[9][24] = board[6][25] = board[4][26] = board[8][26] = board[5][27] = board[6][27] = board[7][27] = board[6][28] = board[3][31] = board[4][31] = board[5][31] = board[3][32] = board[4][32] = board[5][32] = board[2][33] = board[6][33] = board[1][35] = board[2][35] = board[6][35] = board[7][35] = board[3][45] = board[4][45] = board[3][46] = board[4][46] = true;
    }

    void simkinGliderGun()
    {
        board[22][22] = board[23][22] = board[22][23] = board[23][23] = board[25][26] = board[26][26] = board[25][27] = board[26][27] = board[22][29] = board[23][29] = board[22][30] = board[23][30] = board[39][42] = board[40][42] = board[39][43] = board[41][43] = board[41][44] = board[41][45] = board[42][45] = board[32][43] = board[33][43] = board[34][43] = board[31][44] = board[34][44] = board[31][45] = board[34][45] = board[31][47] = board[31][48] = board[35][48] = board[32][49] = board[34][49] = board[33][50] = board[33][53] = board[34][53] = board[33][54] = board[34][54] = true;
    }

    void pulsar()
    {
        board[15][13] = board[16][13] = board[17][13] = board[21][13] = board[22][13] = board[23][13] = board[13][15] = board[18][15] = board[20][15] = board[25][15] = board[13][16] = board[18][16] = board[20][16] = board[25][16] = board[13][17] = board[18][17] = board[20][17] = board[25][17] = board[15][18] = board[16][18] = board[17][18] = board[21][18] = board[22][18] = board[23][18] = board[15][20] = board[16][20] = board[17][20] = board[21][20] = board[22][20] = board[23][20] = board[13][21] = board[18][21] = board[20][21] = board[25][21] = board[13][22] = board[18][22] = board[20][22] = board[25][22] = board[13][23] = board[18][23] = board[20][23] = board[25][23] = board[15][25] = board[16][25] = board[17][25] = board[21][25] = board[22][25] = board[23][25] = true;
    }

    void pentadecathlon()
    {
        board[11][12] = board[12][12] = board[14][12] = board[15][12] = board[16][12] = board[17][12] = board[19][12] = board[20][12] = board[13][11] = board[13][13] = board[18][11] = board[18][13] = true;
    }

    bool displayMenu()
    {
        int choice;
        cout << "\n\t\tSelect\n\t\t\t0 - Place Life Mannually\n\t\t\t1 - Gosper Glider Gun\n\t\t\t2 - Simkin Glider Gun\n\t\t\t3 - Pulsar\n\t\t\t4 - Pentadecathlon\n\t\t\t5 - Exit\n\t\tEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 0:
            placeLifeManually();
            break;
        case 1:
            gosperGliderGun();
            break;
        case 2:
            simkinGliderGun();
            break;
        case 3:
            pulsar();
            break;
        case 4:
            pentadecathlon();
            break;
        default:
            return true;
        }

        return false;
    }
};

class GenerateLife : virtual protected Board
{
protected:
    int **findAliveNeighbour()
    {
        int **alive_neighbour = new int *[row]();

        for (int i = 1; i <= row; i++)
        {
            alive_neighbour[i - 1] = new int[col]();

            for (int j = 1; j <= col; j++)
            {
                alive_neighbour[i - 1][j - 1] = 0;
                if (board[i - 1][j - 1])
                    alive_neighbour[i - 1][j - 1]++;
                if (board[i - 1][j])
                    alive_neighbour[i - 1][j - 1]++;
                if (board[i - 1][j + 1])
                    alive_neighbour[i - 1][j - 1]++;
                if (board[i][j - 1])
                    alive_neighbour[i - 1][j - 1]++;
                if (board[i][j + 1])
                    alive_neighbour[i - 1][j - 1]++;
                if (board[i + 1][j - 1])
                    alive_neighbour[i - 1][j - 1]++;
                if (board[i + 1][j])
                    alive_neighbour[i - 1][j - 1]++;
                if (board[i + 1][j + 1])
                    alive_neighbour[i - 1][j - 1]++;
            }
        }
        return alive_neighbour;
    }

    void generateLife()
    {
        int **alive_neighbour = findAliveNeighbour();

        for (int i = 1; i <= row; i++)
            for (int j = 1; j <= col; j++)
                if (!board[i][j] && alive_neighbour[i - 1][j - 1] == 3)
                    board[i][j] = true;
                else if (board[i][j] && (alive_neighbour[i - 1][j - 1] < 2 || alive_neighbour[i - 1][j - 1] > 3))
                    board[i][j] = false;

        for (int i = 0; i < row; i++)
            delete[] alive_neighbour[i];
        delete[] alive_neighbour;
    }
};

class PlayGame : protected InputLife, protected GenerateLife
{
public:
    PlayGame(int row, int col) : Board(row, col)
    {
        while (true)
        {
            cleanBoard();
            SetConsoleTextAttribute(console, 245);
            system("cls");

            cout << "\n\n\t\tWelcome to Game of Life!!\n";
            if (displayMenu())
                break;

            int gen;
            cout << "\n\t\tEnter no. of generation you want to observe: ";
            cin >> gen;

            printBoard(0);

            for (int i = 1; i <= gen; i++)
            {
                generateLife();
                findAliveNeighbour();

                printBoard(i);
                Sleep(60);
            }

            Sleep(2000);
        }

        cout << "\n\t\tThanks for playing!!\n";
        Sleep(2000);
    }
};

int main()
{
    PlayGame game_of_life(50, 75);
    return 0;
}
