// билет 3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    const wchar_t* SEM_NAME = L"Global\\MySuperSem"; // Уникальное имя семафора

    // --- ЧАСТЬ 1: ИСПОЛНИТЕЛЬ (Child Process) ---
    // Если программа запущена с аргументом "worker"
    if (argc > 1 && string(argv[1]) == "worker") {

        // 1. Открываем семафор, созданный диспетчером
        HANDLE hSem = OpenSemaphore(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, FALSE, SEM_NAME);

        if (hSem) {
            // 2. Ждем доступ (уменьшаем счетчик семафора)
            WaitForSingleObject(hSem, INFINITE);

            // 3. Работаем (спим 4 секунды)
            cout << "Исполнитель: Работаю 4 секунды..." << endl;
            Sleep(4000);

            // 4. Освобождаем семафор (увеличиваем счетчик)
            ReleaseSemaphore(hSem, 1, NULL);
            CloseHandle(hSem);
        }
        return 0; // Завершаем процесс исполнителя
    }

    // --- ЧАСТЬ 2: ДИСПЕТЧЕР (Parent Process) ---

    // 1. Создаем именованный семафор (Максимум 3, Текущий 3)
    HANDLE hSem = CreateSemaphore(NULL, 3, 3, SEM_NAME);
    if (!hSem) {
        cout << "Ошибка создания семафора" << endl;
        return 1;
    }

    HANDLE hProcesses[6]; // Массив для хранения хендлов процессов
    wchar_t path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH); // Получаем путь к самому себе

    // 2. Запускаем 6 дочерних процессов
    for (int i = 0; i < 6; i++) {
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        // Формируем команду запуска: "путь_к_программе worker"
        wstring cmdLine = wstring(path) + L" worker";

        if (CreateProcess(NULL, (LPWSTR)cmdLine.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            hProcesses[i] = pi.hProcess; // Сохраняем хендл процесса
            CloseHandle(pi.hThread);     // Хендл потока нам не нужен, закрываем сразу
            cout << "Диспетчер: Запущен процесс " << i + 1 << endl;
        }
    }

    // 3. Ждем завершения ВСЕХ 6 процессов
    WaitForMultipleObjects(6, hProcesses, TRUE, INFINITE);

    // 4. Выводим сообщения о завершении и чистим память
    for (int i = 0; i < 6; i++) {
        cout << "Диспетчер: Процесс " << i + 1 << " завершил работу." << endl;
        CloseHandle(hProcesses[i]);
    }

    // 5. Закрываем семафор
    CloseHandle(hSem);

    return 0;
}
