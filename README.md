A console-based application for managing daily tasks. You can:
- Add new tasks
- View pending and completed tasks
- Mark tasks as done
- Delete tasks
- Save/load tasks to/from a file

## Build Instructions
Use Code::Blocks to open `DailyTaskManager.cbp` or use a terminal with g++:

```bash
g++ src/main.cpp src/Task.cpp -Iinclude -o bin/DailyTaskManager
