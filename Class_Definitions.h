#ifndef AIRLINES_CLASS_DEFINITIONS_H
#define AIRLINES_CLASS_DEFINITIONS_H
#include "Random_Generator.h"
//#include "Get_Disk.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

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

    void add_flight(string _flight_id){
        my_flights.insert(pair<string, string>(_flight_id, ""));
    }

    map<string, string> get_my_flights(){
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
    //vector<string>  flight_ids;
    map<string, string> my_flights;
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
    map<string, string> passengers;

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
    void add_passenger(string _username){
        passengers.insert(pair<string, string>(_username, ""));
    }
    map<string, string> get_my_passengers(){
        return passengers;
    }
    double get_price(){
        return price;
    }
};

#endif