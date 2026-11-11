#ifndef MAINMENU_H
#define MAINMENU_H

#pragma once
#include <Game.h>


class MainMenu : public Game
{
    public:
        void init(GameContext& context, Renderer& renderer) override;
        void update(float deltaTime, GameContext& context) override;
        void render(Renderer& renderer) override;

    private:
        Texture titleTex;
};

#endif // MAINMENU_H
