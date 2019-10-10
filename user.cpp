#include "user.h"
#include <iostream>
#include "tweet.h"
#include "util.h"
#include <sstream>
#include "hsort.h"

using namespace std;

User::User(string name) 
  : name_(name)
{

}

User::~User() {
	 myTweets_.clear();
}
//setters and getters
string User::name() const {
	return name_;
}

set<User*> User::followers() const {
	return followers_;
}

set<User*> User::following() const {
	return following_;
}

list<Tweet*> User::tweets() const {
	return myTweets_;
}

void User::addFollower(User* u) {
	followers_.insert(u);
}

void User::addFollowing(User* u) {
	following_.insert(u);
}

void User::addTweet(Tweet* t) {
	myTweets_.push_back(t);
}

vector<Tweet*> User::getFeed() {
	vector<Tweet*> userFeed;
	//gets all tweets of this user
	for (list<Tweet*>::iterator kt= myTweets_.begin(); kt != myTweets_.end(); ++kt) {
		userFeed.push_back(*kt);
	}
	//gets all tweets of users that this is following
	for (set<User*>::iterator it= following_.begin(); it != following_.end(); ++it) {
		list<Tweet*> temp= (*it)->tweets();
		for (list<Tweet*>::iterator jt= temp.begin(); jt!= temp.end(); ++jt) {
			string temp1= (*jt)->text();
			//dont wanna put in main feed if it starts with @
			if (temp1[0] != '@') {
				userFeed.push_back(*jt);
			}
			else {
				stringstream ss(temp1);
				string temp2;
				ss >> temp2;
				if (temp2.substr(1) == this->name_ ) {
					userFeed.push_back(*jt);
				}
			}	
		}
	}
	//sort tweets by time
	hsort(userFeed, TweetComp());
	//sort(userFeed.begin(), userFeed.end(), TweetComp());
	return userFeed;
}


void User::addMentions(Tweet* t) {
	mentions.insert(t);
}

vector<Tweet*> User::getMentions() {
	vector<Tweet*> userMentions;
	//gets all the mentions of that user
	for(set<Tweet*>::iterator it= mentions.begin(); it != mentions.end(); ++it) {
		stringstream ss((*it)->text());
		string temp;
		ss >> temp;
		if (temp[0] == '@') {
			if (temp.substr(1) == this->name_) {
				userMentions.push_back(*it);
			}
		}
		else {
			userMentions.push_back(*it);
		}

	}
	hsort(userMentions, TweetComp());
	//sort(userMentions.begin(), userMentions.end(), TweetComp() );
	return userMentions;
}
