all: twitter

user.o: user.cpp user.h tweet.h util.h hsort.h
	g++ -g -Wall -c -std=c++11 user.cpp -o user.o

tweet.o: tweet.h tweet.cpp datetime.h util.h user.h
	g++ -g -Wall -c -std=c++11 tweet.cpp -o tweet.o

datetime.o: datetime.cpp datetime.h util.h
	g++ -g -Wall -c -std=c++11 datetime.cpp -o datetime.o

util.o: util.h util.cpp hsort.h
	g++ -g -Wall -c -std=c++11 util.cpp -o util.o

twiteng.o: twiteng.h twiteng.cpp tweet.h user.h util.h datetime.h
	g++ -g -Wall -c -std=c++11 twiteng.cpp -o twiteng.o

cmdhandler.o: cmdhandler.cpp cmdhandler.h util.h twiteng.h datetime.h
	g++ -g -Wall -c -std=c++11 cmdhandler.cpp -o cmdhandler.o

handler.o: handler.cpp handler.h 
	g++ -g -Wall -c -std=c++11 handler.cpp -o handler.o

twitter: twitter.cpp twiteng.o util.o datetime.o tweet.o user.o cmdhandler.o handler.o 
	g++ -g -Wall -std=c++11 $^ -o twitter
