#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class FoodItem
{
public:
    string name;
    double price;

    FoodItem(string n, double p) : name(n), price(p) {}

    void displayItem()
    {
        cout << name << " - Rs " << price << endl;
    }
};

class CustomerBasicInfo
{
public:
    string username;
    string mobNumber;

public:
    void input1()
    {
        cout << "Enter your name: ";
        cin >> username;
        do
        {
            cout << "Enter your mobile number: ";
            cin >> mobNumber;

            if (mobNumber.size() != 10)
            {
                cout << "\nPlease enter a valid phone number!" << endl;
            }

        } while (mobNumber.size() != 10);
    }
};

class CustomerAdd
{
public:
    string flat, city, Area, nearby;

public:
    void input2()
    {
        cout << "Enter city: ";
        cin >> city;
        cin.ignore();
        cout << "Enter Area: ";
        getline(cin, Area);
        cout << "Enter nearby places/ landmark*: ";
        getline(cin, nearby);
        cout << "Enter Flat/House/Floor No: ";
        getline(cin, flat);
    }
};

class CustomerInfo : public CustomerBasicInfo, public CustomerAdd
{
public:
    CustomerInfo()
    {
        input1();
        input2();
    }
};

class ProcessOrder
{
public:
    vector<FoodItem> items;

    void addItem(FoodItem &item)
    {
        items.push_back(item);
    }

    double calculateTotal()
    {
        double total = 0;
        for (int i = 0; i < items.size(); i++)
        {
            total += items[i].price;
        }
        return total;
    }

    void viewOrder()
    {
        cout << "--------------------------------------------" << endl;
        for (int i = 0; i < items.size(); i++)
        {
            items[i].displayItem();
        }
        cout << "--------------------------------------------" << endl;
        cout << "Total: " << calculateTotal() << " Rs " << endl;
        cout << "--------------------------------------------" << endl;
    }

    void printBill(const CustomerInfo &in)
    {
        viewOrder();
        // Save the order details to a file
        ofstream outFile("order.txt");
        if (outFile.is_open())
        {
            outFile << "Name: " << in.username << endl;
            outFile << "Phone: " << in.mobNumber << endl;
            outFile << "City: " << in.city << endl;
            outFile << "Area: " << in.Area << endl;
            outFile << "Flat/House No./Floor No: " << in.flat << endl;
            outFile << "Nearby places/ landmark*: " << in.nearby << endl;
            outFile << "-------------------------------------" << endl;
            outFile << "McDonald's Order: " << endl;
            for (int i = 0; i < items.size(); i++)
            {
                outFile << items[i].name << " - Rs " << items[i].price << endl;
            }
            outFile << "-------------------------------------" << endl;
            outFile << "Total: Rs " << calculateTotal() << endl
                    << endl;
            outFile.close();
            cout << "\nThank you for placing order!" << endl;
            cout << "\nBill generated successfully !" << endl;
        }
        else
        {
            cout << "\nUnable to save order details to file." << endl;
        }
    }
};

class McDonalds
{
public:
    vector<FoodItem> menu;

    McDonalds()
    {
        // Initialize the menu
        menu.emplace_back(" Big Mac", 89);
        menu.emplace_back(" Chicken McNuggets", 99);
        menu.emplace_back(" McDouble", 299);
        menu.emplace_back(" Coca-Cola", 40);
        menu.emplace_back(" Medium Fries", 99);
        menu.emplace_back(" Allo-Tikki Burger", 49);
        menu.emplace_back(" Meal(Burger + Fries + Coke)", 249);
    }

    void displayMenu()
    {
        cout << "\nMcDonald's Menu:" << endl;
        for (int i = 0; i < menu.size(); i++)
        {
            cout<<i+1<<")";
            menu[i].displayItem();
        }
    }

    void takeOrder()
    {
        ProcessOrder order;
        CustomerInfo in;
        int choice, ch;
        char ans;
        string add;
        do
        {
            cout << "\nMENU" << endl
                 << "1) Add Item" << endl
                 << "2) View Order" << endl
                 << "3) Complete Order" << endl
                 << "4) Take Delivery" << endl
                 << "5) Exit" << endl
                 << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
            {
                displayMenu();
                do
                {
                    cout << "\nEnter the item which you want to order : ";
                    cin >> ch;

                    if (ch > 0 && ch <= menu.size())
                    {
                        order.addItem(menu[ch - 1]);
                        cout << "\n"
                             << menu[ch - 1].name << " added to the order." << endl;
                    }
                    else
                    {
                        cout << "Invalid Choice!  try again.." << endl;
                    }
                    cout << "\nDo you want to add anything else?? [y|n]: ";
                    cin >> ans;
                } while (ans != 'n');

                break;
            }
            case 2:
            {
                cout << "\nORDER DETAILS -"
                     << endl;
                order.viewOrder();
                break;
            }
            case 3:
            {

                cout << "\nORDER -"
                     << endl;
                order.printBill(in);
                break;
            }
            case 4:
            {
                cout << "\nDelivering to >>>> " << in.Area << "," << in.city << endl
                     << "Flat/House no./Floor: " << in.flat << endl
                     << "Near " << in.nearby << endl;
                break;
            }
            case 5:
            {
                cout << "\nExiting the McDonald's app...\n"
                     << endl;
                exit(1);
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }

        } while (choice != 0);
    }
};

int main()
{

    cout << "\n((  Welcome to McDonald's! ))\n"
         << endl;
    McDonalds mcd;
    mcd.takeOrder();
    return 0;
}
