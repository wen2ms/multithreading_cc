#include <functional>
#include <future>
#include <iostream>
#include <thread>

std::string foo() {
    std::this_thread::sleep_for(std::chrono::seconds(3));

    return "Hello, I'm foo...";
}

using func_ptr = std::string (*)(std::string, int);

class Base {
  public:
    std::string operator()(std::string msg) {
        return "operator(): " + msg;
    }

    operator func_ptr() {
        return show_msg;
    }

    static std::string show_msg(std::string msg, int num) {
        return "show_msg: " + msg + ", " + std::to_string(num);
    }

    int increase(int num) {
        return num + 10;
    }
};

int main() {
    std::packaged_task<std::string()> task1(foo);

    std::packaged_task<int(int)> task2([](int num) { return 100; });

    Base b1;
    std::packaged_task<std::string(std::string)> task3(b1);

    Base b2;
    std::packaged_task<std::string(std::string, int)> task4(b2);

    std::packaged_task<std::string(std::string, int)> task5(Base::show_msg);

    Base b3;
    auto obj = std::bind(&Base::increase, &b3, std::placeholders::_1);
    std::packaged_task<int(int)> task6(obj);

    std::thread t1(std::ref(task6), 200);

    std::future<int> f = task6.get_future();

    int num = f.get();

    std::cout << num << std::endl;

    t1.join();

    return 0;
}