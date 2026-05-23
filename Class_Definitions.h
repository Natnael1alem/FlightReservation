#ifndef AIRLINES_CLASS_DEFINITIONS_H
#define AIRLINES_CLASS_DEFINITIONS_H
#include "Random_Generator.h"
// #include "Get_Disk.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;


class City{
private:
    string city;
    string city_code;
public:
    City() {}  
    City(string _city, string _city_code) : city(_city), city_code(_city_code) {}
    string get_city() { return city; }
    string get_city_code() { return city_code; }
};

class PlaneModel {
private:
    string model;
    int capacity;
public:
    PlaneModel() {}
    PlaneModel(string _model, int _capacity) : model(_model), capacity(_capacity) {}
    string get_model() { return model; }
    int get_capacity() { return capacity; }
};

class Datetime {
private:
    int day, month, year, hour, minute;
public:
    Datetime() {}
    Datetime(int _day, int _month, int _year, int _hour, int _minute)
        : day(_day), month(_month), year(_year), hour(_hour), minute(_minute) {}
    string to_string_date(){
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year) +
               " " + to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
    }
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

    void remove_flight(string _flight_id){
        my_flights.erase(_flight_id);
    }

    int get_line(string _flight_id){
        return my_flights[_flight_id];
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
    string origin;
    string destination;
    PlaneModel plane;
    int max_capacity;
    int current_number = 0;
    double price;
    map<string, int> passengers;
    Datetime datetime;

    void set_details(string _flight_id, PlaneModel  _plane, string _origin, string _destination, double _price,  Datetime _datetime){
        flight_id    = _flight_id;
        plane   = _plane;
        origin       = _origin;
        destination  = _destination;
        datetime     = _datetime;
        max_capacity = plane.get_capacity();
        price = _price;

    }      

    string get_flight_detail(){
        return "Flight ID : " + flight_id +
            "\nRoute     : " + origin + " -> " + destination +
            "\nPlane     : " + plane.get_model() +
            "\nDate      : " + datetime.to_string_date() +
            "\nSeats     : " + to_string(current_number) + "/" + to_string(max_capacity) +
            "\nPrice     : " + to_string((int)price) + "$";
    }

    string get_flight_id(){
        return flight_id;
    }
    int get_line(string _username){
        return passengers[_username];
    }
    void add_passenger(string _username, int line){
        passengers[_username] = line;
        current_number += 1;
        cout<<"*user "<<_username<<" added, on line "<<line<<" in flight "<<flight_id<<endl;
    }
    map<string, int> get_my_passengers(){
        return passengers;
    }

    void remove_passenger(string _username){
        passengers.erase(_username);
    }

    double get_price(){
        return price;
    }

    bool is_available() {
        if ((max_capacity - current_number) > 0){
            return true;
        }else{
            cout<<"Flight not Booked, No seat available"<<endl;
            return false;
        }
    }

    string get_origin(){ return origin; }
    string get_destination(){ return destination; }
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