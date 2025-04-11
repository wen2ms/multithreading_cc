#include <iostream>
#include <thread>
#include <mutex>

std::once_flag global_once_flag;

class Dog {
  public:
    Dog(const Dog& other) = delete;
    Dog& operator =(const Dog& other) = delete;

    static Dog* get_instance() {
        std::call_once(global_once_flag, [&]() {
            if (dog_ == nullptr) {
                dog_ = new Dog;

                std::cout << "Dog was created..." << std::endl;
            }
        });

        return dog_;
    }

    void set_name(const std::string& name) {
        name_ = name;
    }

    std::string name() {
        return name_;
    }

  private:
    Dog() = default;

    static Dog* dog_;
    std::string name_;
};

Dog* Dog::dog_ = nullptr;

void set_singleton_name(const std::string& name) {
    Dog::get_instance()->set_name(name);

    std::cout << "Dog's name is " << Dog::get_instance()->name() << std::endl;
}

int main() {
    std::thread t1(set_singleton_name, "Golden Retriver");
    std::thread t2(set_singleton_name, "French Bulldog");
    std::thread t3(set_singleton_name, "Labrador Retriver");

    t1.join();
    t2.join();
    t3.join();

    return 0;
}