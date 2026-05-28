#ifndef AIRLINES_FUNCTIONS
#define AIRLINES_FUNCTIONS
#include "Class_Definitions.h"
#include "Get_Disk.h"
#include <cstdlib>
#include <vector>
#include <fstream>
#include <map>
#include<conio.h>

using namespace std;

inline bool user_has_booking(const string& user, const string& flight_id) {
    for (auto& entry : bookings)
        if (entry.second.get_username() == user && entry.second.get_flight_id() == flight_id)
            return true;
    return false;
}

void enter_delay() {
    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

void flight_booker(string _username);
void store_name(User _temp_user);
void available_flights();
void access_user(string _username);
vector<pair<string, Flight>> my_flights(string _username);
void cancel_booking(string _username);
void update_bookings();
void update_users();
void store_bookings(string _username, string _flight_id, int _line, bool _is_paid, Datetime _expiry);
vector<pair<string, Flight>> filter_flights();
void enter_delay();
void show_my_flights(string _username);

string enter_pass() {
    char pin[100];
    int k=0;
    
    while(true) {
        char ch = getch();
        
        if(ch == '\r') {
            pin[k] = '\0';
            break;
        } else if(ch == '\b') {
            if(k > 0) {
                cout << "\b \b"; // Move cursor back, print space, move cursor back again
                k--;
            }
        } else {
            pin[k] = ch;
            cout << "*";
            k++;
        }
    }
    
    cout << endl;
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

    cout<<"\n#########################################\n---------------- Log-in -----------------\n#########################################\n"<<endl;

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
    string choice;

    do {
        cout << "\n#########################################\n--------------- User Portal --------------\n#########################################\n"<<endl;
        cout << "User: "<< _username << endl << endl;
        cout << "Press 1 Preview My Bookings\n";
        cout << "Press 2 Book Flight\n";
        cout << "Press 3 Cancel Booking\n";
        cout << "Press 4 Show Available Flights\n";
        cout << "Press 5 My Wallet\n";

        cout<<endl;

        do{
            cout<<"Please Enter Your Choice (0 to Log out): ";
            cin>>choice;
        }while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "0");
    
        portal_nav = stoi(choice);

        switch (portal_nav) {
            case 1:
                show_my_flights(_username);
                break;
            case 2:
                flight_booker(_username);
                break;
            case 3:
                cancel_booking(_username);
                break;
            case 4:
                available_flights();
                break;
            case 5:
                wallet(_username);
                break;
            case 0:
                cout << "Logging user out ... " << endl;
                portal_cycle = false;
                break;
            default:
                cout << "Undefined input" << endl;
                break;
        }

        cout<<endl;

    } while (portal_cycle);
}



void flight_booker(string _username){
    cout << "\n#########################################\n------------- Book a Flight ------------\n#########################################" << endl;
    cout << "\nUser: "<< _username << endl;
    cout << "\nAvailable Cities:" << endl;

    vector<pair<string, Flight>> flight_list = filter_flights();

    if(flight_list.empty()){ cout << "\nNo flights available for this route." << endl; enter_delay(); return; }

    
    if (!flight_list.empty() && flight_list[0].first == "0") {
        cout << "\nBooking cancelled." << endl;
        enter_delay();
        return;
    }

    cout << endl;

    for(int i = 0; i < (int)flight_list.size(); i++)
        cout << "\nFlight " << i+1 << flight_list[i].second.get_flight_detail() << endl;

    int flight_choice;
    do {
        cout << "\nEnter Flight Number (0 to cancel): ";
        cin >> flight_choice;
        if(flight_choice == 0){ cout << "Booking cancelled." << endl; enter_delay(); return; }
    } while(flight_choice < 1 || flight_choice > (int)flight_list.size());

    string temp_flight_id = flight_list[flight_choice - 1].first;
    User temp_user = users[_username];
    Flight temp_flight = flights[temp_flight_id];

    if(user_has_booking(_username, temp_flight_id)){
        cout << "\nYou have already booked this flight!" << endl;
        cout << "\nPress Enter to continue...";
        cin.ignore(1000, '\n');
        cin.get();
        return;
    }

    string confirm;
    cout << "\n" << flight_list[flight_choice - 1].second.get_flight_detail() << endl;
    cout << "\nConfirm booking? (y/n): ";
    cin >> confirm;
    if(confirm != "y"){ 
        cout << "\nBooking cancelled." << endl << endl;
        enter_delay();
        return; 
    }

    bool is_paid = make_payment(temp_flight_id, _username);

    Datetime today = Datetime::get_today();
    Datetime flight_date = temp_flight.get_datetime(); // add this getter to Flight
    Datetime one_day_before_flight = Datetime::add_days(flight_date, -1);
    Datetime one_day_from_now = Datetime::add_days(today, 1);

    Datetime expiry = one_day_from_now.is_before(one_day_before_flight) ? one_day_from_now : one_day_before_flight;

    if(users.find(_username) != users.end()){
        line++;
        Booking temp_booking;
        temp_booking.set_booking(_username, temp_flight_id, line, is_paid, expiry);
        bookings[line] = temp_booking;
        temp_user = users[_username];
        temp_user.add_flight(temp_flight_id, line);
        temp_flight.add_passenger(_username, line);
        users[_username] = temp_user;
        flights[temp_flight_id] = temp_flight;
        store_bookings(_username, temp_flight_id, line, is_paid, expiry);
    }

    enter_delay();
}


