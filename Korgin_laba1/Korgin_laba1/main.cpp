#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Pipe{
    string name;
    double length;
    int diameter;
    bool under_repair;
    
    void read(){
        cout << "Enter the name of the pipe: ";
        cin >> name;
        cout << "Enter the lenght of the pipe (in km): ";
        cin >> length;
        cout << "Enter the pipe diameter: ";
        cin >> diameter;
        under_repair = false;
    }
    
    void display() const {
        cout << "Name: " << name << endl;
        cout << "Lengt (km): " << length << endl;
        cout << "Diameter: " << diameter << endl;
        cout << "Under repair: " << (under_repair ? "Yes": "No") << endl;
    }
    
    void toggle_repair(){
        under_repair = !under_repair;
    }
};

struct Compressor_Station{
    string name;
    int num_workshops;
    int num_workshops_in_operation;
    string efficiency;
    
    void read(){
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
        cout << "efficiency: " << efficiency << endl;
    }
};

void saveData(const vector<Pipe>& pipes, const vector<Compressor_Station>& stations, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const Pipe& pipe : pipes){
            file << "Pipe\n";
            file << pipe.name << "\n";
            file << pipe.length << "\n";
            file << pipe.diameter << "\n";
            file << pipe.under_repair << "\n";
        }
        for (const Compressor_Station& station : stations){
            file << "CompressorStation\n";
            file << station.name << "\n";
            file << station.num_workshops << "\n";
            file << station.num_workshops_in_operation << "\n";
            file << station.efficiency << "\n";
        }
        file.close();
        cout << "The data is save in a file: " << filename << endl;
    } else {
        cerr << "File opening error!" << endl;
    }
}

void loadData(vector<Pipe>& pipes, vector<Compressor_Station>& stations, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        pipes.clear();
        stations.clear();
        string line;
        while (getline(file, line)) {
            if (line == "Pipe") {
                Pipe pipe;
                getline(file, pipe.name);
                file >> pipe.length >> pipe.diameter >> pipe.under_repair;
                pipes.push_back(pipe);
            } else if (line == "Compressor_Station") {
                Compressor_Station station;
                getline(file, station.name);
                file >> station.num_workshops >> station.num_workshops_in_operation >> station.efficiency;
                stations.push_back(station);
            }
        }
        file.close();
        cout << "Data downloaded from a file: " << filename << endl;
    } else {
        cerr << "File opening error!" << endl;
    }
}

int main() {
    vector<Pipe> pipes;
    vector<Compressor_Station> stations;
    
    while (true) {
        cout << "Menu:\n";
        cout << "1. Add a pipe\n";
        cout << "2. Add a compressor station\n";
        cout << "3. Viewing all objects\n";
        cout << "4. Edit a pipe\n";
        cout << "5. Edit a compressor station\n";
        cout << "6. Save\n";
        cout << "7. Download\n";
        cout << "0. Exit\n";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 0:
                break;
            case 1:{
                Pipe pipe;
                pipe.read();
                pipes.push_back(pipe);
                break;
            }
            case 2:{
                Compressor_Station station;
                station.read();
                stations.push_back(station);
                break;
            }
            case 3:{
                cout << "Pipes:\n";
                for (const Pipe& pipe : pipes) {
                    pipe.display();
                    cout << endl;
                }
                cout << "Compressor station:\n";
                for (const Compressor_Station& station : stations) {
                    station.display();
                    cout << endl;
                }
                break;
            }
            case 4:{
                // Редактирование трубы
                string pipeName;
                cout << "Enter the name of the pipe to edit: ";
                cin >> pipeName;
                for (Pipe& pipe : pipes) {
                    if (pipe.name == pipeName) {
                        pipe.toggle_repair();
                        cout << "Pipe condition '" << pipe.name << "' Changed to 'Under repair: " << (pipe.under_repair ? "Yes" : "No") << "'\n";
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
                for (Compressor_Station& station : stations) {
                    if (station.name == stationName) {
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
                saveData(pipes, stations, filename);
                break;
            }
            case 7:{
                string filename;
                cout << "Enter the file name to upload: ";
                cin >> filename;
                loadData(pipes, stations, filename);
                break;
            }
                
            default:{
                cout << "A non-correct choice. Try again.\n";
                break;
            }
        }
    }
    return 0;
}
