#ifndef AIRLINES_CLASS_DEFINITIONS_H
#define AIRLINES_CLASS_DEFINITIONS_H
#include "Random_Generator.h"
// #include "Get_Disk.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;


int line = 0;


class Date{
private:
    int day;
    int month;
    int year;
};

class User {
public:
    void set_details(string _username, string _password){
        username = _username;
        password = _password;
    }

    string getUsername(){
        return username;
    }
    string getPassword(){
        return password;
    }

    void add_flight(string _flight_id, int line){
        my_flights[_flight_id] = line;
        cout<<"*flight "<<_flight_id<<" added, on line "<<line<<" on user "<<username<<endl;
    }

    map<string, int> get_my_flights(){
        return my_flights;
    }

    void set_balance(double _balance){
        balance = _balance;
    }

    double get_balance(){
        return balance;
    }

    bool spend(double _amount){
        if (balance >= _amount){
            balance -= _amount;
            return true;
        }else{
            cout<<"Balance not Enough"<<endl;
            return false;
        }
    }

private:
    string username;
    string password;
    double balance;
    map<string, int> my_flights;
};

class Flight {
public:
    string flight_id;
    string beginning;
    string destination;
    string plane_model;
    int max_capacity;
    int current_number;
    bool is_available;
    double price;
    map<string, int> passengers;

    Date date;
    void set_details(string _flight_id, string _plane_model, int _max_capacity, int _price){
        flight_id = _flight_id;
        plane_model = _plane_model;
        max_capacity = _max_capacity;
        price = _price;
    }
    string get_flight_detail(){
        string details =  plane_model+", "+ to_string(max_capacity)+"/"+to_string(current_number) + ", "+ to_string(price)+"$";
        return details;
    }
    string get_flight_id(){
        return flight_id;
    }
    int get_line(string _flight_id){
        return passengers[_flight_id];
    }
    void add_passenger(string _username, int line){
        passengers[_username] = line;
        cout<<"*user "<<_username<<" added, on line "<<line<<" in flight "<<flight_id<<endl;
    }
    map<string, int> get_my_passengers(){
        return passengers;
    }
    double get_price(){
        return price;
    }
};

class Booking{
    private:
        int data_no;
        string username;
        string flight_id;
    public:
        void set_booking(string _username, string _flight_id, int _line){
            username = _username;
            flight_id = _flight_id;
            data_no = _line;
        }
        
        int get_line(){
            //cout << "Booking Line:" << data_no<<endl;
            return data_no; 
        }

        string get_username(){
            return username;
        }

        string get_flight_id(){
            return flight_id;
        }
};


#endif