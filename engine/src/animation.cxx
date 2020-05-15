#include "animation.hxx"
#include <cstddef>

//====================== ANIMATION ==========================================

animation::animation(){};
animation::~animation(){};

//==========================================================================
void animation::set_fps(float fps_value)
{
    fps = fps_value;
}

//==========================================================================
void animation::set_number_of_frames(float f)
{
    number_of_frames = f;
}

//==========================================================================
void animation::restart()
{
    current_time = 0.f;
}

//==========================================================================
int animation::current_frame_number(float delta_time)
{
    current_time += delta_time;

    float one_frame_delta = 1000.f / fps; // float one_frame_delta = 1.f / fps;

    size_t how_may_frames_from_start =
        static_cast<size_t>(current_time / one_frame_delta);

    size_t current_frame_index = how_may_frames_from_start % number_of_frames;

    return current_frame_index;
}

//==========================================================================
void animation::set_last_frame(int lf)
{
    last_frame = lf;
}

//==========================================================================
int animation::get_last_frame()
{
    return last_frame;
}
