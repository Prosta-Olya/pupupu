// билет 9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

int arr[10];  // Глобальный массив
CRITICAL_SECTION cs;  // Критическая секция для синхронизации потоков

// Функция для первого потока: отрицательные → 0
DWORD WINAPI func1(LPVOID param) {
    for (int i = 0; i < 10; i++) {
        EnterCriticalSection(&cs);  // Вход в критическую секцию (блокируем доступ другому потоку)
        if (arr[i] < 0)
            arr[i] = 0;
        LeaveCriticalSection(&cs);  // Выход из критической секции
    }
    return 0;
}

// Функция для второго потока: чётные → -200
DWORD WINAPI func2(LPVOID param) {
    for (int i = 0; i < 10; i++) {
        EnterCriticalSection(&cs);  // Вход в критическую секцию
        if (arr[i] % 2 == 0 && arr[i] != 0)  // Добавили проверку arr[i] != 0
            arr[i] = -200;
        LeaveCriticalSection(&cs);  // Выход из критической секции
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    // Инициализируем критическую секцию перед использованием
    InitializeCriticalSection(&cs);

    // Заполняем массив случайными числами от -150 до 150
    std::cout << "Исходный массив: ";
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 301 - 150;  // rand()%301 даёт 0-300, -150 сдвигает в -150-150
        std::cout << arr[i] << " ";
    }
    std::cout << "\n\n";

    // Создаём и запускаем первый поток
    HANDLE h1 = CreateThread(NULL, 0, func1, NULL, 0, NULL);
    WaitForSingleObject(h1, INFINITE);  // Ждём завершения первого потока
    CloseHandle(h1);  // Закрываем дескриптор первого потока

    // Создаём и запускаем второй поток
    HANDLE h2 = CreateThread(NULL, 0, func2, NULL, 0, NULL);
    WaitForSingleObject(h2, INFINITE);  // Ждём завершения второго потока
    CloseHandle(h2);  // Закрываем дескриптор второго потока

    // Выводим результат
    std::cout << "После обработки: ";
    for (int i = 0; i < 10; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    // Удаляем критическую секцию (освобождаем ресурсы)
    DeleteCriticalSection(&cs);

    return 0;
}
