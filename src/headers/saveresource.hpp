#ifndef SAVERESOURCE_H
#define SAVERESOURCE_H

#include <string>
#include <tuple>

namespace Game {
struct GameBoard;

namespace Saver {
void saveGamePlayState(GameBoard gb);
void createGameSaveFiles();
std::string getPrevGameStateFilename();
std::string getPrevGameStatisticsFilename();
std::string getGameStatisticsFilename();
std::string getGameScoresFilename();
} // namespace Saver
} // namespace Game

#endif
