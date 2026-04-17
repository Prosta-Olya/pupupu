// билет 7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <iostream>

HANDLE hSemaphore;

DWORD WINAPI Worker(LPVOID param) {
    WaitForSingleObject(hSemaphore, INFINITE);

    long long sum = 0;
    for (int i = 1; i <= 100000000; i++) {
        sum += i;
    }
    std::cout << "Process " << (int)(size_t)param << " finished. Sum: " << sum << std::endl;

    ReleaseSemaphore(hSemaphore, 1, NULL);
    return 0;
}

int main() {
    hSemaphore = CreateSemaphore(NULL, 2, 2, NULL);

    HANDLE hThreads[4];
    for (int i = 0; i < 4; i++) {
        hThreads[i] = CreateThread(NULL, 0, Worker, (LPVOID)(size_t)(i + 1), 0, NULL);
    }

    WaitForMultipleObjects(4, hThreads, TRUE, INFINITE);

    std::cout << "All processes completed. System shutdown." << std::endl;

    CloseHandle(hSemaphore);
    return 0;
}
