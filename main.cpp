// compiler MSVC
// Author: Safianova Mariia K25
// Variant: 9

#include <iostream>
#include <string>
#include <thread>
#include <barrier>
#include <chrono>
#include <syncstream>

using namespace std;

const int nt = 3;

// A set can start only after all sets it depends on are finished,
// so every phase boundary below is a barrier shared by all threads
barrier phaseEnd(nt);

void synchronizedOut(const string &s)
{
    osyncstream(cout) << s;
}

// i-th action of set x
void f(char x, int i)
{
    this_thread::sleep_for(chrono::seconds(1));
    synchronizedOut(string("Action ") + to_string(i) + " from set " + x + " completed.\n");
}

void thread1()
{
    f('a', 1); f('a', 2); f('a', 3);
    phaseEnd.arrive_and_wait();

    f('a', 4);
    phaseEnd.arrive_and_wait();

    f('e', 2); f('e', 4); f('e', 6); f('e', 8);
    phaseEnd.arrive_and_wait();

    f('h', 1); f('h', 3); f('h', 5); f('h', 7);
    phaseEnd.arrive_and_wait();

    f('j', 1); f('j', 2);
    phaseEnd.arrive_and_wait();

    f('j', 4); f('i', 2);
    phaseEnd.arrive_and_wait();

    f('k', 1); f('k', 4); f('k', 7);
}

void thread2()
{
    f('b', 1); f('b', 3); f('b', 5);
    phaseEnd.arrive_and_wait();

    f('e', 1);
    phaseEnd.arrive_and_wait();

    f('e', 3); f('e', 5); f('e', 7); f('d', 4);
    phaseEnd.arrive_and_wait();

    f('h', 2); f('h', 4); f('h', 6); f('c', 4);
    phaseEnd.arrive_and_wait();

    f('g', 3); f('g', 5);
    phaseEnd.arrive_and_wait();

    f('j', 5); f('i', 3);
    phaseEnd.arrive_and_wait();

    f('k', 2); f('k', 5); f('k', 8);
}

void thread3()
{
    f('b', 2); f('b', 4); f('b', 6);
    phaseEnd.arrive_and_wait();

    f('g', 1);
    phaseEnd.arrive_and_wait();

    f('d', 1); f('d', 2); f('d', 3); f('d', 5);
    phaseEnd.arrive_and_wait();

    f('c', 1); f('c', 2); f('c', 3); f('g', 2);
    phaseEnd.arrive_and_wait();

    f('g', 4); f('j', 3);
    phaseEnd.arrive_and_wait();

    f('i', 1); f('i', 4);
    phaseEnd.arrive_and_wait();

    f('k', 3); f('k', 6);
}

int main()
{
    synchronizedOut("Computation started.\n");
    auto start = chrono::steady_clock::now();

    jthread t1(thread1);
    jthread t2(thread2);
    jthread t3(thread3);
    t1.join();
    t2.join();
    t3.join();

    chrono::duration<double> total = chrono::steady_clock::now() - start;
    synchronizedOut("Computation finished. Computation time: " + to_string(total.count()) + " seconds.\n");

    return 0;
}
