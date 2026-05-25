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
    
    string to_string_file(){
        return to_string(day) + "." + to_string(month) + "." + to_string(year) + "." + to_string(hour) + "." + to_string(minute);
    }

    string to_string_date(){
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year)
            + " " + to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute);
    }
    
    bool is_before(Datetime other){
        tm t1 = {};
        t1.tm_mday = day; t1.tm_mon = month-1; t1.tm_year = year-1900;
        t1.tm_hour = hour; t1.tm_min = minute;
    
        tm t2 = {};
        t2.tm_mday = other.day; t2.tm_mon = other.month-1; t2.tm_year = other.year-1900;
        t2.tm_hour = other.hour; t2.tm_min = other.minute;
    
        return difftime(mktime(&t1), mktime(&t2)) < 0;
    }
    
    static Datetime get_today(){
        time_t now = time(0);
        tm* t = localtime(&now);
        return Datetime(t->tm_mday, t->tm_mon+1, t->tm_year+1900, t->tm_hour, t->tm_min);
    }
    
    static Datetime add_days(Datetime d, int days){
        tm t = {};
        t.tm_mday = d.day + days; t.tm_mon = d.month-1; t.tm_year = d.year-1900;
        t.tm_hour = d.hour; t.tm_min = d.minute;
        mktime(&t); // normalizes the date
        return Datetime(t.tm_mday, t.tm_mon+1, t.tm_year+1900, t.tm_hour, t.tm_min);
    }
};

class User {
    private:
    string username;
    string password;
    double balance;
    map<string, int> my_flights;

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

    Datetime get_datetime(){ return datetime; }

    string get_origin(){ return origin; }
    string get_destination(){ return destination; }
};

class Booking{
    private:
        int data_no;
        string username;
        string flight_id;
        bool is_paid;
        Datetime booked_on;
        Datetime expiry;
    public:
        void set_booking(string _username, string _flight_id, int _line, bool _is_paid, Datetime _expiry){
            username = _username;
            flight_id = _flight_id;
            data_no = _line;
            is_paid = _is_paid;
            booked_on = Datetime::get_today();
            expiry = _expiry;
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

        bool get_is_paid(){ return is_paid; }
        void set_is_paid(bool _is_paid){ is_paid = _is_paid; }
        Datetime get_expiry(){ return expiry; }
};


#endif