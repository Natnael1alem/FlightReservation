#include <iostream>
#include "Functions.h"
#include <thread>
#include <chrono>
#include <ctime>

using namespace std;

void scheduler(){
    tm target = {};
    target.tm_year = 2026 - 1900;
    target.tm_mon  = 12 - 1;
    target.tm_mday = 13;
    target.tm_hour = 14;
    target.tm_min  = 0;
    target.tm_sec  = 0;
    time_t target_time = mktime(&target);

    bool has_triggered = false;
    while(true){
        time_t now = time(0);
        if(!has_triggered && difftime(now, target_time) >= 0){
            cout << "\n[System] Running expiry check...\n";
            check_expiry();
            has_triggered = true;
        }
        this_thread::sleep_for(chrono::minutes(1));
    }
}

int main(){
    // reads all disks file to memory for easy access
    seed();
    read_disk();

    thread background_scheduler(scheduler);
    background_scheduler.detach();

    bool nav_cycle = true;
    string choice;
    int nav_no;

    do{
        cout<<"#########################################\n--- Welcome to the Flight Reservation ---\n#########################################\n"<<endl;
        cout<<"Press 1 Create User\n";
        cout<<"Press 2 Log in\n";
        cout<<"Press 3 Refresh Data\n";
        cout<<"Press 4 Show Available Flights\n";
        cout<<"Press 9 Quit\n";

        cout<<endl;    

        do{
            cout<<"Please Enter Your Choice: ";
            cin>>choice;
        }while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "9");

        nav_no = stoi(choice);

        switch(nav_no){
            case 1:
                create_user();
                break;
            case 2:
                log_in();
                break;
            case 3:
                read_disk();
                break;
            case 4:
                available_flights();
                break;
            case 9:
                cout<<"Quitting the program ... "<<endl;
                nav_cycle = false;
                break;
            default:
                cout<<"Undefined input"<<endl;
                break;
        }

        cout<<endl;

    }while(nav_cycle);



    return 0;
}