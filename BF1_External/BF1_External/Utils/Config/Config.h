#pragma once
#include <Windows.h>

// ê›íËÇÃï€ë∂Ç‚ì«Ç›çûÇ›
class ConfigManager
{
private:
    // Removed
public:
    // Removed
};

// ñ˘âıÇ»íáä‘ÇΩÇø
struct cfg
{
    // System
    bool Run = false;
    int MenuKey = VK_END;
    RECT GameSize;
    POINT GamePoint;

    // Visual
    bool ESP = true;
    bool ESP_Box = true;
    bool ESP_Line = true;
    bool ESP_Distance = true;
    bool ESP_HealthBar = true;
    bool ESP_Name = true;
    float ESP_MaxDistance = 500.f;

    // Keys
    int AimKey0 = 2;
    int AimKey1 = 0;

    // KeyBind status
    bool KeyBinding = false;
    int BindID = 0;
};

extern cfg g;
extern bool IsKeyDown(int VK);
