
#include "../include/Task.h"
#include <iostream>
using namespace std;

int main() {
    TaskDB taskDB;
    try {
        taskDB.LoadTasks();
    } catch (const exception& e) {
        cerr << "Error loading tasks: " << e.what() << endl;
    }

    Options options;
    int choice;

    while ((choice = DisplayMenu()) != 6) {
        try {
            switch (choice) {
                case 1:
                    options.AddTask(taskDB);
                    break;

                case 2:
                    options.ViewPending(taskDB, options);
                    break;

                case 3:
                    options.MarkDone(taskDB, options);
                    break;

                case 4:
                    options.ViewDone(taskDB, options);
                    break;

                case 5:
                    options.DeleteTask(taskDB, options);
                    break;

                default:
                    cout << "Invalid choice.\n";
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << "\n";
        }
    }

    try {
        taskDB.SaveTasks();
    } catch (const exception& e) {
        cerr << "Error saving tasks: " << e.what() << endl;
    }
    return 0;
}