#include <conio.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <windows.h>

using namespace std;

static int p = 0;
static int q = 0;

struct node
{
    string data;
    struct node *next;
};

class ListQueue //The waiting list is implemented using this queue(implementation using linked list)
{
    struct node *Listfront;
    struct node *Listrear;

public:
    ListQueue();
    void Listenqueue(string); //inserts the name in the waiting list.
    string Listdequeue();     //deletes the name.
    string Listpeek();        //Gives the top name on front.
    int Listsize();           //the size of the given waiting list
    bool ListisEmpty();       //checks whether list is empty.
    void Listdisplay();       //Display the entire waiting list containing all the names of the customers.
};

struct coach
{
    int fare;
    char couch_class[3];
    int total_berth;
    coach *next;
    char berth[40][10];
};

class train

{
    int total_coaches;
    coach *head;
    char train_name[10], arrival[5], depart[5], from[10], to[10];

public:
    char train_number[5];
    train();
    void install_train();            //details of train are input.
    void allotment(ListQueue *l);    //berth is alloted based on the class of coach and the train number
    void empty();                    //all seats are made empty while installing a coach
    void show();                     //Shows all the details for the ticket booked.
    void install_coach();            //details of coach are input.
    void cancellation(ListQueue *l); //Cancels the details input
    void timetable();                //Shows one the entire timetable (routes,train,destination)
    bool isFull();                   //checks whether the list is full or not.
};

ListQueue ::ListQueue()
{
    Listfront = NULL;
    Listrear = NULL;
}

void ListQueue ::Listenqueue(string x)
{
    struct node *temp;
    temp = new node();

    if (Listrear == NULL)
    {
        Listrear = temp;
        Listrear->next == NULL;
        Listrear->data = x;
        Listfront = Listrear;
    }

    else
    {
        Listrear->next = temp;
        temp->data = x;
        temp->next == NULL;
        Listrear = temp;
    }
}

void ListQueue ::Listdisplay()
{
    if (Listfront == NULL && Listrear == NULL)
        cout << " The List is empty" << endl;
    else
    {
        struct node *temp;
        temp = Listfront;

        cout << "Passengers present in the List: " << endl;
        while (temp != NULL)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
    }
    cout << endl;
}

string ListQueue ::Listdequeue()
{
    struct node *temp;

    if (Listfront == NULL && Listrear == NULL)
        return "-1";

    else
    {
        string x = Listfront->data;
        Listfront = Listfront->next;
        free(temp);
        return x;
    }
}

string ListQueue ::Listpeek()
{
    if (Listfront == NULL && Listrear == NULL)
    {
        cout << "The List is Empty" << endl;
        return 0;
    }

    else
    {
        string x = Listfront->data;
        return x;
    }
}

bool ListQueue ::ListisEmpty()
{
    if (Listfront == NULL && Listrear == NULL)

        return true;

    else

        return false;
}

int ListQueue ::Listsize()
{
    if (Listfront == NULL && Listrear == NULL)
        return 0;
    else
    {
        int count = 0;
        node *temp;
        temp = Listfront;
        while (temp != Listrear->next)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }
}

train ::train()
{
    head = NULL;
}

void train ::install_train()
{
    cout << "\nEnter train number: ";
    cin >> train_number;

    cout << "Enter the name of the train: " << endl;
    cin >> train_name;

    cout << "Enter the Arrival time: ";
    cin >> arrival;

    cout << "Enter the Departure time: ";
    cin >> depart;

    cout << "The Train will depart from: ";
    cin >> from;

    cout << "The Train shall reach: ";
    cin >> to;

    cout << "\nEnter the number of coaches: ";
    cin >> total_coaches;

    install_coach();
    empty();
    p++;

    cout << "\n\n\t\t\tThe Train has been successfully installed!" << endl;
}

void train ::install_coach()
{
    for (int i = 0; i < total_coaches; i++)
    {
        coach *temp = new coach;
        cout << "\nCoach number " << i + 1 << endl;
        cout << "Enter the coach class: ";
        cin >> temp->couch_class;
        cout << "Enter the fare for each seat: ";
        cin >> temp->fare;
        cout << "Enter the total number of berths per coach: ";
        cin >> temp->total_berth;

        temp->next = NULL;

        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            coach *ptr = head;
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }
            ptr->next = temp;
        }
    }
}

