<img width="344" height="174" alt="image" src="https://github.com/user-attachments/assets/96520ada-7dd3-42c0-963f-8e7ec7aa8743" />
Flight Reservation System
A console-based C++ application for managing users, flights, bookings, and wallet payments.

</br>

<h1> Run main.cpp to Launch the program </h1> 

run: 'g++ main.cpp -o main' and then './main.exe'
</br>


Features
User registration and login
View and filter available flights
Book and cancel flights
Wallet balance and payment flow
File-based persistent storage (output/*.txt)
Startup seed data for first-time run
Requirements
OS: Windows (recommended, uses conio.h / getch())
Compiler:
g++ with C++17 support (MinGW), or
MSVC (cl) with C++17 support
Terminal/console with read/write access to the project folder
Project Structure
main.cpp - entry point
Functions.h - app logic
Class_Definitions.h - class definitions
Get_Disk.h - file read/write + seed data
output/ - data files used by the app
Installation & Build
1) Clone or download the project
git clone <your-repo-url>
cd FlightReservation
2) Ensure output folder exists
Create an output directory in the project root if it does not exist.

3) Compile
Option A: MinGW g++
g++ -std=c++17 -pthread main.cpp -o flight_reservation.exe
Option B: MSVC (Developer Command Prompt)
cl /EHsc /std:c++17 main.cpp
Run
MinGW build
.\flight_reservation.exe
MSVC build
main.exe
First Run Behavior
On first launch, the app calls seed() and creates default data files inside output/:

NAME_LIST.txt
FLIGHT_LIST.txt
BOOKING_LIST.txt
PLANE_LIST.txt
If these files already exist, seed is skipped and existing data is preserved.

Default Seed Accounts
alex / a
bob / b
chen / c
Troubleshooting
conio.h not found
Use a Windows toolchain (MinGW/MSVC). This project is not directly portable to Linux/macOS without replacing getch() logic.

</br>
Make sure the output folder exists and the app has permission to read/write files.
Thread-related compile issues
For g++, include -pthread as shown above.
Notes
Data is stored in plain text files under output/.
Deleting those files resets persisted state (seed data will be recreated on next run).
