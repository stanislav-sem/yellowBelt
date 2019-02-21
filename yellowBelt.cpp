#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <set>
using namespace std;

/*
[{"IN_PROGRESS": 5}, {}]
[{"TESTING": 5}, {}]
[{"DONE": 1}, {"TESTING": 4}]
[]
[{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4, "DONE": 1}]
{"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
[{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4, "DONE": 1}]
{"NEW": 0, "IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}

Correct output:
[]
[{"IN_PROGRESS": 5}, {}]
[{"TESTING": 5}, {}]
[{"DONE": 1}, {"TESTING": 4}]
[]
[{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
{"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
[{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]
{"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
 */

// ѕеречислимый тип дл€ статуса задачи
enum class TaskStatus {
	NEW,
	IN_PROGRESS,
	TESTING,
	DONE
};

// “ип-синоним дл€ map<TaskStatus, int> позвол€ющий хранить количество задач данного статуса
using TasksInfo = map<TaskStatus, int>;

TasksInfo ZeroElErase(TasksInfo input) {
	TasksInfo result;
	for (auto el : {TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE }) {
		if (input[el] != 0) {
			result[el] = input[el];
		}
	}
	return result;
}

class TeamTasks {
public:
	// ѕолучить статистику по статусам задач конкртеного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return vault.at(person);
	}

	// ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчика
	void AddNewTask(const string& person) {
		++vault[person][TaskStatus::NEW];
	}

	// ќбновить статусы по данному количеству задач конкретного разработчика
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
		TasksInfo copy_tasks = vault[person];
		TasksInfo updated_tasks;
		for (int i = 0; i < task_count; i++) {
			if (copy_tasks[TaskStatus::NEW] > 0) {
				--copy_tasks[TaskStatus::NEW];
				++updated_tasks[TaskStatus::IN_PROGRESS];
				continue;
			} else if (copy_tasks[TaskStatus::IN_PROGRESS] > 0) {
				--copy_tasks[TaskStatus::IN_PROGRESS];
				++updated_tasks[TaskStatus::TESTING];
				continue;
			} else if (copy_tasks[TaskStatus::TESTING] > 0) {
				--copy_tasks[TaskStatus::TESTING];
				++updated_tasks[TaskStatus::DONE];
			}
		}
		for (auto el : {TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE }) {
			vault[person][el] = updated_tasks[el] + copy_tasks[el];
		}
		updated_tasks = ZeroElErase(updated_tasks);
		copy_tasks = ZeroElErase(copy_tasks);
		return tie(updated_tasks, copy_tasks);
	}


private:
	map<string, TasksInfo> vault;
};

void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks, " <<
			tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress, " <<
			tasks_info[TaskStatus::TESTING] << " tasks ate being tested, " <<
			tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}


int main() {
	TeamTasks tasks;
	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	TasksInfo updated_tasks, untouched_tasks;
	tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	tasks.PerformPersonTasks("Alice", 1);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	tasks.PerformPersonTasks("Alice", 2);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	tasks.PerformPersonTasks("Alice", 4);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));


}
