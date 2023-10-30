#include "Pipe.h"
#include <iostream>

int Pipe::nextId = 1;

Pipe::Pipe() {
    id = nextId++;
}

void Pipe::read() {
    std::cout << "Введите название трубы: ";
    std::cin >> std::ws;
    std::getline(std::cin, name);

    std::cout << "Введите длину трубы (в км): ";
    while (!(std::cin >> length) || length <= 0) {
        std::cerr << "Ошибка: Введите корректное значение для длины трубы (в км): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите диаметр трубы: ";
    while (!(std::cin >> diameter) || diameter <= 0) {
        std::cerr << "Ошибка: Введите корректное значение для диаметра трубы: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    under_repair = false;
}

void Pipe::display() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Название: " << name << std::endl;
    std::cout << "Длина (км): " << length << std::endl;
    std::cout << "Диаметр: " << diameter << std::endl;
    std::cout << "На ремонте: " << (under_repair ? "Да" : "Нет") << std::endl;
}

void Pipe::toggle_repair() {
    under_repair = !under_repair;
}

int Pipe::getId() const {
    return id;
}

const std::string& Pipe::getName() const {
    return name;
    
}

double Pipe::getLength() const {
    return length;
}

int Pipe::getDiameter() const {
    return diameter;
}

bool Pipe::getRepairStatus() const {
    return under_repair;
}

void Pipe::setId(int id) {
    this->id = id;
}

void Pipe::setName(const std::string& name) {
    this->name = name;
}

void Pipe::setLength(double length) {
    this->length = length;
}

void Pipe::setDiameter(int diameter) {
    this->diameter = diameter;
}

void Pipe::setRepairStatus(bool under_repair) {
    this->under_repair = under_repair;
}
