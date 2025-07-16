#ifndef TASK1_H
#define TASK1_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>
using namespace std;

struct Task {
	string name;
	char state = 'P';  // 'P' for Pending, 'D' for Done
};

class TaskDB {
private:
	vector<Task> PendingTasks;
	vector<Task> DoneTasks;

public:
	TaskDB();
	void SaveTasks();
	void LoadTasks();

	const vector<Task>& getPendingTasks() const { return PendingTasks; }
	const vector<Task>& getDoneTasks() const { return DoneTasks; }

	void addPendingTask(const Task& task);
	void markTaskDone(size_t index);
	void deletePendingTask(size_t index);
	void deleteDoneTask(size_t index);
};

class Options {
private:
	bool empty = true;
public:
	void AddTask(TaskDB& taskDB);
	void ViewPending(const TaskDB& taskDB, Options& options) const;
	void MarkDone(TaskDB& taskDB, Options& options);
	void ViewDone(const TaskDB& taskDB, Options& options) const;
	void DeleteTask(TaskDB& taskDB, Options& options);
};

int DisplayMenu();

#endif