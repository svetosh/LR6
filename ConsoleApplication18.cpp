#include <iostream> 
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct cAddress {
    std::string street;
    unsigned int houseNumber;
    unsigned int flatNumber;
};
struct occupant {
    std::string name;
    cAddress address;
    std::string gender;
    unsigned int age;
};

std::ostream& operator<<(std::ostream& out, const std::vector<occupant>& dataBase)
{
    for (auto& occupant : dataBase)
    {
        out << occupant.name << ";" << occupant.address.street << ";"
            << occupant.address.houseNumber << ";"
            << occupant.address.flatNumber << ";" << occupant.gender
            << ";" << occupant.age << std::endl;
    }
    return out;
}
std::istream& operator>>(std::istream& in, vector<occupant>& dataBase)
{
    while (!in.eof())
    {
        occupant citizen;
        string buffer;
        getline(in, citizen.name, ';');
        if (in.eof()) break;
        getline(in, citizen.address.street, ';');
        getline(in, buffer, ';');
        citizen.address.houseNumber = stoi(buffer);
        getline(in, buffer, ';');
        citizen.address.flatNumber = stoi(buffer);
        getline(in, citizen.gender, ';');
        getline(in, buffer, '\n');
        citizen.age = stoi(buffer);
        dataBase.push_back(citizen);
    }
    return in;
}

void outputVec(std::vector <occupant> dataBase)
{
    for (int i = 0; i < dataBase.size(); i++) {
        std::cout << dataBase[i].name << std::endl
            << "street: " << dataBase[i].address.street
            << ", houseNumber: " << dataBase[i].address.houseNumber
            << ", flatNumber: " << dataBase[i].address.flatNumber << std::endl
            << "gender: " << dataBase[i].gender << std::endl
            << "age: " << dataBase[i].age << std::endl;
    }
    std::cout << std::endl;
}
void writeToFile(std::vector<occupant> dataBase, std::string nameInFile)
{
    std::ofstream fileWrite;
    fileWrite.open(nameInFile, std::ios::out);
    fileWrite << dataBase;
    fileWrite.close();
}
void readFromFile(std::vector<occupant>& dataBase, std::string nameInFile)
{
    std::ifstream fileRead;
    fileRead.open(nameInFile, std::ios::in);
    fileRead >> dataBase;
    fileRead.close();
}

void writeToFileBin(vector<occupant>& data, string nameInFile)
{
    ofstream ofile(nameInFile, std::ios::binary);
    if (!ofile.is_open())
    {
        std::cout << "Faile" << std::endl;
        return;
    }
    for (occupant o : data)
    {
        unsigned long int s = o.name.size();
        ofile.write(reinterpret_cast<char*>(&s), sizeof(s));
        ofile.write(o.name.c_str(), s);
        s = o.address.street.size();
        ofile.write(reinterpret_cast<char*>(&s), sizeof(s));
        ofile.write(o.address.street.c_str(), s);
        ofile.write(reinterpret_cast<char*>(&o.address.flatNumber), sizeof(o.address.flatNumber));
        ofile.write(reinterpret_cast<char*>(&o.address.houseNumber), sizeof(o.address.houseNumber));
        s = o.gender.size();
        ofile.write(reinterpret_cast<char*>(&s), sizeof(s));
        ofile.write(o.gender.c_str(), s);
        ofile.write(reinterpret_cast<char*>(&o.age), sizeof(o.age));
    }
}

void readFromFileBin(std::vector<occupant>& data, std::string nameInFile)
{
    ifstream ifile(nameInFile, std::ios::binary);
    if (!ifile.is_open())
    {
        std::cout << "Faile" << std::endl;
        return;
    }
    occupant o;
    while(!ifile.eof())
    {
        unsigned long int s;
        ifile.read(reinterpret_cast<char*>(&s), sizeof(s));
        o.name.resize(s);
        ifile.read(o.name.data(), s);
        ifile.read(reinterpret_cast<char*>(&s), sizeof(s));
        o.address.street.resize(s);
        ifile.read(o.address.street.data(), s);
        ifile.read(reinterpret_cast<char*>(&o.address.flatNumber), sizeof(o.address.flatNumber));
        ifile.read(reinterpret_cast<char*>(&o.address.houseNumber), sizeof(o.address.houseNumber));
        ifile.read(reinterpret_cast<char*>(&s), sizeof(s));
        o.gender.resize(s);
        ifile.read(o.gender.data(), s);
        ifile.read(reinterpret_cast<char*>(&o.age), sizeof(o.age));
        if (ifile.eof()) break;
        data.push_back(o);
    }
    ifile.close();
}

int main()
{
    std::vector<occupant> dataBase;
    occupant Jon;
    Jon.name = "Ivanov Jon Ivanovich";
    Jon.address.street = "Pushkina";
    Jon.address.flatNumber = 3;
    Jon.address.houseNumber = 2;
    Jon.gender = "Male";
    Jon.age = 30;
    occupant Lem;
    Lem.name = "Lemonov Lem Lemonovich";
    Lem.address.street = "Volgogradskaya";
    Lem.address.flatNumber = 5;
    Lem.address.houseNumber = 32;
    Lem.gender = "Female";
    Lem.age = 50;
    occupant Goga;
    Goga.name = "Bruno Goga Konst";
    Goga.address.street = "Ptichefabrica";
    Goga.address.flatNumber = 1;
    Goga.address.houseNumber = 32;
    Goga.gender = "Female";
    Goga.age = 20;
    dataBase.push_back(Jon);
    dataBase.push_back(Lem);
    dataBase.push_back(Goga);
    std::sort(dataBase.begin(), dataBase.end(), [](occupant a, occupant b)
        {
            return a.name < b.name;
        });
    outputVec(dataBase);

    int home;
    std::string street;
    std::string output;
    std::cout << "Enter street = ";
    std::getline(std::cin, street);
    std::cout << "Enter number house = ";
    std::cin >> home;
    int counter = 0;
    for (int numOccuo = 0; numOccuo < dataBase.size(); numOccuo++)
    {
        if (dataBase[numOccuo].address.houseNumber == home && dataBase[numOccuo].address.street == street)
        {
            if (dataBase[numOccuo].gender == "Female"
                && (dataBase[numOccuo].age > 24
                    && dataBase[numOccuo].age < 60))
            {
                output = output + dataBase[numOccuo].name + '\n'
                    + dataBase[numOccuo].address.street + ", "
                    + std::to_string(dataBase[numOccuo].address.houseNumber) + ", "
                    + std::to_string(dataBase[numOccuo].address.flatNumber) + '\n'
                    + dataBase[numOccuo].gender + '\n' + std::to_string(dataBase[numOccuo].age)
                    + '\n' + '\n';
                counter++;
            }
        }
    }
    std::cout << std::endl
        << "In this home = " << counter << std::endl
        << output;

    writeToFile(dataBase, "404.txt");
    dataBase.clear();
    readFromFile(dataBase, "404.txt");
    outputVec(dataBase);

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    vector<occupant> datBase;
    writeToFileBin(dataBase, "404Bin.txt");
    readFromFileBin(datBase, "404Bin.txt");
    outputVec(datBase);


    return 0;
}
