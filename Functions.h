#ifndef AIRLINES_FUNCTIONS
#define AIRLINES_FUNCTIONS
#include "Class_Definitions.h"
#include "GET_Disk.h"
#include <cstdlib>
#include <vector>
#include <fstream>
#include <map>
#include<conio.h>

using namespace std;

void flight_booker(string _username);
void store_name(User _temp_user);
void available_flights();
void access_user(string _username);
void my_flights(string _username);
void delete_booking(string _username);
void update_bookings();
void store_bookings(string _username, string _flight_id, int _line);

string enter_pass() {
    char pin[100];
    int k=0;
    //cout<<"Enter  password : ";
    while(pin[k-1]!='\r') {
        pin[k]=getch();
        if(pin[k-1]!='\r') {
            cout<<"*";
        }
        k++;

    }
    pin[k-1]='\0';
    cout<<endl;
    return pin;
}



void wallet(string _username);
void check_balance(string wallet_id);
bool make_payment(string _flight_id, string _username);

bool check_cycle;



//Log-in System
void log_in(){
    check_cycle = true;//initially when function is called it should allow cycle to try to match passwords and usernames

    string temp_username;
    string temp_password;

    do {
        cout << "Enter User Name: ";
        cin >> temp_username;
        cout << "Enter Password: ";
        temp_password = enter_pass();
        //cin >> temp_password;

        if (users.find(temp_username) != users.end()) {
            User temp_user = users[temp_username];
            if (temp_user.getPassword() == temp_password) {
                access_user(temp_username);
            } else {
                cout << "Incorrect username or password!" << endl;
            }
        } else {
            cout << "User " << temp_username << " does not exist." << endl;
        }
    }while(check_cycle);
}
void access_user(string _username) {
    cout << "access granted!" << endl;
    check_cycle = false;
    bool portal_cycle = true;
    int portal_nav;

    do {

        cout << "-----Welcome to the User Portal-----\n";
        cout << "Press 1 Preview My Bookings\n";
        cout << "Press 2 Book Flight\n";
        cout << "Press 3 Delete Booking\n";
        cout << "Press 4 Show Available Flights\n";
        cout << "Press 5 My Wallet\n";
        cout << "Press 9 Log out\n";
        cout << "Please Enter Your Choice: ";
        cin >> portal_nav;

        switch (portal_nav) {
            case 1:
                my_flights(_username);
                break;
            case 2:
                flight_booker(_username);
                break;
            case 3:
                delete_booking(_username);
                break;
            case 4:
                available_flights();
                break;
            case 5:
                wallet(_username);
                break;
            case 9:
                cout << "Logging user out ... " << endl;
                portal_cycle = false;
            break;
            default:
                cout << "Undefined input" << endl;
                break;
        }
    }while (portal_cycle);
}



//Fight Booker
void flight_booker(string _username){

    cout<<"-----Flight Booker-----"<<endl;

    available_flights();
    User temp_user;
    Flight temp_flight;
    string temp_flight_id;
    string old_flight_id;

    do{
        cout<<"Enter the Flight ID From the above: ";
        cin>>temp_flight_id;
    }while(flights.find(temp_flight_id) == flights.end());


    if(make_payment(temp_flight_id, _username)){
        //ADD Flight to User
        if (users.find(_username) != users.end()) {
            //copies user data to temporary user and add flight to the temporary user, replace the old current user by the new temporary user
            temp_user = users[_username];
            temp_flight = flights[temp_flight_id];

            Booking temp_booking;
            temp_booking.set_booking(_username, temp_flight_id, line);
            bookings[line] = temp_booking;

            temp_user.add_flight(temp_flight_id, line);
            temp_flight.add_passenger(_username, line);

            users[_username] = temp_user;
            flights[temp_flight_id] = temp_flight;

            line++;
            store_bookings(temp_flight_id, _username, line);
        } else{
            cout << "User " << _username << " does not exist when adding to user." << endl;
        }

    }else{
        cout<<"couldn't book, not enough balance."<<endl;
    }
}
//Delete any flight user booked
void delete_booking(string _username){
    User temp_user;
    Flight temp_flight;
    string temp_flight_id;

    //Remove Flight Id from User
    temp_user = users[_username];
    do{
        cout<<"Enter the Flight ID From the above: ";
        cin>>temp_flight_id;
    }while(temp_user.get_my_flights().find(temp_flight_id) == temp_user.get_my_flights().end());
    
    // temp_flight = flights[temp_flight_id];

    map<string, int> temp_my_flights = temp_user.get_my_flights();

    bookings.erase(temp_my_flights[temp_flight_id]);
    temp_user.get_my_flights().erase(temp_flight_id);
    flights[temp_flight_id].get_my_passengers().erase(_username);

    users[_username] = temp_user;
    update_bookings();
}

