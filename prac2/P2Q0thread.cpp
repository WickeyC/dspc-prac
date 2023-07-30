#include<iostream> // for std::cout
#include<thread> // for std::thread
using std::this_thread::sleep_for;
using std::chrono::seconds;

auto f() {
    std::cout << "Task started ...\n";
    sleep_for(seconds(2));
    std::cout << " Task done!\n";
}

int main() {
    std::thread t(f);

    std::cout << "Run some other tasks.\n";

    t.join();

    return 0;
}

