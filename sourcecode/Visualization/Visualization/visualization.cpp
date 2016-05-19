#include "visualization.h"
#include <QtWebKitWidgets>
#include <Qdir>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
static std::string colors[] = {"#3366cc", "#dc3912", "#ff9900", "#109618", "#990099", "#0099c6", "#dd4477", 
		                    "#66aa00", "#b82e2e", "#316395", "#994499", "#22aa99", "#aaaa11", "#6633cc", 
							"#e67300", "#8b0707", "#651067", "#329262", "#5574a6", "#3b3eac", "#bca44a"};
Visualization::Visualization(QWidget *parent)
	: QMainWindow(parent), nodes_num(0), neighbor_num(5), pie_type(0), user_selected(0), main_user(0), main_user_recommend(true), index_selected(0), first(true)
{
	ui.setupUi(this);
	colorbar = ui.widget_ColorBar;
	
	movie_data.clear();
	user_data.clear();
	user_distance.clear();
	forceGraphNodes.clear();
	forceGraphLinks.clear();

	readData();
	initUserDistance();
	generateForceGraphData();
	record_neighbor_index.clear();

	//QWebSettings::setObjectCacheCapacities(2048, 2048 , 16 * 1024);
	//userRelation
	ui.webView_UserRelation->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
	ui.webView_UserRelation->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
	ui.webView_UserRelation->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
	connect(ui.webView_UserRelation->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared ()),
            this, SLOT(initUserRelationJS()));
	ui.webView_UserRelation->load("file:///" + QDir::currentPath() + "/D3/force_direct_graph.html");
	//ui.webView_UserRelation->load("file:///" + QDir::currentPath() + "/project/index.html");

	//single user
	ui.webView_SMT->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
	ui.webView_SMT->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
	ui.webView_SMT->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
	connect(ui.webView_SMT->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared ()),
            this, SLOT(initUserSMTJS()));
	ui.webView_SMT->load("file:///" + QDir::currentPath() + "/D3/MST.html");


	//treemap
	ui.webView_TreeMap->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
	ui.webView_TreeMap->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
	ui.webView_TreeMap->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
	connect(ui.webView_TreeMap->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared ()),
            this, SLOT(initUserTreeMapJS()));
	ui.webView_TreeMap->load("file:///" + QDir::currentPath() + "/D3/treeMap.html");

	//test
	//connect(ui.pushButton_LoadData, SIGNAL(clicked()), this, SLOT(setUserSMTData()));
	connect(ui.pushButton_LoadData, SIGNAL(clicked()), this, SLOT(slotSetForceGraphData()));

	//moive type pie
	ui.webView_PieMovieType->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
	ui.webView_PieMovieType->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
	ui.webView_PieMovieType->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
	connect(ui.webView_PieMovieType->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared ()),
            this, SLOT(initUserMoiveType()));
	ui.webView_PieMovieType->load("file:///" + QDir::currentPath() + "/D3/pie_movie_type.html");

	//chord
	ui.webView_Chord->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
	ui.webView_Chord->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
	ui.webView_Chord->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
	connect(ui.webView_Chord->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared ()),
            this, SLOT(initChord()));
	ui.webView_Chord->load("file:///" + QDir::currentPath() + "/D3/chord.html");

	//recommend
	ui.webView_Recommend->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
	ui.webView_Recommend->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
	ui.webView_Recommend->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
	connect(ui.webView_Recommend->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared ()),
            this, SLOT(initRecommend()));
	ui.webView_Recommend->load("file:///" + QDir::currentPath() + "/D3/recommend.html");


	connect(ui.comboBox_MoviePie, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRepaintPie()));
	QString movie_pie_type[] = {"TYPE", "REGION", "YEARS"};
	for(int i = 0; i < 3; i++)
		ui.comboBox_MoviePie->addItem(movie_pie_type[i]);

	//connect(ui.spinBox_NeighborNum, SIGNAL(valueChanged(int)), this, SLOT(slotSetNeighborNumValue(int)));
	connect(ui.pushButton_SetNeighborNum, SIGNAL(clicked()), this, SLOT(slotSetNeighborNumValue()));

	connect(ui.listWidget_Users, SIGNAL(itemSelectionChanged()), this, SLOT(slotListWidgetSelectChanged()));
	
}

Visualization::~Visualization()
{

}

void Visualization::initUserRelationJS(){
	ui.webView_UserRelation->page()->mainFrame()->addToJavaScriptWindowObject("QJSCall", this);
}
void Visualization::initUserSMTJS(){
	ui.webView_SMT->page()->mainFrame()->addToJavaScriptWindowObject("QJSCall", this);
}
void Visualization::initUserMoiveType(){
	ui.webView_PieMovieType->page()->mainFrame()->addToJavaScriptWindowObject("QJSCall", this);
}

