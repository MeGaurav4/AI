#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int main() {
    cout << "=== Restaurant Chatbot ===\n";
    cout << "Ask me anything! (type 'bye' to exit)\n\n";

    string input;

    while (true) {
        cout << "You: ";
        getline(cin, input);
        string msg = toLower(input);

        if (msg == "bye") {
            cout << "Bot: Goodbye! Have a great day!\n";
            break;
        }
        else if (msg.find("menu") != string::npos) {
            cout << "Bot: We serve pizza, pasta, burgers, fries, and cold drinks.\n";
        }
        else if (msg.find("time") != string::npos || msg.find("open") != string::npos) {
            cout << "Bot: We are open every day from 10 AM to 11 PM.\n";
        }
        else if (msg.find("reserve") != string::npos || msg.find("table") != string::npos) {
            cout << "Bot: Sure! You can reserve a table by calling 9876543210.\n";
        }
        else if (msg.find("location") != string::npos) {
            cout << "Bot: We are located near City Center Mall, Ground Floor.\n";
        }
        else if (msg.find("help") != string::npos) {
            cout << "Bot: I can help you with menu, timings, reservations, and location.\n";
        }
        else {
            cout << "Bot: Sorry, I didn't understand that. Try asking about menu, time, reserve, or location.\n";
        }
    }

    return 0;
}
