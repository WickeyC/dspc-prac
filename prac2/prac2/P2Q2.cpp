#include <iostream>
#include <vector>
#include <pthread.h>
#include <chrono>
using namespace std;

// stopwatch. Returns time in seconds
class timer {
public:
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    timer() : lastTime(std::chrono::high_resolution_clock::now()) {}
    inline double elapsed() {
        std::chrono::time_point<std::chrono::high_resolution_clock> thisTime = std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double>(thisTime - lastTime).count();
        lastTime = thisTime;
        return deltaTime;
    }
};

#define NTHREADS 10
const int c = 1000000000;
double timerResult[NTHREADS];

//void* f_count(void* v)
//{
//    //(*(int*)v)++;
//
//    //TODO: print thread count
//    /*pthread_t thread_id;
//    thread_id = pthread_self();*/
//
//    //std::cout << "The ID of the current thread is : " << thread_id << std::endl;
//
//    return NULL;
//}

void* f_count(void* timerResult) {
    pthread_t thread_id = pthread_self();

    volatile int i = 0; // volatile eliminates optimization removal
    timer stopwatch;
    while (i++ < c);
    (*(double*)timerResult) = stopwatch.elapsed();
    return NULL;
}


int main()
{
    //int* count = new int(0);

    //vector<pthread_t> vt;

    //pthread_t t;

    //for (int i = 0; i < 100; i++)
    //    vt.push_back(t);

    //for (auto x : vt)
    //    pthread_create(&x, NULL, &f_count, count),
    //    pthread_join(x, NULL);

    //std::cout << *count << std::endl;
    cout.precision(6);
    cout << fixed;
    f_count(&timerResult[0]);
    cout << "f1 solo execution time " << timerResult[0] << endl;

    timer stopwatch;
    {
        pthread_t thread_id[NTHREADS];

        for (int i = 0; i < NTHREADS; i++)
        {
            //pthread_create(&thread_id[i], NULL, f_count, NULL);
            pthread_create(&thread_id[i], NULL, f_count, &timerResult[i]);
        }

        for (int j = 0; j < NTHREADS; j++)
        {
            pthread_join(thread_id[j], NULL);
        }
    }
    double elapsed = stopwatch.elapsed();
    for (int k = 0; k < NTHREADS; k++)
    {
        cout << "thread " << k << " execution time " << timerResult[k] << endl;
    }
    cout << "f1 - f" << NTHREADS << " execution time " << elapsed << endl << endl;
    cout << "-----DONE-----" << endl;

    return 0;
}