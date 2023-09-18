#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_PIPES = 100;  // Максимальное количество труб
const int MAX_STATIONS = 100;  // Максимальное количество компрессорных станций

struct Pipe {
    string name;
    double length;
    int diameter;
    bool under_repair;

    void read() {
        cout << "Enter the name of the pipe: ";
        cin >> name;
        cout << "Enter the length of the pipe (in km): ";
        cin >> length;
        cout << "Enter the pipe diameter: ";
        cin >> diameter;
        under_repair = false;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Length (km): " << length << endl;
        cout << "Diameter: " << diameter << endl;
        cout << "Under repair: " << (under_repair ? "Yes" : "No") << endl;
    }

    void toggle_repair() {
        under_repair = !under_repair;
    }
};

struct Compressor_Station {
    string name;
    int num_workshops;
    int num_workshops_in_operation;
    string efficiency;

    void read() {
        cout << "Enter the name of the compressor station: ";
        cin >> name;
        cout << "Enter the number of workshops: ";
        cin >> num_workshops;
        cout << "Enter the number of workshops in operation: ";
        cin >> num_workshops_in_operation;
        cout << "Enter efficiency: ";
        cin >> efficiency;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Number of workshops: " << num_workshops << endl;
        cout << "Number of workshops in operation: " << num_workshops_in_operation << endl;
        cout << "Efficiency: " << efficiency << endl;
    }
};

void saveData(const Pipe pipes[], const Compressor_Station stations[], int pipeCount, int stationCount, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < pipeCount; ++i) {
            file << "Pipe\n";
            file << pipes[i].name << "\n";
            file << pipes[i].length << "\n";
            file << pipes[i].diameter << "\n";
            file << pipes[i].under_repair << "\n";
        }
        for (int i = 0; i < stationCount; ++i) {
            file << "CompressorStation\n";
            file << stations[i].name << "\n";
            file << stations[i].num_workshops << "\n";
            file << stations[i].num_workshops_in_operation << "\n";
            file << stations[i].efficiency << "\n";
        }
        file.close();
        cout << "The data is saved in a file: " << filename << endl;
    } else {
        cerr << "File opening error!" << endl;
    }
}

void loadData(Pipe pipes[], Compressor_Station stations[], int& pipeCount, int& stationCount, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        pipeCount = 0;
        stationCount = 0;
        string line;
        while (getline(file, line)) {
            if (line == "Pipe") {
                pipes[pipeCount].read();
                file >> pipes[pipeCount].length >> pipes[pipeCount].diameter >> pipes[pipeCount].under_repair;
                ++pipeCount;
            } else if (line == "CompressorStation") {
                stations[stationCount].read();
                file >> stations[stationCount].num_workshops >> stations[stationCount].num_workshops_in_operation >> stations[stationCount].efficiency;
                ++stationCount;
            }
        }
        file.close();
        cout << "Data loaded from a file: " << filename << endl;
    } else {
        cerr << "File opening error!" << endl;
    }
}

int main() {
    Pipe pipes[MAX_PIPES];
    Compressor_Station stations[MAX_STATIONS];
    int pipeCount = 0;
    int stationCount = 0;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add a pipe\n";
        cout << "2. Add a compressor station\n";
        cout << "3. View all objects\n";
        cout << "4. Edit a pipe\n";
        cout << "5. Edit a compressor station\n";
        cout << "6. Save\n";
        cout << "7. Load\n";
        cout << "0. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
            case 0:
                break;
            case 1:{
                if (pipeCount < MAX_PIPES) {
                    pipes[pipeCount].read();
                    ++pipeCount;
                } else {
                    cerr << "Maximum number of pipes reached!" << endl;
                }
                break;
            }
            case 2:{
                if (stationCount < MAX_STATIONS) {
                    stations[stationCount].read();
                    ++stationCount;
                } else {
                    cerr << "Maximum number of compressor stations reached!" << endl;
                }
                break;
            }
            case 3:{
                cout << "Pipes:\n";
                for (int i = 0; i < pipeCount; ++i) {
                    pipes[i].display();
                    cout << endl;
                }
                cout << "Compressor stations:\n";
                for (int i = 0; i < stationCount; ++i) {
                    stations[i].display();
                    cout << endl;
                }
                break;
            }
            case 4:{
                // Редактирование трубы
                string pipeName;
                cout << "Enter the name of the pipe to edit: ";
                cin >> pipeName;
                for (int i = 0; i < pipeCount; ++i) {
                    if (pipes[i].name == pipeName) {
                        pipes[i].toggle_repair();
                        cout << "Pipe condition '" << pipes[i].name << "' changed to 'Under repair: " << (pipes[i].under_repair ? "Yes" : "No") << "'\n";
                        break;
                    }
                }
                break;
            }
            case 5:{
                // Редактирование КС
                string stationName;
                cout << "Enter the name of the compressor station to edit: ";
                cin >> stationName;
                for (int i = 0; i < stationCount; ++i) {
                    if (stations[i].name == stationName) {
                        // Добавьте здесь логику для редактирования КС
                        break;
                    }
                }
                break;
            }
            case 6:{
                string filename;
                cout << "Enter the file name to save: ";
                cin >> filename;
                saveData(pipes, stations, pipeCount, stationCount, filename);
                break;
            }
            case 7:{
                string loadFilename;
                cout << "Enter the file name to load: ";
                cin >> loadFilename;
                loadData(pipes, stations, pipeCount, stationCount, loadFilename);
                break;
            }
            default:{
                cout << "Invalid choice. Try again.\n";
                break;
            }
        }
    }

    return 0;
}
