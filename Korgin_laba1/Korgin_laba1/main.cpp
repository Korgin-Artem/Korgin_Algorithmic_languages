#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Константы для максимальных значений объектов
const int MAX_LIMITS = 1000; // Максимальное количество игнорируемых пустых строк

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
            cin.ignore(MAX_LIMITS, '\n');
        }

        cout << "Введите диаметр трубы: ";
        while (!(cin >> diameter) || diameter <= 0) {
            cerr << "Ошибка: Введите корректное значение для диаметра трубы: ";
            cin.clear();
            cin.ignore(MAX_LIMITS, '\n');
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
            cin.ignore(MAX_LIMITS, '\n');
        }

        cout << "Введите количество работающих цехов: ";
        while (!(cin >> num_workshops_in_operation) || num_workshops_in_operation < 0 || num_workshops_in_operation > num_workshops) {
            cerr << "Ошибка: Введите корректное значение для количества работающих цехов: ";
            cin.clear();
            cin.ignore(MAX_LIMITS, '\n');
        }

        cout << "Введите эффективность от 0 до 100: ";
        while (!(cin >> efficiency) || efficiency < 0 || efficiency > 100) {
            cerr << "Ошибка: Введите корректное значение эффективности от 0 до 100: ";
            cin.clear();
            cin.ignore(MAX_LIMITS, '\n');
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
            cin.ignore(MAX_LIMITS, '\n');
        }

        cout << "Введите новую эффективность: ";
        while (!(cin >> efficiency) || efficiency < 0 || efficiency > 100) {
            cerr << "Ошибка: Введите корректное значение эффективности от 0 до 100: ";
            cin.clear();
            cin.ignore(MAX_LIMITS, '\n');
        }
    }
};

// Функция для сохранения данных труб в файл
void save_data_pipe(const vector<Pipe>& pipes, const string& file_name) {
    ofstream file(file_name);

    if (!file) {
        cerr << "Ошибка открытия файла для записи: " << file_name << endl;
        return;
    }

    // Сохраняем информацию о трубах
    for (const Pipe& pipe : pipes) {
        file << "Трубы\n";
        file << pipe.name << "\n";
        file << pipe.length << "\n";
        file << pipe.diameter << "\n";
        file << pipe.under_repair << "\n"; // Записываем значение bool напрямую
    }

    file.close();
}

// Функция для сохранения данных компрессорных станций в файл
void save_data_station(const vector<Compressor_Station>& stations, const string& file_name) {
    ofstream file(file_name, ios::app);

    if (!file) {
        cerr << "Ошибка открытия файла для записи: " << file_name << endl;
        return;
    }

    // Сохраняем информацию о компрессорных станциях
    for (const Compressor_Station& station : stations) {
        file << "Компрессорные станции\n";
        file << station.name << "\n";
        file << station.num_workshops << "\n";
        file << station.num_workshops_in_operation << "\n";
        file << station.efficiency << "\n";
    }

    file.close();
}

// Функция для загрузки данных труб из файла
void load_data_pipe(vector<Pipe>& pipes, const string& file_name) {
    ifstream file(file_name);

    if (!file) {
        cerr << "Ошибка открытия файла для чтения: " << file_name << endl;
        return;
    }

    // Очищаем существующие данные
    pipes.clear();
    string line;

    while (getline(file, line)) {
        if (line == "Трубы") {
            Pipe pipe;
            file >> pipe.name >> pipe.length >> pipe.diameter >> pipe.under_repair;
            pipes.push_back(pipe);
            file.ignore(MAX_LIMITS, '\n'); // Пропускаем пустую строку
        }
    }

    file.close();
}

// Функция для загрузки данных компрессорной станции из файла
void load_data_station(vector<Compressor_Station>& stations, const string& file_name) {
    ifstream file(file_name);

    if (!file) {
        cerr << "Ошибка открытия файла для чтения: " << file_name << endl;
        return;
    }

    // Очищаем существующие данные
    stations.clear();
    string line;

    while (getline(file, line)) {
        if (line == "Компрессорные станции") {
            Compressor_Station station;
            file >> station.name >> station.num_workshops >> station.num_workshops_in_operation >> station.efficiency;
            stations.push_back(station);
            file.ignore(MAX_LIMITS, '\n'); // Пропускаем пустую строку
        }
    }

    file.close();
}

int main() {
    vector<Pipe> pipes;
    vector<Compressor_Station> stations;

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
        cout << "\nВведите цифру от 0 до 7, которая соответствует дальнейшему вашему действию: \n";
        while (!(cin >> choice)) {
            cerr << "Ошибка: Введите корректное значение: ";
            cin.clear();
            cin.ignore(MAX_LIMITS, '\n');
        }

        switch (choice) {
            case 0:
                exit(0); // Выход из программы
                break;
            case 1: {
                Pipe pipe;
                pipe.read();
                pipes.push_back(pipe); // Добавляем трубу в вектор
                break;
            }
            case 2: {
                Compressor_Station station;
                station.read();
                stations.push_back(station); // Добавляем компрессорную станцию в вектор
                break;
            }
            case 3: {
                cout << "Трубы:\n";
                for (const Pipe& pipe : pipes) {
                    pipe.display();
                    cout << endl;
                }
                cout << "Компрессорные станции:\n";
                for (const Compressor_Station& station : stations) {
                    station.display();
                    cout << endl;
                }
                break;
            }
            case 4: {
                string pipe_name;
                cout << "Введите название трубы для редактирования: ";
                cin >> pipe_name;
                bool found = false;
                for (Pipe& pipe : pipes) {
                    if (pipe.name == pipe_name) {
                        pipe.toggle_repair();
                        cout << "Состояние трубы '" << pipe.name << "' изменено 'На ремонте: " << (pipe.under_repair ? "Да" : "Нет") << "'\n";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cerr << "Труба с указанным названием не найдена. Попробуйте еще раз или создайте трубу с этим названием.\n";
                }
                break;
            }
            case 5: {
                string station_name;
                cout << "Введите название компрессорной станции для редактирования: ";
                cin >> station_name;
                bool found = false;
                for (Compressor_Station& station : stations) {
                    if (station.name == station_name) {
                        station.editing_compressor_station();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cerr << "Компрессорная станция с указанным названием не найдена. Попробуйте еще раз или создайте станцию с этим названием.\n";
                }
                break;
            }
            case 6: {
                string file_name;
                cout << "Введите имя файла для сохранения ('имя файла.txt'): ";
                cin >> file_name;
                save_data_pipe(pipes, file_name);
                save_data_station(stations, file_name);
                cout << "Данные сохранены в файл: " << file_name << endl;
                break;
            }
            case 7: {
                string load_file_name;
                cout << "Введите имя файла для загрузки ('имя файла.txt'): ";
                cin >> load_file_name;
                load_data_pipe(pipes, load_file_name);
                load_data_station(stations, load_file_name);
                cout << "Данные загружены из файла: " << load_file_name << endl;
                break;
            }
            default: {
                cerr << "Неверный выбор. Попробуйте снова.\n";
                break;
            }
        }
    }

    return 0;
}
