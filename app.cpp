#include <iostream>
#include <stdlib.h>
#include <string>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iomanip>
#define MAX_ITEMS 15

using namespace std;

string medicines[MAX_ITEMS]={
    "Agiolax",
    "Mebo (30g)",
    "Aspirin Protect 100",
    "Cipralex (15mg)",
    "Tramal",
    "Nabilet (5mg)",
	"Unifed",
    "Relaxon",
    "Deflat (120mg)",
    "Fendol (500mg)",
    "Motitium (10mg)",
    "Duspatalin",
    "Lexotanil (3mg)",
    "Zeranase",
    "Euthyrox (100mg)"};
double medicine_prices[MAX_ITEMS] = {150.00, 146.00, 100.00, 500.00, 300.00, 200.00, 250.00, 400.00, 169.00, 199.00, 245.00, 329.00, 140.00, 59.00, 230.00};


struct order_item
{
    int order_number;
    string order_name;
    string order_date;
    int quantity[MAX_ITEMS];
    double total;
    int order_items[MAX_ITEMS];
    double order_amount[MAX_ITEMS];
    int number_of_items;
    bool paid = false;
    order_item *next_item;
    order_item *prev_item;
};

order_item *head = NULL;
order_item *tail = NULL;

void print_medicines()
{
    cout<<"List of available medicines"<<endl;
    cout<<"<<-------------------------------------->>"<<endl;
    cout<<"index \t\t "<<"Medicine name \t\t Medicine price"<<endl;
    for(int i=0; i<MAX_ITEMS; i++)
    {
        cout<<i+1<<" \t\t "<<medicines[i]<<" \t\t "<<medicine_prices[i]<<" RUB"<<endl;
    }
}
void print_order(order_item *item)
{
    double total = 0.0;
    cout<<"Order Number: "<<item->order_number<<endl;
    cout<<"Order name: "<<item->order_name<<endl;
    cout<<"Order date: "<<item->order_date<<endl;
    cout<<"Order Items:-"<<endl;
    for(int i=0; i<item->number_of_items; i++)
    {
        cout<<i+1<<". "<<medicines[item->order_items[i]-1]<< " with amount of "<<item->quantity[i]<<"pack(s) with price "<<item->order_amount[i]<<" RUB"<<endl;
        total += item->order_amount[i];
        
    }
    cout<<"total order amount: "<<total<<" RUB."<<endl;
    cout<<"<<------------------------------------------------------------------>>"<<endl;

}

class Pharmacy
{
    public:
    Pharmacy()
    {

    }
    
    void start_order()
    {
        print_medicines();
        order_item *new_order = new order_item;
        int number;
        bool found = false;
        do
        {
            cout<<"Enter order number: ";
            cin>>number;
            found = false;
            order_item *tmp = head;
            while(tmp != NULL)
            {
                if (tmp->order_number == number)
                {
                    found = true;
                }
                
                tmp = tmp->next_item;
            }
        } while (found==true);
        new_order->order_number = number;
        cout<<"Enter order name: ";
        cin>>new_order->order_name;
        cout<<"Enter Date: ";
        cin>>new_order->order_date;
        do
        {
            cout<<"Enter number of order items (MAX. 15 items): ";
            cin>>new_order->number_of_items;
        } while (new_order->number_of_items>15);

        for(int i=0; i<new_order->number_of_items; i++)
        {
            cout<<"Select item: ";
            cin>>new_order->order_items[i];
            cout << "number of packs: ";
            cin >> new_order->quantity[i];
            new_order->order_amount[i] = new_order->quantity[i] * medicine_prices[new_order->order_items[i]-1];
            cout<< "Medicine Name: " <<medicines[new_order->order_items[i]-1]<<endl;
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
            order_item *tmp = head;
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
                    cout<<"The following order has been deleted"<<endl;
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

    int display_orders()
    {
        order_item *tmp = head;
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
            order_item *tmp = head;
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
            order_item *tmp = head;
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
                cout<<"Order required to modify is with the following details:-"<<endl;
                print_order(tmp);
                cout<<"Select item you want to change: ";
                cin>>change_item;
                cout<<"Select new item from the following list: ";
                print_medicines();
                cout<<"Select item: ";
                cin>>tmp->order_items[change_item-1];
                cout << "number of packs: ";
                cin >> tmp->quantity[change_item-1];
                tmp->order_amount[change_item-1] = tmp->quantity[change_item-1] * medicine_prices[tmp->order_items[change_item-1]-1];
                cout<< "Medicine Name: " <<medicines[tmp->order_items[change_item-1]-1]<<endl;
                cout << "The amount You need to pay is: " << tmp->order_amount[change_item-1]<<" RUB"<<endl;
            }
            else
            {
                cout<<"No order with number "<<num<<" found in the system"<<endl;
            }
        }

    }
    
};
void print_message()
{
    cout<<"Welcome to the pharmacy system"<<endl;
    cout<<"<<----------------------------------------------->>"<<endl;
    cout<<"Here Are the system options"<<endl;
    cout<<"1. Place a new order"<<endl;
    cout<<"2. Delete avaialable order"<<endl;
    cout<<"3. List available orders"<<endl;
    cout<<"4. Display and pay for order"<<endl;
    cout<<"5. Change an order"<<endl;
    cout<<"6. Quit"<<endl;
    cout<<"<<----------------------------------------------->>"<<endl;
    cout<<"Process number: ";
}

int main()
{
    
    int choice;
    Pharmacy store;
    do
    {
        print_message();
        cin>>choice;
        switch (choice)
        {
            case 1:
            {
                store.start_order();
                break;
            }
            case 2:
            {
                store.delete_order();
                break;
            }
            case 3:
            {
                store.display_orders();
                break;
            }
            case 4:
            {
                store.retrieve_pay_order();
                break;
            }
            case 5:
            {
                store.change_order();
                break;
            }
            case 6:
            {
                break;
            }
            default:
            {
                    cout<<"invalid input. Try Again!!"<<endl;
                    break;
            }
        }

    } while (choice != 6);
    cout<<"Thank You for using our system"<<endl;
    return 0;

}