#include "Player.h"
#include "Ball.h"
#include "DrawTools.h"
#include "timercpp.h"
#include <string>

typedef enum
{
    Player1Goal,
    Player2Goal,
    Player1Wins,
    Player2Wins,
    Start,
    Reset,
    Playing,
} Status;
class Game
{
public:
    int scoreP1 = 0;
    int scoreP2 = 0;

private:
    bool shouldReset = false;

public:
    Status s = Reset;

    void updateObjects(Ball &b, Player &p1, Player &p2)
    {
        if (s == Player1Wins)
        {
            print(250, 250, "PLAYER 1 WIN");
            shouldReset = true;
            later l(5000, true, [&]()
                    {
                resetPlayer1(p1);
                resetPlayer2(p2);
                resetBall(b, 0);
                s = Reset; 
                shouldReset = false;
                });
        }
        if (s == Player2Wins)
        {
            print(250, 250, "PLAYER 2 WIN");
            shouldReset = true;
            later l(5000, true, [&]()
                    {
                resetPlayer1(p1);
                resetPlayer2(p2);
                resetBall(b, 0);
                s = Reset; 
                shouldReset = false;
                });
        }
        if (s == Player1Goal)
        {
            std::string p1ScoreTxt = std::to_string(scoreP1);
            std::string p2ScoreTxt = std::to_string(scoreP2);

            print(250, 250, (char *)(p1ScoreTxt.append(" : ").append(p2ScoreTxt)).c_str());
            shouldReset = true;
            later l(
                1000, true, [&]()
                {
                resetPlayer1(p1);
                resetPlayer2(p2);
                resetBall(b, -1); 
                s = Playing; 
                shouldReset = false;
                });
        }
        if (s == Player2Goal)
        {
            std::string p1ScoreTxt = std::to_string(scoreP1);
            std::string p2ScoreTxt = std::to_string(scoreP2);

            print(250, 250, (char *)(p1ScoreTxt.append(" : ").append(p2ScoreTxt)).c_str());
            shouldReset = true;
            later l(
                1000, true, [&]()
                {

            resetPlayer1(p1);
            resetPlayer2(p2);
            resetBall(b, 1); 
            s = Playing; 
            shouldReset = false;});
        }

        if (s == Reset)
        {
            resetPlayer1(p1);
            resetPlayer2(p2);
            resetBall(b, 0);
            scoreP1 = 0;
            scoreP2 = 0;
            shouldReset = false;
            s = Playing;
        }
    }

    void player1Scored()
    {
        if (s == Playing)
        {
            scoreP1++;
            s = Player1Goal;
            if (scoreP1 == 5)
            {
                s = Player1Wins;
            }
        }
    }

    void player2Scored()
    {
        if (s == Playing)
        {
            s = Player2Goal;
            scoreP2++;
            if (scoreP2 == 5)
            {
                s = Player2Wins;
            }
        }
    }

    void resetPlayer1(Player &p)
    {
        if (shouldReset)
        {
            p.location.x = 250;
            p.location.y = 540;
        }
    }

    void resetPlayer2(Player &p)
    {
        if (shouldReset)
        {
            p.location.x = 250;
            p.location.y = 60;
        }
    }

    void resetBall(Ball &b, int n)
    {
        if (shouldReset)
        {
            if (n == 1)
            {
                b.location.y = 260;
            }
            else if (n == -1)
            {
                b.location.y = 340;
            }
            else
            {
                b.location.y = 300;
            }
            b.speed.x = 0;
            b.speed.y = 0;
            b.location.x = 250;
        }
    }
};
