#ifndef AIRLINES_READ_DISK_H
#define AIRLINES_READ_DISK_H
#include "Class_Definitions.h"
#include <vector>
#include <fstream>
#include <map>
#include <string>

using namespace std;


//Memory Locations
map<string, User> users;
map<string, Flight> flights;
map<int, Booking> bookings;


void read_flights();
void read_users();
void read_bookings();
void i_flight_booker(string _flight_id, string _username);
void refresh_bookings();


void read_disk(){
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

    ifstream i_name_list("NAME_LIST.txt", ios::in);
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

    Flight temp_flight;
    string temp_beginning;
    string temp_destination;
    string temp_flight_id;
    string temp_plane_model;
    int temp_max_capacity;
    double temp_price;

    ifstream i_flight_list("FLIGHT_LIST.txt", ios::in);
    if(i_flight_list.fail()){
        cerr<<"Flight List not found, failed to read disk!";
        exit(1);
    }


    string flight_line;

    while(getline(i_flight_list, flight_line)){
        size_t pos = flight_line.find("$");
        size_t pos2 = flight_line.find("*");
        size_t pos3 = flight_line.find("&");
        temp_flight_id = flight_line.substr(0, pos);
        temp_plane_model = flight_line.substr(pos+1,(pos2-pos-1));
        temp_max_capacity = stoi(flight_line.substr(pos2+1,pos3-pos2-1));
        temp_price = stoi(flight_line.substr(pos3+1));

        temp_flight.set_details(temp_flight_id, temp_plane_model,temp_max_capacity,temp_price);

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

    ifstream i_booking_list("BOOKING_LIST.txt", ios::in);
    if(i_booking_list.fail()){
        cerr<<"Booking List not found, failed to read disk!";
        exit(1);
    }



    string flight_line;
    while(getline(i_booking_list, flight_line)){
        size_t pos = flight_line.find("$");
        temp_username = flight_line.substr(0, pos);
        temp_flight_id = flight_line.substr(pos+1);

        i_flight_booker(temp_flight_id, temp_username);
    }

    cout<<endl;

    i_booking_list.close();
}


void i_flight_booker(string _flight_id, string _username){
    //Add Booking Relationship
    Booking temp_booking;
    temp_booking.set_booking(_username, _flight_id, line);
    bookings[line] = temp_booking;
    //cout<<"Booking read User: "<<temp_booking.get_line()<<endl;
    cout<<"Booking read User: "<<bookings[temp_booking.get_line()].get_username()<<", Flight: "<<bookings[temp_booking.get_line()].get_flight_id()<<", Line: "<<bookings[temp_booking.get_line()].get_line()<<endl;

    //Add Flight to the User
    if (users.find(_username) != users.end()) {
        //copies user data to temporary user
        User temp_user = users[_username];

        //add flight to the temporary user
        temp_user.add_flight(_flight_id, line);

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
        temp_flight.add_passenger(_username, line);
    
        //replace the old flight by the new temporary flight
        flights[_flight_id] = temp_flight;

        cout<<"Flight: "<<_flight_id<<": Passenger "<<temp_user.getUsername()<<" has Booked."<<endl;
    } else {
        cout << "User " << _username <<", flight id: "<<_flight_id<< " does not exist cannot book flight." << endl;
    }
    
    line++;
    refresh_bookings(); //Add flight Count for the Plane
}

//Update_booking
void refresh_bookings(){
    Flight temp_flight;
    User temp_user;

    for (const auto& user_map : users) {
        temp_user = users[user_map.first];
        for (const auto& flight_map : temp_user.get_my_flights()){
            temp_flight = flights[flight_map.first];
            if(flights.find(temp_flight.get_flight_id()) == flights.end()){
                cout<<"Error Found, Mismatch of booking, User "<<temp_user.getUsername()<<" booked unknown Flight!"<<endl;
            }
        }
    }

    for (const auto& flight_map : flights) {
        temp_flight = flights[flight_map.first];
        for (const auto& user_map : temp_flight.get_my_passengers()){
            temp_user = users[user_map.first];
            if(users.find(temp_user.getUsername()) == users.end()){
                cout<<"Error Found, Mismatch of booking, Unknown passenger booked on Flight "<<temp_flight.get_flight_id()<<"!"<<endl;
            }
        }
    }
}

#endif