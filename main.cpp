#define NOMINMAX

#include <string>
#include <thread>
#include <vector>

#include <curl/curl.h>

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
    static_cast<std::string*>(userp)->append(static_cast<char*>(contents), size * nmemb);
    return size*nmemb;
}


void curl_test()
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL* curl =  curl_easy_init();
    
    std::string read_buffer;
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}


int main()
{
    for (int t = 0; t < 10; ++t)
    {
        const int nr_threads = 10000;
        std::vector<std::thread> threads(nr_threads);
        for (int i = 0; i < nr_threads; ++i)
        {
            threads[i] = std::thread(curl_test);
        }

        for (auto& thread: threads)
        {
            thread.join();
        }
    }
}
