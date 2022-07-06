//
//      Data Structures and Algorithm Project by Pair
//              Student Election Voting System
//
//      Submitted by:
//                   John Ross Ferrancullo
//                   Zarene Claire Guingab
//                      BSCS - 2A - M

#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>                          //libraries
#include <string>
#include <array>
#define MAX 100


using namespace std;

//Structure data for voter profile
typedef struct voter{
    string firstN;                          //for first name
    string lastN;                           //for last name
    string course;                          //for course
    string pw;                              //for account password
    string id;                              //for student id
    string pres;                            //voting history data for president
    string vp;                              //voting history data for vice president
    string sec;                             //voting history data for secretary
}VOT;

//Class - student record
class record{

//Private class
private:
    VOT vt[MAX];                            //structured voter profile
    int last;                               //last structure indicator
    int locate(string n);                   //locate function
    int pos(string n);                      //pos function for sorting

//Public class
public:
    void makenull()                         //make null function
    {
        last = -1;                          //set last to -1
    };
    void add(VOT a);                        //voter data insert function
    void addhis(VOT a);                     //voter history data insert function
    void login();                           //login fucntion
    void card();                            //function for usb drive insert checker
    void history();                         //display function for voter history
    void retrieve();                        //file data retrieve function
    void save();                            //data save to file function
    void reg();                             //voter data registration function
    int isfull();                           //determine if record is full
    int isempty();                          //determine if record is empty
    int votingMenu();                       //menu
};

//Add
void record::add(VOT a)
{
    int i, p;

    if(isfull())
    {
        cout << "\n\t\t\tList is full\n";                       //call isfull function
        getch();
    }

    else
    {
        if(locate(a.pw)>=0)                                     //compare locate function return value
        {
            system("cls");
            cout << "\n================================================================================";
            cout << "\t\t                   REGISTER MODE         ";
            cout << "\n================================================================================";                             //if locate return value greater than or equal to 0 display record found and try again
            cout << "\n\n\t\t   Duplicate Record Found! Register Again.\n";
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n================================================================================";

        }
        else
        {
            p = pos(a.pw);                                      //if decision return false call pos function
            for(i=last;i>=p;i--)
            {
                vt[i+1] = vt[i];                                //move existing data from the specified location all towards to the right
            }
            vt[p].firstN = a.firstN;
            vt[p].lastN = a.lastN;                              //save data from VOT a to VOT vt structure
            vt[p].course = a.course;
            vt[p].id = a.id;
            vt[p].pw = a.pw;
            last++;                                             //increment last indicator
        }
    }
}

//Add voter history
void record::addhis(VOT a)
{
    int i;
    i = locate(a.pw);                                            //call locate to locate record
    if(i<0)
    {
        cout << "\n\t\t\tVoter record is not found.\n";          //if locate return value less than to 0 display record not found
        getch();
    }
    else
    {
        vt[i].pres = a.pres;
        vt[i].vp = a.vp;                                         //if decision return false, save voting history data in VOT a t VOT vt pres, vp, sec
        vt[i].sec = a.sec;
    }
}

//Display voter history
void record::history()
{
    int i, k ,l;

    system("cls");
    if(isempty())
    {
        cout << "\n\t\t\tHistory is empty.";                    //call isempty function then determine value returned
        getch();
    }
    else
    {
        cout << "\n================================================================================\n";
        cout << "\t\t                  VOTING HISTORY         ";                                            //if false branch out to voting history
        cout << "\n================================================================================";

        cout << "\n\t\t\t\tFor President:\n";
        for (i=0;i<=last;i++)
        {
            cout << setw(44) << vt[i].pres << endl;             //display data stored in pres
        }

        cout << "\n\t\t\t\tFor Vice President:\n";
        for (k=0;k<=last;k++)
        {
            cout << setw(45) << vt[k].vp << endl;               //display data stored in vp
        }

        cout << "\n\t\t\t\tSecretary:\n";
        for (l=0;l<=last;l++)
        {
            cout << setw(43) << vt[l].sec << endl;              //display data stored in sec
        }
    }
}

//Is full
int record::isfull()
{
    return(last == MAX-1);                                      //compare last to MAX-1
}

//Is empty
int record::isempty()
{
    return(last == -1);                                         //compare last to -1
}

