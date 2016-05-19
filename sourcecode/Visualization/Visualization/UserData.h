#ifndef USERDATA_H
#define USERDATA_H
#include <string>
#include <vector>
static std::string movie_type[14] = {"STORY","LOVE","COMEDY","CRIME","ADVENTURE","FANTASY","ACTION","CARTOON","SUSPENSE","FAMILY","SCARY","SCI-FI","WAR","OTHERS"}; 
static std::string movie_region[10] = {"AMERICA","BRITISH", "FRANCE", "JAPAN", "HK", "GERMANY", "MAINLAND CHINA", "ITALY", "KOREA", "OTHERS"};
static std::string movie_year[9] = {"1930s", "1940s", "1950s", "1960s", "1970s", "1980s", "1990s", "2000s", "2010s"};

class MovieData {
public:
	std::string name;
	int rank;
	int id;
	float score;
	int year;
	int region;
	std::vector<int> type;
	MovieData(){
		type.clear();
	}
	~MovieData(){
		type.clear();
	}
};


class UserData {
public:
	std::string id;
	std::string name;
	//std::vector<int> movie_seen;
	//std::vector<int> movie_interested;
	int movie_seen;
	int movie_interested;
	int movie_comments;
	int top250_seen;

	//comment
	std::vector<std::string> comments;
	std::vector<int> ranks;
	std::vector<int> score;
	std::vector<std::string> title;
	std::vector<int> words_num;
	std::vector<char> character; 
	float average_words_conut;

	UserData(){
		comments.clear();
		ranks.clear();
		score.clear();
		title.clear();
		words_num.clear();
		character.clear();
		average_words_conut = 0;
	}

};
#endif