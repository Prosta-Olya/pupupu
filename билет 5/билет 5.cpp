// билет 5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>

int main() {
    // Устанавливаем кодировку для корректного вывода кириллицы в консоли
    system("chcp 65001 > nul");

    // 1. Имя семафора. Оно должно быть уникальным.
    const wchar_t* SEM_NAME = L"MySuperUniqueSemaphoreVariant5";

    // 2. Создаем или открываем именованный семафор.
    // 2-й аргумент (2) - начальное значение (сколько мест свободно).
    // 3-й аргумент (2) - максимальное значение.
    HANDLE hSemaphore = CreateSemaphore(NULL, 2, 2, SEM_NAME);

    if (hSemaphore == NULL) {
        std::wcout << L"Ошибка создания семафора!" << std::endl;
        return 1;
    }

    // 3. Пытаемся захватить семафор БЕЗ ожидания (таймаут 0).
    // Если успешно - уменьшаем счетчик на 1.
    DWORD waitResult = WaitForSingleObject(hSemaphore, 0);

    if (waitResult == WAIT_OBJECT_0) {
        // УСПЕХ: Мы получили доступ (свободно было 1 или 2 места)
        std::wcout << L"Программа запущена успешно. Семафор захвачен." << std::endl;
        std::wcout << L"Работаю... Нажмите Enter для выхода." << std::endl;

        // Имитация работы программы
        std::cin.get();

        // 4. При выходе освобождаем семафор (увеличиваем счетчик на 1)
        ReleaseSemaphore(hSemaphore, 1, NULL);
        std::wcout << L"Семафор освобожден." << std::endl;
    }
    else {
        // ПРОВАЛ: Счетчик был 0 (уже работают 2 программы)
        std::wcout << L"ОШИБКА: Превышено допустимое количество копий (2)!" << std::endl;
    }

    // Закрываем дескриптор
    CloseHandle(hSemaphore);
    return 0;
}
