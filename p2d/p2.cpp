#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>
#include <functional>
#include <list>
#include <chrono>

using namespace std;
using namespace chrono;

class Workers {
private:
    vector<thread> worker_threads;
    list<function<void()>> tasks;
    mutex tasks_mutex;
    int numThreads;
    bool run = true;
    condition_variable cv;

public:
    explicit Workers(int numThreads) {
        this->numThreads = numThreads;
    }

     // Creating and starting threads.
    void start() {

        if(!run) {
            // Worker pool is already started.
            return;
        }

        for (int i = 0; i < numThreads; i++) {
            worker_threads.emplace_back([i, this] {
                while(run) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(tasks_mutex);
                        while(tasks.empty()) {
                            cout << to_string(i+1) << ": No tasks to work on.\n";
                            cout << to_string(i+1) << ": Going to sleep.\n";
                            cv.wait(lock);
                            cout << to_string(i+1) << ": Got woken up.\n";
                        }
                        if(!tasks.empty()) {
                            task = *tasks.begin();
                            tasks.pop_front();
                        }
                    }
                    if(task) {
                        cout << to_string(i+1) << ": Running task.\n";
                        task();
                    }
                }
            });
        }
        cv.notify_one();
    }

    // Placing function in queue and is ready to be worked on.
    void post(const function<void()>& function) {
        unique_lock<mutex> lock(tasks_mutex);
        tasks.emplace_back(function);
           cv.notify_one();
    }

    // Makes the function wait for a specified time.
    void post_timeout(const function<void()>& function, int t) {
        post([&function, t] {
            this_thread::sleep_for(milliseconds (t));
            function();
        });
    }

    void stop() {
        run = false;
        cv.notify_all();
        for(auto &thread: worker_threads)
            thread.join();
    }
};

int main() {
    Workers workerThreads(4);
    Workers eventLoop(1);

    workerThreads.start();
    eventLoop.start();

    workerThreads.post([] {
        cout << "Function 1 running.\n";
    });

    workerThreads.post([] {
       cout << "Function 2 running.\n";
    });

    eventLoop.post([] {
       cout << "Function 3 running.\n";
    });

    eventLoop.post([] {
        cout << "Function 4 running.\n";
    });

    workerThreads.post_timeout([] {
        cout << "Function 5 running with timeout delay.\n";
    }, 2000);

    workerThreads.stop();
    eventLoop.stop();
}
