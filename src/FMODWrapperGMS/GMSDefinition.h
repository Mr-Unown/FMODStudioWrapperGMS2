#pragma once

#define GM_FUNC extern "C" __declspec (dllexport)

// GM Constants
constexpr unsigned int GM_true() { return 1; }
constexpr unsigned int GM_false() { return 0; }
constexpr unsigned int GM_error() { return -1; }

// GM Instance Constants
constexpr unsigned int GM_noone() { return -4; }
