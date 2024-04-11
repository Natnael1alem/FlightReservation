#include <iostream>
#include "Functions.h"

using namespace std;

bool nav_cycle = true;
string choice;
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
    }while(nav_cycle);

    return 0;
}