#pragma once

class FileIO {
public:
	int readScoreFromFile(std::string& score);
	int writeScoreToFile(int score);
};