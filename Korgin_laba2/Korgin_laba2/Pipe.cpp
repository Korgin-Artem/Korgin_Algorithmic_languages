#include <iostream>
#include <fstream>

#include "Pipe.h"
#include "Get_Correct.cpp"

int Pipe::Nextid = 1;

Pipe::Pipe()
{
    id = Nextid++;
}

void Pipe::read() {
    cout << "Enter the pipe name: ";
    name = get_str();
    std::cout << "Enter the length of the pipe (in km): ";
    length = get_correct_value<int>(1, INT_MAX);
    std::cout << "Enter the diameter of the pipe: ";
    diameter = get_correct_value<int>(1, INT_MAX);
    under_repair = false;
}

void Pipe::display() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Length (km): " << length << std::endl;
    std::cout << "Diameter: " << diameter << std::endl;
    std::cout << "Under repair: " << (under_repair ? "Yes" : "No") << std::endl;
}

void Pipe::toggle_repair() {
    under_repair = !under_repair;
}

void Pipe::save_data(const std::unordered_map<int, Pipe>& pipes, const string& file_name) {
    ofstream file(file_name);

    if (!file) {
        cerr << "Error opening file for writing " << file_name << endl;
        return;
    }

    for (const auto& pipeEntry : pipes) {
        const Pipe& pipe = pipeEntry.second;
        file << "Pipe\n";
        file << pipe.id << "\n";
        file << pipe.name << "\n";
        file << pipe.length << "\n";
        file << pipe.diameter << "\n";
        file << pipe.under_repair << "\n";
    }

    file.close();
}

void Pipe::load_data(ifstream& read) {
    if (read.is_open()) {
            read >> id;
            read >> name;
            read >> length;
            read >> diameter;
            read >> under_repair;

        }
        else {
            cout << "Error!";
        }
}
