//
// Created by 16979 on 2022/7/2.
//

#include <iostream>
#include "course.h"



TechnicalCourse::TechnicalCourse(std::string coursecode, int size) {
    sizeTasks = size;
    numTasks = 0;
    courseCode = coursecode;
    tasks=new Task[sizeTasks];
}

TechnicalCourse::~TechnicalCourse() {
    delete [] tasks;
}

void TechnicalCourse::updateTask(const std::string &type, int index, int dueMonth, int dueDay)
// REQUIRES: dueMonth and dueDay are in normal range.
// MODIFIES: this
// EFFECTS: if Task index of type already exists in tasks, updates its dueMonth & dueDay ;
//          otherwise, adds Task i of type at the end of tasks if tasks is not full,
//          throw an exception if tasks is full
{
    int judge=0;
    int i;
    if(numTasks<sizeTasks){
        for (i=0; i < numTasks; i++){              //update the item if it already exists
            if((tasks[i].type==type)&&(tasks[i].index==index)){
                judge=1;
                break;
            }
        }
        if(judge==1){
            tasks[i].type=type;
            tasks[i].index=index;
            tasks[i].dueMonth=dueMonth;
            tasks[i].dueDay=dueDay;
        }
        else{
            tasks[numTasks].type=type;
            tasks[numTasks].index=index;
            tasks[numTasks].dueMonth=dueMonth;
            tasks[numTasks].dueDay=dueDay;
            numTasks++;
        }

        if(type=="Lab"||type=="Project"){
            if(judge==0){                               //if the item has existed, don't output anything
                std::cout<<courseCode<<" "<<type<<" "<<index<<" is released! Submit it via oj!"<<std::endl;
            }
        }
        else{
            if(judge==0){
                std::cout<<courseCode<<" "<<type<<" "<<index<<" is released! Submit it via canvas!"<<std::endl;
            }
        }
    }
    else{
        throw TooManyTasks();
    }
}

void TechnicalCourse::finishTask(const std::string &type, int index, int finishMonth, int finishDay)
// REQUIRES: Task index of type is in tasks. finishMonth and finishDay are in normal range.
// MODIFIES: this
// EFFECTS: removes Task index of type
{
    int i;
    for (i = 0; i < numTasks; i++){
        if((tasks[i].type==type)&&(tasks[i].index==index)){
            break;
        }
    }
    if((tasks[i].dueMonth<finishMonth)||((tasks[i].dueMonth==finishMonth)&&(tasks[i].dueDay<finishDay))){                 //not finish in time
        std::cout<<courseCode<<" "<<type<<" "<<index<<" is overdue!"<<std::endl;
    }
    else{
        std::cout<<courseCode<<" "<<type<<" "<<index<<" is finished!"<<std::endl;
    }
    int j;
    for(j=i;j<numTasks-1;j++){                            // put each item front
        tasks[j].type=tasks[j+1].type;
        tasks[j].index=tasks[j+1].index;
        tasks[j].dueMonth=tasks[j+1].dueMonth;
        tasks[j].dueDay=tasks[j+1].dueDay;
    }
    numTasks--;
}

void TechnicalCourse::print() const {
    std::cout << courseCode << std::endl;
    for (int i = 0; i < numTasks; ++i) {
        std::cout << tasks[i].type << " " << tasks[i].index << ": "
                  << tasks[i].dueMonth << "/" << tasks[i].dueDay << std::endl;
    }
}

UpperLevelTechnicalCourse::UpperLevelTechnicalCourse(const std::string &coursecode, int size): TechnicalCourse(coursecode,size) {
    sizeTasks = size;
    numTasks = 0;
    courseCode = coursecode;
}


