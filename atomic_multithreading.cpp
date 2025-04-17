#include <iostream>
#include <thread>
#include <atomic>

class Counter {
  public:
    void increment_1() {
        for (int i = 0; i < 100; ++i) {
            number_++;
            std::cout << "increment_1 thread id: " << std::this_thread::get_id() << ", number: " << number_ << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void increment_2() {
        for (int i = 0; i < 100; ++i) {
            number_++;
            std::cout << "increment_2 thread id: " << std::this_thread::get_id() << ", number: " << number_ << std::endl;
            
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    std::atomic_int number_ = 0;
};

int main() {
    Counter counter;
    std::thread t1(&Counter::increment_1, &counter);
    std::thread t2(&Counter::increment_2, &counter);

    t1.join();
    t2.join();

    return 0;
}