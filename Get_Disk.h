#ifndef AIRLINES_READ_DISK_H
#define AIRLINES_READ_DISK_H
#include "Class_Definitions.h"
#include <vector>
#include <fstream>
#include <map>
#include <string>

using namespace std;



int line = 0;


//Memory Locations
map<string, User> users;
map<string, Flight> flights;
map<int, Booking> bookings;
map<string, City> cities;
map<string, PlaneModel> plane_models;



void read_flights();
void read_users();
void read_bookings();
void i_flight_booker(string _flight_id, string _username, int _line, bool _is_paid, Datetime _expiry);
void check_bookings();
void read_plane_models();
void update_bookings();

void load_cities(){
    cities["JFK"] = City("New York", "JFK");
    cities["LHR"] = City("London", "LHR");
    cities["DXB"] = City("Dubai", "DXB");
    cities["CDG"] = City("Paris", "CDG");
    cities["HND"] = City("Tokyo", "HND");
    cities["FRA"] = City("Frankfurt", "FRA");
    cities["SIN"] = City("Singapore", "SIN");
    cities["LAX"] = City("Los Angeles", "LAX");
}

// Default dummy datas (for during development)
void seed(){
    // Load the cities
    load_cities();

    // Check if files already exist
    ifstream check("output/NAME_LIST.txt");
    if(check.good()){
        cout << "Data files already exist, skipping seed." << endl;
        check.close();
        return; // Exit early, don't overwrite
    }
    check.close();

    // --- Users ---
    ofstream o_name_list("output/NAME_LIST.txt", ios::out);
    if(o_name_list.fail()){ cerr << "NAME_LIST not found!"; return; }
    o_name_list << "alex$a*70000\n";
    o_name_list << "bob$b*50000\n";
    o_name_list << "chen$c*30000\n";
    o_name_list.close();

    // --- Flights ---
    ofstream o_flight_list("output/FLIGHT_LIST.txt", ios::out);
    if(o_flight_list.fail()){ cerr << "FLIGHT_LIST not found!"; return; }
    // JFK connections
    o_flight_list << "FL001$B737*2500&New York#London@10.6.2026.8.0\n";
    o_flight_list << "FL002$A320*2700&New York#London@15.6.2026.14.0\n";
    o_flight_list << "FL003$B777*3500&New York#Paris@11.6.2026.9.30\n";
    o_flight_list << "FL004$A380*3200&New York#Paris@18.6.2026.16.0\n";
    o_flight_list << "FL005$B787*4000&New York#Dubai@12.6.2026.11.0\n";
    o_flight_list << "FL006$B737*4200&New York#Tokyo@13.6.2026.7.0\n";
    // LHR connections
    o_flight_list << "FL007$A320*2500&London#New York@10.6.2026.10.0\n";
    o_flight_list << "FL008$B777*2800&London#New York@17.6.2026.15.30\n";
    o_flight_list << "FL009$A380*3000&London#Paris@11.6.2026.8.0\n";
    o_flight_list << "FL010$B737*3100&London#Paris@14.6.2026.12.0\n";
    o_flight_list << "FL011$B787*3800&London#Dubai@12.6.2026.9.0\n";
    o_flight_list << "FL012$A320*4500&London#Tokyo@13.6.2026.6.30\n";
    // CDG connections
    o_flight_list << "FL013$B777*3200&Paris#New York@10.6.2026.13.0\n";
    o_flight_list << "FL014$A380*3400&Paris#London@11.6.2026.7.30\n";
    o_flight_list << "FL015$B737*2900&Paris#Dubai@15.6.2026.10.0\n";
    o_flight_list << "FL016$B787*3600&Paris#Tokyo@16.6.2026.8.0\n";
    // DXB connections
    o_flight_list << "FL017$A380*3000&Dubai#London@12.6.2026.2.0\n";
    o_flight_list << "FL018$B777*3200&Dubai#Paris@13.6.2026.3.30\n";
    o_flight_list << "FL019$B787*4500&Dubai#Tokyo@14.6.2026.1.0\n";
    o_flight_list << "FL020$A320*3800&Dubai#New York@15.6.2026.23.0\n";
    // HND connections
    o_flight_list << "FL021$B777*4200&Tokyo#New York@10.6.2026.11.0\n";
    o_flight_list << "FL022$A380*4500&Tokyo#London@11.6.2026.10.30\n";
    o_flight_list << "FL023$B787*3900&Tokyo#Dubai@12.6.2026.9.0\n";
    o_flight_list << "FL024$A320*3500&Tokyo#Singapore@13.6.2026.5.0\n";
    // SIN connections
    o_flight_list << "FL025$B737*3200&Singapore#Tokyo@14.6.2026.6.0\n";
    o_flight_list << "FL026$B777*3800&Singapore#Dubai@15.6.2026.2.30\n";
    o_flight_list << "FL027$A380*4200&Singapore#London@16.6.2026.22.0\n";
    o_flight_list.close();

    // --- Bookings ---
    ofstream o_booking_list("output/BOOKING_LIST.txt", ios::out);
    if(o_booking_list.fail()){ cerr << "BOOKING_LIST not found!"; return; }
    o_booking_list << "1.FL001$alex\n";
    o_booking_list << "2.FL002$bob\n";
    o_booking_list.close();

    // check if plane list exists
    ofstream o_plane_list("output/PLANE_LIST.txt", ios::out);
    if(o_plane_list.fail()){ cerr << "PLANE_LIST not found!"; return; }
    o_plane_list << "B737$Boeing 737*150\n";
    o_plane_list << "A320$Airbus A320*180\n";
    o_plane_list << "B777$Boeing 777*300\n";
    o_plane_list << "A380$Airbus A380*500\n";
    o_plane_list << "B787$Boeing 787*240\n";
    o_plane_list.close();

    cout << "Seed data written successfully!" << endl;
}

