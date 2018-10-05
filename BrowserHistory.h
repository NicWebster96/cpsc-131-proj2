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

BrowserHistory::BrowserHistory(){         //initliazes all to null
	navHistory = {};
	navPos = {};
	sitesVisited = {};
	numSites = 0;
}

void BrowserHistory::visitSite(Webpage newsite) {   
	sitesVisited.push_back(newsite);	//pushes back because sitesVisited contains all sites
	if ( numSites == 0) {                 //checks to see if empty to set iterator to the beginning 
		navPos = navHistory.begin();
	}											 // when make a newsite and not at end and there are sites after we erase them
	else if ( navPos != --navHistory.end()){     //else if not at the last element we make a new iterator that holds our current position 
		list<Webpage>::iterator itr;             //then increments it and erases the temp iterator and the last element
		itr = navPos;
		itr++;
		navHistory.erase(itr, navHistory.end());
	}
	navHistory.push_back(newsite);          //pushes newsite onto NavHistory
	++navPos;								//increments our iterator position
	++numSites;								//increments the number of Sites
}

string BrowserHistory::back() {             //allows our iterator to move backwards in the list 
	if (navPos != navHistory.begin()) {     //decrements them 
		--numSites;                         //checks to see if at beginning because we can't move back if already at beginning
		--navPos;  
	}
	else throw invalid_argument("You cannot go back");  
	return navPos->getUrl();
}
string BrowserHistory::forward() {          //moves iterator forward, checks to see if at end because can't move forward if at end
	if (navPos != --navHistory.end()){
		++numSites;
		++navPos;
	}		
	else throw invalid_argument("You cannot go forward");
	return navPos->getUrl();

}

 string BrowserHistory::getUrl(){                      //checks to see if we have visited any Sites, returns getUrl
	 if (numSites == 0) {
		 throw invalid_argument("You have not visited any sites");
	 }
	return navPos->getUrl();
}

size_t BrowserHistory::getNavSize(){            //returns the size of Nav History
	return navHistory.size();
}

list<Webpage> BrowserHistory::getSitesVisited() {       //returns the total number of sitesvisited
	return sitesVisited;
}






