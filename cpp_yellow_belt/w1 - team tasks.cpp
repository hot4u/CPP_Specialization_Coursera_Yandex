#include <iostream>
#include <string>
#include <map>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};


// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return all_tasks.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчика
    void AddNewTask(const string& person) {
        all_tasks[person][TaskStatus::NEW]++;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    // Возвращает кортеж измененных задач и оставшихся без изменений
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count) {
        TasksInfo updated_tasks;
        TasksInfo untouched;
        TaskStatus cur_tasks = TaskStatus::NEW;
        while (task_count > 0 && cur_tasks != TaskStatus::DONE)
        {
            switch (cur_tasks) {
            case TaskStatus::NEW:
                if (all_tasks[person][cur_tasks] >= task_count)
                {
                    updated_tasks[TaskStatus::IN_PROGRESS] = task_count;
                    all_tasks[person][cur_tasks] -= task_count;
                    task_count = 0;
                }
                else if (all_tasks[person][cur_tasks] != 0)
                {
                    updated_tasks[TaskStatus::IN_PROGRESS] = all_tasks[person][cur_tasks];
                    task_count -= all_tasks[person][cur_tasks];
                    all_tasks[person][cur_tasks] = 0;
                }
                cur_tasks = TaskStatus::IN_PROGRESS;
                break;
            case TaskStatus::IN_PROGRESS:
                if (all_tasks[person][cur_tasks] >= task_count)
                {
                    updated_tasks[TaskStatus::TESTING] = task_count;
                    all_tasks[person][cur_tasks] -= task_count;
                    task_count = 0;
                }
                else if (all_tasks[person][cur_tasks] != 0)
                {
                    updated_tasks[TaskStatus::TESTING] = all_tasks[person][cur_tasks];
                    task_count -= all_tasks[person][cur_tasks];
                    all_tasks[person][cur_tasks] = 0;
                }
                cur_tasks = TaskStatus::TESTING;
                break;
            case TaskStatus::TESTING:
                if (all_tasks[person][cur_tasks] >= task_count)
                {
                    updated_tasks[TaskStatus::DONE] = task_count;
                    all_tasks[person][cur_tasks] -= task_count;
                    task_count = 0;
                }
                else if (all_tasks[person][cur_tasks] != 0)
                {
                    updated_tasks[TaskStatus::DONE] = all_tasks[person][cur_tasks];
                    task_count -= all_tasks[person][cur_tasks];
                    all_tasks[person][cur_tasks] = 0;
                }
                cur_tasks = TaskStatus::DONE;
                break;
            } //switch
        } //while

        for (const auto& tasks : all_tasks[person])
        {
            if (tasks.second != 0)
                untouched[tasks.first] =  tasks.second;
        }
        untouched.erase(TaskStatus::DONE);
        // обновляем all_tasks;
        for (const auto &tasks : updated_tasks)
        {
            all_tasks[person][tasks.first] += tasks.second;
        }

        RemoveZeroTasks(person);

        return { updated_tasks, untouched };
    }

private:
    map<string, TasksInfo> all_tasks;
    void RemoveZeroTasks(const string& person)
    {
        if (all_tasks[person][TaskStatus::NEW] == 0)
            all_tasks[person].erase(TaskStatus::NEW);
        if (all_tasks[person][TaskStatus::IN_PROGRESS] == 0)
            all_tasks[person].erase(TaskStatus::IN_PROGRESS);
        if (all_tasks[person][TaskStatus::TESTING] == 0)
            all_tasks[person].erase(TaskStatus::TESTING);
        if (all_tasks[person][TaskStatus::DONE] == 0)
            all_tasks[person].erase(TaskStatus::DONE);
    }
};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
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

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
       
    return 0;
}
