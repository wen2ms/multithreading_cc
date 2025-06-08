#include <future>
#include <iostream>
#include <thread>

void worker(std::promise<std::string>& pro) {
    std::this_thread::sleep_for(std::chrono::seconds(3));

    pro.set_value("Hello Main...");

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    std::promise<std::string> pro;

    // std::thread t1(work, std::ref(pro));

    std::thread t2(
        [](std::promise<std::string>& pro) {
            std::this_thread::sleep_for(std::chrono::seconds(3));

            pro.set_value("Hello Main...");

            std::this_thread::sleep_for(std::chrono::seconds(1));
        },
        std::ref(pro));

    std::future<std::string> f = pro.get_future();

    std::string str = f.get();

    std::cout << "Subthread say: " << str << std::endl;

    // t1.join();

    t2.join();

    return 0;
}