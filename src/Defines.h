#pragma once
constexpr auto WINDOW_WIDTH = 640;
constexpr auto WINDOW_HEIGHT = 480;
constexpr auto PIXEL_SCALE = 2;

constexpr auto TICK_REPRODUCE = 1;
constexpr auto TICK_DIE = 2;

#define BUFFER_WIDTH (WINDOW_WIDTH/PIXEL_SCALE)
#define BUFFER_HEIGHT (WINDOW_HEIGHT/PIXEL_SCALE)