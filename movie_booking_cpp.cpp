#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <conio.h>
#include <algorithm>
#include <cstring>

using namespace std;

int seata[100];
vector<int> bookeda;
vector<int> bookedb;
vector<string>userid;
int seatb[100];
int an=0;
int bn=0;
void setseats() //To set price of each seat
{
    for(int i=0;i<100;i++)
    {
        if(i<60){seata[i]=120;seatb[i]=120;}
        else{seata[i]=200;seatb[i]=200;}
    }
}

class User
{
    string name;
    string id;
    string password;
public:
    void regis() //To register as a user
    {
            cout<<"\n\n\n\t\tName: ";
            cin>>name;
            ID:
            cout<<"\n\n\n\t\tID: ";
            cin>>id;
            if(userid.empty() || (count(userid.begin(),userid.end(),id)==0))
            userid.push_back(id);
            else{cout<<"\n\n\t\t***************User ID already exists!!!*****************";goto ID;}
            cout<<"\n\n\n\t\tPassword: ";
            cin>>password;
            cout<<"\n\n\n\t\t\tRegistration successful!!!\n\n\t\t\tThanks for registering!!!\n\n";
    }
    string getid()
    {
        return id;
    }
    string getpassword()
    {
        return password;
    }
    void view() //To display user details
    {
        cout<<"\n\t***************User Details***************\n";
        cout<<"\n\t\tName: "<<name;
        cout<<"\n\t\tID: "<<id;
        cout<<"\n\n";
    }
};

class booking
{
    int bid;
    string id;
    char movie[25];
    float cost;
    vector<int> s;
public:
    void book(char m[],int bookid,string userid) //To book a seat using userid
    {
        strcpy(movie,m);
        bid=bookid;
        id=userid;
        cost=0;
        int n;
        cout<<"\n\n\t\tEnter seat no you want to book (-1 to stop): ";
        cin>>n;
        while(n!=-1)
        {
            if(strcmp(movie,"Twilight")==0)
            {
                if(!binary_search(bookeda.begin(),bookeda.end(),n))
                {
                    bookeda.push_back(n);
                    cost+=seata[n-1];
                    s.push_back(n);
                }

            }
            else
            {
               if(!binary_search(bookedb.begin(),bookedb.end(),n))
               {
                bookedb.push_back(n);
                cost+=seatb[n-1];
                s.push_back(n);
               }
            }
            cin>>n;
        }
        sort(bookeda.begin(),bookeda.end());
        sort(bookedb.begin(),bookedb.end());
        sort(s.begin(),s.end());
        char ch;
        cout<<"\n\t\tProceed to pay Rs."<<cost<<"(y/n): ";cin>>ch;
        if(ch=='y')
            {
                cout<<"\n\t\tYour tickets are booked!!!\n\t\tThank you for booking!!!";
                getch();
                system("cls");
                cout<<"\n\t***************Booking Details***************\n";
                view();
            }
        else
        {
            cout<<"\n\t\tYour transaction failed!!!";
        }
    }
    void view() //To display booking details
    {
        cout<<"\n\tBooking id: "<<bid;
        cout<<"\n\t\tMovie: "<<movie;
        cout<<"\n\t\tTime: 10:00 am";
        cout<<"\n\t\tYour seats: ";
        for(int i=0;i<s.size();i++)
        {
            cout<<s[i]<<" ";
        }
        cout<<"\n\t\tTicket fare: Rs."<<cost;
    }

    void cancel() //To remove seats from list of booked seats represented in vector
    {
        for(int i=0;i<s.size();i++)
        {
            vector<int>::iterator it;
            if(strcmp(movie,"Twilight")==0)
            {
               it=find(bookeda.begin(),bookeda.end(),s[i]);
               if(it!=bookeda.end()){bookeda.erase(it);}
            }
            else
            {
               it=find(bookedb.begin(),bookedb.end(),s[i]);
               if(it!=bookedb.end()){bookedb.erase(it);}
            }
        }
        s.clear();

    }
    int getbid()
    {
        return bid;
    }
    string getid()
    {
        return id;
    }
};

vector<booking> booked;

vector<User> user;

string login() //To check login details
    {
        string ID,p,f="not found";
        cout<<"\n\t\tID: ";cin>>ID;
        cout<<"\n\t\tPassword: ";cin>>p;
        for(int i=0;i<user.size();i++)
        {
            if(user[i].getid()==ID && user[i].getpassword()==p)
                {
                    cout<<"\n\t\tLogin successful!!!\n\n";
                    getch();
                    system("cls");
                    user[i].view();
                    return ID;
                }
        }
        return f;
    }