//Delete any flight user booked
void cancel_booking(string _username){
    User temp_user;
    Flight temp_flight;
    string temp_flight_id;

    cout<<"\n#########################################\n----------- Cancel a Flight ----------\n#########################################\n"<<endl;

    
    cout<<"User: "<< _username << endl;

    vector<pair<string, Flight>> flight_list = my_flights(_username);

    if(flight_list.empty()){ cout << "You have no flights booked." << endl; enter_delay(); return; }

    if(flight_list[0].first == "0"){ cout << "Exit" << endl; enter_delay(); return; }

    for(int i = 0; i < (int)flight_list.size(); i++)
        cout << i+1 << ". " << flight_list[i].second.get_flight_id() << flight_list[i].second.get_flight_detail() << endl << endl;
    
    // cout << endl;

    int flight_choice;
    do {
        cout << "\nEnter Flight Number to be cancelled (0 to Return Back): ";
        cin >> flight_choice;
        if(flight_choice == 0){ cout << endl; enter_delay(); return; }
    } while(flight_choice < 1 || flight_choice > (int)flight_list.size());

    temp_flight_id = flight_list[flight_choice - 1].first;
    temp_flight = flights[temp_flight_id];
    temp_user = users[_username];
    
    vector<int> lines_to_remove;
    for (auto& entry : bookings) {
        if (entry.second.get_username() == _username && entry.second.get_flight_id() == temp_flight_id)
            lines_to_remove.push_back(entry.first);
    }
    for (int ln : lines_to_remove)
        bookings.erase(ln);

    users[_username].remove_flight(temp_flight_id);
    flights[temp_flight_id].remove_passenger(_username);

    //send confirmation message that is have been deleted
    cout<<"Flight "<<temp_flight_id<<" has been deleted From user "<<_username<<endl;

    //update the changes made (deletions)
    update_bookings();

    enter_delay();
}

void store_bookings(string _username, string _flight_id, int _line, bool _is_paid, Datetime _expiry){ 
    ofstream o_booking_list("output/BOOKING_LIST.txt", ios::app);
    if(o_booking_list.fail()){
        cerr<<"Booking file not found!";
    }

    // o_booking_list<<_line<<"."<<_username<<"$"<<_flight_id<< "%" << _is_paid << "!" << _expiry.to_string_file() <<endl;
    o_booking_list << _line << "." << _flight_id << "$" << _username << "%" << _is_paid << "!" << _expiry.to_string_file() << endl;
     
    o_booking_list.close();
}

