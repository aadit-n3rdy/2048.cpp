#include "saveresource.hpp"
#include "gameboard.hpp"
#include "platform_folders.h"
#include <iostream>
#include <fstream>
#include <ghc/filesystem.hpp>

namespace Game {
namespace Saver {

std::string getPrevGameStateFilename() {
	return sago::getSaveGamesFolder1() + "/2048/previousGame";
}

std::string getPrevGameStatisticsFilename() {
	return sago::getSaveGamesFolder1() + "/2048/previousGameStats";
}

std::string getGameStatisticsFilename() {
	return sago::getSaveGamesFolder1() + "/2048/statistics.txt";
}

std::string getGameScoresFilename() {
	return sago::getSaveGamesFolder1() + "/2048/scores.txt";
}

void createGameSaveFiles() {
	namespace fs = ghc::filesystem;
	std::string saveDir = sago::getSaveGamesFolder1() + "/2048";
	if (!fs::is_directory(saveDir)) {
		fs::create_directories(sago::getSaveGamesFolder1() + "/2048");
	}
	if (!fs::exists(getGameStatisticsFilename())) {
		std::fstream statsFile;
		statsFile.open(getGameStatisticsFilename(), std::ios::out);
		statsFile << "0\n0\n0\n0\n0\n";
		statsFile.close();
	}
	if (!fs::exists(getGameScoresFilename())) {
		std::fstream scoresFile;
		scoresFile.open(getGameScoresFilename(), std::ios::out);
		scoresFile.close();
	}
}

namespace {

bool generateFilefromPreviousGameStatisticsData(std::ostream &os,
                                                const GameBoard &gb) {
  os << gb.score << ":" << MoveCountOnGameBoard(gb);
  return true;
}

bool generateFilefromPreviousGameStateData(std::ostream &os,
                                           const GameBoard &gb) {
  os << printStateOfGameBoard(gb);
  return true;
}

void saveToFilePreviousGameStateData(std::string filename,
                                     const GameBoard &gb) {
  std::ofstream stateFile(filename, std::ios_base::app);
  generateFilefromPreviousGameStateData(stateFile, gb);
}

void saveToFilePreviousGameStatisticsData(std::string filename,
                                          const GameBoard &gb) {
  std::ofstream stats(filename, std::ios_base::app);
  generateFilefromPreviousGameStatisticsData(stats, gb);
}

} // namespace

void saveGamePlayState(GameBoard gb) {
  // Currently two datafiles for now.
  // Will be merged into one datafile in a future PR.
  //constexpr auto filename_game_data_state = "../data/previousGame";
  //constexpr auto filename_game_data_statistics = "../data/previousGameStats";
  std::remove(getPrevGameStateFilename().c_str());
  std::remove(getPrevGameStatisticsFilename().c_str());

  saveToFilePreviousGameStateData(getPrevGameStateFilename(), gb);
  saveToFilePreviousGameStatisticsData(getPrevGameStatisticsFilename(), gb);
}

} // namespace Saver
} // namespace Game
