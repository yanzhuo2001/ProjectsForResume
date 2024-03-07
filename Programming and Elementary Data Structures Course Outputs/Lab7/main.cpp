#include <iostream>
#include "course.h"


int main() {
    Course *ve281 = create("Upper Level Technical", "VE281");
    ve281->updateTask("Project", 1, 10, 20);
    ve281->updateTask("Lab", 1, 9, 20);
    ve281->print();
    delete ve281;
    return 0;
}
