// helper1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(1251);

    // Открываем существующее событие
    HANDLE event = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Event1");

    if (event) {
        std::cout << "Активация события 1...\n";
        SetEvent(event);  // Сигнализируем событие
        CloseHandle(event);
    }
    else {
        std::cout << "Событие не найдено! Запустите сначала main.exe\n";
    }

    system("pause");
    return 0;
}
