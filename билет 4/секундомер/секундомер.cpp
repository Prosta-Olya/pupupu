// секундомер.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(1251); // Для русского текста

    // Создаем два именованных события
    HANDLE event1 = CreateEvent(NULL, FALSE, FALSE, L"Event1"); // Показать счет
    HANDLE event2 = CreateEvent(NULL, FALSE, FALSE, L"Event2"); // Пауза/старт

    int counter = 0;        // Счетчик секунд
    bool paused = false;    // Флаг паузы

    cout << "Секундомер запущен (нажмите Ctrl+C для выхода)" << endl;

    while (true) {
        // Проверяем события (ждем 1 секунду)
        DWORD result = WaitForMultipleObjects(2, &event1, FALSE, 1000);

        if (result == WAIT_OBJECT_0) {
            // Первое событие - вывести текущее значение
            cout << "Текущий счетчик: " << counter << endl;
        }
        else if (result == WAIT_OBJECT_0 + 1) {
            // Второе событие - пауза/продолжить
            paused = !paused;
            if (paused)
                cout << "Пауза" << endl;
            else
                cout << "Продолжить" << endl;
        }

        // Увеличиваем счетчик каждую секунду (если не на паузе)
        if (!paused) {
            counter++;
        }
    }

    CloseHandle(event1);
    CloseHandle(event2);
    return 0;
}

