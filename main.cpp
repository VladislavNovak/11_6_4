// Задание 4. Оценка результатов игры в крестики-нолики
// Интересно: Реализован accumulate
#include <iostream>
#include <vector>
#include <string>
#include <numeric> // accumulate

using std::cout;
using std::endl;
using std::vector;
using std::string;

void displayBoard(const vector<vector<char>> &board) {
    cout << "\n\tPLAYER - 1 [X]\t PLAYER - 2 [O]\n" << endl;

    for (int line = 0; line < 3; ++line) {
        cout << "\t\t     |     |     \n\t\t  ";
        for (int cell = 0; cell < 3; ++cell) cout << board[line][cell] << (cell < 2 ? "  |  " : " \n");
        cout << (line < 2 ? "\t\t_____|_____|_____\n" : "\t\t     |     |     \n");
    }
}

void printReport(const vector<int>& result, const vector<int>& charData, int gridNumber, const char TIC, const char TAC) {
    // количество символов для победы
    const int AMOUNT_TO_WIN = 3;
    const int MAX_TIC = 4;
    const int MAX_TAC = 5;
    int ticCount = charData[0];
    int tacCount = charData[1];
    int foundForbiddenSymbols = charData[2];
    // количество заполненных одним символом линий
    int ticLines = 0;
    int tacLines = 0;
    string resultMsg = "Not valid";

    cout << "------- " << (gridNumber + 1) << " -------" << endl;
    // для логирования: раскомментировать
    // for (int res: result) cout << res << endl;
    cout << "number of tic: " << ticCount << endl;
    cout << "number of tac: " << tacCount << endl;

    for (int i = 0; i < result.size(); ++i) {
        int line = result[i];

        char symbol;
        if (line == (TIC * 3)) {
            symbol = TIC;
            ++ticLines;
        } else if (line == (TAC * 3)) {
            symbol = TAC;
            ++tacLines;
        } else {
            symbol = ' ';
        }

        if (symbol == TIC || symbol == TAC) {
            if (i <= 2) cout << "Found row with: " << symbol << endl;
            if (i >= 3 && i <= 5) cout << "Found column with: " << symbol << endl;
            if (i == 6 || i == 7) cout << "Found diagonal with: " << symbol << endl;
        }
    }

    // ошибки типа Error (v...) можно подробнее описать
    if (foundForbiddenSymbols) {
        resultMsg = "Error. Forbidden characters found";
    } else if ((ticCount > MAX_TIC || tacCount > MAX_TAC) || (ticCount > tacCount)) {
        resultMsg = "Error (v1). Wrong number of characters";
    } else if ((tacLines == 0 && ticLines == 0) && (ticCount == MAX_TIC && tacCount == MAX_TAC)) {
        resultMsg = "Draw. Moves are over";
    }  else if ((tacLines == 1 && ticLines == 1) && (tacCount > ticCount)) {
        resultMsg = "Error (v8). Wrong number of characters";
    } else if ((tacLines == 0 && ticLines == 0) && (ticCount + tacCount < 9)) {
        resultMsg = "The game isn't over yet";
    } else if ((tacLines == 1 && ticLines == 0) && (tacCount > AMOUNT_TO_WIN)) {
        resultMsg = "Error (v3). Wrong number of characters";
    } else if ((tacLines == 1 && ticLines == 0) && (tacCount > ticCount)) {
        resultMsg = "First player win (with X)";
    } else if ((tacLines == 1 && ticLines == 0) && (tacCount == ticCount)) {
        resultMsg = "Error (v2). Wrong number of characters";
    } else if ((ticLines == 1 && tacLines == 0) && (ticCount > AMOUNT_TO_WIN)) {
        resultMsg = "Error (v4). Wrong number of characters";
    } else if ((ticLines == 1 && tacLines == 0) && (tacCount == ticCount)) {
        resultMsg = "Second player win (with O)";
    } else if ((ticLines == 1 && tacLines == 1) && (tacCount == ticCount)) {
        resultMsg = "Draw";
    } else if ((ticLines == 1 && tacLines == 0) && (tacCount > AMOUNT_TO_WIN)) {
        resultMsg = "Error (v5). Wrong number of characters";
    }

    cout << "RESULT: " << resultMsg << endl;
}

