#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

class TaskQueue {
  public:
    void put(int task) {
        std::lock_guard<std::mutex> locker(mutex_);
        // When the thread is blocked, if the thread has locked the mutex, the lock will be unlocked.
        // When the thread is unblocked, the thread lock the mutex again
        not_full_.wait(mutex_, [=]() {
            // Returning true means unblocked
            return max_size_ != task_queue_.size();
        });
        task_queue_.push(task);
        std::cout << "Add task: " << task << ", thread ID: " << std::this_thread::get_id() << std::endl;

        not_empty_.notify_one();
    }

    void take() {
        mutex_.lock();
        not_empty_.wait(mutex_, [=]() {
            return !task_queue_.empty();
        });
        int node = task_queue_.front();
        task_queue_.pop();
        mutex_.unlock();
        std::cout << "Delete task: " << node << ", thread ID: " << std::this_thread::get_id() << std::endl;

        not_full_.notify_all();
    }

    bool is_full() {
        std::lock_guard<std::mutex> locker(mutex_);
        return max_size_ == task_queue_.size();
    }

    bool is_empty() {
        std::lock_guard<std::mutex> locker(mutex_);
        return task_queue_.empty();
    }

    int queue_size() {
        std::lock_guard<std::mutex> locker(mutex_);
        return task_queue_.size();
    }

  private:
    int max_size_;
    std::queue<int> task_queue_;
    std::mutex mutex_;
    std::condition_variable_any not_full_;
    std::condition_variable_any not_empty_;
};

int main() {
    std::thread producers[5];
    std::thread consumers[5];
    
    TaskQueue task_queue;
    for (int i = 0; i < 5; ++i) {
        producers[i] = std::thread(&TaskQueue::put, &task_queue, 100 + i);
        consumers[i] = std::thread(&TaskQueue::take, &task_queue);
    }

    for (int i = 0; i < 5; ++i) {
        producers[i].join();
        consumers[i].join();
    }

    return 0;
}