void store_bookings(string _username, string _flight_id, int _line){ 
    ofstream o_booking_list("BOOKING_LIST.txt", ios::app);
    if(o_booking_list.fail()){
        cerr<<"Booking file not found!";
    }

    o_booking_list<<_line<<"."<<_username<<"$"<<_flight_id<<endl;
     
    o_booking_list.close();
}

void update_bookings(){ 
    ofstream o_booking_list("BOOKING_LIST.txt", ios::out);
    if(o_booking_list.fail()){
        cerr<<"Booking file not found!";
    }
    
    for (const auto& bookings_map : bookings){
        Booking temp_booking = bookings[bookings_map.first];
        o_booking_list<<temp_booking.get_line()<<"."<<temp_booking.get_flight_id()<<"$"<<temp_booking.get_username()<<endl;
    }

    o_booking_list.close();
}



//User Creator
void create_user(){
    User temp_user;
    string temp_username;
    string temp_password;

    cout<<"Enter User Name: ";
    cin>>temp_username;
    cout<<"Enter Password: ";
    temp_password = enter_pass();

    //temporary
    temp_user.set_details(temp_username, temp_password);
    temp_user.set_balance(70000);

    store_name(temp_user);// to disk
    users[temp_username] = temp_user;// to memory
}
void store_name(User temp_user){
    ofstream o_name_list("NAME_LIST.txt", ios::app);
    if(o_name_list.fail()){
        cerr<<"NAME_LIST not found, Users not stored to disk!";
        exit(1);
    }

    o_name_list<<temp_user.getUsername()<<"$"<<temp_user.getPassword()<<"*"<<temp_user.get_balance()<<endl;
    o_name_list.close();
}


//Wallet Access
void wallet(string _username){
    int ch;
    bool wallet_cycle = true;

    do {
        cout << "1. Check balance " << endl;
        cout << "9. Return Back" << endl;
        cout << "Enter a number to choose: ";
        cin >> ch;
        switch (ch) {
            case 1:
                check_balance(_username);
                break;
            case 9:
                cout << "Returning back ... " << endl;
                wallet_cycle = false;
                break;
            default:
                cout<<"Enter a valid choice!"<<endl;
                break;
        }

    } while (wallet_cycle);
}
void check_balance(string _username){
    cout<<"Your current balance is: "<<users[_username].get_balance()<<endl;
}


//Make Payment
bool make_payment(string _flight_id, string _username){
    Flight temp_flight = flights[_flight_id];
    string order_code = "o_"+generateRandomString();
    double amount = temp_flight.get_price();
    bool proceed = false;

    //spend balance for booking
    User temp_user = users[_username]; //makes a copy of the user
    //cout<<"Before payment Balance: "<<wallets[wallet_id].get_balance()<<endl;
    proceed = temp_user.spend(amount); // apply changes(spend some money) to the user copy
    users[_username] = temp_user;   //replace the actual user by the copy

    cout<<"Remaining Balance: "<<users[_username].get_balance()<<endl;
    cout<<"your order code is: "<<order_code<<endl;
    
    return proceed;
}





//All available Flights
void available_flights(){
    for (auto flight_map = flights.begin(); flight_map != flights.end(); ++flight_map) {
        cout << "flight ID: " << flight_map->first<< "\t " <<flight_map->second.get_flight_detail()<< endl;
    }

    cout<<endl;
}
//My Flights View
void my_flights(string _username){
    User cur_user;

    //find current user using his username
    if (users.find(_username) != users.end()) {
        cur_user = users[_username];
    } else {
        cout << "User " << _username << " does not exist." << endl;
    }

    //get the current(logged in user) booked flights
    Flight temp_flight;


    if(cur_user.get_my_flights().empty()){
        cout << "No Flights Booked Yet." << endl;
        return;
    }


    //get the flight details from the flights map using the _flight_id
    cout<<"Your Flights are: "<<endl;

    for (const auto& flight_map : cur_user.get_my_flights()){
        temp_flight = flights[flight_map.first];
        cout << "Flight " << temp_flight.get_flight_id() << " " << temp_flight.get_flight_detail()<<", Line: "<<cur_user.get_line(flight_map.first)<<endl;
    }
}

#endif