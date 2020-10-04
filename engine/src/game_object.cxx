#include "game_object.hxx"
#include <string>

//==========================================================================
const std::string person::system_name{"person_sys"};

long long int person::global_personID_counter{0};

//==========================================================================

person::person() : logger(LogManager::get_logger(system_name))
{
    personID = ++global_personID_counter;
    logger << "person with ID = " << std::to_string(personID) << " created" << INFO;
}

//==========================================================================
void person::set_geometry(float center_x, float center_y, float width_x,
                          float height_y)
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

    // textures
    person_geometry.v[0].tx = 0.f;
    person_geometry.v[0].ty = 0.f;

    person_geometry.v[1].tx = 0.f;
    person_geometry.v[1].ty = 1.f;

    person_geometry.v[2].tx = 1.f;
    person_geometry.v[2].ty = 0.f;

    person_geometry.v[3].tx = 1.f;
    person_geometry.v[3].ty = 1.f;
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
rectangle &person::get_geometry()
{
    return person_geometry;
}

//==========================================================================
rectangle person::get_geometry_copy()
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
void person::add_angle(float angle_increment) // can be negative
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
void person::set_direction(const direction in_direction)
{
    m_direction = in_direction;
}

//==========================================================================
void person::set_texture(unsigned int texture_id)
{
    person_texture_id = texture_id;
}

//==========================================================================
void person::set_texture_to_sprite(unsigned int texture_id)
{
    person_sprite.push_back(texture_id);
}

//==========================================================================
unsigned int person::get_from_sprite(unsigned int num)
{
    unsigned int number;
    number = person_sprite.at(num);
    return number;
}

//==========================================================================
const std::vector<unsigned int> &person::get_sprite() const
{
    return person_sprite;
}

//==========================================================================
void person::set_render_marker(bool value)
{
    render_this = value;
}

//==========================================================================
//==========================================================================
const std::string rot_object::system_name{"rot_object_sys"};

long long int rot_object::global_personID_counter{0};

rot_object::rot_object() : logger(LogManager::get_logger(system_name))
{
    personID = ++global_personID_counter;
    logger << "rot_object with ID = " << std::to_string(personID) << " created" << INFO;
}

//==========================================================================
void rot_object::set_geometry(float center_x, float center_y, float width_x,
                              float height_y)
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

    // textures
    person_geometry.v[0].tx = 0.f;
    person_geometry.v[0].ty = 0.f;

    person_geometry.v[1].tx = 0.f;
    person_geometry.v[1].ty = 1.f;

    person_geometry.v[2].tx = 1.f;
    person_geometry.v[2].ty = 0.f;

    person_geometry.v[3].tx = 1.f;
    person_geometry.v[3].ty = 1.f;
}

//==========================================================================
rectangle &rot_object::get_geometry()
{
    return person_geometry;
}

//==========================================================================
rectangle rot_object::get_geometry_copy()
{
    return person_geometry;
}

//==========================================================================
void rot_object::set_rotatinon_paremetres(float in_speed, int direction)
{
    m_rotation_speed = in_speed;
    m_direction = direction;
}

//==========================================================================
float rot_object::get_speed()
{
    return m_rotation_speed;
}

//==========================================================================
int rot_object::get_direction()
{
    return m_direction;
}

//==========================================================================
float rot_object::get_calculaterd_speed()
{
    return m_rotation_speed * 6.f * (1 / 60.f); // lvi my formula
}

//==========================================================================
void rot_object::set_texture(unsigned int texture_id)
{
    person_texture_id = texture_id;
}