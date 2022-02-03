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
    bool waiting;
    condition_variable cv;

public:
    explicit Workers(int numThreads) {
        this->numThreads = numThreads;
    }

    void start() {
        for (int i = 0; i < numThreads; i++) {
            worker_threads.emplace_back([this] {
                while(run) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(tasks_mutex);
                        while(waiting) {
                            cv.wait(lock);
                        }
                        waiting = true;
                        if(!tasks.empty()) {
                            task = *tasks.begin();
                            tasks.pop_front();
                        }
                        lock.unlock();
                        waiting = false;
                        cv.notify_one();
                    }
                    if(task) {
                        task();
                    }
                }
            });
        }
        cv.notify_one();
    }

    void post(const function<void()>& function) {
        unique_lock<mutex> lock(tasks_mutex);
        tasks.emplace_back(function);
        lock.unlock();
        waiting = false;
        cv.notify_one();
    }

    void post_timeout(const function<void()>& function, int t) {
        this_thread::sleep_for(milliseconds (t));
        unique_lock<mutex> lock(tasks_mutex);
        tasks.emplace_back(function);
        waiting = false;
        cv.notify_one();
    }

    void stop() {
        run = false;
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
        cout << "task " << 1
            << " runs in thread "
            << this_thread::get_id()
            << endl;
    });

    workerThreads.post([] {
       cout << "task " << 2
            << " runs in thread "
            << this_thread::get_id()
            << endl;
    });

    eventLoop.post([] {
       cout << " task " << 3
            << " runs in thread "
            << this_thread::get_id()
            << endl;
    });

    eventLoop.post([] {
        cout << " task " << 4
             << " runs in thread "
             << this_thread::get_id()
             << endl;
    });

    workerThreads.post_timeout([] {
        cout << " timed task, running in thread: "
             << this_thread::get_id() << endl;
    }, 2000);

    workerThreads.stop();
    eventLoop.stop();
}
