// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(1251); // Для русского текста

    // Создаем 3 именованных события
    HANDLE events[3];
    events[0] = CreateEvent(NULL, TRUE, FALSE, L"Event1");
    events[1] = CreateEvent(NULL, TRUE, FALSE, L"Event2");
    events[2] = CreateEvent(NULL, TRUE, FALSE, L"Event3");

    std::cout << "Ожидание событий (10 секунд)...\n";
    std::cout << "Запустите helper1.exe, helper2.exe или helper3.exe\n\n";

    // Ждем ЛЮБОЕ из событий (таймаут 10000 мс = 10 секунд)
    DWORD result = WaitForMultipleObjects(3, events, FALSE, 10000);

    // Проверяем, какое событие сработало
    if (result == WAIT_OBJECT_0) {
        std::cout << ">>> Событие 1 произошло!\n";
    }
    else if (result == WAIT_OBJECT_0 + 1) {
        std::cout << ">>> Событие 2 произошло!\n";
    }
    else if (result == WAIT_OBJECT_0 + 2) {
        std::cout << ">>> Событие 3 произошло!\n";
    }
    else if (result == WAIT_TIMEOUT) {
        std::cout << ">>> Таймаут! Ни одно событие не произошло.\n";
    }

    // Закрываем события
    for (int i = 0; i < 3; i++) {
        CloseHandle(events[i]);
    }

    system("pause");
    return 0;
}
