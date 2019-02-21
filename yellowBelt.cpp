#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <set>
using namespace std;

// ������������ ��� ��� ������� ������
enum class TaskStatus {
	NEW,
	IN_PROGRESS,
	TESTING,
	DONE
};

// ���-������� ��� map<TaskStatus, int> ����������� ������� ���������� ����� ������� �������
using TasksInfo = map<TaskStatus, int>;

//void UpdateTask(int& tasks, int& task_count) {
//	if
//}

class TeamTasks {
public:
	// �������� ���������� �� �������� ����� ����������� ������������
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return vault.at(person);
	}

	// �������� ����� ������ (� ������� NEW) ��� ����������� ������������
	void AddNewTask(const string& person) {
		++vault[person][TaskStatus::NEW];
	}

	// �������� ������� �� ������� ���������� ����� ����������� ������������
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
		TasksInfo updated_tasks = vault[person];
		vector<TaskStatus> selector{TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING};
		int tmp_count = 0;
		for (auto el : selector) {
			updated_tasks[el] += tmp_count;
			if (updated_tasks[el] > task_count) {
				updated_tasks[el] -= task_count;
				updated_tasks[static_cast<TaskStatus>(static_cast<int>(el) +1)] += task_count;
				tmp_count = task_count;
				break;
			} else {
				task_count -= updated_tasks[el];
				tmp_count = updated_tasks[el];
				updated_tasks[el] = 0;
			}
		}
//		updated_tasks[TaskStatus::DONE] += tmp_count;
		vault[person] = updated_tasks;
		return tie(updated_tasks, updated_tasks);
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
