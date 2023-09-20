#include <iostream>
#include <cstdlib> // Для использования системных вызовов
#include <string>
#include <limits>

using namespace std;

const int MAX_PIPES = 100;       // Максимальное количество труб
const int MAX_STATIONS = 100;    // Максимальное количество компрессорных станций

// Структура для представления трубы
struct Pipe {
    string name;
    double length;
    int diameter;
    bool under_repair;

    // Метод для ввода данных о трубе
    void read() {
        cout << "Введите название трубы: ";
        cin >> name;

        cout << "Введите длину трубы (в км): ";
        while (!(cin >> length) || length <= 0) {
            cerr << "Ошибка: Введите корректное значение для длины трубы (в км): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Введите диаметр трубы: ";
        while (!(cin >> diameter) || diameter <= 0) {
            cerr << "Ошибка: Введите корректное значение для диаметра трубы: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        under_repair = false;
    }

    // Метод для отображения данных о трубе
    void display() const {
        cout << "Название: " << name << endl;
        cout << "Длина (км): " << length << endl;
        cout << "Диаметр: " << diameter << endl;
        cout << "На ремонте: " << (under_repair ? "Да" : "Нет") << endl;
    }

    // Метод для переключения состояния ремонта
    void toggle_repair() {
        under_repair = !under_repair;
    }
};

// Структура для представления компрессорной станции
struct Compressor_Station {
    string name;
    int num_workshops;
    int num_workshops_in_operation;
    double efficiency;

    // Метод для ввода данных о компрессорной станции
    void read() {
        cout << "Введите название компрессорной станции: ";
        cin >> name;

        cout << "Введите количество цехов: ";
        while (!(cin >> num_workshops) || num_workshops <= 0) {
            cerr << "Ошибка: Введите корректное значение для количества цехов: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Введите количество работающих цехов: ";
        while (!(cin >> num_workshops_in_operation) || num_workshops_in_operation < 0 || num_workshops_in_operation > num_workshops) {
            cerr << "Ошибка: Введите корректное значение для количества работающих цехов: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Введите эффективность от 0 до 100: ";
        while (!(cin >> efficiency) || efficiency < 0 || efficiency > 100) {
            cerr << "Ошибка: Введите корректное значение эффективности от 0 до 100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Метод для отображения данных о компрессорной станции
    void display() const {
        cout << "Название: " << name << endl;
        cout << "Количество цехов: " << num_workshops << endl;
        cout << "Количество работающих цехов: " << num_workshops_in_operation << endl;
        cout << "Эффективность: " << efficiency << endl;
    }
    
    // Метод для редактирования данных о компрессорной станции
    void editing_compressor_station() {
        cout << "Введите новое количество работающих цехов: ";
        while (!(cin >> num_workshops_in_operation) || num_workshops_in_operation < 0 || num_workshops_in_operation > num_workshops) {
            cerr << "Ошибка: Введите корректное значение для количества работающих цехов: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        cout << "Введите новую эффективность: ";
        while (!(cin >> efficiency) || efficiency < 0 || efficiency > 100) {
            cerr << "Ошибка: Введите корректное значение эффективности от 0 до 100: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
};

int main() {
    Pipe pipes[MAX_PIPES];
    Compressor_Station stations[MAX_STATIONS];
    int pipe_count = 0;
    int station_count = 0;

    while (true) {
        cout << "Меню:\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить компрессорную станцию\n";
        cout << "3. Просмотреть все объекты\n";
        cout << "4. Редактировать трубу\n";
        cout << "5. Редактировать компрессорную станцию\n";
        cout << "6. Сохранить\n";
        cout << "7. Загрузить\n";
        cout << "0. Выход\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 0:
                exit(0); // Выход из программы
                break;
            case 1:{
                if (pipe_count < MAX_PIPES) {
                    pipes[pipe_count].read(); // Ввод данных о трубе
                    ++pipe_count;
                } else {
                    cerr << "Достигнуто максимальное количество труб!" << endl;
                }
                break;
            }
            case 2:{
                if (station_count < MAX_STATIONS) {
                    stations[station_count].read(); // Ввод данных о компрессорной станции
                    ++station_count;
                } else {
                    cerr << "Достигнуто максимальное количество компрессорных станций!" << endl;
                }
                break;
            }
            case 3:{
                cout << "Трубы:\n";
                for (int i = 0; i < pipe_count; ++i) {
                    pipes[i].display(); // Отображение данных о трубе
                    cout << endl;
                }
                cout << "Компрессорные станции:\n";
                for (int i = 0; i < station_count; ++i) {
                    stations[i].display(); // Отображение данных о компрессорной станции
                    cout << endl;
                }
                break;
            }
            case 4:{
                string pipe_name;
                cout << "Введите название трубы для редактирования: ";
                cin >> pipe_name;
                for (int i = 0; i < pipe_count; ++i) {
                    if (pipes[i].name == pipe_name) {
                        pipes[i].toggle_repair(); // Переключение состояния ремонта трубы
                        cout << "Состояние трубы '" << pipes[i].name << "' изменено 'На ремонте: " << (pipes[i].under_repair ? "Да" : "Нет") << "'\n";
                        break;
                    }
                }
                break;
            }
            case 5:{
                string station_name;
                cout << "Введите название компрессорной станции для редактирования: ";
                cin >> station_name;
                for (int i = 0; i < station_count; ++i) {
                    if (stations[i].name == station_name) {
                        stations[i].editing_compressor_station(); // Редактирование данных о компрессорной станции
                        break;
                    }
                }
                break;
            }
            case 6:{
                // Добавить код для сохранения данных
                break;
            }
            case 7:{
                // Добавить код для загрузки данных
                break;
            }
            default:{
                cerr << "Неверный выбор. Попробуйте снова.\n";
                break;
            }
        }
        system("pause"); // Пауза для ожидания нажатия клавиши перед очисткой экрана
        system("clear"); // Очистка экрана в Linux/macOS (используйте "cls" для Windows)
    }

    return 0;
}
