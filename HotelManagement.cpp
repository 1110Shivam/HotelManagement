#include <fstream>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;
class Hotel
{
private:
    int room_number;
    char name[30], address[50], mobile_no[15];

public:
    void add_customer()
    {
        cout << "\nEnter the room number = ";
        cin >> room_number;
        cout << "\nEnter the customer's name = ";
        cin.ignore();
        cin.getline(name, 30);
        cout << "\nEnter the customer's address =";
        cin.ignore();
        cin.getline(address, 50);
        cout << "\nEnter the customer's mobile no =";
        cin.ignore();
        cin.getline(mobile_no, 15);
        cout << mobile_no;
    }
    void show_customer()
    {
        cout << "\nRoom number = " << room_number;
        cout << "\nCustomer's name = " << name;
        cout << "\nCustomer's address = " << address;
        cout << "\nCustomer's mobile No. = " << mobile_no;
    }
    void modify_customer_record()
    {
        cout << "\nRoom number = " << room_number;
        cout << "\nModify customer's name = ";
        cin.ignore();
        cin.getline(name, 30);
        cout << "\nModify customer's address =";
        cin.ignore();
        cin.getline(address, 50);
        cout << "\nModify customer's mobile no. =";
        cin.ignore();
        cin.getline(mobile_no, 15);
    }
    int getRoomNumber()
    {
        return room_number;
    }
    char *getName()
    {
        return name;
    }
    char *getAddress()
    {
        return address;
    }
    char *getMobileNo()
    {
        return mobile_no;
    }
    void report()
    {
        cout << room_number << setw(10) << name << setw(20) << address << setw(20) << mobile_no << endl;
    }
};

fstream fp;
Hotel h;

void save_customer()
{
    system("cls");
    fp.open("main.dat", ios::out | ios::app);
    h.add_customer();
    fp.write((char *)&h, sizeof(Hotel));
    fp.close();
}
void display_customer(int RoomNumber)
{
    system("cls");
    cout << "\nCustomer details\n";
    int check = 0;
    fp.open("main.dat", ios::in);
    while (fp.read((char *)&h, sizeof(Hotel)))
    {
        if (h.getRoomNumber() == RoomNumber)
        {
            h.show_customer();
            check = 1;
        }
    }
    fp.close();
    if (check == 0)
        cout << "\nCustomer does not exist.";
}

void modifyCustomer()
{
    system("cls");
    int RoomNumber, found = 0;
    cout << "\n\n\tModify customer's record";
    cout << "\n\n\tEnter the room number = ";
    cin >> RoomNumber;
    fp.open("main.dat", ios::in | ios::out);
    while (fp.read((char *)&h, sizeof(Hotel)) && found == 0)
    {
        if (h.getRoomNumber() == RoomNumber)
        {
            h.show_customer();
            cout << "\nEnter customer's new information" << endl;
            h.modify_customer_record();
            long long unsigned int pos = -1 * sizeof(h);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&h, sizeof(Hotel));
            cout << "\n\n\tRecord updated successfully...";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\nRecord not found";
}
void delete_cutomer()
{
    system("cls");
    char RoomNumber;
    int flag = 0;
    cout << "\n\n\n\tDelete customer";
    cout << "\n\nEnter the room of the customer you want to delete = ";
    cin >> RoomNumber;
    fp.open("main.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&h, sizeof(Hotel)))
    {
        if (h.getRoomNumber() == RoomNumber)
        {
            fp2.write((char *)&h, sizeof(Hotel));
        }
        else
            flag = 1;
    }
    fp2.close();
    fp.close();
    remove("main.dat");
    rename("Temp.dat", "main.dat");
    if (flag == 1)
    {
        cout << "\n\n\tRecord deleted...";
    }
    else
        cout << "\n\nRecord not found";
}

int main()
{
    int ch;
    for (;;)
    {
        cout << "\n\n\t\t***********************************************************************************";
        cout << "\n\t\tPress 1 to book a room";
        cout << "\n\t\tPress 2 to display customer record";
        cout << "\n\t\tPress 3 to modify customer record";
        cout << "\n\t\tPress 4 to delete customer record";
        cout << "\n\t\tPress 5 to exit";
        cout << "\n\n\t\t************************************************************************************\n";
        cout << "\n\t\tEnter your choice = ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            save_customer();
            system("cls");
            break;

        case 2:
            int RoomNumber;
            system("cls");
            cout << "\n\n\tPlease enter customer's room number = ";
            cin >> RoomNumber;
            display_customer(RoomNumber);
            break;
        case 3:
            modifyCustomer();
            system("cls");
            break;
        case 4:
            delete_cutomer();
            system("cls");
            break;
        case 5:
            exit(0);
        default:
            cout << "\a";
            break;
        }
    }
    return 0;
}