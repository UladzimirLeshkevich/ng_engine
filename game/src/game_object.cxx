#include "game_object.hxx"

//==========================================================================
void person::set_geometry(float center_x, float center_y, float width_x, float height_y)
{
    person_geometry.v[0].x = center_x - (width_x / 2);
    person_geometry.v[0].y = center_y + (height_y / 2);

    person_geometry.v[1].x = center_x - (width_x / 2);
    person_geometry.v[1].y = center_y - (height_y / 2);

    person_geometry.v[2].x = center_x + (width_x / 2);
    person_geometry.v[2].y = center_y + (height_y / 2);

    person_geometry.v[3].x = center_x + (width_x / 2);
    person_geometry.v[3].y = center_y - (height_y / 2);

    // direction ??
    person_geometry.v[4].x = center_x;
    person_geometry.v[4].y = center_y + height_y / 2;

    // center
    person_geometry.v[5].x = center_x;
    person_geometry.v[5].y = center_y;
}

//==========================================================================
void person::set_health(float value)
{
    health = value;
}

//==========================================================================
void person::make_damage(float value)
{
    health -= value;
}

//==========================================================================
float person::get_health()
{
    return health;
}

//==========================================================================
rectangle& person::get_geometry()
{
    return person_geometry;
}

//==========================================================================
void person::set_speed(float in_speed)
{
    speed = in_speed;
}

//==========================================================================
float person::get_speed()
{
    return speed;
}

//==========================================================================
void person::set_angle(float in_angle)
{
    scale = in_angle;
}

//==========================================================================
float person::get_angle()
{
    return angle;
}

//==========================================================================
void person::add_angle(float angle_increment) //can be negative
{
    angle += angle_increment;
}

//==========================================================================
void person::set_scale(float in_scale)
{
    scale = in_scale;
}

//==========================================================================
float person::get_scale()
{
    return scale;
}

//==========================================================================
bool person::get_render_marker()
{
    return render_this;
}

//==========================================================================
void person::set_render_marker(bool value)
{
    render_this = value;
}
