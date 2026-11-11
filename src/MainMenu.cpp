#include "MainMenu.h"
#include "Pong.h"

using namespace PongConst;

void MainMenu::init(GameContext& context, Renderer& renderer){
    Font title("assets/pong_font.ttf", 32);
    titleTex = title.createTextTexture(renderer, "PONG", ColorCodes::WHITE);
}

void MainMenu::update(float deltaTime, GameContext& context){
    if(context.input.wasKeyPressed(Key::Space)){
        context.scenes.changeScene(std::make_unique<Pong>());
    }
    if(context.input.wasKeyPressed(Key::Escape)){
        context.input.setQuit(true);
    }
}

void MainMenu::render(Renderer& renderer){
    renderer.setColor(ColorCodes::BLACK);
    renderer.clear();

    Rect titleRect = {(SCREEN_WIDTH - TITLE_W)*0.5f, (SCREEN_HEIGHT - TITLE_H)*0.5f, TITLE_W, TITLE_H};
    renderer.drawTexture(titleTex, titleRect);
}
