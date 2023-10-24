#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Pipe.h"
#include "CompressorStation.h"

using namespace std;

void save_data_pipe(const unordered_map<int, Pipe>& pipes, const string& file_name) {
    ofstream file(file_name);

    if (!file) {
        cerr << "Ошибка открытия файла для записи: " << file_name << endl;
        return;
    }

    for (const auto& pipeEntry : pipes) {
        const Pipe& pipe = pipeEntry.second;
        file << "Трубы\n";
        file << pipe.getId() << "\n";
        file << pipe.getName() << "\n";
        file << pipe.getLength() << "\n";
        file << pipe.getDiameter() << "\n";
        file << pipe.getRepairStatus() << "\n";
    }

    file.close();
}

void save_data_station(const unordered_map<int, CompressorStation>& stations, const string& file_name) {
    ofstream file(file_name, ios::app);

    if (!file) {
        cerr << "Ошибка открытия файла для записи: " << file_name << endl;
        return;
    }

    for (const auto& stationEntry : stations) {
        const CompressorStation& station = stationEntry.second;
        file << "Компрессорные станции\n";
        file << station.getId() << "\n";
        file << station.getName() << "\n";
        file << station.getNumWorkshops() << "\n";
        file << station.getNumWorkshopsInOperation() << "\n";
        file << station.getEfficiency() << "\n";
    }

    file.close();
}

