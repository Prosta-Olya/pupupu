// билет 8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int* sumRows(int** matrix, int rows, int cols) {
    int* sums = new int[rows];
    for (int i = 0; i < rows; i++) {
        sums[i] = 0;
        for (int j = 0; j < cols; j++)
            sums[i] += matrix[i][j];
    }
    return sums;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    int n, m;
    cout << "Введите количество строк: ";
    cin >> n;
    cout << "Введите количество столбцов: ";
    cin >> m;

    // Создание матрицы (указатель на указатель)
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[m];

    // Заполнение случайными числами
    cout << "\nМатрица:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 10;
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Получение сумм строк
    int* rowSums = sumRows(matrix, n, m);

    cout << "\nСуммы строк:\n";
    for (int i = 0; i < n; i++)
        cout << "Строка " << i << ": " << rowSums[i] << endl;

    // Освобождение памяти
    delete[] rowSums;
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}
