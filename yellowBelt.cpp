#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <set>
using namespace std;

// ѕеречислимый тип дл€ статуса задачи
enum class TaskStatus {
	NEW,
	IN_PROGRESS,
	TESTING,
	DONE
};

// “ип-синоним дл€ map<TaskStatus, int> позвол€ющий хранить количество задач данного статуса
using TasksInfo = map<TaskStatus, int>;

//void UpdateTask(int& tasks, int& task_count) {
//	if
//}

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
		TasksInfo updated_tasks, untouched_tasks;
		for (int i = 0; i < task_count; i++) {
			if (copy_tasks[TaskStatus::NEW] > 0) {
				--copy_tasks[TaskStatus::NEW];
				++updated_tasks[TaskStatus::NEW];
				continue;
			} else if (copy_tasks[TaskStatus::IN_PROGRESS] > 0) {
				--copy_tasks[TaskStatus::IN_PROGRESS];
				++updated_tasks[TaskStatus::IN_PROGRESS];
				continue;
			} else if (copy_tasks[TaskStatus::TESTING] > 0) {
				--copy_tasks[TaskStatus::TESTING];
				++updated_tasks[TaskStatus::TESTING];
			}
		}
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
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	cout << "-----------------" << endl;
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));


//	cout << "-----------------" << endl;
//	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
//	cout << "Updated Ivan's tasks: ";
//	PrintTasksInfo(updated_tasks);
//	cout << "Untouched Ivan's tasks: ";
//	PrintTasksInfo(untouched_tasks);
}
