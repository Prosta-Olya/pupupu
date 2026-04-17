// билет 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <iostream>

int arr[10] = { 0 }; // массив из 10 элементов, заполненный нулями
HANDLE semaphore; // дескриптор семафора
int filledCount = 0; // счётчик заполненных элементов

// заполняет массив по одному элементу каждые 500 мс и сигнализирует семафору
DWORD WINAPI FillArray(LPVOID) {
    for (int i = 0; i < 10; i++) {
        Sleep(500);  // ждём 500 миллисекунд
        arr[i] = i + 1; // заполняем элемент (значения 1,2,3...10)
        filledCount++;  // увеличиваем счётчик заполненных элементов
        ReleaseSemaphore(semaphore, 1, NULL); // сигнализируем семафору
    }
    return 0;
}

// ждёт сигнала семафора и выводит только заполненные элементы
DWORD WINAPI DisplayArray(LPVOID) {
    for (int i = 0; i < 10; i++) {
        WaitForSingleObject(semaphore, INFINITE); // ждём сигнал семафора
        system("cls"); // очищаем экран
        for (int j = 0; j < filledCount; j++)  // выводим только заполненные
            std::cout << arr[j] << " ";
        std::cout << std::endl;
    }
    return 0;
}

int main() {

    // создаем потоки и семафор
    semaphore = CreateSemaphore(NULL, 0, 10, NULL);

    HANDLE h1 = CreateThread(NULL, 0, FillArray, NULL, 0, NULL);
    HANDLE h2 = CreateThread(NULL, 0, DisplayArray, NULL, 0, NULL);

    // ждем, пока оба потока завершатся
    WaitForSingleObject(h1, INFINITE);
    WaitForSingleObject(h2, INFINITE);

    // освобождаем память, занятую потоками и семафором
    CloseHandle(h1);
    CloseHandle(h2);
    CloseHandle(semaphore);

    return 0;
}

