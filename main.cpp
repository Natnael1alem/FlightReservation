#include <iostream>
#include "Functions.h"

using namespace std;

bool nav_cycle = true;
int nav_no;

int main(){
    read_disk();// reads all disks file to memory for easy access

    do{
        cout<<"#########################################\n---------Welcome to the Navigator--------\n#########################################\n";
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
    }while(nav_cycle && (nav_no == 1 || nav_no == 2 || nav_no == 3 || nav_no == 4 || nav_no == 9));

    return 0;
}