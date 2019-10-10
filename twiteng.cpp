#include <map>
#include <string>
#include <cstring>
#include <set>
#include <vector>
#include "twiteng.h"
#include <sstream>
#include <fstream>
#include "tweet.h"
#include "util.h"
#include <iostream>
#include <iomanip>
#include "user.h"

using namespace std;

TwitEng::TwitEng () {

}
TwitEng::~TwitEng() {
	//deletes all the tweets of each user first, then deletes that user
	map<string, User*>::iterator it= users_.begin();
	for (; it != users_.end(); ++it) {
		list<Tweet*> temp= it->second->tweets();
		for (list<Tweet*>::iterator jt= temp.begin(); jt != temp.end(); ++jt) {
			delete *jt;
		}
		delete it->second;
	}
}

bool TwitEng::parse(char* filename) {
	string buffer1;
	string buffer2;
	string temp1;
	string temp2;
	set<string> names;
	//opens input file
	ifstream ifile(filename);
	if (ifile.fail()) {
		return true;
	}
	ifile >> userCount;

	if(ifile.fail()) {
		return true;
	}
	//gets rest of first line
	getline(ifile, buffer1);
	for (int i=0; i< userCount; i++) {
		//gets line for each user
		getline(ifile, buffer1);
		stringstream ss(buffer1);
		ss >> temp1;
		if (ss.fail()) {
			return true;
		}
		//puts user in map only if not already added
		if ( users_.find(temp1) == users_.end() ) {
			User* guy= new User(temp1);
			users_.insert(pair<string,User*>(temp1, guy ) );
		}
		//puts each following in appropiate database
		while (ss >> temp2 ) {
			//brand new user
			if (users_.find(temp2)== users_.end()) {
				User* following_= new User(temp2);
			
				map<string,User*>::iterator it= users_.find(temp1);
				if (temp1 != following_->name()) {
					it->second->addFollowing(following_);
					following_->addFollower(it->second); //
					users_.insert(pair<string,User*>(temp2,following_));
				}
			}
			//if user is already in map
			else {
				map<string,User*>::iterator jt= users_.find(temp1);
				map<string,User*>::iterator kt= users_.find(temp2);
				jt->second->addFollowing(kt->second);
				kt->second->addFollower(jt->second);
			}

		}
		ss.clear();
	}
	//first tweet outside while loop to reach eof correctly
	string currentName;
	DateTime time_;

	ifile >> time_;
	ifile >> currentName;
	getline(ifile, buffer2);
	//only put the tweet in if its legit
	while (!ifile.fail()) {
		if (currentName != "") {
			trim(buffer2);
			addTweet(currentName, time_, buffer2);
		}
		//retreive info for next line
		ifile >> time_;
		ifile >> currentName;
		getline(ifile, buffer2);
	}
	ifile.close();
	return false;
}

void TwitEng::addTweet(const string& username, const DateTime& time, const std::string& text) {
	//dynamically allocate for new tweet
	if (users_.find(username) == users_.end()) {
		return;
	}
	Tweet* twit= new Tweet(users_[username], time, text);
	set<Tweet*> temp;
	temp.insert(twit);
	map<string,User*>::iterator it= users_.find(username);
	//adds tweet into correct user's database
	
	it->second->addTweet(twit);
	set<string> currentHash= twit->hashTags();
	set<string> currentMentions= twit->mentions();
	//this is for the second map of hashtags for searching later
	for (set<string>::iterator jt= currentHash.begin(); jt!= currentHash.end(); ++jt) {
		map<string,set<Tweet*>>::iterator kt=hashtags.find(*jt);
		if (kt == hashtags.end()) {
			hashtags.insert(pair<string, set<Tweet*>> (*jt, temp));
		}
		else {
			kt->second.insert(twit);
		}
	}

	for(set<string>::iterator lt= currentMentions.begin(); lt!= currentMentions.end(); ++lt) {
		std::map<std::string,User*>::iterator mt= users_.find(*lt);
		mt->second->addMentions(twit);
	}
}

vector<Tweet*> TwitEng::search(vector<string>& terms, int strategy) {
	vector<Tweet*> matches;
	//intersection (and)
	if (terms.size() == 0) {
		return matches;
	}
	if (strategy== 0) {
		set<Tweet*> intersection;
		convUpper(terms[0]);
		intersection= hashtags[terms[0]];
		for (unsigned int i=1; i < terms.size(); i++) {
			//gets repeated intersection for each new term
			convUpper(terms[i]);
			intersection= hashtags[terms[i]] & intersection;
		}
		//puts it all in a vector to work with
		for (set<Tweet*>::iterator jt= intersection.begin();
			jt != intersection.end(); ++jt) {
			matches.push_back(*jt);
		}
		return matches;
	}
	else  {
		//same as above but for union
		set<Tweet*> union_;
		convUpper(terms[0]);
		union_= hashtags[terms[0]];
		for (unsigned int i=0; i < terms.size(); i++) {
			convUpper(terms[i]);
			union_= hashtags[terms[i]] | union_;		 
		} 
		for (set<Tweet*>::iterator it= union_.begin();
			it != union_.end(); ++it) {
			 
				matches.push_back(*it);
		}
		return matches;
	}

}

void TwitEng::dumpFeeds() {
	for (map<string,User*>::iterator it= users_.begin(); 
		it != users_.end(); ++it ) {
		//makes a file for each user
		vector<Tweet*> feed;
		string filename= it->first+ ".feed";
		ofstream ofile(filename);
		//outputs name
		ofile << it->first << endl;
		//gets feed
		feed= it->second->getFeed();
		//outputs feed
		for (unsigned int i=0; i < feed.size(); i++) {
			ofile << *(feed[i]) << endl;
		}

	}
	dumpMentions();
}

void TwitEng::dumpMentions() {
	for (map<string,User*>::iterator it= users_.begin(); 
		it != users_.end(); ++it ) {

		vector<Tweet*> mentionFeed;
		string filename= it->first+ ".mentions";
		ofstream ofile(filename);
		//outputs name
		ofile << it->first << endl;
		mentionFeed= it->second->getMentions();
	
		//outputs appropiate mentions
		for (unsigned int i=0; i < mentionFeed.size(); i++) {
			ofile << *(mentionFeed[i]) << endl;
		}
	}
}


void TwitEng::addFollowing(std::string follower, std::string following) {
	//adds follower and following on both ends
	map<string, User*>::iterator it= users_.find(follower);
	if (it != users_.end()) {
		map<string, User*>::iterator jt= users_.find(following);
		if (jt != users_.end()) {
			it->second->addFollowing(jt->second);
			jt->second->addFollower(it->second);
		}
	
	}
}

void TwitEng::saveFile(const string filename) {
	ofstream ofile(filename);

	int count=0;
	for (map<std::string,User*>::iterator it= users_.begin(); 
		it != users_.end(); ++it) {
		++count;
	}
	//output file resembles input data files
	ofile << count << endl;
	for (map<std::string,User*>::iterator it= users_.begin(); 
		it != users_.end(); ++it) {
		ofile << it->first << ' ';
		set<User*> temp = it->second->following();
		for (set<User*>::iterator jt = temp.begin(); jt != temp.end();
			++jt) {
			ofile << (*jt)->name() << ' ';
		}
		ofile << endl;
	}

	for (map<std::string,User*>::iterator kt= users_.begin(); 
		kt != users_.end(); ++kt) {
		list<Tweet*> temp2 = kt->second->tweets();
		for (list<Tweet*>::iterator lt= temp2.begin(); lt != temp2.end();
			++lt) {
			ofile << (**lt) << endl;
		}

	}
	ofile.close();

}