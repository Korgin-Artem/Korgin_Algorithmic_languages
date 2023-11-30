#include <iostream>
#include <string>

#include "Logging.h"

using namespace std;

inline string get_str() {
    string str;
    cin >> ws;
    getline(cin, str);
    cerr << str << "\n";
    return str;
}

inline int get_correct_diameter() {
    int diameter;
    while (true) {
        std::cout << "Enter the pipe diameter (500, 700, 1000, 1400 mm): ";
        if (!(std::cin >> diameter) || (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400)) {
            std::cout << "Invalid input! Please enter a valid diameter.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return diameter;
}

template <typename T>
T get_correct_value(T min, T max) {
    T value;
    cin >> value;
    cerr << value << "\n";
    while (cin.fail() || cin.peek() != '\n' || value < min || value > max) {
        cin.clear();
        cin.ignore(10000, '\n');
        cerr << "ERROR: Enter a valid value: ";
        cin >> value;
        cerr << value << "\n";
    }
    return value;
}
