#include <future>
#include <iostream>

int main() {
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl;

    std::future<std::string> f = std::async(
        [](int num) {
            std::cout << "Thread id = " << std::this_thread::get_id() << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(3));

            return "num = " + std::to_string(num);
        },
        100);

    std::future_status status;

    do {
        status = f.wait_for(std::chrono::seconds(1));

        if (status == std::future_status::deferred) {
            std::cout << "Subthread has not been processed" << std::endl;
            f.wait();
        } else if (status == std::future_status::ready) {
            std::cout << "Ready, data: " << f.get() << std::endl;
        } else {
            std::cout << "subthread is running" << std::endl;
        }
    } while (status != std::future_status::ready);

    f = std::async(
        std::launch::deferred,
        [](int num) {
            std::cout << "Thread id = " << std::this_thread::get_id() << std::endl;

            return "num = " + std::to_string(num);
        },
        100);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    std::cout << "data: " << f.get() << std::endl;

    return 0;
}