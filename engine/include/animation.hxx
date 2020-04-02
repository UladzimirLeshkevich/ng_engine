#pragma once

//====================== ANIMATION ============================================
class animation
{
public:
    animation();
    ~animation();

    void set_fps(float fps_value);
    void set_number_of_frames(float f);
    void restart();
    int  current_frame_number(float delta_time);
    void set_last_frame(int lf);
    int  get_last_frame();

private:
    int   number_of_frames; // textures number in one animation
    float fps;
    float current_time = 0.f;
    int   last_frame   = 0;
};