void train::empty()
{
    coach *temp;
    temp = head;

    for (int i = 0; i < total_coaches; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            strcpy(temp->berth[j], "Empty");
        }
        temp = temp->next;
    }
}

void train::allotment(ListQueue *l)
{

    int berth_number;
    char y[2];
    char passenger_name[10];

    cout << "Coach Class: ";
    cin >> y;

    coach *temp = head;
    for (int j = 0; j < total_coaches; j++)
    {

        if (strcmp(temp->couch_class, y) == 0)
        {
            cout << "Name of Passenger: ";
            cin >> passenger_name;

            if (isFull())
            {
                cout << "\n\n\tSorry! The train is already full! We shall add your name to the waiting list.\n\n";
                l->Listenqueue(passenger_name);
            }

            else
            {
                while (1)
                {
                    cout << "Please Enter Berth number: ";
                    cin >> berth_number;

                    if ((berth_number <= temp->total_berth) && (strcmp(temp->berth[berth_number - 1], "Empty") == 0))
                    {
                        strcpy(temp->berth[berth_number - 1], passenger_name);
                        cout << "\t\tTicket has been registered succesfully! Have a safe Journey!\n\n";
                        break;
                    }

                    else if ((berth_number <= temp->total_berth) && (strcmp(temp->berth[berth_number - 1], "Empty") != 0))
                    {
                        cout << "\nSorry, the berth has already been booked, please choose another berth!\n";
                        continue;
                    }

                    else
                    {
                        cout << "\nInvalid berth number. Please re-enter another berth-number.\n";
                        continue;
                    }
                }
            }
        }

        temp = temp->next;
    }
}

void train::show()
{
    cout << "************************************************************************************\n";
    cout << "\t\t\t\t\t" << train_name << "\n";
    cout << "************************************************************************************\n\n";
    cout << "The Train Number:                   " << train_number << "\t";
    cout << "The Number of coaches in the Train: " << total_coaches << "\n\n";
    cout << "TRAIN ROUTE:  " << endl
         << "The Train shall reach To:           " << to << "\t"
         << "From:                               " << from << "\n\n";
    cout << "TRAIN SCHEDULE: " << endl
         << "Departure time:                     " << depart << "\t"
         << "Arrival time:                       " << arrival << endl;
    cout << "\n************************************************************************************\n";

    coach *temp = head;
    for (int j = 0; j < total_coaches; j++)
    {
        cout << "\n\n\t\t\tPlease enter the Coach number " << j + 1 << endl
             << "\t\t\tClassof the Coach: " << temp->couch_class << endl
             << "\t\t\tFare: " << temp->fare << endl;

        for (int k = 0; k < temp->total_berth; k++)
        {
            if ((k) % 5 != 0)
            {
                if (k <= 8)
                    cout << k + 1 << " :" << temp->berth[k] << "\t";
                else
                    cout << k + 1 << ":" << temp->berth[k] << "\t";
            }

            else
            {
                if (k <= 8)
                    cout << endl
                         << k + 1 << " :" << temp->berth[k] << "\t";
                else
                    cout << endl
                         << k + 1 << ":" << temp->berth[k] << "\t";
            }
        }
        temp = temp->next;
    }
}