void Visualization::initUserTreeMapJS(){
	ui.webView_TreeMap->page()->mainFrame()->addToJavaScriptWindowObject("QJSCall", this);
}

void Visualization::initChord(){
	ui.webView_Chord->page()->mainFrame()->addToJavaScriptWindowObject("QJSCall", this);
}

void Visualization::initRecommend(){
	ui.webView_Recommend->page()->mainFrame()->addToJavaScriptWindowObject("QJSCall", this);
}

void Visualization::showUserMovie(int id){
	//ui.scrollArea_Movie;
	ui.listWidget_Movie->clear();
	//QTextCodec *codec = QTextCodec::codecForName("GB2312");//ªÚ’ﬂ «GB18030

	for(int i = 0; i < user_data[id]->ranks.size(); i++){
		QString name = QString::fromLocal8Bit(movie_data[user_data[id]->ranks[i] - 1]->name.c_str());
		ui.listWidget_Movie->addItem(name);
	}
}

void Visualization::showMoveType(int id){
	int movieType[14] = {0};
	int movieRegion[10] = {0};
	int movieYear[9] = {0};

	for(int i = 0; i < user_data[id]->ranks.size(); i++){
		int movie_id = user_data[id]->ranks[i] - 1;

		for(int i = 0; i < movie_data[movie_id]->type.size(); i++)
			movieType[movie_data[movie_id]->type[i]]++;

		//for(int i = 0; i < movie_data[movie_id]->region.size(); i++)
		movieRegion[movie_data[movie_id]->region]++;

		//year
		if(movie_data[movie_id]->year < 1940){
			movieYear[0]++;
		}
		else if(movie_data[movie_id]->year < 1950){
			movieYear[1]++;
		}
		else if(movie_data[movie_id]->year < 1960){
			movieYear[2]++;
		}
		else if(movie_data[movie_id]->year < 1970){
			movieYear[3]++;
		}
		else if(movie_data[movie_id]->year < 1980){
			movieYear[4]++;
		}
		else if(movie_data[movie_id]->year < 1990){
			movieYear[5]++;
		}
		else if(movie_data[movie_id]->year < 2000){
			movieYear[6]++;
		}
		else if(movie_data[movie_id]->year < 2010){
			movieYear[7]++;
		}
		else{
			movieYear[8]++;
		}

	}
	//generate data
	//std::string colors[] = {"#2484c1", "#0c6197", "#4daa4b", "#90c469", "#daca61", "#e4a14b", "#e98125",
	//                        "#cb2121", "#830909", "#923e99", "#ae83d5", "#bf273e", "#ce2aeb", "#bca44a"};
	//std::string colors[] = {"##3366cc", "#dc3912", "#ff9900", "#109618", "#990099", "#0099c6", "#dd4477",
	//                         "#66aa00", "#b82e2e", "#316395", "#994499", "#22aa99", "#aaaa11", "#6633cc"};

	std::string data_content = "";
	std::string type;
	if(pie_type == 0){
		type = "0";
		data_content += "[\n";
		for(int i = 0; i < 14; i++){
			char type[15] = {0};
			itoa(movieType[i], type, 10);
			data_content += "{\n\"label\":\"" + movie_type[i] + "\",\n" + "\"value\":" + type + ",\n" + "\"color\":\"" + colors[i] + "\"\n}";
			if(i < 13)
				data_content += ",\n";
		}
		data_content += "\n]";
	}
	else if(pie_type == 1){
		type = "1";
		data_content += "[\n";
		for(int i = 0; i < 10; i++){
			char region[15] = {0};
			itoa(movieRegion[i], region, 10);
			data_content += "{\n\"label\":\"" + movie_region[i] + "\",\n" + "\"value\":" + region + ",\n" + "\"color\":\"" + colors[i] + "\"\n}";
			if(i < 9)
				data_content += ",\n";
		}
		data_content += "\n]";
	}
	else{
		type = "2";
		data_content += "[\n";
		for(int i = 0; i < 9; i++){
			char year[15] = {0};
			itoa(movieYear[i], year, 10);
			data_content += "{\n\"label\":\"" + movie_year[i] + "\",\n" + "\"value\":" + year + ",\n" + "\"color\":\"" + colors[i] + "\"\n}";
			if(i < 8)
				data_content += ",\n";
		}
		data_content += "\n]";
	}
	std::string javaScript = "showpie(" + type + "," + data_content +");";
	ui.webView_PieMovieType->page()->mainFrame()->evaluateJavaScript(QString::fromStdString(javaScript));
}

void Visualization::showTreeMap(int id){
	if(pie_type == 0){
		showTreeMapType(id);
	}

	else if(pie_type == 1){
		showTreeMapRegion(id);	
	}

	else{
		showTreeMapYear(id);	
	}
}