//Locate
int record::locate(string n)
{
    int i;
    for(i=0;i<=last;i++)
    {
        if(vt[i].pw.compare(n)==0)                              //compare name passed to name from record
        {
            return(i);                                          //if true return index
        }

    }
    return(-1);                                                 //else return -1
}

//Pos(for sorting data)
int record::pos(string n)
{
    int i;
    for(i=0;i<=last;i++)
    {
        if(vt[i].pw.compare(n)>0)                               //compare name passed to name from record
        {
            return (i);                                         //return index value
        }
    }
    return (i);
}

//Save
void record::save()
{
    fstream f;
    int i;

    f.open("E:\\Student profile.dbf", ios::out);                //open dbf file for saving data

    for(i=0;i<=last;i++)
    {
        f << vt[i].firstN << " " << vt[i].lastN << " " << vt[i].id << " " << vt[i].course << " " << vt[i].pw << endl;          //save first name, last name, student id, course, and password from record to dbf file
    }
    f.close();                                                  //close file
}

//Retrieve
void record::retrieve()
{
    fstream f;
    int i;
    VOT x;

    f.open("E:\\Student profile.dbf", ios::in);                 //open file for data retrieve
    if(!f)
    {
        f.open("E:\\Student profile.dbf", ios::out);            //if file is NULL create dbf file
    }
    else
    {
        while(true)                                             //set loop to indefinite
        {
            f >> x.firstN >> x.lastN >> x.id >> x.course >> x.pw;               //read first name, last name, student id, course and password from file
            if(f.eof())
            {
                break;                                          //if pointer reach end of file - break loop
            }
            add(x);                                             //pass data read fromo file to add() function to be inserted in structure record
        }
    }
    f.close();                                                  //close file
}

//Menu
int record::votingMenu()
{
    int i, op;

    system("cls");
    cout << "\n================================================================================\n";
    cout << "\t\t          STUDENT VOTING SYSTEM MENU      ";
    cout << "\n================================================================================";
    cout << "\n\t\t\t   1. Student Election\n";                                                                //display voting menu
    cout << "\n\t\t\t   2. Voting History\n";
    cout << "\n\t\t\t   3. Exit\n";

    cout << "\n\t\t\t   Select 1-3: ";
    cin >> op;                                                  //store data enter in op

    return(op);                                                 //return op value

}

//Voter registration
void record::reg()
{
    VOT a;

    system("cls");

    cout << "\n================================================================================\n";
    cout << "\t\t                   REGISTER MODE         ";
    cout << "\n================================================================================\n";
    cout << "\t\t\tInput Required Information\n";

    cout << "\n\t\t\tFirst Name: ";
    cin >> a.firstN;                                                                                        //enter first name then store in a.firstN
    cout << "\n\t\t\tLast Name: ";
    cin >> a.lastN;                                                                                         //enter last name then store in a.lastN
    cout << "\n\t\t\tStudent ID: ";
    cin >> a.id;                                                                                            //enter student id then store in a.id
    cout << "\n\t\t\tCourse(abbrev. only): ";
    cin >> a.course;                                                                                        //enter course then store in a.course
    cout << "\n\t\t\tPassword(5 digits): ";
    cin >> a.pw;                                                                                            //enter password then store in a.pw
    cout << "\n\t  The information is successfully added. You are now registered!";
    cout << "\n================================================================================";

    add(a);                                                     //pass data in VOT a to add function
    getch();
    login();                                                    //call log in function
}

