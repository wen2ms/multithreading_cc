#include <iostream>
#include <atomic>

struct Student {
    Student(std::string n, int a) : name(n), age(a) {}

    int age;
    std::string name;
};

int main() {
    std::atomic<char> c('a');
    std::atomic_char cc('b');

    std::atomic<int> b;
    std::atomic_init(&b, 10);

    cc = 'c';
    b.store(99);

    char ccc = c.exchange('e');

    Student student("Chen", 18);
    std::atomic<Student*> student_atomic(&student);

    std::cout << "c value: " << c << std::endl;
    std::cout << "ccc value: " << ccc << std::endl;
    std::cout << "b value: " << b.load() << std::endl;

    Student* student_ptr = student_atomic;
    std::cout << "Name: " << student_ptr->name << ", age: " << student_ptr->age << std::endl; 

    return 0;
}