void Visualization::showTreeMapType(int id){
	std::vector<int> record[14];
	for(int i = 0; i < 14; i++)
		record[i].clear();
	int repeat[250] = {0};

	for(int i = 0; i < user_data[id]->ranks.size(); i++){
		int movie_id = user_data[id]->ranks[i] - 1;

		for(int j = 0; j < movie_data[movie_id]->type.size(); j++){
			record[movie_data[movie_id]->type[j]].push_back(movie_id);
		}
		if(movie_data[movie_id]->type.size() > 1)
			repeat[movie_id]++;
	}

	std::string data_content = "\n";
	data_content += "{\n\"name\":\"" + user_data[id]->id + " has seen those movies\",\n";
	data_content += "\"children\":[\n";
	for(int i = 0; i < 14; i++){
		//if(record[i].size() == 0)
		//	continue;
		data_content += "{\n\"name\":\""  + movie_type[i] + "\",\n"
					  + "\"children\": [\n";

		for(int j = 0; j < record[i].size(); j++){
			if(j < record[i].size() - 1){
				if(record[i][j + 1] == record[i][j])
					continue;
			}
			std::string name = movie_data[record[i][j]]->name;
			if(repeat[record[i][j]] > 0)
				name += " (" + movie_type[i] + ")";
			data_content += "{\"name\":\"" + name + """\",\"size\":1},\n";
		}
		data_content += "]\n}";
		if(i < 13)
			data_content += ",\n";
	}
		data_content += "\n]\n}";
	std::string javaScript = "switchData(" + data_content +");";
	ui.webView_TreeMap->page()->mainFrame()->evaluateJavaScript(QString::fromLocal8Bit(javaScript.c_str()));
}

void Visualization::showTreeMapRegion(int id){
	std::vector<int> record[10];
	for(int i = 0; i < 10; i++)
		record[i].clear();

	for(int i = 0; i < user_data[id]->ranks.size(); i++){
		int movie_id = user_data[id]->ranks[i] - 1;
		record[movie_data[movie_id]->region].push_back(movie_id);

	}

	std::string data_content = "\n";
	data_content += "{\n\"name\":\"" + user_data[id]->id + " has seen those movies\",\n";
	data_content += "\"children\":[\n";
	for(int i = 0; i < 10; i++){
		//if(record[i].size() == 0)
		//	continue;
		data_content += "{\n\"name\":\""  + movie_region[i] + "\",\n"
					  + "\"children\": [\n";

		for(int j = 0; j < record[i].size(); j++){
			if(j < record[i].size() - 1){
				if(record[i][j + 1] == record[i][j])
					continue;
			}
			std::string name = movie_data[record[i][j]]->name;
			data_content += "{\"name\":\"" + name + "\",\"size\":1},\n";
		}
		data_content += "]\n}";
		if(i < 9)
			data_content += ",\n";
	}
		data_content += "\n]\n}";
	std::string javaScript = "switchData(" + data_content +");";
	ui.webView_TreeMap->page()->mainFrame()->evaluateJavaScript(QString::fromLocal8Bit(javaScript.c_str()));
}

void Visualization::showTreeMapYear(int id){
	std::vector<int> record[9];
	for(int i = 0; i < 9; i++)
		record[i].clear();

	for(int i = 0; i < user_data[id]->ranks.size(); i++){
		int movie_id = user_data[id]->ranks[i] - 1;
		if(movie_data[movie_id]->year < 1940){
			record[0].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 1950){
			record[1].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 1960){
			record[2].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 1970){
			record[3].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 1980){
			record[4].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 1990){
			record[5].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 2000){
			record[6].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 2010){
			record[7].push_back(movie_id);
		}
		else{
			record[8].push_back(movie_id);
		}

	}

	std::string data_content = "\n";
	data_content += "{\n\"name\":\"" + user_data[id]->id + " has seen those movies\",\n";
	data_content += "\"children\":[\n";
	for(int i = 0; i < 9; i++){
		//if(record[i].size() == 0)
		//	continue;
		data_content += "{\n\"name\":\""  + movie_year[i] + "\",\n"
					  + "\"children\": [\n";

		for(int j = 0; j < record[i].size(); j++){
			if(j < record[i].size() - 1){
				if(record[i][j + 1] == record[i][j])
					continue;
			}
			std::string name = movie_data[record[i][j]]->name;
			char y[20];
			itoa(movie_data[record[i][j]]->year, y, 10);
			data_content += "{\"name\":\"" + name + " (" + y + ")\",\"size\":1},\n";
		}
		data_content += "]\n}";
		if(i < 8)
			data_content += ",\n";
	}
		data_content += "\n]\n}";
	std::string javaScript = "switchData(" + data_content +");";
	ui.webView_TreeMap->page()->mainFrame()->evaluateJavaScript(QString::fromLocal8Bit(javaScript.c_str()));
}

void Visualization::showRecommendTreeMap(int id, std::vector<int> rank){
	if(pie_type == 0){
		showRecommendTreeMapType(id, rank);
	}

	else if(pie_type == 1){
		showRecommendTreeMapRegion(id, rank);	
	}

	else{
		showRecommendTreeMapYear(id, rank);	
	}
}

void Visualization::showRecommendTreeMapType(int id, std::vector<int> ranks){
	std::vector<int> record[14];
	for(int i = 0; i < 14; i++)
		record[i].clear();
	int repeat[250] = {0};

	for(int i = 0; i < ranks.size(); i++){
		if(ranks[i] < 0) 
			continue;
		int movie_id = ranks[i] - 1;

		for(int j = 0; j < movie_data[movie_id]->type.size(); j++){
			record[movie_data[movie_id]->type[j]].push_back(movie_id);
		}
		if(movie_data[movie_id]->type.size() > 1)
			repeat[movie_id]++;
	}

	std::string data_content = "\n";
	std::string name = user_data[id]->id;
	if(main_user_recommend)
		name = "all neighbors";
	data_content += "{\n\"name\":\" movies recommended from " + name + "\",\n";
	data_content += "\"children\":[\n";
	for(int i = 0; i < 14; i++){
		//if(record[i].size() == 0)
		//	continue;
		data_content += "{\n\"name\":\""  + movie_type[i] + "\",\n"
					  + "\"children\": [\n";

		for(int j = 0; j < record[i].size(); j++){
			if(j < record[i].size() - 1){
				if(record[i][j + 1] == record[i][j])
					continue;
			}
			std::string name = movie_data[record[i][j]]->name;
			if(repeat[record[i][j]] > 0)
				name += " (" + movie_type[i] + ")";
			data_content += "{\"name\":\"" + name + "\",\"size\":1},\n";
		}
		data_content += "]\n}";
		if(i < 13)
			data_content += ",\n";
	}
		data_content += "\n]\n}";
	std::string javaScript = "switchData(" + data_content +");";
	ui.webView_Recommend->page()->mainFrame()->evaluateJavaScript(QString::fromLocal8Bit(javaScript.c_str()));
}

void Visualization::showRecommendTreeMapRegion(int id, std::vector<int> ranks){
	std::vector<int> record[10];
	for(int i = 0; i < 10; i++)
		record[i].clear();

	for(int i = 0; i < ranks.size(); i++){
		if(ranks[i] < 0)
			continue;

		int movie_id = ranks[i] - 1;
		record[movie_data[movie_id]->region].push_back(movie_id);

	}

	std::string data_content = "\n";
	std::string name = user_data[id]->id;
	if(main_user_recommend)
		name = "all neighbors";
	data_content += "{\n\"name\":\" movies recommended from " + name + "\",\n";
	data_content += "\"children\":[\n";
	for(int i = 0; i < 10; i++){
		//if(record[i].size() == 0)
		//	continue;
		data_content += "{\n\"name\":\""  + movie_region[i] + "\",\n"
					  + "\"children\": [\n";

		for(int j = 0; j < record[i].size(); j++){
			if(j < record[i].size() - 1){
				if(record[i][j + 1] == record[i][j])
					continue;
			}
			std::string name = movie_data[record[i][j]]->name;
			data_content += "{\"name\":\"" + name + "\",\"size\":1},\n";
		}
		data_content += "]\n}";
		if(i < 9)
			data_content += ",\n";
	}
		data_content += "\n]\n}";
	std::string javaScript = "switchData(" + data_content +");";
	ui.webView_Recommend->page()->mainFrame()->evaluateJavaScript(QString::fromLocal8Bit(javaScript.c_str()));
}

void Visualization::showRecommendTreeMapYear(int id, std::vector<int> ranks){
	std::vector<int> record[9];
	for(int i = 0; i < 9; i++)
		record[i].clear();

	for(int i = 0; i < ranks.size(); i++){
		if(ranks[i] < 0)
			continue;
		int movie_id = ranks[i] - 1;
		if(movie_data[movie_id]->year < 1940){
			record[0].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 1950){
			record[1].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 1960){
			record[2].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 1970){
			record[3].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 1980){
			record[4].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 1990){
			record[5].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 2000){
			record[6].push_back(movie_id);
		}
		else if(movie_data[movie_id]->year < 2010){
			record[7].push_back(movie_id);
		}
		else{
			record[8].push_back(movie_id);
		}

	}

	std::string data_content = "\n";
	std::string name = user_data[id]->id;
	if(main_user_recommend)
		name = "all neighbors";
	data_content += "{\n\"name\":\" movies recommended from " + name + "\",\n";
	data_content += "\"children\":[\n";
	for(int i = 0; i < 9; i++){
		//if(record[i].size() == 0)
		//	continue;
		data_content += "{\n\"name\":\""  + movie_year[i] + "\",\n"
					  + "\"children\": [\n";

		for(int j = 0; j < record[i].size(); j++){
			if(j < record[i].size() - 1){
				if(record[i][j + 1] == record[i][j])
					continue;
			}
			std::string name = movie_data[record[i][j]]->name;
			char y[20];
			itoa(movie_data[record[i][j]]->year, y, 10);
			data_content += "{\"name\":\"" + name + " (" + y + ")\",\"size\":1},\n";
		}
		data_content += "]\n}";
		if(i < 8)
			data_content += ",\n";
	}
		data_content += "\n]\n}";
	std::string javaScript = "switchData(" + data_content +");";
	ui.webView_Recommend->page()->mainFrame()->evaluateJavaScript(QString::fromLocal8Bit(javaScript.c_str()));
}

void Visualization::showChord(int id){
	
}

void Visualization::showCharacter(int id){
	colorbar->startY = int(user_data[id]->average_words_conut / 400 * 450);
	colorbar->mHeight = 450 - colorbar->startY;
	colorbar->update();
}

void Visualization::UserRelationSelected(int id){
	user_selected = id;
	main_user = id;
	setUserSMTData(id);
	showMoveType(id);
	showTreeMap(id);
	showUserMovie(id);
	showChord(id);
	showRecommendMovie(0);
	showCharacter(id);
}

void Visualization::UserNeighborSelected(int id){
	user_selected = record_neighbor_index[id];
	//setUserSMTData(id);
	showMoveType(user_selected);
	showTreeMap(user_selected);
	showUserMovie(user_selected);
	showCharacter(id);
	//showRecommendMovie(id);
}
void Visualization::UserNeighborRecommend(int index){
	showRecommendMovie(index);
}
void Visualization::showRecommendMovie(int index){
	int id = record_neighbor_index[index];
	index_selected = index;
	
	std::vector<int> rank1, rank2;
	

	for(int i = 0; i < user_data[main_user]->ranks.size(); i++)
		rank2.push_back(user_data[main_user]->ranks[i]);


	if(index == 0){
		main_user_recommend = true;
		int rank_m[250] = {0};

		for(int i = 1; i < record_neighbor_index.size(); i++){
			int uid = record_neighbor_index[i];

			for(int j = 0; j < user_data[uid]->ranks.size(); j++){
				int movie_id = user_data[uid]->ranks[j] - 1;
				rank_m[movie_id]++;
			}	
		}
		for(int i = 0; i < rank2.size(); i++){
			int movie_rank = rank2[i] - 1;
			rank_m[movie_rank] = 0;
		}
		for(int i = 0; i < 250; i++){
			if(rank_m[i] > record_neighbor_index.size() / 2)
				rank1.push_back(i + 1);
		}
	}

	else{
		main_user_recommend = false;
		for(int i = 0; i < user_data[id]->ranks.size(); i++)
			rank1.push_back(user_data[id]->ranks[i]);

		for(int i  = 0; i < rank1.size(); i++){
			for(int j = 0; j < rank2.size(); j++){
				if(rank1[i] == rank2[j]){
					rank1[i] = -1;
					break;
				}
			}
		}
	}
	showRecommendTreeMap(id, rank1);
}

void Visualization::setUserSMTData(int id){
	std::vector<int> ids;
	std::vector<float> dis;
	ids.resize(nodes_num);
	dis.resize(nodes_num);
	for(int i = 0; i < nodes_num; i++){
		ids[i] = i;
		dis[i] = user_distance[id * user_data.size() + i];
	}

	for(int i = 0; i < nodes_num - 1; i++){
		for(int j = i + 1; j < nodes_num; j++){
			if(dis[i] < dis[j]){
				float tempdis = dis[j];
				dis[j] = dis[i];
				dis[i] = tempdis;

				int temp = ids[j];
				ids[j] = ids[i];
				ids[i] = temp;

			}
		}
	}

	std::string nodes = "[", links = "[";
	nodes += forceGraphNodes[id] + ",";
	for(int i = 0; i < neighbor_num ; i++){
		nodes += forceGraphNodes[ids[i]];
		if(i == neighbor_num - 1)
			nodes += "]";
		else
			nodes += ",";
	}
	//neighbor_num = ui.spinBox_NeighborNum->value();
	for(int i = 0; i < neighbor_num ; i++){
		//links += forceGraphLinks[id * user_data.size() + ids[i]];
		char t[10];
		itoa(i + 1, t, 10);
		char d[10];
		itoa(dis[i], d, 10);

		links += "{\"source\":0,\"target\":" + std::string(t) + ",\"value\":" + std::string(d) + "}";
		if(i == neighbor_num - 1)
			links += "]";
		else
			links += ",";
	}

	std::string javaScript = "open(" + nodes + "," + links + ");";
	ui.webView_SMT->page()->mainFrame()->evaluateJavaScript(QString::fromStdString(javaScript));

	//QString javaScript = "open(" + s1 + "," + s2 + ");";
	//ui.webView_SMT->page()->mainFrame()->evaluateJavaScript(javaScript);


	//chord	
	record_neighbor_index.clear();
	std::vector<int> cids;

	cids.push_back(id);
	for(int i = 0; i < neighbor_num; i++)
		cids.push_back(ids[i]);

	for(int i = 0; i < cids.size(); i++)
		record_neighbor_index.push_back(cids[i]);

	//compute matrix
	float m[100][100];
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 100; j++)
			m[i][j] = 0;
	}
	for(int i = 0; i < cids.size(); i++){
		for(int j = i; j < cids.size(); j++){
			if(j == i)
				m[i][j] = 0;
			else{
				int id1 = cids[i];
				int id2 = cids[j];
				int count = 0;
				for(int k = 0; k < user_data[id1]->ranks.size(); k++){
					for(int l = 0; l < user_data[id2]->ranks.size(); l++){
						if(user_data[id1]->ranks[k] == user_data[id2]->ranks[l])
							count++;
					}
				}
				m[i][j] = count;
				m[j][i] = count;
			}
		}
	}

	for(int i = 0; i < cids.size(); i++){
		for(int j = 0; j < cids.size(); j++){
			m[i][j] /= user_data[cids[i]]->ranks.size();
		}
	}

	std::string matrix = "[";
	for(int i = 0; i < cids.size(); i++){
		matrix += "\n[";
		for(int j = 0; j < cids.size(); j++){
			std::string cstr;
			std::stringstream stream;
			stream<<m[i][j];
			stream>>cstr;
			matrix += cstr;
			if(j < cids.size() - 1)
				matrix += ",";
		}
		matrix += "]";
		if(i < cids.size() - 1)
			matrix += ",";
	}
	matrix += "\n]";

	
	

	std::string users = "[";
	for(int i = 0; i < cids.size(); i++){
		users += "\n{\"name\":\"" + user_data[cids[i]]->id + "\",\"color\":\"" + colors[i] + "\"}";
		if(i < cids.size() - 1)
			users += ",";
	}
	users += "\n]";

	std::string javaScriptChord = "drawChord(" + matrix + "," + users + ");";
	ui.webView_Chord->page()->mainFrame()->evaluateJavaScript(QString::fromStdString(javaScriptChord));
}

void Visualization::slotSetForceGraphData(){
	nodes_num = ui.spinBox_DataNum->value();
	std::string nodes = "[", links = "[";
	for(int i = 0; i < nodes_num; i++){
		nodes += forceGraphNodes[i];
		if(i == nodes_num - 1)
			nodes += "]";
		else
			nodes += ",";
	}
	
	for(int i = 0; i < nodes_num - 1; i++){
		for(int j = i + 1; j < nodes_num; j++){
			links += forceGraphLinks[i * user_data.size() + j];
			if(i == nodes_num - 2 && j == nodes_num - 1)
				links += "]";
			else 
				links += ",";
		}
	}

	std::string javaScript = "open(" + nodes + "," + links + ");";
	ui.webView_UserRelation->page()->mainFrame()->evaluateJavaScript(QString::fromStdString(javaScript));

	ui.listWidget_Users->clear();
	for(int i = 0; i < nodes_num; i++){
		char num[10];
		itoa(user_data[i]->top250_seen, num, 10);
		std::string str = user_data[i]->id.c_str() + std::string("   ") + num + " movies";
		QString name = QString::fromLocal8Bit(str.c_str());
		ui.listWidget_Users->addItem(name);
	}
	
}

void Visualization::readData(){
	char buffer[200];

	std::fstream userfile("douban_data/user_info.dat");
	//std::string tempstr;
	int count = 0;
	while(!userfile.eof()){
		memset(buffer,0,200);
		userfile.getline(buffer,200);
		QString tempstr(buffer);
		QStringList lists = tempstr.split('|');
		UserData *userdata = new UserData();
		userdata->id = lists[0].toLocal8Bit();
		char * tmp = lists[1].toUtf8().data();
		userdata->name = std::string(tmp);
		userdata->movie_seen = lists[2].toInt();
		userdata->movie_interested = lists[3].toInt();
		userdata->movie_comments = lists[4].toInt();
		//userdata->movie_seen = lists[2].toInt();
		user_data.push_back(userdata);

		count++;
	}

	userfile.close();


	std::fstream moviefile("douban_data/movie_list.dat");
	while(!moviefile.eof()){
		memset(buffer,0,200);
		moviefile.getline(buffer,200);
		QString tempstr(buffer);
		QStringList lists = tempstr.split('|');
		if(lists.size() == 1)
			break;
		MovieData *moviedata = new MovieData();
		moviedata->rank = lists[0].toInt();
		//moviedata->name
		int pos1 = 0, pos2 = 0;
		for(int i = 0; i < 200; i++){
			if(buffer[i] == '|'){
				if(pos1 == 0){
					pos1 = i + 1;
				}
				else{
					pos2 = i;
					break;
				}
			}
		}
		char name[50];
		for(int i = 0; i < 50; i++){
			if(i + pos1 == pos2){
				name[i] = 0;
				break;
			}
			name[i] = buffer[i + pos1];
		}
		moviedata->name = name;
		moviedata->id = lists[2].toInt();
		moviedata->score = lists[3].toFloat();
		moviedata->year = lists[4].toInt();
		moviedata->region = lists[5].toInt();
		//userdata->movie_seen = lists[2].toInt();

		QStringList types = lists[6].split(' ');
		for(int i = 0; i < types.size(); i++){
			moviedata->type.push_back(types[i].toInt());
		}
		movie_data.push_back(moviedata);
	}
	moviefile.close();


	std::fstream userlistfile("douban_data/user_list.dat");
	while(!userlistfile.eof()){
		memset(buffer,0,200);
		userlistfile.getline(buffer,200);
		QString tempstr(buffer);
		QStringList lists = tempstr.split('|');
		if(lists.size() == 1)
			break;
		std::string userid = lists[0].toLocal8Bit();
		
		for(int i = 0; i < user_data.size(); i++){
			if(user_data[i]->id == userid){
				user_data[i]->top250_seen = lists[1].toInt();
				break;
			}
		}
	}
	userlistfile.close();


	std::fstream reviewfile("douban_data/review_list.dat");
	while(!reviewfile.eof()){
		memset(buffer,0,200);
		reviewfile.getline(buffer,200);
		QString tempstr(buffer);
		QStringList lists = tempstr.split('|');
		if(lists.size() == 1)
			break;
		std::string userid = lists[0].toLocal8Bit();
		int rank = lists[1].toInt();
		std::string commentfilestr = "douban_data/review_info/" + lists[2].toLocal8Bit() + ".out";

		for(int i = 0; i < user_data.size(); i++){
			if(user_data[i]->id == userid){
				user_data[i]->ranks.push_back(rank);

				char tempbuffer[1000];
				std::fstream commentfile(commentfilestr);
				memset(tempbuffer,0,1000);
				commentfile.getline(tempbuffer, 1000);
				QString tempscore(tempbuffer);
				user_data[i]->score.push_back(tempscore.toInt());

				//if(tempscore == "?"){
				//	int a = 1;
				//}


				//memset(tempbuffer,0,1000);
				//std::string temptitle;

				//std::getline(commentfile, temptitle);
				//std::wstring ws = std::wstring(temptitle.begin(), temptitle.end());
				////user_data[i]->title.push_back(temptitle);

				//std::string comment = "";
				//while(!commentfile.eof()){
				//	memset(tempbuffer,0,1000);
				//	commentfile.getline(tempbuffer, 1000);

				//	comment += tempbuffer;
				//}
				//user_data[i]->comments.push_back(comment);
				//commentfile.close();
				//break;
			}
		}
	}
	reviewfile.close();


	//read comment analysis data
	for(int i = 0; i < user_data.size(); i++){
		user_data[i]->character.resize(user_data[i]->ranks.size());
		user_data[i]->title.resize(user_data[i]->ranks.size());
		user_data[i]->words_num.resize(user_data[i]->ranks.size());
	}
	std::fstream commentfile("douban_data/comments.txt");
	while(!commentfile.eof()){
		memset(buffer,0,200);
		commentfile.getline(buffer,200);
		
		for(int i = 0; ; i++){
			if(buffer[i] == 0)
				break;	
			buffer[i] = buffer[i + 1];
			if(buffer[i] == 0){
				buffer[i - 1] = 0;
				break;
			}
		}
		QString tempstr(buffer);
		QStringList lists = tempstr.split(',');
		if(lists.size() == 1)
			break;
		std::string uid = lists[0].toLocal8Bit();
		int mid = lists[1].toInt();

		char character_;
		if(lists[3].toLocal8Bit() == "L")
			character_ = 'L';
		else
			character_ = 'G';
		std::string title_ = lists[4].toLocal8Bit();
		int wn = lists[5].toInt();

		for(int i = 0; i < user_data.size(); i++){
			if(user_data[i]->id == uid){
				for(int j = 0; j < user_data[i]->ranks.size(); j++){
					if(mid == user_data[i]->ranks[j]){
						user_data[i]->title[j] = title_;
						user_data[i]->words_num[j] = wn;
						user_data[i]->character[j] = character_;
						break;
					}
				}
				break;
			}
		}
	}
	commentfile.close();

	//float max = 0;
	//float r[100];
	for(int i = 0; i < user_data.size(); i++){
		int record = 0;
		int num = 0;
		for(int j = 0; j < user_data[i]->words_num.size(); j++){
			if(user_data[i]->words_num[j] > 0){
				num++;
				record += user_data[i]->words_num[j];
			}
		}
		user_data[i]->average_words_conut = record * 1.0 / num;
		if(user_data[i]->average_words_conut > 400)
			user_data[i]->average_words_conut = 400;

		//if(user_data[i]->average_words_conut > max)
		//	max = user_data[i]->average_words_conut;
		//r[i] = user_data[i]->average_words_conut;
	}
	//int b = 0;
}

void Visualization::initUserDistance(){
	user_distance.resize(user_data.size() * user_data.size());
	float dis[] = {5, 2, 0, -2, -5};
	for(int i = 0; i < user_data.size(); i++){
		for(int j = i; j < user_data.size(); j++){
			if(i == j){
				user_distance[i * user_data.size() + i] = 0;
			}
			else{
				float tmpdis = 0;
				for(int m = 0; m < user_data[i]->ranks.size(); m++){
					for(int n = 0; n < user_data[j]->ranks.size(); n++){
						if(user_data[i]->ranks[m] == user_data[j]->ranks[n]){
							if(user_data[i]->score[m] * user_data[j]->score[n] != 0)
								tmpdis += dis[abs(user_data[i]->score[m] - user_data[j]->score[n])];
						}
					}
				}
				user_distance[i * user_data.size() + j] = tmpdis;
				user_distance[j * user_data.size() + i] = tmpdis;
			}
		}
	}

	//reverse
	//float max = 0;
	//for(int i = 0; i < user_data.size() - 1; i++){
	//	for(int j = i + 1; j < user_data.size(); j++){
	//		if(user_distance[i * user_data.size() + j] > max)
	//			max = user_distance[i * user_data.size() + j];
	//	}
	//}

	//for(int i = 0; i < user_data.size(); i++){
	//	for(int j = 0; j < user_data.size(); j++){
	//		user_distance[i * user_data.size() + j] = max - user_distance[i * user_data.size() + j];
	//	}
	//}
}

void Visualization::generateForceGraphData(){
	for(int i = 0; i < user_data.size(); i++){
		int num = user_data[i]->top250_seen;
		char numstr[15];
		itoa(num, numstr, 10);
		std::string str = "{\"name\":\"" + user_data[i]->id + "\",\"scale\":" + std::string(numstr) + "}";
		forceGraphNodes.push_back(str);
	}
	forceGraphLinks.resize(user_data.size() * user_data.size());
	for(int i = 0; i < user_data.size() - 1; i++){
		for(int j = i + 1; j < user_data.size(); j++){
			char sourcestr[15];
			itoa(i, sourcestr,10);
			char targetstr[15];
			itoa(j, targetstr,10);
			char distancestr[15];
			itoa(user_distance[i * user_data.size() + j], distancestr,10);
			std::string str = "{\"source\":" + std::string(sourcestr) + ",\"target\":" + std::string(targetstr) + ",\"value\":" + std::string(distancestr) + "}";
			//forceGraphLinks.push_back(str);
			forceGraphLinks[i * user_data.size() + j] = str;
			forceGraphLinks[j * user_data.size() + i] = str;
		}
	}
}

void Visualization::generateMSTData(){
	
}

void Visualization::slotRepaintPie(){
	if(first){
		first = false;
		return;
	}
	pie_type = ui.comboBox_MoviePie->currentIndex();
	showMoveType(user_selected);
	showTreeMap(user_selected);
	showRecommendMovie(index_selected);
}

void Visualization::slotSetNeighborNumValue(){
	neighbor_num = ui.spinBox_NeighborNum->value();
}

void Visualization::slotListWidgetSelectChanged(){
	user_selected = ui.listWidget_Users->currentRow();
	main_user = user_selected;
	int id = user_selected;

	char idstr[10];
	itoa(id, idstr, 10);
	std::string javaScript = "highlight(" + std::string(idstr) +");";
	ui.webView_UserRelation->page()->mainFrame()->evaluateJavaScript(QString::fromLocal8Bit(javaScript.c_str()));

	setUserSMTData(id);
	showMoveType(id);
	showTreeMap(id);
	showUserMovie(id);
	showChord(id);
	showRecommendMovie(0);
	showCharacter(id);
}