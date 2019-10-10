#include "tweet.h"
#include <iostream> 
#include <sstream>
#include <set>
#include "user.h"
#include "util.h"

using namespace std;
//output components of a tweet
ostream& operator<<(ostream& os, const Tweet& t) {
	os << t.time_ << ' ' << t.user_->name() << ' ' << t.content_;
	return os;
}



Tweet::Tweet() 
: time_(), content_("")
{

}
//construct using colon
Tweet::Tweet(User* user, const DateTime& time, const std::string& text) 
: time_(time), content_(text)
{
	user_=user;
}
//getters
DateTime const & Tweet::time() const {
	return time_;
}

string const & Tweet::text() const {
	return content_;
}

User* Tweet::user() const {
	return user_;
}

set<string> Tweet::hashTags() const {
	set<string> hashtags_;
	stringstream ss(content_);
	string temp;
	//reads content word by word to identify hashtags then enters them into database
	while (ss >> temp) {
		if(temp[0]== '#') {
			string hash=temp.substr(1);
			convUpper(hash);
			hashtags_.insert(hash);
		}
	}
	return hashtags_;
}
//refer to datetime <operator
bool Tweet::operator<(const Tweet& other) const {
	return time_< other.time_;
}

set<string> Tweet::mentions() const {
	set<string> mentions;
	stringstream ss(content_);
	string temp;

	while (ss>> temp) {
		if(temp[0]== '@') {
			string ment= temp.substr(1);
			mentions.insert(ment);
		}
	}
	return mentions;
}
