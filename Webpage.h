#pragma once

#include <string>
using namespace std;

class Webpage {
public:
	Webpage();
	Webpage(const string& webpageUrl, const time_t& timeVisited);

	string getUrl();
	time_t getTime();

private:
	string url;
	time_t time;
	
};

Webpage::Webpage() {          //initializes url and time to 0
	url = "";
	time = 0;
}

Webpage::Webpage(const string& webpageUrl, const time_t& timeVisited) {    //sets url and time to be accessed
	url = webpageUrl;
	time = timeVisited;
}

string Webpage::getUrl() {      //returns a string that is url
	return url;
}
time_t Webpage::getTime() {    //returns the time when the site was visited
	return time;
}
