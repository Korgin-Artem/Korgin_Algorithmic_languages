#include "CompressorStation.h"
#include <iostream>

int CompressorStation::nextId = 1;

CompressorStation::CompressorStation() {
    id = nextId++;
}

void CompressorStation::read() {
    std::cout << "Введите название компрессорной станции: ";
    std::cin >> std::ws;
    std::getline(std::cin, name);

    std::cout << "Введите количество цехов: ";
    while (!(std::cin >> num_workshops) || num_workshops <= 0) {
        std::cerr << "Ошибка: Введите корректное значение для количества цехов: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите количество работающих цехов: ";
    while (!(std::cin >> num_workshops_in_operation) || num_workshops_in_operation < 0 || num_workshops_in_operation > num_workshops) {
        std::cerr << "Ошибка: Введите корректное значение для количества работающих цехов: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите эффективность от 0 до 100: ";
    while (!(std::cin >> efficiency) || efficiency < 0 || efficiency > 100) {
        std::cerr << "Ошибка: Введите корректное значение эффективности от 0 до 100: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void CompressorStation::display() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Название: " << name << std::endl;
    std::cout << "Количество цехов: " << num_workshops << std::endl;
    std::cout << "Количество работающих цехов: " << num_workshops_in_operation << std::endl;
    std::cout << "Эффективность: " << efficiency << std::endl;
}

void CompressorStation::edit() {
    std::cout << "Введите новое количество работающих цехов: ";
    while (!(std::cin >> num_workshops_in_operation) || num_workshops_in_operation < 0 || num_workshops_in_operation > num_workshops) {
        std::cerr << "Ошибка: Введите корректное значение для количества работающих цехов: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите новую эффективность: ";
    while (!(std::cin >> efficiency) || efficiency < 0 || efficiency > 100) {
        std::cerr << "Ошибка: Введите корректное значение эффективности от 0 до 100: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int CompressorStation::getId() const {
    return id;
}

const std::string& CompressorStation::getName() const { 
    return name;
}

int CompressorStation::getNumWorkshops() const {
    return num_workshops;
}

int CompressorStation::getNumWorkshopsInOperation() const {
    return num_workshops_in_operation;
}

double CompressorStation::getEfficiency() const {
    return efficiency;
}

void CompressorStation::setId(int id) {
    this->id = id;
}

void CompressorStation::setName(const std::string& name) {
    this->name = name;
}

void CompressorStation::setNumWorkshops(int num_workshops) {
    this->num_workshops = num_workshops;
}

void CompressorStation::setNumWorkshopsInOperation(int num_workshops_in_operation) {
    this->num_workshops_in_operation = num_workshops_in_operation;
}

void CompressorStation::setEfficiency(double efficiency) {
    this->efficiency = efficiency;
}
