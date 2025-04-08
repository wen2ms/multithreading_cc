#include <iostream>
#include <thread>

void foo() {
    std::cout << "Foo id: " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::thread thread1;

    std::cout << "thread1 joinable: " << thread1.joinable() << std::endl;

    std::thread thread2(foo);

    std::cout << "thread2 joinable before join: " << thread2.joinable() << std::endl;

    thread2.join();

    std::cout << "thread2 joinable after join: " << thread2.joinable() << std::endl;

    std::thread thread3(foo);
    thread3.detach();

    std::cout << "thread3 joinable: " << thread3.joinable() << std::endl;

    return 0;
}