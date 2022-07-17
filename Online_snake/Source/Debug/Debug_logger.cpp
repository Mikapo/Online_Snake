#include "Debug_logger.h"
#include <chrono>
#include <ctime>
#include <fstream>

Debug_logger::~Debug_logger()
{
    write_to_log_file();
}

std::string Debug_logger::get_time_string() const
{
    using namespace std::chrono;

    const auto current_time = system_clock::now();
    const time_t time = system_clock::to_time_t(current_time);

    std::array<char, 26> buffer;
    ctime_s(buffer.data(), buffer.size(), &time);
    const std::string time_string = buffer.data();

    return time_string.substr(11, 8);
}

Debug_logger& Debug_logger::get() noexcept
{
    static Debug_logger logger;
    return logger;
}

void Debug_logger::log(Log_severity severity, Log_type type, std::string_view msg)
{
    if (!is_log_alloved(severity, type))
        return;

    const std::string current_time = get_time_string();
    const std::string_view severity_string = enum_to_string(severity);
    const std::string_view type_string = enum_to_string(type);

    const std::string output = std::format("[{}] {} {}: {} \n", current_time, severity_string, type_string, msg);
    logs += output;

    std::cout << output;
    std::cout.flush();
}

void Debug_logger::write_to_log_file() const
{
    LOG(notification, logger, "Writing to log file");

    std::ofstream log_file("Log.txt");

    if (log_file.is_open())
    {
        log_file << logs;
        log_file.close();
    }
    else
        LOG(error, logger, "Failed to open log file");
}

bool Debug_logger::is_log_alloved(Log_severity severity, Log_type type)
{
    const auto is_severity_enabled = m_enabled_severities.find(severity);
    const auto is_type_enabled = m_enabled_types.find(type);

    if (is_severity_enabled == m_enabled_severities.end())
        m_enabled_severities.emplace(severity, true);
    else if (!is_severity_enabled->second)
        return false;

    if (is_type_enabled == m_enabled_types.end())
        m_enabled_types.emplace(type, true);
    else if (!is_type_enabled->second)
        return false;

    return true;
}
