#ifndef COMPRESSORSTATION_H
#define COMPRESSORSTATION_H

#include <string>

class CompressorStation {
public:
    CompressorStation();

    void read();
    void display() const;
    void edit();
    
    int getId() const;
    const std::string& getName() const;
    int getNumWorkshops() const;
    int getNumWorkshopsInOperation() const;
    double getEfficiency() const;
    
    void setId(int id);
    void setName(const std::string& name);
    void setNumWorkshops(int num_workshops);
    void setNumWorkshopsInOperation(int num_workshops_in_operation);
    void setEfficiency(double efficiency);

private:
    int id;
    static int nextId;

    std::string name;
    int num_workshops;
    int num_workshops_in_operation;
    double efficiency;
};

#endif // COMPRESSORSTATION_H
