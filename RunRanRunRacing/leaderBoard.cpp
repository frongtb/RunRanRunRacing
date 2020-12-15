#include "leaderBoard.h"

bool sortinrev(const pair<int, string>& a, const pair<int, string>& b) {
	return(a.first > b.first);
}

leaderBoard::leaderBoard(Font* font)
{
	txt = "Res/Text/";
	title.setFont(*font);
	title.setCharacterSize(80);
	title.setFillColor(Color(255, 255, 102, 255));
	title.setOutlineThickness(4.0f);
	title.setOutlineColor(Color::Black);
	title.setPosition(Vector2f(1220, 200));
	title.setString("Ranking");
	for (int i = 0; i < 5; i++) {
		name[i].setPosition(Vector2f((float)1100, (float)350 + (i * 80)));
		Tscore[i].setPosition(Vector2f((float)1540, (float)350 + (i * 80)));
		name[i].setFont(*font);
		Tscore[i].setFont(*font);
		name[i].setCharacterSize(60);
		Tscore[i].setCharacterSize(60);
		name[i].setOutlineThickness(3.0f);
		Tscore[i].setOutlineThickness(3.0f);
		name[i].setOutlineColor(Color::Black);
		Tscore[i].setOutlineColor(Color::Black);
		name[i].setFillColor(Color(190, 190, 190, 255));
		Tscore[i].setFillColor(Color(190, 190, 190, 255));
	}

}

leaderBoard::~leaderBoard()
{
}

void leaderBoard::fistWriteText()
{

	ifstream Ifile(txt + "images/ScoreBoard.txt");
	do {
		Ifile >> line;
		sScore = line.substr(0, line.find(','));
		sName = line.substr(line.find(',') + 1, line.length());
		pairScoreName.push_back(make_pair(atoi(sScore.c_str()), sName));
	} while (Ifile.good());
	Ifile.close();
	for (int i = 0; i < 5; i++) {
		name[i].setString(pairScoreName[i].second);
		Tscore[i].setString(to_string(pairScoreName[i].first));
	}

}

void leaderBoard::writeText(string str, int distance)
{
	pairScoreName.push_back(make_pair(distance, str));
	sort(pairScoreName.begin(), pairScoreName.end(), sortinrev);

	ofstream Ofile(txt + "images/ScoreBoard.txt");
	for (int i = 0; i < 5; i++) {
		Ofile << pairScoreName[i].first << ',' << pairScoreName[i].second << endl;
	}
	Ofile.close();
	pairScoreName.clear();
	ifstream Ifile(txt + "images/ScoreBoard.txt");
	do
	{
		Ifile >> line;
		string highscoreScore = line.substr(0, line.find(','));
		string highscoreName = line.substr(line.find(',') + 1, line.length());
		pairScoreName.push_back(make_pair(atoi(highscoreScore.c_str()), highscoreName));
	} while (Ifile.good());
	Ifile.close();
	for (int i = 0; i < 5; i++) {
		name[i].setString(pairScoreName[i].second);
		Tscore[i].setString(to_string(pairScoreName[i].first));
	}
}

void leaderBoard::Draw(RenderWindow& window)
{
	for (int i = 0; i < 5; i++) {
		window.draw(name[i]);
		window.draw(Tscore[i]);
	}
	window.draw(title);
}