// подсчитываем количество знаков у TIC, TAC и, если знак запрещен, foundForbiddenSymbols
vector<int> getDataForEachChar(const vector<vector<char>> &grid, const char TIC, const char TAC) {
    int foundTic = 0;
    int foundTac = 0;
    int foundForbiddenSymbols = 0;

    for (const vector<char>& row : grid) {
        for (const char& cell : row) {
            if (cell == TIC) {
                ++foundTic;
            } else if (cell == TAC) {
                ++foundTac;
            } else if (cell != ' ') {
                ++foundForbiddenSymbols;
            }
        }
    }

    return {foundTic, foundTac, foundForbiddenSymbols};
}

// возвращает массив с суммарными данными по строкам, колонкам и диагоналям
vector<int> returnDataForEachLines(const vector<vector<char>> &grid) {
    const int LEFT_DIAGONAL = 6;
    const int RIGHT_DIAGONAL = 7;
    // 0,1,2 - для строк, 3,4,5 - для колонок, 6,7 - для диагоналей
    vector<int> lines = {0, 0, 0, 0, 0, 0, 0, 0};
    size_t gridSize = grid.size();

    for (int i = 0, rowReversed = (int) gridSize - 1; i < gridSize; ++i, --rowReversed) {
        vector<char> row = grid[i];
        size_t rowSize = row.size();

        // сохраняем результат по строкам
        lines[i] = accumulate(row.begin(), row.end(), 0);

        for (int j = 0, start = 3, columnReversed = (int) rowSize - 1; j < rowSize; ++j, ++start, --columnReversed) {
            char cell = row[j];

            // сохраняем результат по столбцам
            lines[start] += cell;

            // результат первой диагонали
            if (i == j) lines[LEFT_DIAGONAL] += cell;

            // результат второй диагонали
            if (rowReversed == columnReversed) lines[RIGHT_DIAGONAL] += row[columnReversed];
        }
    }

    return lines;
}

void checkWinner(const vector<vector<char>> &grid, int gridNumber) {
    const char TIC = 'o'; // 111
    const char TAC = 'x'; // 120

    vector<int> lines = returnDataForEachLines(grid);

    vector<int> charData = getDataForEachChar(grid, TIC, TAC);

    printReport(lines, charData, gridNumber, TIC, TAC);
    displayBoard(grid);
}

int main() {
    vector<vector<vector<char>>> superSet = {
            //            1. Ответ: Nobody (потому что это ничья):
            {       {'x', 'x', 'o'},
                    {'o', 'o', 'x'},
                    {'x', 'o', 'x'}},
            //            2. Incorrect (потому что ноликов в конце игры не может быть больше, чем крестиков):
            {       {'x', ' ', ' '},
                    {'o', 'x', 'o'},
                    {'o', 'o', 'o'}},
            //            3. Nobody (потому что они не доиграли):
            {       {'x', ' ', ' '},
                    {' ', 'x', ' '},
                    {'o', 'o', ' '}},
            //            4. Incorrect (крестики уже победили, и ноликов не может быть столько же)
            {       {'x', 'o', ' '},
                    {'x', 'o', ' '},
                    {'x', ' ', 'o'}},
            //            5. Incorrect (потому что нолики выиграли за три хода, и на поле за это время не могло успеть появиться четыре):
            {       {'o', 'x', ' '},
                    {'x', 'o', 'x'},
                    {'x', ' ', 'o'}},
            //            6. First won
            {       {' ', ' ', 'x'},
                    {'o', 'x', ' '},
                    {'x', ' ', 'o'}},
            //            7. Incorrect (потому что допускаются только символы X, O и точка, а цифра 0 не является допустимым символом):
            {       {'0', ' ', ' '},
                    {' ', ' ', ' '},
                    {' ', ' ', ' '}},
            //            8. Invalid (Both X and O cannot win):
            {       {'o', 'x', 'x'},
                    {'o', 'x', 'x'},
                    {'o', 'o', 'x'}},
    };

    for (int gridNumber = 0; gridNumber < superSet.size(); ++gridNumber) {
        auto grid = superSet[gridNumber];
        checkWinner(grid, gridNumber);
    }
}