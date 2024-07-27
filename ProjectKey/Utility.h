#pragma once
#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <iterator>
class Utility
{
public:
	static std::set<int> writeHightScore(int score)
	{
		std::string fileName = "highscore.txt";
		std::fstream highScoreFile(fileName);
		std::istream_iterator<int> start(highScoreFile),end;
		std::set<int>highscores(start, end);
		highScoreFile.close();

		if (highscores.size() == 0)
		{
			highscores.insert(100);
			highscores.insert(50);
			highscores.insert(20);
			highscores.insert(10);
			highscores.insert(5);

			std::ofstream outFile(fileName);	
			std::ostream_iterator<int> output_iterator(outFile, "\n");
			std::copy(highscores.begin(), highscores.end(), output_iterator);
			outFile.close();
		}

		highscores.insert(score);
		highscores.erase(highscores.begin());

		std::ofstream outFile(fileName);
		std::ostream_iterator<int> output_iterator(outFile, "\n");
		std::copy(highscores.begin(), highscores.end(), output_iterator);

		return highscores;
	}
};