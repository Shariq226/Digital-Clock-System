#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <ctime> // For system time
#include <conio.h> // For keyboard input (Windows-specific)

using namespace std;

// Function prototypes
void displayClock(int hour, int min, int sec);
void setAlarm(int alarmHour, int alarmMin, int alarmSec);
void stopwatch();
void timer(int duration);

int main() {
    int choice;

    do {
        system("cls"); // Clear screen (Windows-specific)
        cout << "DIGITAL CLOCK WITH FEATURES\n";
        cout << "===========================\n";
        cout << "1. Display Current Time\n";
        cout << "2. Set Alarm\n";
        cout << "3. Stopwatch\n";
        cout << "4. Timer\n";
        cout << "5. Exit\n";
        cout << "===========================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Fetch system time and display the clock
                time_t now = time(0);
                tm *ltm = localtime(&now);

                int hour = ltm->tm_hour;
                int min = ltm->tm_min;
                int sec = ltm->tm_sec;

                displayClock(hour, min, sec);
                break;
            }
            case 2: {
                int alarmHour, alarmMin, alarmSec;
                cout << "Set Alarm Time (HH MM SS): ";
                cin >> alarmHour >> alarmMin >> alarmSec;
                setAlarm(alarmHour, alarmMin, alarmSec);
                break;
            }
            case 3:
                stopwatch();
                break;
            case 4: {
                int duration;
                cout << "Set Timer Duration in Seconds: ";
                cin >> duration;
                timer(duration);
                break;
            }
            case 5:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}

// Function to display a real-time clock
void displayClock(int hour, int min, int sec) {
    while (!_kbhit()) { // Runs until a key is pressed
        system("cls");
        cout << "CURRENT TIME\n";
        cout << "============\n";
        cout << setw(2) << setfill('0') << hour << " : "
             << setw(2) << setfill('0') << min << " : "
             << setw(2) << setfill('0') << sec << endl;

        this_thread::sleep_for(chrono::seconds(1));
        sec++;
        if (sec == 60) {
            sec = 0;
            min++;
        }
        if (min == 60) {
            min = 0;
            hour++;
        }
        if (hour == 24) {
            hour = 0;
        }
    }
    _getch(); // Clear the pressed key
}

// Function to set an alarm
void setAlarm(int alarmHour, int alarmMin, int alarmSec) {
    while (true) {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        int hour = ltm->tm_hour;
        int min = ltm->tm_min;
        int sec = ltm->tm_sec;

        system("cls");
        cout << "CURRENT TIME\n";
        cout << "============\n";
        cout << setw(2) << setfill('0') << hour << " : "
             << setw(2) << setfill('0') << min << " : "
             << setw(2) << setfill('0') << sec << endl;

        cout << "\nALARM SET FOR\n";
        cout << "=============\n";
        cout << setw(2) << setfill('0') << alarmHour << " : "
             << setw(2) << setfill('0') << alarmMin << " : "
             << setw(2) << setfill('0') << alarmSec << endl;

        if (hour == alarmHour && min == alarmMin && sec == alarmSec) {
            cout << "\nALARM RINGING! PRESS ANY KEY TO STOP...\n";
            _getch(); // Wait for key press to stop the alarm
            break;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// Function to implement stopwatch
void stopwatch() {
    int sec = 0, min = 0, hour = 0;
    cout << "STOPWATCH STARTED! PRESS ANY KEY TO STOP...\n";

    while (!_kbhit()) {
        system("cls");
        cout << "STOPWATCH\n";
        cout << "=========\n";
        cout << setw(2) << setfill('0') << hour << " : "
             << setw(2) << setfill('0') << min << " : "
             << setw(2) << setfill('0') << sec << endl;

        this_thread::sleep_for(chrono::seconds(1));
        sec++;
        if (sec == 60) {
            sec = 0;
            min++;
        }
        if (min == 60) {
            min = 0;
            hour++;
        }
    }
    _getch(); // Clear the pressed key
    cout << "\nSTOPWATCH STOPPED!\n";
    system("pause");
}

// Function to implement timer
void timer(int duration) {
    while (duration > 0) {
        system("cls");
        cout << "TIMER\n";
        cout << "=====\n";
        cout << "Time Remaining: " << duration << " seconds\n";
        this_thread::sleep_for(chrono::seconds(1));
        duration--;
    }
    cout << "\nTIME'S UP! PRESS ANY KEY TO EXIT TIMER.\n";
    _getch();
}
