#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <stdexcept>
#include "Webpage.h"
using namespace std;

class BrowserHistory {
public:
	BrowserHistory();

	void visitSite(Webpage newSite);
	string back();
	string forward();

	void readHistory(string fileName);

	string getUrl();
	size_t getNavSize();
	list<Webpage> getSitesVisited();

private:
	list<Webpage> navHistory;
	list<Webpage>::iterator navPos;
	list<Webpage> sitesVisited;
	int numSites;
};

void BrowserHistory::readHistory(string fileName) {
	string temp;
	int newTime;
	Webpage newSite;
	ifstream inFile(fileName.c_str());

	while (inFile >> temp) {
		if (temp == "new") {
			inFile >> temp >> newTime;
			newSite = Webpage(temp, time_t(newTime));
			visitSite(newSite);
		}
		else if (temp == "back") {
			back();
		}
		else if (temp == "forward") {
			forward();
		}
		else {
			throw logic_error("invalid command");
		}
	}
}

BrowserHistory::BrowserHistory(){
	navHistory = {};
	navPos = {};
	sitesVisited = {};
	numSites = 0;
}

void BrowserHistory::visitSite(Webpage newsite) {
	sitesVisited.push_back(newsite);	
	if ( numSites == 0) {
		navPos = navHistory.begin();
	}
	else if ( navPos != navHistory.end()){
		list<Webpage>::iterator itr;
		itr = navPos;
		navHistory.erase(++itr, navHistory.end());
	}
	navHistory.push_back(newsite);
	++navPos;
	++numSites;
}

string BrowserHistory::back() {
	if (navPos != navHistory.begin()) {
		--numSites;
		--navPos;
	}
	else throw invalid_argument("You cannot go back");
	return navPos->getUrl();
}
string BrowserHistory::forward() {
	if (navPos != --navHistory.end()){
		++numSites;
		++navPos;
	}		
	else throw invalid_argument("You cannot go forward");
	return navPos->getUrl();

}

 string BrowserHistory::getUrl(){
	 if (numSites == 0) {
		 throw invalid_argument("You have not visited any sites");
	 }
	return navPos->getUrl();
}

size_t BrowserHistory::getNavSize(){
	return ++numSites;
}

list<Webpage> BrowserHistory::getSitesVisited() {
	return sitesVisited;
}






