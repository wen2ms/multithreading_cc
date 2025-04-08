#include <iostream>
#include <thread>

void foo() {
    std::cout << "Foo id: " << std::this_thread::get_id() << std::endl;
}

void bar(std::string name, int age) {
    std::cout << "Name: " << name << " , age: " << age << std::this_thread::get_id() << std::endl;
}

int main() {
    // Empty thread object
    std::thread thread1;

    std::thread thread2(foo);

    std::thread thread3(bar, "Lucy", 18);

    std::thread thread4([=](int id) {
        std::cout << "Id: " << id << std::this_thread::get_id() << std::endl;
    }, 0001);

    std::thread&& thread5 = std::move(thread4);

    std::cout << "Foo get_id(): " << thread2.get_id() << std::endl;

    thread2.join();
    thread3.join();
    thread5.join();

    return 0;
}