void train ::cancellation(ListQueue *l)
{
    int berth_number;
    char y[2];

    cout << "\nClass of the coach: ";
    cin >> y;

    coach *temp = head;
    for (int j = 0; j < total_coaches; j++)
    {

        if (strcmp(temp->couch_class, y) == 0)
        {

            while (1)
            {
                cout << "Enter the berth number: ";
                cin >> berth_number;

                if ((berth_number <= temp->total_berth) && (strcmp(temp->berth[berth_number - 1], "Empty") != 0) && !(isFull()))
                {
                    strcpy(temp->berth[berth_number - 1], "Empty");
                    cout << "\t\t\t Ticket succesfully cancelled! Thank you!\n\n";
                    break;
                }

                else if ((berth_number <= temp->total_berth) && (strcmp(temp->berth[berth_number - 1], "Empty") != 0) && (isFull()))
                {
                    string x = l->Listdequeue();
                    strcpy(temp->berth[berth_number - 1], (x).c_str());
                    cout << "\t\t\t Ticket succesfully cancelled! Thank you!\n\n";
                    break;
                }

                else if ((berth_number <= temp->total_berth) && (strcmp(temp->berth[berth_number - 1], "Empty") == 0))
                {
                    cout << "\nThe berth is already empty!\n";
                    continue;
                }

                else
                {
                    cout << "\nInvalid berth number. Please re-enter the berth number.\n";
                    continue;
                }
            }
        }

        temp = temp->next;
    }
}

void train ::timetable()
{
    cout << "************************************************************************************\n";
    cout << "\t\t\t\t\t" << train_name << "\n";
    cout << "************************************************************************************\n\n";
    cout << "Number of the Train:         " << train_number << endl;
    cout << "Number of coaches:           " << total_coaches << endl;
    cout << "TRAIN ROUTE:                 " << endl;
    cout << "The Train shall reach To:    " << to << endl;
    cout << "From:                        " << from << endl;
    cout << "TRAIN SCHEDULE:              " << endl;
    cout << "Departure time:              " << depart << endl;
    cout << "Arrival time:                " << arrival << endl;
    cout << "\n----------------------------------------------------------------------------------\n";
}

bool train ::isFull()
{
    coach *temp = head;
    for (int j = 0; j < total_coaches; j++)
    {
        for (int i = 0; i < temp->total_berth; i++)
        {
            if (strcmp(temp->berth[i], "Empty") == 0)
                return false;
        }
        temp = temp->next;
    }
    return true;
}