void UpperLevelTechnicalCourse::updateTask(const std::string &type, int index, int dueMonth, int dueDay)
// REQUIRES: dueMonth and dueDay are in normal range.
// MODIFIES: this
// EFFECTS: If Task index of type does not exist in tasks,
//          adds Task i of type according to its due date if tasks is not full, throw an exception if tasks is full.
//          If Task index of type already exists in tasks,
//          updates its position in tasks & dueMonth & dueDay if its dueMonth/dueDay is changed,
//          do nothing if its dueMonth/dueDay is unchanged.
{
    int judge=0;
    int i;
    Task temp;
    temp.type=type;
    temp.index=index;
    temp.dueMonth=dueMonth;
    temp.dueDay=dueDay;
    int position;
    if(numTasks<sizeTasks){
        for (i=0; i < numTasks; i++){
            if((tasks[i].type==type)&&(tasks[i].index==index)){
                judge=1;
                break;
            }
        }
        if(judge==1){           //update the item if it already exists
            tasks[i].type=type;
            tasks[i].index=index;
            tasks[i].dueMonth=dueMonth;
            tasks[i].dueDay=dueDay;
        }
        else{
            tasks[numTasks].type=type;
            tasks[numTasks].index=index;
            tasks[numTasks].dueMonth=dueMonth;
            tasks[numTasks].dueDay=dueDay;
            numTasks++;
        }

        for (i=0; i < numTasks; i++){      //find the position of item, using i to express
            if((tasks[i].type==type)&&(tasks[i].index==index)){
                break;
            }
        }
        position=i;

        if(numTasks==2){      //the situation that there are just 2 elements is different from the following
            if((tasks[1].dueMonth<tasks[0].dueMonth)||((tasks[1].dueMonth==tasks[0].dueMonth)&&(tasks[1].dueDay<tasks[0].dueDay))){
                temp=tasks[1];
                tasks[1]=tasks[0];
                tasks[0]=temp;
            }
        }
        else{
            bool judge11;
            bool judge12;
            bool judge21;
            bool judge22;
            int j;
            for(i=0;i<numTasks;i++){
                //the following judgements are used to judge if tasks[position] is between tasks[i] and tasks[i+1]
                judge11=tasks[position].dueMonth>tasks[i].dueMonth;
                judge12=(tasks[position].dueMonth==tasks[i].dueMonth)&&(tasks[position].dueDay>=tasks[i].dueDay);
                judge21=tasks[position].dueMonth<tasks[i+1].dueMonth;
                judge22=(tasks[position].dueMonth==tasks[i+1].dueMonth)&&(tasks[position].dueDay<tasks[i+1].dueDay);
                if(i==0){
                    if((tasks[position].dueMonth<tasks[i].dueMonth)||((tasks[position].dueMonth==tasks[i].dueMonth)&&(tasks[position].dueDay<tasks[i].dueDay))){
                        for(i=0;i<position-1;i++){
                            tasks[i+1]=tasks[i];
                        }
                        tasks[0]=temp;
                        break;
                    }
                }
                if(i>=0&&i<numTasks-1){
                    if((judge11||judge12)&&(judge21||judge22)){
                        if(i!=position){
                            if(i<position){        // item between [i+1,position-1] become [i+2,position]
                                for(j=i+1;j<position;j++){
                                    tasks[j+1]=tasks[j];
                                }
                                tasks[i+1]=temp;
                                break;
                            }
                            else{                  // item between [position+1,i] become [position,i-1]
                                for(j=position+1;j<i+1;j++){
                                    tasks[j-1]=tasks[j];
                                }
                                tasks[i]=temp;
                                break;
                            }
                        }
                    }
                }
                else if(i==numTasks-1){                          //i=numTasks-1
                    if((tasks[position].dueMonth>tasks[i].dueMonth)||((tasks[position].dueMonth==tasks[i].dueMonth)&&(tasks[position].dueDay<tasks[i].dueDay))||((tasks[position].dueMonth==tasks[i].dueMonth)&&(tasks[position].dueDay==tasks[i].dueDay))){
                        if(position!=i){       //originally not at the last position
                            for(j=position+1;j<numTasks;j++){
                                tasks[j-1]=tasks[j];
                            }
                            tasks[i]=temp;
                            break;
                        }
                    }
                }
            }
        }

        if(type=="Lab"||type=="Project"){
            if(judge==0){                               //if the item has existed, don't output anything
                std::cout<<courseCode<<" "<<type<<" "<<index<<" is released! Submit it via oj!"<<std::endl;
            }
        }
        else if(type=="Team Project"){
            if(judge==0){                               //if the item has existed, don't output anything
                std::cout<<courseCode<<" "<<type<<" "<<index<<" is released! Submit it via github!"<<std::endl;
            }
        }
        else{
            if(judge==0) {
                std::cout << courseCode << " " << type << " " << index << " is released! Submit it via canvas!"<< std::endl;
            }
        }
    }
    else{
        throw TooManyTasks();
    }
}

Course *create(const std::string &classType, const std::string &courseCode) {
    if (classType == "Technical") {
        return new TechnicalCourse(courseCode);
    } else if (classType == "Upper Level Technical") {
        return new UpperLevelTechnicalCourse(courseCode);
    } else {
        return nullptr;
    }
}

Course *create(const std::string &classType, const std::string &courseCode, const int &size) {
    if (classType == "Technical") {
        return new TechnicalCourse(courseCode, size);
    } else if (classType == "Upper Level Technical") {
        return new UpperLevelTechnicalCourse(courseCode, size);
    } else {
        return nullptr;
    }
}
