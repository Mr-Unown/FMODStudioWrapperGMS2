#pragma once

#define GM_FUNC extern "C" __declspec (dllexport)

// GM Constants
constexpr double GM_true() { return 1.0; }
constexpr double GM_false() { return 0.0; }
constexpr double GM_error() { return -1.0; }

// GM Instance Constants
constexpr double GM_noone() { return -4.0; }