//Login
void record::login()
{
    fstream f;
    VOT x;
    std::array <std::string, MAX> temp{};                       //define array temp
    int p, a=0, i=0, j=0;
    char choice;
    char c=' ';
    char pword[10];                                             //char pword with 10 size

    system("cls");
    cout << "\n================================================================================" << endl;
    cout << "\n\t\t\t   Enter Password: ";
    while(i<10)
    {
        pword[i] = getch();                                     //store input in pword
        c = pword[i];                                           //copy data stored in pword to c
        if(c == 13)
        {
            break;                                              //check if c is equal to 13 -  if true break from while loop
        }
        else
        {
            cout << "*";
        }
        i++;                                                    //increment index
    }

    pword[i]='\0';                                              //set pword to null pointer
    i=0;                                                        //declare i = 0

    f.open("E:\\Student profile.dbf", ios::in);                 //open file
    if(!f)
    {
        f.open("E:\\Student profile.dbf", ios::out);            //if file is null create file
    }
    else
    {
        while(true)                                             //set loop to indefinite
        {
            f >> x.firstN >> x.lastN >> x.id >> x.course >> x.pw;                               //save data from file to structure
            if(f.eof())
            {
                break;                                           //if file = eof break from loop
            }
            temp[j] = x.pw;                                      //copy data from structure x.pw to temp

            if(pword==temp[j])                                   //compare pword to temp
            {
                system("cls");
                cout << "\n================================================================================\n";
                cout << "\t                WELCOME TO STUDENT VOTING SYSTEM!!!         ";
                cout << "\n================================================================================" << endl;
                cout << "\n\t\t\tYou have already voted!" << endl;
                cout << "\n\t\t\tThank you for using our program." << endl;                                             //if pword is equal to temp display you've already voted
                cout << "\n\t\t\tTerminating program..." << endl;
                getch();
                exit(0);                                        //terminate program
            }
            j++;                                                //increment temp index j
            flush(f);                                           //flush file buffer
        }
    }
    f.close();                                                  //close file
    flush(f);

    if(locate(pword)>=0)
    {
        cout << "\n\n\n\t\t\t   WELCOME!!";
        cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t   Press any key to continue....!!";
        cout << "\n================================================================================" << endl;       //locate pword in structure - if return value is greater than or equal to 0 continue to welcome
        getch();
    }
    else
    {
        cout << "\n\n\t\t\t   INCORRECT PASSWORD!!" << endl;    //else display password is incorrect
        cout << "\n\t\t\t   Register to Vote?(Y/N): ";          //ask user if he/she wants to register
        cin >> choice;

        switch(toupper(choice))
        {
        case 'Y':
            reg();                                              //if Y go to registration
            break;

        case 'N':
            login();                                            //if N loop back to login
            break;

        default:
            cout << "\n\t\t\t\tInvalid choice!\n";              //unknown input
            getch();
        }
    }
}

//Insert Card(usb drive)
void record::card()
{
    fstream f;

    while(true)                                                  //loop
    {
        f.open("E:\\Student profile.dbf", ios::in);              //open file in loop
        if(!f)
        {
            system("cls");
            cout << "Please insert card";
            getch();

            system("cls");
            cout << "Please insert card.";                       //if file is null - display please insert card (usb drive)
            getch();

            system("cls");
            cout << "Please insert card..";
            getch();

            system("cls");
            cout << "Please insert card...";
            getch();
        }
        else                                                    //if file exist continue and break from loop
        {
            cout << "\n================================================================================" << endl;
            cout << "\n\n\n\t                WELCOME TO STUDENT VOTING SYSTEM!!!         ";
            cout << "\n\n\n\n\n\n\n\n================================================================================" << endl;
            getch();
            break;
        }

    }
    flush(f);                                                   //flush file buffer
    f.close();                                                  //close file
}

