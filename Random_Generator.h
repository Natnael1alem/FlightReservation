#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;


string generateRandomString() {
    int length = 4;
    // Characters to be used in the random string
    string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int charsetLength = charset.length();

    // Seed the random number generator
    srand(static_cast<unsigned int>(std::time(nullptr)));

    string randomString;
    randomString.reserve(length);

    // Generate random characters and append to the string
    for (int i = 0; i < length; ++i) {
        randomString += charset[std::rand() % charsetLength];
    }

    return randomString;
}
