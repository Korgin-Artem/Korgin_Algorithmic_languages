#ifndef PIPE_H
#define PIPE_H

#include <string>

class Pipe {
public:
    Pipe();

    void read();
    void display() const;
    void toggle_repair();

    int getId() const;
    const std::string& getName() const;
    double getLength() const;
    int getDiameter() const;
    bool getRepairStatus() const;
    
    void setId(int newId);
    void setName(const std::string& name);
    void setLength(double length);
    void setDiameter(int diameter);
    void setRepairStatus(bool under_repair);

private:
    int id;
    std::string name;
    double length;
    int diameter;
    bool under_repair;
};

#endif // PIPE_H
