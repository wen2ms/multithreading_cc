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
                std::lock_guard<std::recursive_mutex> guard(mutex_);
                increment(2);
                --number_;
                std::cout << "--current number: " << number_ << std::endl;
            }

            std::this_thread::yield();
        }
    }

    void work() {
        while (true) {
            if (timed_mutex_.try_lock_for(std::chrono::milliseconds(100))) {
                count_++;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::cout << "Grabbed the mutex, thread ID: " << std::this_thread::get_id() << std::endl;
                timed_mutex_.unlock();
                break;
            } else {
                std::cout << "Not grabbed the mutex, thread ID: " << std::this_thread::get_id() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }

  private:
    int number_ = 999;
    std::recursive_mutex mutex_;

    int count_ = 0;
    std::timed_mutex timed_mutex_;
};

int main() {
    Operation operation;
    // std::thread t1(&Operation::increment, &operation, 10);
    // std::thread t2(&Operation::decrement, &operation, 10);

    std::thread t1(&Operation::work, &operation);
    std::thread t2(&Operation::work, &operation);

    t1.join();
    t2.join();

    return 0;
}