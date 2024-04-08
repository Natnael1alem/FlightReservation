//User program
#include <iostream>
#include "Functions.h"

using namespace std;

bool nav_cycle = true;

void navigator(){
    int nav_no;

    cout<<"Press 1 Create User\n";
    cout<<"Press 2 Log in\n";
    cout<<"Press 3 Refresh Data\n";
    cout<<"Press 4 Show Available Flights\n";
    cout<<"Press 9 Quit\n";

    cout<<"Please Enter Your Choice: ";
    cin>>nav_no;

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
}

int main(){
    read_disk();// reads all disks file to memory for easy access

    do{
        cout<<"#########################################\n---------Welcome to the Navigator--------\n#########################################\n";
        navigator();
    }while(nav_cycle);

    return 0;
}