//Update all the changes made to booking to the disk(BOOKING_LIST.txt)
void update_bookings(){ 
    ofstream o_booking_list("output/BOOKING_LIST.txt", ios::out);
    if(o_booking_list.fail()){
        cerr<<"Booking file not found!";
    }
    
    for (const auto& bookings_map : bookings){
        Booking temp_booking = bookings_map.second;
        o_booking_list << temp_booking.get_line() << "." << temp_booking.get_flight_id() << "$"
            << temp_booking.get_username() << "%" << temp_booking.get_is_paid() << "!"
            << temp_booking.get_expiry().to_string_file() << endl;
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
    ofstream o_name_list("output/NAME_LIST.txt", ios::app);
    if(o_name_list.fail()){
        cerr<<"NAME_LIST not found, Users not stored to disk!";
        exit(1);
    }

    o_name_list<<temp_user.getUsername()<<"$"<<temp_user.getPassword()<<"*"<<temp_user.get_balance()<<endl;
    o_name_list.close();
}

void update_users(){
    ofstream o_name_list("output/NAME_LIST.txt", ios::out);
    if(o_name_list.fail()){
        cerr << "NAME_LIST not found, failed to save balances!";
        return;
    }
    for (auto& user_map : users)
        o_name_list << user_map.second.getUsername() << "$" << user_map.second.getPassword()
                    << "*" << user_map.second.get_balance() << endl;
    o_name_list.close();
}


//Wallet Access
void wallet(string _username){
    int ch;
    bool wallet_cycle = true;

    do {
        cout<<"\n#########################################\n-------------- Wallet -------------\n#########################################\n"<<endl;

        cout<<"User: "<< _username << endl;

        cout << "\n1. Check balance " << endl;
        cout << "2. Top up balance" << endl;
        // cout << "9. Return Back" << endl;
        cout << "\nEnter a number to choose (0 to Exit): ";
        cin >> ch;
        switch (ch) {
            case 1:
                check_balance(_username);
                break;
            case 2: {
                double amount;
                cout << "\nEnter amount to top up: ";
                cin >> amount;
                double before_topup = users[_username].get_balance();
                users[_username].set_balance(before_topup + amount);
                cout << "\nBalance before top up: " << before_topup << endl;
                cout << "Balance after top up: " << users[_username].get_balance() << endl;

                for(auto& booking_map : bookings){
                    Booking& b = booking_map.second;
                    if(b.get_username() == _username && !b.get_is_paid()){
                        double price = flights[b.get_flight_id()].get_price();
                        if(users[_username].spend(price)){
                            b.set_is_paid(true);
                            cout << "\nBooking " << b.get_flight_id() << " is now paid!" << endl;
                            cout << "Balance after payment: " << users[_username].get_balance() << endl << endl;
                        }
                    }
                }
                update_users();
                update_bookings();
                break;
            }
            case 0:
                cout << "\nExit ... " << endl;
                enter_delay();
                wallet_cycle = false;
                return;
                break;
            default:
                cout<<"Enter a valid choice!"<<endl;
                break;
        }

        enter_delay();

    } while (wallet_cycle);

}
void check_balance(string _username){
    cout<<"\nYour current balance is: "<<users[_username].get_balance()<<endl;
}

bool make_payment(string _flight_id, string _username){
    Flight temp_flight = flights[_flight_id];
    double amount = temp_flight.get_price();

    User temp_user = users[_username];
    double before = temp_user.get_balance();
    bool paid = temp_user.spend(amount);
    users[_username] = temp_user;

    if(paid){
        cout << "\nPayment successful!" << endl;
        cout << "Before payment balance: " << before << endl;
        cout << "Remaining balance: " << users[_username].get_balance() << endl << endl;
        update_users();
    } else {
        cout << "Insufficient balance. Booking will be held but expires in 1 day." << endl;
    }
    return paid;
}


vector<pair<string, Flight>> filter_flights(){
    vector<pair<string, City>> city_list(cities.begin(), cities.end());

    for(int i = 0; i < (int)city_list.size(); i++)
        cout << i+1 << ". " << city_list[i].second.get_city() << endl;

    int origin_choice, destination_choice;
    do {
        cout << "\nEnter Origin Number (0 to cancel): ";
        cin >> origin_choice;
        if(origin_choice == 0) return { {"0", Flight()} };
    } while(origin_choice < 1 || origin_choice > (int)city_list.size());

    do {
        cout << "Enter Destination Number (0 to cancel): ";
        cin >> destination_choice;
        if(destination_choice == 0) return {{"0", Flight()}};
    } while(destination_choice < 1 || destination_choice > (int)city_list.size());

    string origin_name      = city_list[origin_choice - 1].second.get_city();
    string destination_name = city_list[destination_choice - 1].second.get_city();

    vector<pair<string, Flight>> flight_list;
    for (auto& flight_map : flights){
        Flight temp_flight = flight_map.second;
        if(temp_flight.get_origin() == origin_name && temp_flight.get_destination() == destination_name)
            flight_list.push_back({flight_map.first, temp_flight});
    }

    return flight_list;
}

void available_flights(){
    cout << "\n#########################################\n---------------- Flights ---------------\n#########################################" << endl;
    cout << "\nAvailable Cities:" << endl;
    vector<pair<string, Flight>> flight_list = filter_flights();

    cout << endl;

    if(flight_list.empty()){ cout << "No flights available for this route." << endl; enter_delay(); return; }

    for(int i = 0; i < (int)flight_list.size(); i++)
        cout << "\nFlight " << i+1 << flight_list[i].second.get_flight_detail() << endl;

    enter_delay();
}

//My Flights View
vector<pair<string, Flight>> my_flights(string _username){
    User cur_user;

    if (users.find(_username) != users.end()) {
        cur_user = users[_username];
    } else {
        cout << "User " << _username << " does not exist." << endl;
        // enter_delay();
        return {};
    }

    if(cur_user.get_my_flights().empty()){
        cout << "\nYou have no flights booked." << endl;
        // enter_delay();
        return {};
    }

    vector<pair<string, Flight>> flight_list;
    int i = 1;

    for (const auto& flight_map : cur_user.get_my_flights()){
        Flight temp_flight = flights[flight_map.first];
        flight_list.push_back({flight_map.first, temp_flight});
        i++;
    }

    return flight_list;
}

void show_my_flights(string _username){
    cout<<"\n#########################################\n-------------- My Flights -------------\n#########################################\n";

    vector<pair<string, Flight>> flight_list = my_flights(_username);

    for(int i = 0; i < (int)flight_list.size(); i++)
        cout << "\n" << i+1 << ". " << flight_list[i].second.get_flight_id() << flight_list[i].second.get_flight_detail() << endl;

    enter_delay();
}

#endif