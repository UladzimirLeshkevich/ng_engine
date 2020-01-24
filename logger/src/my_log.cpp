#include "my_log.h"
#define WIDTH_SYSTEM 14
#define WIDTH_TYPE 3

bool My_Log::log_opened = false;

//==================================================================
Log& My_Log::operator<<(std::string msg)
{
    stream_buffer << " " << msg;
    return *this;
}

//==================================================================
Log& My_Log::operator<<(std::shared_ptr<Log> splog)
{
    return *splog;
}

//==================================================================
Log& My_Log::operator<<(int num)
{
    stream_buffer << " " << num;
    return *this;
}

//==================================================================
Log& My_Log::operator<<(float num)
{
    stream_buffer << " " << num;
    return *this;
}

//==================================================================
Log& My_Log::operator<<(double num)
{
    stream_buffer << " " << num;
    return *this;
}

//==================================================================
Log& My_Log::operator<<(typelog level)
{
    // add time to log
    logfile << "\n" + current_time() + " | ";
    // add level to log
    std::string resized_lebel = get_label(level);
    resized_lebel.resize(WIDTH_TYPE);
    logfile << resized_lebel + " | ";
    // add system_name to log
    std::string resized_system_name;
    stream_buffer >> resized_system_name;
    resized_system_name.resize(WIDTH_SYSTEM);
    logfile << resized_system_name + " | ";
    // add message to log
    stream_buffer >> logfile.rdbuf();
    stream_buffer.clear();
    return *this;
}

//==================================================================
My_Log::My_Log() {}

//==================================================================
void My_Log::open_logfile(const std::string& filepath)
{
    if (!log_opened)
    {
        logfile.open(filepath);
        logfile << "Log started by My_Log at " << current_time() + "\n";
        log_opened = true;
    }
}

//==================================================================
void My_Log::close_log()
{
    if (log_opened)
    {
        logfile << "\n\nLog closed by My_Log at " << current_time();
        logfile.close();
        log_opened = false;
    }
}

//==================================================================
My_Log::~My_Log() { close_log(); }

//==================================================================
std::string My_Log::get_label(typelog type)
{
    std::string label;
    switch (type)
    {
    case DEBUG:
        label = "<D";
        break;
    case INFO:
        label = "<I";
        break;
    case WARNING:
        label = "<W";
        break;
    case SYSTEM_ERROR:
        label = "<E";
        break;
    case CRITICAL:
        label = "<C";
        break;
    }
    return label;
}

//==================================================================
std::string My_Log::current_time()
{
    time(&rawtime);
    std::string s(ctime(&rawtime));
    s.resize(s.size() - 1);
    return s;
}
