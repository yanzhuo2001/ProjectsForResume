//
// Created by 16979 on 2022/7/2.
//

#ifndef COURSE_H
#define COURSE_H

/*
 * Task is used to represent tasks in a course.
 * type could be "Lab", "Project" and etc., which specifies the type of the task,
 * index is the number of task of this type,
 * dueMonth and dueDay specifies its due date
 */
struct Task {
    std::string type;
    int index{}; // Task index of type
    int dueMonth{};
    int dueDay{};
};

const int MAX_TASKS = 4; // default value of the maximum number of tasks in a course at a time

// an exception class
class TooManyTasks : public std::exception {

};

class Course {
public:
    virtual void updateTask(const std::string &type, int index, int dueMonth, int dueDay)=0;
// REQUIRES: dueMonth and dueDay are in normal range.
// MODIFIES: this
// EFFECTS: adds/updates Task index of type; throw exception if fails to add Task
    virtual void finishTask(const std::string &type, int index, int finishMonth, int
    finishDay)=0;
// REQUIRES: Task index of type exists in tasks. finishMonth and finishDay are in normal range.
// MODIFIES: this
// EFFECTS: removes Task index of type
    virtual void print() const=0;
// EFFECTS: prints all unfinished tasks of this Course
    virtual ~Course()=default;
};

Course *create(const std::string &classType, const std::string &courseCode, const int &size);

Course *create(const std::string &classType, const std::string &courseCode);

/*
 * EFFECTS: returns a pointer according to classType
 *          If classType is not "Technical" or "Upper Level Technical", returns a null pointer.
 *          If we have a third argument and it is an integer, the maximum number of tasks will be this integer
 *          otherwise, the maximum number of tasks is the default value.
 */

class TechnicalCourse : public Course {
protected:
    Task *tasks;
    int sizeTasks;
    int numTasks;
    std::string courseCode;
public:
    // TODO: implement the constructor
    TechnicalCourse(std::string courseCode, int size = MAX_TASKS);

    // TODO: declare and implement the destructor
    ~TechnicalCourse() override;

    // TODO: declare updateTask method
    void updateTask(const std::string &type, int index, int dueMonth, int dueDay) override;

    void finishTask(const std::string &type, int index, int finishMonth, int finishDay) override;

    void print() const override;
};

class UpperLevelTechnicalCourse : public TechnicalCourse {
public:
    // TODO: implement the constructor
    UpperLevelTechnicalCourse(const std::string &courseCode, int size = MAX_TASKS);

    // TODO: declare and implement the destructor
    ~UpperLevelTechnicalCourse() override = default;

    void updateTask(const std::string &type, int index, int dueMonth, int dueDay) override;
};

#endif //COURSE_H
