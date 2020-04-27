#pragma once
#include "../../common/geometry.hxx"
#include <iostream> // lvi debug
#include <vector>

enum direction
{
    left,
    right,
    up,
    down,
    rotate, // lvi need or not ??
    up_left // lvi need or not ??
};

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

    void set_direction(const direction in_direction);

    direction get_direction() { return m_direction; }

    virtual ~person() {}

    // textures

    //    void render_with_texture(int number)
    //    {
    //        render_textured_rectangle(person_geometry, number);
    //    }

    void set_texture(unsigned int texture_id);

    unsigned int get_texture() { return person_texture_id; }

    void set_texture_to_sprite(unsigned int texture_id);

    unsigned int get_from_sprite(unsigned int num);

    const std::vector<unsigned int>& get_sprite() const;

private:
    direction m_direction;
    rectangle person_geometry;
    float     health;
    float     speed;
    float     angle; // center of the rectangle relative to x axis
    float     scale{ 1.f };
    bool      render_this{ true };

    // textures
    unsigned int              person_texture_id;
    std::vector<unsigned int> person_sprite;
};
