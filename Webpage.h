#pragma once

#include <string>
using namespace std;

class Webpage {
public:
    Webpage(){
    url = "";
    time = 0;
    }

    Webpage(const string& webpageUrl, const time_t& timeVisited){
	url = webpageUrl;
	time = timeVisited;
    }

    string getUrl(){
	return url;
    }
    time_t getTime(){
	return time;
    }

private:
    string url;
    time_t time;
};