int main()
{
    VOT y;
    record s;                                                   //declare public class elements in main
    int i, op, c1, c2, c3, p=0;
    char confirm;
    char c=' ';
    char pword[10];

    std::array <std::string, 2> pres {"Frenzy Reyes", "Rasheed Riga"};
    std::array <std::string, 2> vp {"Angelo Andres", "Joshua Garcia"};              //candidates stored in array using array class
    std::array <std::string, 2> sec {"Jeorge Dans", "Mika Gajeto"};

    system("COLOR B4");                                         //change console background and foreground color
    s.makenull();                                               //call makenull function
    s.retrieve();                                               //call retrieve function
    s.card();                                                   //call card function
    s.login();                                                  //call login function

    system("cls");
    while(true)                                                 //loop set to always true
    {
        op=s.votingMenu();                                      //call voting menu and store return value into op
        switch(op)                                              //switch case using op
        {
        case 1:                                                 //case 1 voting system,

            system("cls");
            cout << "\n================================================================================\n";
            cout << "\t\t                   VOTE WISELY         ";
            cout << "\n================================================================================";
            cout << "\n\t\tWho would you like to be the next President?\n" << endl;
            for(i=0;i<2;i++)
            {
                std::cout << setw(20) << i+1 << " ." << pres[i] << endl;                                        //display elements in array pres
            }
            while(true)
            {
                cout << "\n\t\tEnter the number of your choice!: ";                                             //while loop set to always true - ask user to whom he/she will vote for pres
                cin >> c1;                                                                                      //store choice in c1
                if(c1>2)
                {
                    cout << "\n\t\tUnknown input." << endl;                                                     //if c1 > 2 display unknown input and continue to loop
                    getch();
                }
                else
                {
                    break;                                                                                      //else break from loop
                }
            }
            y.pres = pres[c1-1];                                                                                //store data from array pres with index of c1 -1 to structure y

            system("cls");
            cout << "\n================================================================================\n";
            cout << "\t\t                   VOTE WISELY         ";
            cout << "\n================================================================================";
            cout << "\n\t\tWho would you like to be the next Vice President?\n" << endl;
            for(i=0;i<2;i++)
            {
                std::cout << setw(20) << i+1 << " ." << vp[i] << endl;                                          //display elements in array vp
            }
            while(true)
            {
                cout << "\n\t\tEnter the number of your choice!: ";                                             //while loop set to always true - ask user to whom he/she will vote for vp
                cin >> c2;                                                                                      //store choice in c2
                if(c2>2)
                {
                    cout << "\n\t\tUnknown input." << endl;                                                     //if c2 > 2 display unknown input and continue to loop
                    getch();
                }
                else
                {
                    break;                                                                                      //else break from loop
                }
            }
            y.vp = vp[c2-1];                                                                                    //store data from array vp with index of c2-1 to structure y

            system("cls");
            cout << "\n================================================================================\n";
            cout << "\t\t                   VOTE WISELY         ";
            cout << "\n================================================================================";
            cout << "\n\t\tWho would you like to be the next Secretary?\n" << endl;
            for(i=0;i<2;i++)
            {
                std::cout << setw(20) << i+1 << " ." << sec[i] << endl;                                         //display elements in array vp
            }
            while(true)
            {
                cout << "\n\t\tEnter the number of your choice!: ";                                             //while loop set to always true - ask user to whom he/she will vote for sec
                cin >> c3;                                                                                      //store choice in c3
                if(c3>2)
                {
                    cout << "\n\t\tUnknown input." << endl;                                                     //if c3 > 2 display unknown input and continue to loop
                    getch();
                }
                else
                {
                    break;                                                                                      //else break from loop
                }
            }
            y.sec = sec[c3-1];                                                                                  //store data from array sec with index of c3-1 to structure y

            system("cls");
            cout << "\n================================================================================\n";
            cout << "\t\t                   VOTE WISELY         ";
            cout << "\n================================================================================";
            cout << "\n\t\t\tREMINDER: YOU CAN ONLY VOTE ONCE!" << endl;
            cout << "\n\t\tONCE YOU'VE VOTED YOU CANNOT LOGIN YOUR ACCOUNT AGAIN TO VOTE!" << endl;
            cout << "\n\t\t\tDo you want to continue?(Y/N): ";                                                  //voting confirmation
            cin >> confirm;

            switch(toupper(confirm))
            {
                case 'Y':                                                                   //if user enter Y

                    cout << "\n\t\tEnter your password to confirm your vote: ";             //user password confirmation

                    while(p<10)
                    {
                        pword[p] = getch();
                        c = pword[p];
                        if(c == 13)
                        {
                            break;                                                          //hide inputted password in ***** same with login function
                        }
                        else
                        {
                            cout << "*";
                        }
                        p++;
                    }

                    pword[p]='\0';
                    p=0;

                    y.pw = pword;                                                           //store password to structure y
                    //cin >> y.pw;
                    break;

                case 'N':                                                                   //if user enter N
                    system("pause");
                    exit(0);                                                                //terminate program
                default:
                    cout << "\n\t\tUnknown input!" << endl;                                 //unknown input repeat loop
                    getch();
            }

            s.addhis(y);                                                                    //pass data from structure y to addhis function
            break;

        case 2:
            s.history();                                                                    //call voting history function
            getch();
            break;

        case 3:
            s.save();                                                                       //call save function
            exit(0);                                                                        //terminate program

        default:
            cout << "\n\t\t\tSelect 1-3 only!.\n";                                          //invalid input repeat loop
            getch();
        }
    }

return(0);
}
