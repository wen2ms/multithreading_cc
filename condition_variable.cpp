#include <iostream>
#include <thread>
#include <queue>

class TaskQueue {
  public:
    void put(int& task) {
        task_queue_.push(task);
        std::cout << "Add task: " << task << ", thread ID: " << std::this_thread::get_id() << std::endl;
    }

    void take() {
        int node = task_queue_.front();
        task_queue_.pop();
        std::cout << "Delete task: " << node << ", thread ID: " << std::this_thread::get_id() << std::endl;
    }

    bool is_full() {
        return max_size_ == task_queue_.size();
    }

    bool is_empty() {
        return task_queue_.empty();
    }

    int queue_size() {
        return task_queue_.size();
    }

  private:
    int max_size_;
    std::queue<int> task_queue_;
};

int main() {

    return 0;
}