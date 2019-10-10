#include "cmdhandler.h"
#include "util.h"
#include "datetime.h"
#include "twiteng.h"
#include <fstream>
using namespace std;

QuitHandler::QuitHandler()
: Handler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}

AndHandler::AndHandler() 
: Handler()
{

}
//intitalize using colon
AndHandler::AndHandler(Handler* next) 
: Handler(next) 
{

}
//just see if user typed and
bool AndHandler::canHandle(const string& cmd) const {
	return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, istream& instr) const{
	vector<string> terms;
	string input;
	//reads in hashtag terms
	while (instr>> input) {
		convUpper(input);
		terms.push_back(input);
	}
	//finds matches of intersection
	vector<Tweet*> matches;
	matches=eng->search(terms, 0);
	//output it
	displayHits(matches);

	return HANDLER_OK;

}

OrHandler::OrHandler() 
: Handler()
{

}

OrHandler::OrHandler(Handler* next) 
: Handler(next)
{

}
//same as and but for or
bool OrHandler::canHandle(const string& cmd) const {
	return cmd == "OR";
}
//same but for union
Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, istream& instr) const{
	vector<string> terms;
	string input;
	while (instr>> input) {
		convUpper(input);
		terms.push_back(input);
	}
	vector<Tweet*> matches;
	matches=eng->search(terms, 1);

	displayHits(matches);

	return HANDLER_OK;
}

TweetHandler::TweetHandler() 
: Handler()
{

}

TweetHandler::TweetHandler(Handler*next) 
: Handler(next)
{

}

bool TweetHandler::canHandle(const string& cmd) const {
	return cmd == "TWEET";
}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const {
	string name;
	string text;
	//put the user of tweet in variable
	instr >> name;
	if (instr.fail()) {
		return HANDLER_ERROR;
	}
	//gets content of tweet
	getline(instr, text);
	if (instr.fail()) {
		return HANDLER_ERROR;
	}
	//time based on current time
	time_t rawtime;
 	struct tm * timeinfo;
  	time (&rawtime);
  	timeinfo = localtime(&rawtime);
	DateTime date(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, timeinfo->tm_year+1900,
		timeinfo->tm_mon +1, timeinfo->tm_mday);
	//insert the tweet into database
	eng->addTweet(name, date, text);
	return HANDLER_OK;
}

FollowHandler::FollowHandler() 
: Handler()
{

}

FollowHandler::FollowHandler(Handler* next) 
: Handler(next)
{

}

bool FollowHandler::canHandle(const string& cmd) const {
	return cmd == "FOLLOW";
}

Handler::HANDLER_STATUS_T FollowHandler::process(TwitEng* eng, std::istream& instr) const {
	string follower;
	string following;
	instr >> follower;
	if (instr.fail()) {
		return HANDLER_ERROR;
	}
	instr >> following;
	if (instr.fail()) {
		return HANDLER_ERROR;
	}
	
	eng->addFollowing(follower, following);

	return HANDLER_OK;
}

SaveHandler::SaveHandler() 
: Handler()
{

}

SaveHandler::SaveHandler(Handler* next) 
: Handler(next)
{

}

bool SaveHandler::canHandle(const string& cmd) const {
	return cmd == "SAVE";
}

Handler::HANDLER_STATUS_T SaveHandler::process(TwitEng* eng, std::istream& instr) const {
	string filename;
	instr >> filename;
	if (instr.fail()) {
		return HANDLER_ERROR;
	}

	eng->saveFile(filename);

	return HANDLER_OK;


	
}

