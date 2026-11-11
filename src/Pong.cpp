#include "../include/Pong.h"
#include "PauseScene.h"
#include "MainMenu.h"

using namespace PongConst;

void Pong::init(GameContext& context, Renderer& renderer){
    leftScoreBox = {SCREEN_WIDTH / 4 - NUM_WIDTH/2,
            0,
            NUM_WIDTH,
            NUM_HEIGHT
    };
    leftScore = 0;
    rightScoreBox = {(((SCREEN_WIDTH / 4)*3) - NUM_WIDTH/2),
            0,
            NUM_WIDTH,
            NUM_HEIGHT
    };
    rightScore = 0;

    leftPaddle = {L_PAD_X + SIDE_PAD,
            PAD_Y,
            PADDLE_WIDTH,
            PADDLE_HEIGHT};
    rightPaddle = {R_PAD_X - SIDE_PAD,
            PAD_Y,
            PADDLE_WIDTH,
            PADDLE_HEIGHT};
    ball = {BALL_X,
            BALL_Y,
            BALL_SIZE,
            BALL_SIZE};
    ballVelocity = {BALL_SPEED,
            BALL_SPEED, BALL_SPEED};

    paddleSound = context.audio.generateTone(PADDLE_HIT, HIT_DURATION, VOLUME);
    wallSound = context.audio.generateTone(WALL_HIT, HIT_DURATION, VOLUME);
    scoreSound = context.audio.generateTone(SCORE, SCORE_DURATION, VOLUME);
}

void Pong::update(float deltaTime, GameContext& context){
    const float paddleSpeed = PADDLE_SPEED;

    if(context.input.isKeyDown(Key::W)){
        if(leftPaddle.y >= 0)
            leftPaddle.y -= paddleSpeed * deltaTime;
    }
    if(context.input.isKeyDown(Key::S)){
        if(leftPaddle.y <= SCREEN_HEIGHT - PADDLE_HEIGHT)
            leftPaddle.y += paddleSpeed * deltaTime;
    }
    if(context.input.wasKeyPressed(Key::P)){
        context.scenes.pushScene(std::make_unique<PauseScene>());
        return;
    }
    if(context.input.isKeyDown(Key::Up)){
        if(rightPaddle.y >= 0)
            rightPaddle.y -= paddleSpeed * deltaTime;
    }
    if(context.input.isKeyDown(Key::Down)){
        if(rightPaddle.y <= SCREEN_HEIGHT - PADDLE_HEIGHT)
            rightPaddle.y += paddleSpeed * deltaTime;
    }
    if(context.input.wasKeyPressed(Key::Escape)){
        context.scenes.changeScene(std::make_unique<MainMenu>());
        return;
    }

    if(!active){
        respawnTimer.update(deltaTime);
        if(respawnTimer.finished()){
            active = true;
        }
        return;
    }

    checkPaddle((ballVelocity.x > 0), context.audio);

    if(hitUpBound(ball)){
        ball.y = 0;
        ballVelocity.y = std::abs(ballVelocity.y);
        context.audio.playSfx(wallSound);
    }

    if(hitLoBound(ball, SCREEN_HEIGHT)){
        ball.y = SCREEN_HEIGHT - ball.height;
        ballVelocity.y = -std::abs(ballVelocity.y);
        context.audio.playSfx(wallSound);
    }

    if(hitRBound(ball, SCREEN_WIDTH, SIDE_PAD)){
        ++leftScore;
        resetBall(context.audio);
        return;
    }
    if(hitLBound(ball, SIDE_PAD)){
        ++rightScore;
        resetBall(context.audio);
        return;
    }

    ball.x += ballVelocity.x * deltaTime;
    ball.y += ballVelocity.y * deltaTime;
}

void Pong::render(Renderer& renderer){
    renderer.setColor(0, 0, 0, 255);
    renderer.clear();

    renderer.setColor(255, 255, 255, 255);

    renderer.drawLine(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT, true);
    renderer.drawNumber(leftScoreBox, leftScore%10);
    renderer.drawNumber(rightScoreBox, rightScore%10);
    renderer.drawRect(leftPaddle, 1);
    renderer.drawRect(rightPaddle, 1);
    if(active)
        renderer.drawRect(ball, 1);
}

void Pong::resetBall(AudioSystem& audio){
    audio.playSfx(scoreSound);
    ball.x = BALL_X;
    ballVelocity.x *= -1;
    active = false;
    respawnTimer.start(RESPAWN_DELAY);
}

int Pong::checkPaddleSegment(bool isRight){
    const auto& paddle = isRight ? rightPaddle : leftPaddle;

    float dist = (ball.y + ball.height * 0.5) - paddle.y;
    int seg = static_cast<int>(dist / (paddle.height / 8.0f));

    return std::clamp(seg, 0, 7);
}

void Pong::checkPaddle(bool isRight, AudioSystem& audio){
    if(isRight){
        if(intersects(ball, rightPaddle) && ballVelocity.x > 0){
            ball.x = rightPaddle.x - ball.width;
            int seg = checkPaddleSegment(true);
            setAngle(PADDLE_ANGLES[seg], ballVelocity);
            ballVelocity.x = -std::abs(ballVelocity.x);
            audio.playSfx(paddleSound);
        }
    }else{
        if(intersects(ball, leftPaddle) && ballVelocity.x < 0){
            ball.x = leftPaddle.x + leftPaddle.width;
            int seg = checkPaddleSegment(false);
            setAngle(PADDLE_ANGLES[seg], ballVelocity);
            ballVelocity.x = std::abs(ballVelocity.x);
            audio.playSfx(paddleSound);
        }
    }
}