void read_disk(){
    read_plane_models();
    read_users();
    read_flights();
    read_bookings();
}



void read_users(){
    users.clear();// Clearing the map

    User temp_user;
    string temp_username;
    string temp_password;
    double temp_balance;

    ifstream i_name_list("output/NAME_LIST.txt", ios::in);
    if(i_name_list.fail()){
        cerr<<"Name List not found, failed to read disk!";
        exit(1);
    }


    string user_line;

    while(getline(i_name_list, user_line)){
        size_t pos = user_line.find("$");
        size_t pos1 = user_line.find("*");
        temp_username = user_line.substr(0, pos);
        temp_password = user_line.substr(pos+1, pos1-pos-1);
        temp_balance = stod(user_line.substr(pos1+1));

        temp_user.set_details(temp_username, temp_password);
        temp_user.set_balance(temp_balance);
        temp_user.get_my_flights().clear();

        users[temp_username] = temp_user;
    }

    i_name_list.close();

    /*
    for (auto user_map = users.begin(); user_map != users.end(); ++user_map) {
        std::cout << "Key: " << user_map->first << std::endl;
    }
    cout<<endl;
    */

}

void read_flights(){
    flights.clear();// Clearing the map

   


    ifstream i_flight_list("output/FLIGHT_LIST.txt", ios::in);
    if(i_flight_list.fail()){
        cerr<<"Flight List not found, failed to read disk!";
        exit(1);
    }


    string flight_line;

    while(getline(i_flight_list, flight_line)){
        Flight temp_flight;
        size_t pos  = flight_line.find("$");
        size_t pos2 = flight_line.find("*", pos);
        size_t pos3 = flight_line.find("&", pos2);
        size_t pos4 = flight_line.find("#", pos3);
        size_t pos5 = flight_line.find("@", pos4);

        string temp_flight_id  = flight_line.substr(0, pos);
        string temp_plane_code = flight_line.substr(pos+1, pos2-pos-1);
        double temp_price      = stod(flight_line.substr(pos2+1, pos3-pos2-1));
        string temp_origin     = flight_line.substr(pos3+1, pos4-pos3-1);
        string temp_destination= flight_line.substr(pos4+1, pos5-pos4-1);

        // parse date
        string date_str = flight_line.substr(pos5+1);
        int d, mo, y, h, mi;
        sscanf(date_str.c_str(), "%d.%d.%d.%d.%d", &d, &mo, &y, &h, &mi);
        Datetime temp_datetime(d, mo, y, h, mi);

        temp_flight.set_details(temp_flight_id, plane_models[temp_plane_code], temp_origin, temp_destination, temp_price, temp_datetime);

        flights[temp_flight_id] = temp_flight;
    }

    i_flight_list.close();

    /*
    for (auto flight_map = flights.begin(); flight_map != flights.end(); ++flight_map) {
        std::cout << "flight key: " << flight_map->first<< ", " << flight_map->second.get_flight_detail() << std::endl;
    }
    cout<<endl;
    */
}

void read_bookings(){
    string temp_flight_id;
    string temp_username;
    int temp_line = 0;

    ifstream i_booking_list("output/BOOKING_LIST.txt", ios::in);
    if(i_booking_list.fail()){
        cerr<<"Booking List not found, failed to read disk!";
        exit(1);
    }

    string flight_line;
    while(getline(i_booking_list, flight_line)){
        if(flight_line.empty()) continue;

        size_t pos  = flight_line.find(".");
        size_t pos1 = flight_line.find("$");
        size_t pos2 = flight_line.find("%");
        size_t pos3 = flight_line.find("!");

        temp_line      = stoi(flight_line.substr(0, pos));
        temp_flight_id = flight_line.substr(pos+1, pos1-pos-1);

        bool temp_is_paid = true;
        Datetime temp_expiry = Datetime::add_days(Datetime::get_today(), 1);
        bool legacy_format = (pos2 == string::npos || pos3 == string::npos);

        if(legacy_format){
            temp_username = flight_line.substr(pos1+1);
        } else {
            temp_username = flight_line.substr(pos1+1, pos2-pos1-1);
            temp_is_paid = (flight_line.substr(pos2+1, pos3-pos2-1) == "1");
            string date_str = flight_line.substr(pos3+1);
            int d, mo, y, h, mi;
            sscanf(date_str.c_str(), "%d.%d.%d.%d.%d", &d, &mo, &y, &h, &mi);
            temp_expiry = Datetime(d, mo, y, h, mi);
        }

        i_flight_booker(temp_flight_id, temp_username, temp_line, temp_is_paid, temp_expiry);
    }
    // while(getline(i_booking_list, flight_line)){
    //     size_t pos = flight_line.find(".");
    //     size_t pos1 = flight_line.find("$");
    //     temp_line = stoi(flight_line.substr(0,pos));
    //     temp_flight_id = flight_line.substr(pos+1,(pos1-pos-1));
    //     temp_username = flight_line.substr(pos1+1);

    //     i_flight_booker(temp_flight_id, temp_username, temp_line);
    // }

    line = temp_line;

    cout<<endl;

    i_booking_list.close();
}


