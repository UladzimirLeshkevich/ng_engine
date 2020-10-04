#include <fstream>
#include <iostream>
#include <memory>

#define DEFAULT_LOGFILE_ADDRESS "log_h.txt"

struct logfile_handler
{
    logfile_handler()
    {
        open_logfile();
    }

    //void open_logfile(const std::string &filepath)
    void open_logfile()
    {
        if (!logfile_opened)
        {
            logfile.open(DEFAULT_LOGFILE_ADDRESS);

            if (logfile)
            {
                logfile_opened = true;
            }
        }
    }

    template <typename T>
    void operator<<(const T &info_to_file)
    {
        logfile << info_to_file;
    }

    ~logfile_handler()
    {
        if (logfile_opened)
        {
            logfile.close();
        }
    }

    void close()
    {
        if (logfile_opened)
        {

            logfile_opened = false;
            logfile.close();
        }
    }

    std::streambuf *rdbuf()
    {
        return logfile.rdbuf();
    }

    void flush()
    {
        logfile.flush();
    }

    std::ofstream logfile;
    bool logfile_opened{false};
    std::string filepath; // ??
};

class log_file_manager
{
public:
    static const std::shared_ptr<logfile_handler> &get_logfile_handler();

private:
    static std::shared_ptr<logfile_handler> logfile_handler_ptr;
};
