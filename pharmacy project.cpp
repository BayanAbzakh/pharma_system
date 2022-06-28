#include <iostream>
#include <string>

#define MAX_ITEMS 15
using namespace std;

//first class
class inventory{
    //variables:
    int price;
    string id;
    string name;
    const string type = "OTC";
public:
    inventory() {
        price =0;
    }
    void setId(string s){
        id = s;
    }
    void set(int p, string n){
        price = p;
        name = n;
    }
    int getPrice()const{
        return price;
    }

    string getId()const{
        return id;
    }

    string getName()const{
        return name;
    }

    string getType()const{
        return type;
    }
};
//second class:
class order{
    inventory inv[15];
    int order_number;
    string order_name;
    string order_date;
    int quantity[MAX_ITEMS];
    double total;
    int order_items[MAX_ITEMS];
    double order_amount[MAX_ITEMS];
    int number_of_items;
    bool paid = false;
    order *next_item;
    order *prev_item;
    order *head = NULL;
    order *tail = NULL;
public:
    order(){
        //medicine inventory:
        total =0;
        inv[0].set(150, "Agiolax                "), inv[1].set(146,"Mebo (30g)             ");
        inv[2].set(100, "Aspirin Protect 100    "), inv[3].set(500,"Cipralex (15mg)        ");
        inv[4].set(300, "Tramal                 "), inv[5].set(200, "Nabilet (5mg)          ");
        inv[6].set(250,"Unifed                 "), inv[7].set(400,"Relaxon                ");
        inv[8].set(169,"Deflat (120mg)         " ), inv[9].set(199, "Fendol (500mg)         ");
        inv[10].set(245,"Motitium (10mg)        " ), inv[11].set(329, "Duspatalin             ");
        inv[12].set(140,"Lexotanil (3mg)        " ), inv[13].set(59, "Zeranase               ");
        inv[14].set(230,"Euthyrox (100mg)       " );
        for(int i = 0; i<15; i++){
            inv[i].setId(to_string(i+1));
        }

    }
    //function to take order details from user:
    void print_order(order *item)
    {
        cout<<"Order Number: "<<item->order_number<<endl;
        cout<<"Order name: "<<item->order_name<<endl;
        cout<<"Order date: "<<item->order_date<<endl;
        cout<<"Order Items:-"<<endl;
        for(int i=0; i<item->number_of_items; i++)
        {
            cout<<i+1<<". "<<inv[item->order_items[i]-1].getName()<< " with amount of "<<item->quantity[i]<<"pack(s) with price "<<item->order_amount[i]<<" RUB"<<endl;
            total += item->order_amount[i];

        }
        cout<<"total order amount: "<<total<<" RUB."<<endl;
        cout<<"<<------------------------------------------------------------------>>"<<endl;

    }
    void printMenu()const{
        //function to print names of medicines:
        cout<<"List of available medicines!!!"<<endl;
        cout<<"###############################################################################\n\n";
        cout<<"###############################################################################\n";
        cout<<"Id   \t\tDrug Type\tMedicine Name \t        Medicine Price"<<endl;
        cout<<"###############################################################################\n";
        for(int i=0; i<15; i++)
        {
            cout<<inv[i].getId()<<" \t\t "<<inv[i].getType()<<" \t\t "<<inv[i].getName()<<"\t\t"<<inv[i].getPrice()<<" RUB"<<endl;
        }
    }
    //function to take new order
    void newOrder(){
        int number;

        cout<<"Enter order number: ";
        cin >> number;
    }
    void start_order()
    {
        //called the printMenu() function
        printMenu();
        order *new_order = new order;
        //new variables
        int number;
        bool found = false;
        do
        {
            //take order number
            cout<<"Enter order number: ";
            cin>>number;
            found = false;
            order *tmp = head;
            while(tmp != NULL)
            {
                if (tmp->order_number == number)
                {
                    found = true;
                }

                tmp = tmp->next_item;
            }
        } while (found);
        //give order name and date
        new_order->order_number = number;
        cout<<"Enter order name: ";
        cin>>new_order->order_name;
        cout<<"Enter Date: ";
        cin>>new_order->order_date;
        do
        {
            //how many items are to be ordered
            cout<<"Enter number of order items (MAX. 15 items): ";
            cin>>new_order->number_of_items;
        } while (new_order->number_of_items>15);

        for(int i=0; i<new_order->number_of_items; i++)
        {
            //choosing order details
            cout<<"Select item: ";
            cin>>new_order->order_items[i];
            cout << "number of packs: ";
            cin >> new_order->quantity[i];
            new_order->order_amount[i] = new_order->quantity[i] * inv[new_order->order_items[i]-1].getPrice();
            cout<< "Medicine Name: " <<inv[new_order->order_items[i]-1].getName()<<endl;
            cout << "The amount You need to pay is: " << new_order->order_amount[i]<<" RUB"<<endl;
        }
        cout<<"Order placed!! Go to order summary and proceed to pay!"<<endl;
        new_order->next_item = NULL;
        new_order->prev_item = NULL;
        if(head == NULL && tail == NULL)
        {
            head = tail = new_order;
        }
        else
        {
            tail->next_item = new_order;
            new_order->prev_item = tail;
            tail = new_order;
        }

    }
    //function to delete a specific order
    int delete_order()
    {
        int num;
        cout<<"Enter order number to delete: ";
        cin>>num;
        if(head==NULL && tail==NULL)
        {
            cout<<"There are no orders to Delete."<<endl;
            return 1;
        }
        else
        {
            order *tmp = head;
            while(tmp != NULL)
            {
                if(tmp->order_number == num)
                {
                    if(tmp == head)
                    {
                        head = head->next_item;
                    }
                    else if(tmp == tail)
                    {
                        tail = tail->prev_item;
                    }
                    else
                    {
                        tmp->next_item->prev_item = tmp->prev_item;
                        tmp->prev_item->next_item = tmp->next_item;
                    }
                    cout<<"Order placed!! Go to order summary and proceed to pay!"<<endl;
                    print_order(tmp);
                    delete tmp;
                    return 0;
                }
                tmp = tmp->next_item;
            }
        }
        cout<<"order with number  "<<num<<" was not found."<<endl;
        return 2;
    }
    //function to display available orders:
    int display_orders()
    {
        order *tmp = head;
        if(tmp == NULL)
        {
            cout<<"No orders to display. please place an order"<<endl;
            return 0;
        }
        while(tmp != NULL)
        {
            print_order(tmp);
            tmp = tmp->next_item;
        }
        return 1;


    }
    //function to show order about to be paid for
    void retrieve_pay_order()
    {
        int num;
        double amount;
        cout<<"Enter order number you want to pay: ";
        cin>>num;
        bool found = false;
        if(head==NULL && tail==NULL)
        {
            cout<<"There are no orders to Delete."<<endl;
        }
        else
        {
            order *tmp = head;
            while(tmp != NULL)
            {
                if(tmp->order_number == num)
                {
                    print_order(tmp);
                    cout<<"The amount you will pay: "<<endl;
                    cin>>amount;
                    cout<<"Order has been paid successfully!!\nThank you for using our system\n";
                    found=true;
                }
                tmp = tmp->next_item;
            }
        }
        if (found == false)
        {
            cout<<"order with number  "<<num<<" was not found."<<endl;
        }
    }
    //function to edit order details
    void change_order()
    {
        int num, change_item, new_item;
        double amount;
        cout<<"Enter order number you want to change: ";
        cin>>num;
        bool found = false;
        if(head==NULL && tail==NULL)
        {
            cout<<"There are no orders in the system\n";
        }
        else
        {
            order *tmp = head;
            while(tmp != NULL)
            {
                if(tmp->order_number == num)
                {
                    found = true;
                    break;
                }
                tmp = tmp->next_item;
            }
            if(found)
            {
                //details or new changes
                cout<<"Order required to modify is with the following details:-"<<endl;
                print_order(tmp);
                cout<<"Select item you want to change: ";
                cin>>change_item;
                cout<<"Select new item from the following list: ";
                printMenu();
                cout<<"Select item: ";
                cin>>tmp->order_items[change_item-1];
                cout << "number of packs: ";
                cin >> tmp->quantity[change_item-1];
                tmp->order_amount[change_item-1] = tmp->quantity[change_item-1] * inv[tmp->order_items[change_item-1]-1].getPrice();
                cout<< "Medicine Name: " <<inv[tmp->order_items[change_item-1]-1].getName()<<endl;
                cout << "The amount You need to pay is: " << tmp->order_amount[change_item-1]<<" RUB"<<endl;
            }
            else
            {
                cout<<"No order with number "<<num<<" found in the system"<<endl;
            }
        }

    }



};
//third class
class print{
public:
    //function to print all functionalities of system on terminal
    void print_message()
    {
        cout<<"Welcome to the pharmacy system"<<endl;
        cout<<"<<----------------------------------------------->>"<<endl;
        cout<<"Here Are the system options"<<endl;
        cout<<"1. Place a new order"<<endl;
        cout<<"2. Delete available order"<<endl;
        cout<<"3. List available orders"<<endl;
        cout<<"4. Display and pay for order"<<endl;
        cout<<"5. Change an order"<<endl;
        cout<<"6. Quit"<<endl;
        cout<<"<<----------------------------------------------->>"<<endl;
        cout<<"Process number: ";
    }
};
//main function
int main(){
    int choice;
    print p;
    order store;
    do {
        p.print_message();
        cin >> choice;
        switch (choice) {
            case 1: {
                store.start_order();
                break;
            }
            case 2: {
                store.delete_order();
                break;
            }
            case 3: {
                store.display_orders();
                break;
            }
            case 4: {
                store.retrieve_pay_order();
                break;
            }
            case 5: {
                store.change_order();
                break;
            }
            case 6: {
                break;
            }
            default: {
                cout << "invalid input. Try Again!!" << endl;
                break;
            }
        }

    } while (choice != 6);
    cout << "Thank You for using our system" << endl;
    return 0;

}


