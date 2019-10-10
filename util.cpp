#include <string>
#include <cctype>
#include "util.h"
#include <algorithm>
#include <set>
#include "tweet.h"
#include "hsort.h"

using namespace std;

void convLower(string& s)
{
  for(unsigned int i=0; i < s.size(); i++){
    s[i] = tolower(s[i]);
  }
}

void convUpper(string& s)
{
  for(unsigned int i=0; i < s.size(); i++){
    s[i] = toupper(s[i]);
  }
}

void displayHits(vector<Tweet*>& hits)
{
  if(hits.size() > 0){
    hsort(hits, TweetComp());
    //sort(hits.begin(), hits.end(), TweetComp());
    cout << hits.size() << " matches:" << endl;
    for(vector<Tweet*>::iterator it = hits.begin(); it != hits.end(); ++it){
      cout << (**it) << endl;
    }
  }
  else {
    cout << "No matches." << endl;
  }
}

set<Tweet*> operator&(const set<Tweet*>& s1, const set<Tweet*>& s2){
  set<Tweet*> intersection;
  for (set<Tweet*>::iterator it= s1.begin(); it != s1.end(); ++it) {
    if (s2.find(*it) != s2.end()) {
      intersection.insert(*it);
    }
  }
  return intersection;
}

// Computes the union of s1 and s2
set<Tweet*> operator|(const set<Tweet*>& s1, const set<Tweet*>& s2) {
  set<Tweet*> onion; 
  for(set<Tweet*>::iterator it= s1.begin(); it != s1.end(); ++it) {
    onion.insert(*it);
  }
  for (set<Tweet*>::iterator jt= s2.begin(); jt != s2.end(); ++jt ) {
    if (onion.find(*jt) == onion.end()) {
      onion.insert(*jt);
    }
  }
  return onion;
}