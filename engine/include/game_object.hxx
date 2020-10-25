#pragma once
#include "../../common/geometry.hxx"
#include <iostream> // lvi debug
#include <vector>
#include "../../logger/include/log_manager.h"

enum direction
{
    left,
    right,
    up,
    down,
    toward,
    backward
};

class game_object
{
public:
    virtual ~game_object() {}
};

class person : public game_object
{
public:
    person();

    void set_geometry(float center_x, float center_y, float width_x,
                      float height_y);

    void set_world_geometry(float center_x, float center_y, float width_x,
                            float height_y);

    rectangle &get_geometry();

    rectangle get_geometry_copy();

    void set_health(float value);
    void make_damage(float value);
    float get_health();

    void set_speed(float in_speed);
    float get_speed();

    void set_angle(float in_angle);
    float get_angle();
    void add_angle(float angle_increment);

    void set_scale(float in_scale);
    float get_scale();

    void set_render_marker(bool value);
    bool get_render_marker();

    void set_direction(const direction in_direction);

    direction get_direction() { return m_direction; }

    virtual ~person() { logger << "person with ID = " << std::to_string(personID) << " destructed" << INFO; }

    // textures

    //    void render_with_texture(int number)
    //    {
    //        render_textured_rectangle(person_geometry, number);
    //    }

    void set_texture(unsigned int texture_id);

    unsigned int get_texture() { return person_texture_id; }

    void set_texture_to_sprite(unsigned int texture_id);

    unsigned int get_from_sprite(unsigned int num);

    const std::vector<unsigned int> &get_sprite() const;

private:
    direction m_direction;
    rectangle person_geometry;
    float health;
    float speed;
    float angle; // center of the rectangle relative to x axis
    float scale{1.f};
    bool render_this{true};

    // textures
    unsigned int person_texture_id;
    std::vector<unsigned int> person_sprite;

    const static std::string system_name;
    std::shared_ptr<Log> logger;

    static long long int global_personID_counter;
    long long int personID;
};

class rot_object : public game_object
{
public:
    rot_object();

    void set_geometry(float center_x, float center_y, float width_x,
                      float height_y);

    rectangle &get_geometry();
    rectangle get_geometry_copy();

    void set_rotatinon_paremetres(float in_speed, int direction);

    float get_speed();
    float get_calculaterd_speed();

    int get_direction();

    void set_texture(unsigned int texture_id);
    unsigned int get_texture() { return person_texture_id; }

    virtual ~rot_object() { logger << "person with ID = " << std::to_string(personID) << " destructed" << INFO; }

private:
    rectangle person_geometry;

    float m_rotation_speed;
    int m_direction; // 1 or -1

    float scale{1.f};
    bool render_this{true};

    const static std::string system_name;
    std::shared_ptr<Log> logger;

    static long long int global_personID_counter;
    long long int personID;

    // textures
    unsigned int person_texture_id;
    //std::vector<unsigned int> person_sprite;
};
