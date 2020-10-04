#include "logfile_handler.h"

const std::shared_ptr<logfile_handler> &log_file_manager::get_logfile_handler()
{
    if (!logfile_handler_ptr)
    {
        logfile_handler_ptr = std::make_shared<logfile_handler>();
    }

    return logfile_handler_ptr;
}

std::shared_ptr<logfile_handler> log_file_manager::logfile_handler_ptr;