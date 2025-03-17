#include "game.h"
#include "renderer.h"
#include "window.h"

int main(int argc, char* argv[]) {
    Window* window = new Window();

    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.disable_hardware_pulsing = true;
    
    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL)
        return 1;

    Renderer* renderer = new Renderer(window, canvas);
    Game* game = new Game();

    game->Setup();
	
    while (game->m_isGameRunning) {
        game->Update();
        renderer->Render(game);
        game->Delay(FRAME_TIME_LENGTH);
    }
	
    delete game;
    delete renderer;
    delete window;
    return 0;
}