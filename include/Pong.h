#ifndef PONG_H
#define PONG_H

#include <Game.h>

namespace PongConst{
    inline constexpr int16_t SCREEN_WIDTH = 1920;
    inline constexpr int16_t SCREEN_HEIGHT = 1080;
    inline constexpr uint16_t SIDE_PAD = SCREEN_WIDTH/10;

    inline constexpr float PADDLE_SPEED = SCREEN_WIDTH;
    inline constexpr float BALL_SPEED = SCREEN_HEIGHT/2;

    inline constexpr uint8_t PADDLE_WIDTH = 15.0f;
    inline constexpr uint8_t PADDLE_HEIGHT = 80.0f;
    inline constexpr uint16_t L_PAD_X = (SCREEN_WIDTH / 16) - PADDLE_WIDTH;
    inline constexpr uint16_t R_PAD_X = SCREEN_WIDTH - (SCREEN_WIDTH/16) - PADDLE_WIDTH;
    inline constexpr uint16_t PAD_Y = (SCREEN_HEIGHT/2) - (PADDLE_HEIGHT/2);

    inline constexpr uint8_t BALL_SIZE = 15.0f;
    inline constexpr uint16_t BALL_X = (SCREEN_WIDTH/2) - (BALL_SIZE/2);
    inline constexpr uint16_t BALL_Y = (SCREEN_HEIGHT/2) - (BALL_SIZE/2);

    inline constexpr uint8_t WINNING_SCORE = 10;

    inline constexpr uint8_t NUM_WIDTH = 100;
    inline constexpr uint8_t NUM_HEIGHT = 128;

    inline constexpr float RESPAWN_DELAY = 1.0f;

    inline constexpr float PADDLE_ANGLES[8] = {
        -60.0f,
        -45.0f,
        -30.0f,
        0,
        0,
        30.0f,
        45.0f,
        60.0f
    };

    inline constexpr float PADDLE_HIT = 900.0f;
    inline constexpr float WALL_HIT = 650.0f;
    inline constexpr float SCORE = 300.0f;

    inline constexpr float HIT_DURATION = 0.025f;
    inline constexpr float SCORE_DURATION = 0.1f;

    inline constexpr float VOLUME = 0.25f;

    inline constexpr float TITLE_W = SCREEN_WIDTH / 2;
    inline constexpr float TITLE_H = SCREEN_HEIGHT / 3;

    inline constexpr float PAUSE_W = TITLE_W / 4;
    inline constexpr float PAUSE_H = TITLE_H / 4;
}

class Pong : public Game
{
    public:
        void init(GameContext& context, Renderer& renderer) override;

        void update(float deltaTime, GameContext& context) override;

        void render(Renderer& renderer) override;
    private:
        Rect leftScoreBox;
        uint8_t leftScore;
        Rect rightScoreBox;
        uint8_t rightScore;

        bool active = true;

        Countdown respawnTimer;

        Rect leftPaddle;
        Rect rightPaddle;
        Rect ball;

        Vector2 ballVelocity;

        void resetBall(AudioSystem& audio);
        void checkPaddle(bool isRight, AudioSystem& audio);
        int checkPaddleSegment(bool isRight);

        SoundBuffer paddleSound;
        SoundBuffer wallSound;
        SoundBuffer scoreSound;
};

#endif // PONG_H
