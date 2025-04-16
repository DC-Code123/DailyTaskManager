#include "../include/Task.h"

int main() {
  vector<Task> pendingTasks;
  vector<Task> doneTasks;

  // Load tasks from file at the start
  LoadTasks(pendingTasks, doneTasks);

  char rerun;
  do {
    int choice = DisplayMenu();
    if (choice == -1) {
      continue;
    }

    switch (choice) {
      case 1:
        AddTask(pendingTasks);
        break;
      case 2:
        ViewTask(pendingTasks);
        break;
      case 3:
        MarkDone(pendingTasks, doneTasks);
        break;
      case 4:
        ViewDone(doneTasks);
        break;
      case 5:
        ViewTask(pendingTasks);
        ViewDone(doneTasks);
        break;
      case 6:
        DeleteTask(pendingTasks, doneTasks);
        break;
      case 7:
        SaveTasks(pendingTasks, doneTasks);
        break;
      case 8:
        cout << "Thanks for using the app.\nExiting program...\n";
        return 0;
    }

    do {
      cout << "\nDo you want to perform another operation? (y = yes, n = no): ";
      cin >> rerun;
      if (rerun != 'y' && rerun != 'Y' && rerun != 'n' && rerun != 'N') {
        cout << "Invalid input. Please enter 'y' or 'n'.\n";
      }
    } while (rerun != 'y' && rerun != 'Y' && rerun != 'n' && rerun != 'N');

  } while (rerun == 'y' || rerun == 'Y');

  SaveTasks(pendingTasks, doneTasks);

  return 0;
}
