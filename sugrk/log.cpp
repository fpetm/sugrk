#include "log.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace sugrk {
std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Init() {
  std::vector<spdlog::sink_ptr> sinks;

  sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
  sinks.emplace_back(
      std::make_shared<spdlog::sinks::basic_file_sink_mt>("sugrk.log"));

  sinks[0]->set_pattern("%^[%T] %n: %v%$");
  sinks[1]->set_pattern("[%T] [%l] %n: %v");

  s_Logger =
      std::make_shared<spdlog::logger>("sugrk", begin(sinks), end(sinks));
  spdlog::register_logger(s_Logger);
  s_Logger->set_level(spdlog::level::trace);
  s_Logger->flush_on(spdlog::level::trace);
}
} // namespace sugrk
