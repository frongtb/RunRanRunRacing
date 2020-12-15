/*#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <algorithm>
#include <fstream>


using namespace sf;
using namespace std;

bool sortinrev(const pair<int, string>& a, const pair<int, string>& b);

class leaderBoard
{
public:
	leaderBoard(Font* font);
	~leaderBoard();

	void fistWriteText();
	void writeText(string str, int distance);
	void Draw(RenderWindow& window);

private:
	string txt, sName, sScore, line;
	Text name[5], Tscore[5], title;

	vector<pair<int, string>> pairScoreName;
};
*/