int main()
{
    train t[10];
    ListQueue l[10];

    while (1)
    {
        system("Color 17");
        cout << "\n\n\n********************************************************************************\n\n\t\t\t WELCOME TO THE INDIAN RAILWAYS\n\n********************************************************************************";
        cout << "\n\n\t\t\t\t MAIN MENU";
        cout << "\n\n\t\t\tEnter any one of the option: ";
        cout << "\n\n\t\t1. Admin user";//Admin mode
        cout << "\n\t\t2. Passenger user";//Passenger mode
        cout << "\n\t\t3. Exit";

        int choice;
        cout << "\n\nPlease enter your Choice: ";
        cin >> choice;
        system("Color 70");
        switch (choice)
        {

        case 1:
        {
            system("cls");
            cout << "\n\n--------------------------------------------------------------------------------\n\n\t\t\t\t ADMIN SECTION\n\n--------------------------------------------------------------------------------";
            cout << "\n\n\t\t\tEnter any one of the option: ";
            cout << "\n\n\t\t1. Install Train";
            cout << "\n\t\t2. Show all available trains";
            cout << "\n\t\t3. Show the tickets of a train";
            cout << "\n\t\t4. Show the waiting list of a train";
            cout << "\n\t\t5. Return to main menu";

            int choice1;
            cout << "\n\nChoice: ";
            cin >> choice1;

            switch (choice1)
            {
            case 1:
            {
                system("cls");
                t[p].install_train();
                break;
            }

            case 2:
            {
                system("cls");
                cout << "\t\t\t Showing all the available trains!\n\n";
                for (int i = 0; i < p; i++)
                {
                    t[i].timetable();
                }
                break;
            }

            case 3:
            {
                system("cls");
                cout << "\nTrain no: ";
                char x[5];
                cin >> x;
                for (int i = 0; i < p; i++)
                {
                    if (strcmp(t[i].train_number, x) == 0)
                    {
                        t[i].show();
                    }
                }
                break;
            }

            case 4:
            {
                system("cls");
                cout << "\nPlease enter the details of the train\n\n";
                cout << "\nTrain number: ";
                char x[5];
                cin >> x;

                for (int i = 0; i < p; i++)
                {
                    if (strcmp(t[i].train_number, x) == 0)
                    {
                        l[i].Listdisplay();
                    }
                }
            }

            case 5:
            {
                break;
            }
            }

            break;
        }

        case 2:
        {
            system("cls");
            cout << "\n\n--------------------------------------------------------------------------------\n\n\t\t\t\t PASSENGER USER\n\n--------------------------------------------------------------------------------";
            cout << "\n\n\t\t\tEnter any one of the option: ";
            cout << "\n\n\t\t1. Show schedule of all trains";
            cout << "\n\t\t2. Book tickets";
            cout << "\n\t\t3. Show the booked tickets";
            cout << "\n\t\t4. Cancel tickets";
            cout << "\n\t\t5. Check if a train is full or not";
            cout << "\n\t\t6. Check the waiting list";
            cout << "\n\t\t7. Return to main menu";

            int choice2;
            cout << "\n\nChoice: ";
            cin >> choice2;

            switch (choice2)
            {

            case 1:
            {
                system("cls");
                cout << "\t\t\t Showing all the available trains!\n\n";
                for (int i = 0; i < p; i++)
                {
                    t[i].timetable();
                }
                break;
            }

            case 2:
            {
                system("cls");
                cout << "\nPlease enter the following details for booking tickets\n\n";
                cout << "\nTrain number: ";
                char x[5];
                cin >> x;
                int flag = 0;

                for (int i = 0; i < p; i++)
                {
                    if (strcmp(t[i].train_number, x) == 0)
                    {
                        flag = 1;
                        t[i].allotment(&l[i]);
                    }
                }

                if (flag == 0)
                {
                    cout << "\nSorry! No such train found.\n";
                }

                break;
            }

            case 3:
            {
                system("cls");
                cout << "\nPlease enter the details\n\n";
                cout << "\nTrain number: ";
                char x[5];
                cin >> x;
                int flag = 0;

                for (int i = 0; i < p; i++)
                {
                    if (strcmp(t[i].train_number, x) == 0)
                    {
                        flag = 1;
                        t[i].show();
                    }
                }

                if (flag == 0)
                {
                    cout << "\nSorry! No such train found.\n";
                }
                break;
            }

            case 4:
            {
                system("cls");
                cout << "\nPlease enter the following details for cancelling tickets\n\n";
                cout << "\nTrain number: ";
                char x[5];
                cin >> x;
                int flag = 0;

                for (int i = 0; i < p; i++)
                {
                    if (strcmp(t[i].train_number, x) == 0)
                    {
                        flag = 1;
                        t[i].cancellation(&l[i]);
                    }
                }

                if (flag == 0)
                {
                    cout << "\nSorry! No such train found.\n";
                }
                break;
            }

            case 5:
            {
                system("cls");
                cout << "\nPlease enter the details\n\n";
                cout << "\nTrain number: ";
                char x[5];
                cin >> x;
                int flag = 0;

                for (int i = 0; i < p; i++)
                {
                    if (strcmp(t[i].train_number, x) == 0)
                    {
                        flag = 1;
                        if (t[i].isFull())
                        {
                            cout << "\n\t\t\tSorry! The train is full!\n";
                        }
                        else
                            cout << "\n\t\t\tThe train is not full!\n";
                    }
                }

                if (flag == 0)
                {
                    cout << "\nSorry! No such train found.\n";
                }
                break;
            }

            case 6:
            {
                system("cls");
                cout << "\nPlease enter the details of the train\n\n";
                cout << "\nTrain number: ";
                char x[5];
                cin >> x;

                for (int i = 0; i < p; i++)
                {
                    if (strcmp(t[i].train_number, x) == 0)
                    {
                        l[i].Listdisplay();
                    }
                }
            }
            }
            break;
        }

        case 3:
        {
            cout << "\n\n\t\tThank you! Visit again!";
            cout << "\n\n\n\tDone by:\n\n\t\tParva Dhami (202001117)\n\n\t\tDevarsh Nagrecha (202001224)\n\n";
            exit(0);
        }

        default:
        {
            cout << "\n\nEnter valid choice" << endl;
        }
        }
    }
}
