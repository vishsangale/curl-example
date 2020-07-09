#define NOMINMAX

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>  

#include <curl/curl.h>

std:: mutex _mutex;

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), size * nmemb);
    return size*nmemb;
}

void lock()
{
   _mutex.lock();
}

void unlock()
{
   _mutex.unlock();
}

void curl_test()
{
    CURL* curl =  curl_easy_init();
    
    std::string read_buffer;
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        //curl_share_setopt(curl, CURLSHOPT_LOCKFUNC, lock);
        //curl_share_setopt(curl, CURLSHOPT_UNLOCKFUNC, unlock);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);
    for (int t = 0; t < 10; ++t)
    {
        const int nr_threads = 10000;
        std::vector<std::thread> threads(nr_threads);
        for (int i = 0; i < nr_threads; ++i)
        {
            threads[i] = std::thread(curl_test);
            std::cout << "Iteration: " << t << ", Thread: " << i << std::endl;
        }
        int joined = 0;
        for (auto& thread: threads)
        {
            thread.join();
            ++joined;
            std::cout << "Thread joined: " << joined << std::endl;
        }
        std::cout << "Interation finished: " << t << std::endl;
    }
    curl_global_cleanup();
}
