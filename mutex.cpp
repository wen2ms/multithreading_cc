#include <iostream>
#include <thread>
#include <mutex>

class Operation {
  public:
    void increment(int count) {
        for (int i = 0; i < count; ++i) {
            mutex_.lock();
            ++number_;
            std::cout << "++current number: " << number_ << std::endl;
            mutex_.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    void decrement(int count) {
        for (int i = 0; i < count; ++i) {
            // mutex_.lock();
            // --number_;
            // std::cout << "--current number: " << number_ << std::endl;
            // mutex_.unlock();

            {
                std::lock_guard<std::mutex> guard(mutex_);
                --number_;
                std::cout << "--current number: " << number_ << std::endl;
            }

            std::this_thread::yield();
        }
    }

  private:
    int number_ = 999;
    std::mutex mutex_;
};

int main() {
    Operation operation;
    std::thread t1(&Operation::increment, &operation, 10);
    std::thread t2(&Operation::decrement, &operation, 10);

    t1.join();
    t2.join();

    return 0;
}