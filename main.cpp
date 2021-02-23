#include <iostream>
#include "./httplib.h"
#include <vector>
#include <thread>
#include <windows.h>

using namespace std;

mutex npx;

int tempMain() {
    while (true) {
        httplib::Client cli("localhost", 80);

        npx.lock();

        if (auto res = cli.Get("/json/temp.php")) {
            if (res->status == 200) {
                cout << res->body << endl;
            }
        }
        else {
            auto err = res.error();
        }
        npx.unlock();
        Sleep(1000);
    }
    
}

int cisnMain() {
    while (true) {
        httplib::Client cli("localhost", 80);
        npx.lock();
        if (auto res = cli.Get("/json/cisn.php")) {
            if (res->status == 200) {
                cout << res->body << endl;
            }
        }
        else {
            auto err = res.error();
        }
        npx.unlock();
        Sleep(500);
    }
    
}

int wilgMain() {
    while (true) {
        httplib::Client cli("localhost", 80);
        npx.lock();
        if (auto res = cli.Get("/json/wilg.php")) {
            if (res->status == 200) {
                cout << res->body << endl;
            }
        }
        else {
            auto err = res.error();
        }
        npx.unlock();
        Sleep(2000);
        
    }
}

int main()
{
    vector <thread*> threads1;

    thread* watek = new thread(tempMain);
    threads1.push_back(watek);


    thread* watek2 = new thread(cisnMain);
    threads1.push_back(watek2);

    thread* watek3 = new thread(wilgMain);
    threads1.push_back(watek3);

    for (vector<thread*>::iterator it = threads1.begin(); it != threads1.end(); ++it) {
        (*it)->join(); //tablica wskaźników na wątki, a it to wskaźnik na wskaźnik
    }

    return 0;
}
