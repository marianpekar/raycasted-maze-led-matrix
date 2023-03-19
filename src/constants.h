#pragma once

constexpr auto PI = 3.14159265;
constexpr auto TWO_PI = 6.28318530;

constexpr auto TILE_SIZE = 64;
constexpr auto MAZE_NUM_ROWS = 64;
constexpr auto MAZE_NUM_COLS = 64;
constexpr auto NUM_TEXTURES = 8;

constexpr auto PLAYER_WALK_SPEED = 150;
constexpr auto PLAYER_TURN_SPEED = 90;

constexpr auto WINDOW_WIDTH = 64;
constexpr auto WINDOW_HEIGHT = 64;

constexpr auto TEXTURE_WIDTH = 64;
constexpr auto TEXTURE_HEIGHT = 64;

constexpr auto FOV_ANGLE = (60 * PI / 180);
constexpr auto NUM_RAYS = WINDOW_WIDTH;

constexpr auto FPS = 100;
constexpr auto FRAME_TIME_LENGTH = (1000 / FPS);

constexpr auto REDBRICK_TEXTURE_FILEPATH = "./src/images/redbrick.png";
constexpr auto PURPLESTONE_TEXTURE_FILEPATH = "./src/images/purplestone.png";
constexpr auto MOSSYSTONE_TEXTURE_FILEPATH = "./src/images/mossystone.png";
constexpr auto GRAYSTONE_TEXTURE_FILEPATH = "./src/images/graystone.png";
constexpr auto COLORSTONE_TEXTURE_FILEPATH = "./src/images/colorstone.png";
constexpr auto BLUESTONE_TEXTURE_FILEPATH = "./src/images/bluestone.png";
constexpr auto WOOD_TEXTURE_FILEPATH = "./src/images/wood.png";
constexpr auto EAGLE_TEXTURE_FILEPATH = "./src/images/eagle.png";

constexpr auto FBM_X_SCALE = 0.0001f;
constexpr auto FBM_Y_SCALE = 0.0001f;
constexpr auto FBM_OCTAVES = 8;
constexpr auto FBM_PERSISTENCE = 28;