void display(char m[]) //To display seat availability for a show
{
    int scount=0;system("cls");
    vector<int>::iterator it;
    if(strcmp(m,"Twilight")==0)
    {
        for(int k=0;k<100;k++)
        {
            scount++;
            if(scount==1){cout<<"\n\t\t\t**************Executive(Rs.120)**************\n";}
            else if(scount==61)
            {
                cout<<"\n\t\t**************Premium(Rs.200)**************\n";
            }
            if(count(bookeda.begin(),bookeda.end(),scount)==0)
            {
                cout<<"\t"<<scount;
            }
            else
            {
                cout<<"\t"<<"__";
            }
            if(scount%10==0)cout<<"\n";
        }
        an=distance(bookeda.begin(),max_element(bookeda.begin(),bookeda.end()))+1;
        if(bookeda.empty()){an=0;}
        cout<<"\n\n\tBooked(__):"<<an<<"seats\t\tAvailable:"<<100-an<<"seats\t\tTotal: 100 seats\n\n";
    }
    else if(strcmp(m,"Maleficent")==0)
    {
       for(int k=0;k<100;k++)
        {
            scount++;
            if(scount==1){cout<<"\n\t\t\t**************Executive(Rs.120)**************\n";}
            else if(scount==61)
            {
                cout<<"\n\t\t**************Premium(Rs.200)**************\n";
            }
            if(!binary_search(bookedb.begin(),bookedb.end(),scount))
            {
                cout<<"\t"<<scount;
            }
            else
            {
                cout<<"\t"<<"__";
            }
            if(scount%10==0)cout<<"\n";
        }
        bn=distance(bookedb.begin(),max_element(bookedb.begin(),bookedb.end()))+1;
        if(bookedb.empty()){bn=0;}
        cout<<"\n\n\tBooked(__):"<<bn<<"seats\t\tAvailable:"<<100-bn<<"seats\t\tTotal: 100 seats\n\n";
    }
    else
    {
        cout<<"\n\t\tNo such movie available!!!";
        return;
    }
}

int menu() //To display the menu
{
    int n;
    cout<<"\t\t*************Welcome to book your show****************\n";
    cout<<"\n\t\t1. Register";
    cout<<"\n\t\t2. Display";
    cout<<"\n\t\t3. Book a show";
    cout<<"\n\t\t4. Cancel my show";
    cout<<"\n\t\t5. View my bookings";
    cout<<"\n\t\t6. Exit";
    cout<<"\n\n\tEnter your choice: ";cin>>n;
    system("cls");
    return n;
}

int create() //To create an User object
{
            User t;
            user.push_back(t);
            return(user.size()-1);
}

int bcreate() //To create a booking object
{
            booking b;
            booked.push_back(b);
            return(booked.size()-1);
}

int main()
{
    char ch;int ucount,bcount;string uid;
    string f="not found";char m[25];
    setseats();
    do
    {
        int n;
        n=menu();
        switch(n)
        {
        case 1:
            ucount=create();
            user.at(ucount).regis();
            break;
        case 2:
            cout<<"\n\tAvailable Shows: 1) Twilight\t\t 2) Maleficent\n";
            cout<<"\n\t\tMovie you would like to watch: ";
            cin>>m;
            display(m);
            break;
        case 3:
            uid=login();
            if(uid!=f)
            {
                cout<<"\n\tAvailable Shows: 1) Twilight\t\t 2) Maleficent\n";
                cout<<"\n\n\t\tMovie you would like to watch: ";
                cin>>m;
                display(m);
                bcount=bcreate();
                booked.at(bcount).book(m,bcount+1,uid);
            }
            else{cout<<"\n\t\tNo such login id found!!!";cout<<"\n\t\tPlease register before you book your show!!!";}
            break;
        case 4:
           uid=login();
           if(uid!=f)
           {
               int id;int flag=-1;
               cout<<"\n\t\tEnter the booking id: ";
               cin>>id;
               for(int k=0;k<booked.size();k++)
               {
                    if(booked[k].getbid()==id)
                    {flag=0;booked[k].cancel();booked.erase(booked.begin()+k);cout<<"\n\t\tYour show has been canceled!!!";break;}
               }
               if(flag==-1){cout<<"\n\t\tNo such booking id!!!";}
           }
           else{cout<<"\n\t\tNo such login id found!!!";}
           break;
        case 5:
            uid=login();
            if(uid!=f)
            {
                int b=0;
                cout<<"\n\t***************Booking Details***************\n";
                for(int j=0;j<booked.size();j++)
                {
                    if(booked[j].getid()==uid)
                    {
                        booked[j].view();b=1;
                    }
                }
                if(!b){cout<<"\n\t\tNo bookings made yet!!!";}
            }
            else{cout<<"\n\t\tNo such login id found!!!";}
            break;
        case 6:
            cout<<"\n\t\tThank you for visiting!!!\n\n";
            exit(0);
            break;
        default:
            cout<<"\n\t\tWrong Choice !!!\n\t\tCheck your choice and try again!!!!";
            break;
        }
    cout<<"\n\n\tDo you like to book the show (y/n): ";
    cin>>ch;
    system("cls");
    }while(ch=='y');
    cout<<"\n\n\t\t*****************Thank you for visiting!!!********************\n\n";
    return 0;

}
