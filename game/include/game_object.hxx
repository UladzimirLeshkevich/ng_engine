#pragma once
#include "../../common/geometry.hxx"

class game_object
{
public:
    virtual ~game_object() {}
};

class person : public game_object
{
public:
    void set_geometry(float center_x, float center_y, float width_x,
                      float height_y);

    rectangle& get_geometry();

    void  set_health(float value);
    void  make_damage(float value);
    float get_health();

    void  set_speed(float in_speed);
    float get_speed();

    void  set_angle(float in_angle);
    float get_angle();
    void  add_angle(float angle_increment);

    void  set_scale(float in_scale);
    float get_scale();

    void set_render_marker(bool value);
    bool get_render_marker();

    virtual ~person() {}

private:
    rectangle person_geometry;
    float     health;
    float     speed;
    float     angle; // relative to x axis
    float     scale{ 1.f };
    bool      render_this{ true };
};
