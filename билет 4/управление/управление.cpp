// управление.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(1251);

    // Открываем существующие события
    HANDLE event1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Event1");
    HANDLE event2 = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Event2");

    if (!event1 || !event2) {
        cout << "Ошибка: запустите сначала секундомер!" << endl;
        return 1;
    }

    cout << "Управление:" << endl;
    cout << "  Клавиша 1 - показать счетчик" << endl;
    cout << "  Клавиша 2 - пауза/продолжить" << endl;
    cout << "  Esc - выход" << endl;

    while (true) {
        // Проверяем нажатия клавиш
        if (GetAsyncKeyState('1') & 1) {
            cout << "Отправлено событие 1" << endl;
            SetEvent(event1);
            Sleep(300); // Задержка чтобы не спамить
        }

        if (GetAsyncKeyState('2') & 1) {
            cout << "Отправлено событие 2" << endl;
            SetEvent(event2);
            Sleep(300);
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 1) {
            break;
        }

        Sleep(50); // Небольшая задержка
    }

    CloseHandle(event1);
    CloseHandle(event2);
    return 0;
}
