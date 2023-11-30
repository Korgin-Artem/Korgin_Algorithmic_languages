#pragma once
#include <fstream>

class Pipe {
private:
    int id;
    static int Nextid;

public:
    inline int getid() const { return id; };
    std::string name;
    int length;
    int diameter;
    bool under_repair;
    int id_cs_of_the_entrance;
    int id_cs_of_the_exit;

    Pipe();

    void read();

    void toggle_repair();
    
    void connecting_with_cs(int id_from, int id_to);

    void save_data(std::ofstream& out);

    void load_data(std::ifstream& read);
    
    friend std::ostream& operator << (std::ostream& out, const Pipe& p);
};
