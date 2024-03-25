/**
 * @file Scoreboard.h
 * @author Will Gamba
 *
 * Class that implements a scoreboard
 */

#ifndef PROJECT_1_SCOREBOARD_H
#define PROJECT_1_SCOREBOARD_H

/**
 * The scoreboard
 */
class Scoreboard{
private:
    /// Current score of the level
    int mLevelScore = 0;

    /// Current total score of the game
    int mTotalScore = 0;

public:
    /**
    * Returns the current score of the level
    * @return int for the level score
    */
    int GetLevelScore() {return mLevelScore;}

    /**
    * Returns the current score of the total game
    * @return int for the total score
    */
    int GetTotalScore(){return mTotalScore;}

    void SetLevelScore(int score){ mLevelScore += score; }
    void SetTotalScore(int score){ mTotalScore += score; }
    void ResetLevelScore(){ mLevelScore = 0; }


};

#endif //PROJECT_1_SCOREBOARD_H
