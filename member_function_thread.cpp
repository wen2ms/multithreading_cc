#include <functional>
#include <iostream>
#include <thread>

class Animation {
  public:
    void title(std::string title) {
        std::cout << "Title is " << title << std::endl;
    }

    static void print_type() {
        std::cout << "Animation..." << std::endl;
    }
};

int main() {
    std::thread t1(&Animation::print_type);

    Animation animation;

    std::thread t2(&Animation::title, animation, "Peace");
    std::thread t3(&Animation::title, &animation, "Peace");

    std::thread t4(std::bind(&Animation::title, &animation, "Peace"));
    std::thread t5(std::bind(&Animation::title, animation, "Peace"));
    std::thread t6(std::bind(&Animation::title, animation, std::placeholders::_1), "Peace");

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    return 0;
}