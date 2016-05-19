#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <QtWidgets/QMainWindow>
#include "ui_visualization.h"
#include "qcolorbar.h"
#include "UserData.h"
class Visualization : public QMainWindow
{
	Q_OBJECT

public:
	Visualization(QWidget *parent = 0);
	~Visualization();

private:
	Ui::VisualizationClass ui;
	QColorBar *colorbar;
	std::vector<MovieData*> movie_data;
	std::vector<UserData*> user_data;
	std::vector<float> user_distance;
	void readData();
	void generateForceGraphData();
	void generateMSTData();
	void setUserSMTData(int id);
	std::vector<std::string> forceGraphNodes;
	std::vector<std::string> forceGraphLinks;

	std::vector<std::string> MSTNodes;
	std::vector<std::string> MSTLinks;
	int user_selected;
	int main_user;
	int pie_type;
	int nodes_num;
	int neighbor_num;
	bool main_user_recommend;
	int index_selected;
	std::vector<int> record_neighbor_index;
	bool first;

	void showTreeMap(int id);
	void showTreeMapType(int id);
	void showTreeMapRegion(int id);
	void showTreeMapYear(int id);

	int ftoa(char *str, float num, int n);

	void showUserMovie(int id);

	void showMoveType(int id);
	
	
	void initUserDistance();
	void showChord(int id);

	//void showRecommendMovieSingle();
	void showRecommendMovie(int index);


	void showRecommendTreeMap(int id, std::vector<int> rank);
	void showRecommendTreeMapType(int id, std::vector<int> rank);
	void showRecommendTreeMapRegion(int id, std::vector<int> rank);
	void showRecommendTreeMapYear(int id, std::vector<int> rank);
	
	void showCharacter(int id);
public slots:	
	void slotRepaintPie();
	void slotSetNeighborNumValue();
	void slotSetForceGraphData();
	void UserNeighborSelected(int id);
	void UserRelationSelected(int id);
	void initUserRelationJS();
	void initUserSMTJS();
	void initUserMoiveType();
	void initUserTreeMapJS();
	void initChord();
	void initRecommend();

	void UserNeighborRecommend(int index);
	void slotListWidgetSelectChanged();
};

#endif // VISUALIZATION_H