void load_data_pipe(unordered_map<int, Pipe>& pipes, const string& file_name) {
    ifstream file(file_name);

    if (!file) {
        cerr << "Ошибка открытия файла для чтения: " << file_name << endl;
        return;
    }

    pipes.clear();
    string line;

    while (getline(file, line)) {
        if (line == "Трубы") {
            Pipe pipe;
            int id;
            file >> id >> ws;
            pipe.setId(id);
            file >> ws;
            getline(file, line);
            pipe.setName(line);
            double length;
            file >> length;
            pipe.setLength(length);
            int diameter;
            file >> diameter;
            pipe.setDiameter(diameter);
            bool under_repair;
            file >> under_repair;
            pipe.setRepairStatus(under_repair);
            pipes[pipe.getId()] = pipe;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    file.close();
}

void load_data_station(unordered_map<int, CompressorStation>& stations, const string& file_name) {
    ifstream file(file_name);

    if (!file) {
        cerr << "Ошибка открытия файла для чтения: " << file_name << endl;
        return;
    }

    stations.clear();
    string line;

    while (getline(file, line)) {
        if (line == "Компрессорные станции") {
            CompressorStation station;
            int id;
            file >> id >> ws;
            station.setId(id);
            file >> ws;
            getline(file, line);
            station.setName(line);
            int num_workshops, num_workshops_in_operation;
            double efficiency;
            file >> num_workshops >> num_workshops_in_operation >> efficiency;
            station.setNumWorkshops(num_workshops);
            station.setNumWorkshopsInOperation(num_workshops_in_operation);
            station.setEfficiency(efficiency);
            stations[station.getId()] = station;
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    file.close();
}

void editPipes(unordered_map<int, Pipe>& pipes) {
    // Пакетное редактирование труб
    int subChoice;
    cout << "1. Редактировать все найденные трубы\n";
    cout << "2. Редактировать подмножество труб (пользователь указывает ID)\n";
    cout << "3. Отмена\n";
    cout << "Введите цифру от 1 до 3 для выбора действия: ";
    while (!(cin >> subChoice)) {
        cerr << "Ошибка: Введите корректное значение: ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    switch (subChoice) {
        case 1: {
            // Редактировать все найденные трубы
            int pipe_edit_choice;
            cout << "1. Установить в ремонт\n";
            cout << "2. Установить в рабочее состояние\n";
            cout << "3. Отмена\n";
            cout << "Введите цифру от 1 до 3 для выбора действия: ";
            while (!(cin >> pipe_edit_choice)) {
                cerr << "Ошибка: Введите корректное значение: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            switch (pipe_edit_choice) {
                case 1: {
                    // Установить все найденные трубы в ремонт
                    for (auto& pipeEntry : pipes) {
                        Pipe& pipe = pipeEntry.second;
                        pipe.setRepairStatus(true);
                    }
                    cout << "Все найденные трубы установлены в ремонт.\n";
                    break;
                }
                case 2: {
                    // Установить все найденные трубы в рабочее состояние
                    for (auto& pipeEntry : pipes) {
                        Pipe& pipe = pipeEntry.second;
                        pipe.setRepairStatus(false);
                    }
                    cout << "Все найденные трубы установлены в рабочее состояние.\n";
                    break;
                }
                case 3:
                    // Отмена
                    break;
                default:
                    cerr << "Неверный выбор. Попробуйте снова.\n";
                    break;
            }
            break;
        }
        case 2: {
            vector<int> pipesToEdit;
            string editChoice;

            // Запрашиваем ID труб, которые нужно отредактировать
            while (true) {
                int pipeId;
                cout << "Введите ID трубы для редактирования (0 для завершения): ";
                cin >> pipeId;

                if (pipeId == 0) {
                    break;
                }

                auto it = pipes.find(pipeId);
                if (it != pipes.end()) {
                    pipesToEdit.push_back(pipeId);
                } else {
                    cerr << "Труба с ID " << pipeId << " не найдена.\n";
                }
            }

            if (pipesToEdit.empty()) {
                cout << "Нет труб для редактирования.\n";
                return;
            }

            // Выводим информацию о выбранных трубах
            cout << "Выбранные трубы для редактирования:\n";
            for (int id : pipesToEdit) {
                cout << "ID: " << id << " - ";
                pipes[id].display();
            }

            // Предлагаем редактировать или удалить выбранные трубы
            cout << "Вы хотите редактировать (E) или удалить (D) выбранные трубы (E/D)? ";
            cin >> editChoice;

            if (editChoice == "E" || editChoice == "e") {
                // Редактирование выбранных труб
                for (int id : pipesToEdit) {
                    Pipe& pipe = pipes[id];
                    pipe.toggle_repair();
                    cout << "Состояние трубы с ID " << id << " изменено 'На ремонте: " << (pipe.getRepairStatus() ? "Да" : "Нет") << "'\n";
                }
            } else if (editChoice == "D" || editChoice == "d") {
                // Удаление выбранных труб
                for (int id : pipesToEdit) {
                    pipes.erase(id);
                    cout << "Труба с ID " << id << " удалена.\n";
                }
            }
            break;
        }
        case 3:
            // Отмена
            break;
        default:
            cerr << "Неверный выбор. Попробуйте снова.\n";
            break;
    }
}

int main() {
    unordered_map<int, Pipe> pipes;
    unordered_map<int, CompressorStation> stations;
    int nextPipeId = 1; // Используем переменную для следующего доступного id для труб
    int nextStationId = 1; // Используем переменную для следующего доступного id для станций


    while (true) {
        cout << "Меню:\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить компрессорную станцию\n";
        cout << "3. Просмотреть все объекты\n";
        cout << "4. Редактировать трубу\n";
        cout << "5. Редактировать компрессорную станцию\n";
        cout << "6. Удалить трубу\n";
        cout << "7. Удалить компрессорную станцию\n";
        cout << "8. Сохранить\n";
        cout << "9. Загрузить\n";
        cout << "10. Поиск труб по названию\n";
        cout << "11. Поиск труб по статусу ремонта\n";
        cout << "12. Поиск КС по названию\n";
        cout << "13. Поиск КС по проценту незадействованных цехов\n";
        cout << "14. Пакетное редактирование труб\n";
        cout << "0. Выход\n";

        int choice;
        cout << "\nВведите цифру от 0 до 14, которая соответствует дальнейшему вашему действию: \n";
        while (!(cin >> choice)) {
            cerr << "Ошибка: Введите корректное значение: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
            case 0:
                exit(0);
                break;
            case 1: {
                Pipe pipe;
                pipe.read();
                pipe.setId(nextPipeId);
                pipes[nextPipeId] = pipe;
                nextPipeId++; // Увеличиваем id для следующей трубы
                break;
            }
            case 2: {
                CompressorStation station;
                station.read();
                station.setId(nextStationId);
                stations[nextStationId] = station;
                nextStationId++; // Увеличиваем id для следующей станции
                break;
            }
            case 3: {
                cout << "Трубы:\n";
                for (const auto& pipeEntry : pipes) {
                    const Pipe& pipe = pipeEntry.second;
                    pipe.display();
                    cout << endl;
                }
                cout << "Компрессорные станции:\n";
                for (const auto& stationEntry : stations) {
                    const CompressorStation& station = stationEntry.second;
                    station.display();
                    cout << endl;
                }
                break;
            }
            case 4: {
                int pipe_id;
                cout << "Введите ID трубы для редактирования: ";
                while (!(cin >> pipe_id) || pipes.find(pipe_id) == pipes.end()) {
                    cerr << "Ошибка: Введите существующий ID трубы: ";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                Pipe& pipe = pipes[pipe_id];
                pipe.toggle_repair();
                cout << "Состояние трубы с ID " << pipe_id << " изменено 'На ремонте: " << (pipe.getRepairStatus() ? "Да" : "Нет") << "'\n";
                break;
            }
            case 5: {
                int station_id;
                cout << "Введите ID компрессорной станции для редактирования: ";
                while (!(cin >> station_id) || stations.find(station_id) == stations.end()) {
                    cerr << "Ошибка: Введите существующий ID компрессорной станции: ";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                CompressorStation& station = stations[station_id];
                station.edit();
                break;
            }
            case 6: {
                int pipe_id;
                cout << "Введите ID трубы для удаления: ";
                while (!(cin >> pipe_id) || pipes.find(pipe_id) == pipes.end()) {
                    cerr << "Ошибка: Введите существующий ID трубы: ";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                pipes.erase(pipe_id);
                cout << "Труба с ID " << pipe_id << " удалена.\n";
                break;
            }
            case 7: {
                int station_id;
                cout << "Введите ID компрессорной станции для удаления: ";
                while (!(cin >> station_id) || stations.find(station_id) == stations.end()) {
                    cerr << "Ошибка: Введите существующий ID компрессорной станции: ";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                stations.erase(station_id);
                cout << "Компрессорная станция с ID " << station_id << " удалена.\n";
                break;
            }
            case 8: {
                string file_name;
                cout << "Введите имя файла для сохранения ('имя файла.txt'): ";
                cin >> file_name;
                save_data_pipe(pipes, file_name);
                save_data_station(stations, file_name);
                cout << "Данные сохранены в файл: " << file_name << endl;
                break;
            }
            case 9: {
                string load_file_name;
                cout << "Введите имя файла для загрузки ('имя файла.txt'): ";
                cin >> load_file_name;
                load_data_pipe(pipes, load_file_name);
                load_data_station(stations, load_file_name);
                cout << "Данные загружены из файла: " << load_file_name << endl;
                break;
            }
            case 10: {
                // Поиск труб по названию
                string searchName;
                cout << "Введите название трубы для поиска: ";
                cin >> searchName;
                for (const auto& pipeEntry : pipes) {
                    const Pipe& pipe = pipeEntry.second;
                    if (pipe.getName() == searchName) {
                        cout << "Результат поиска:\n";
                        pipe.display();
                        cout << endl;
                    }
                }
                break;
            }
            case 11: {
                // Поиск труб по статусу ремонта
                bool searchRepairStatus;
                cout << "Введите статус ремонта (1 - на ремонте, 0 - не на ремонте): ";
                cin >> searchRepairStatus;
                for (const auto& pipeEntry : pipes) {
                    const Pipe& pipe = pipeEntry.second;
                    if (pipe.getRepairStatus() == searchRepairStatus) {
                        cout << "Результат поиска:\n";
                        pipe.display();
                        cout << endl;
                    }
                }
                break;
            }
            case 12: {
                // Поиск КС по названию
                string searchName;
                cout << "Введите название компрессорной станции для поиска: ";
                cin >> searchName;
                for (const auto& stationEntry : stations) {
                    const CompressorStation& station = stationEntry.second;
                    if (station.getName() == searchName) {
                        cout << "Результат поиска:\n";
                        station.display();
                        cout << endl;
                    }
                }
                break;
            }
            case 13: {
                // Поиск КС по проценту незадействованных цехов
                double searchUnutilizedPercentage;
                cout << "Введите процент незадействованных цехов для поиска: ";
                cin >> searchUnutilizedPercentage;
                for (const auto& stationEntry : stations) {
                    const CompressorStation& station = stationEntry.second;
                    double unutilizedPercentage = (static_cast<double>(station.getNumWorkshops() - station.getNumWorkshopsInOperation()) / station.getNumWorkshops()) * 100.0;
                    if (unutilizedPercentage >= searchUnutilizedPercentage) {
                        cout << "Результат поиска:\n";
                        station.display();
                        cout << endl;
                    }
                }
                break;
            }
            case 14: {
                // Пакетное редактирование труб
                editPipes(pipes);
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