void i_flight_booker(string _flight_id, string _username, int temp_line, bool _is_paid, Datetime _expiry){
    //Add Booking Relationship
    Booking temp_booking;
    // temp_booking.set_booking(_username, _flight_id, temp_line );
    temp_booking.set_booking(_username, _flight_id, temp_line, _is_paid, _expiry);
    bookings[temp_line] = temp_booking;
    //cout<<"Booking read User: "<<temp_booking.get_line()<<endl;
    cout<<"Booking read User: "<<bookings[temp_booking.get_line()].get_username()<<", Flight: "<<bookings[temp_booking.get_line()].get_flight_id()<<", Line: "<<bookings[temp_booking.get_line()].get_line()<<endl;

    //Add Flight to the User
    if (users.find(_username) != users.end()) {
        //copies user data to temporary user
        User temp_user = users[_username];

        //add flight to the temporary user
        temp_user.add_flight(_flight_id, temp_line);

        //replace the old user by the new temporary user
        users[_username] = temp_user;

        cout<<"Passenger "<<_username<<" booked on flight: "<<_flight_id<<endl;
    } else {
        cout << "User " << _username <<", flight id: "<<_flight_id<< " does not exist can't add flight from disk." << endl;
    }


    //Add Passenger to the Flight
    if (flights.find(_flight_id) != flights.end()) {
        //copies flight data to temporary flight
        Flight temp_flight = flights[_flight_id];
        User temp_user = users[_username];

        //add passenger to the temporary flight
        temp_flight.add_passenger(_username, temp_line);
    
        //replace the old flight by the new temporary flight
        flights[_flight_id] = temp_flight;

        cout<<"Flight: "<<_flight_id<<": Passenger "<<temp_user.getUsername()<<" has Booked."<<endl;
    } else {
        cout << "User " << _username <<", flight id: "<<_flight_id<< " does not exist cannot book flight." << endl;
    }
    
    check_bookings(); //Add flight Count for the Plane
}

//Update_booking
void check_bookings(){
    Flight temp_flight;
    User temp_user;

    //check my flights
    for (const auto& user_map : users) {
        temp_user = users[user_map.first];
        for (const auto& flight_map : temp_user.get_my_flights()){
            temp_flight = flights[flight_map.first];
            if(flights.find(temp_flight.get_flight_id()) == flights.end()){
                cout<<"Error Found, Mismatch of booking, User "<<temp_user.getUsername()<<" booked unknown Flight!"<<endl;
            }
        }
    }

    //check passengers
    for (const auto& flight_map : flights) {
        temp_flight = flights[flight_map.first];
        for (const auto& user_map : temp_flight.get_my_passengers()){
            temp_user = users[user_map.first];
            if(users.find(temp_user.getUsername()) == users.end()){
                cout<<"Error Found, Mismatch of booking, Unknown passenger booked on Flight "<<temp_flight.get_flight_id()<<"!"<<endl;
            }
        }
    }

    //check bookings list
}

void read_plane_models(){
    plane_models.clear();
    ifstream file("output/PLANE_LIST.txt");
    if(file.fail()){ cerr << "PLANE_LIST not found!"; exit(1); }

    string line_str;
    while(getline(file, line_str)){
        size_t pos  = line_str.find("$");
        size_t pos2 = line_str.find("*", pos);
        string code     = line_str.substr(0, pos);
        string name     = line_str.substr(pos+1, pos2-pos-1);
        int capacity    = stoi(line_str.substr(pos2+1));
        plane_models[code] = PlaneModel(name, capacity);
    }
    file.close();
}

void check_expiry(){
    Datetime today = Datetime::get_today();
    vector<int> to_delete;

    for(auto& booking_map : bookings){
        Booking& b = booking_map.second;
        if(!b.get_is_paid() && today.is_before(b.get_expiry()) == false){
            cout << "[System] Booking expired for " << b.get_username() << " on flight " << b.get_flight_id() << endl;
            users[b.get_username()].remove_flight(b.get_flight_id());
            flights[b.get_flight_id()].remove_passenger(b.get_username());
            to_delete.push_back(booking_map.first);
        }
    }

    for(int key : to_delete) bookings.erase(key);
    if(!to_delete.empty()) update_bookings();
}

#endif