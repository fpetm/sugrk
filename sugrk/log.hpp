#pragma once

#include <spdlog/spdlog.h>

namespace sugrk {
class Log {
public:
  static void Init();
  static std::shared_ptr<spdlog::logger> &GetLogger() { return s_Logger; }

private:
  static std::shared_ptr<spdlog::logger> s_Logger;
};

} // namespace sugrk

#define SG_TRACE(...) ::sugrk::Log::GetLogger()->trace(__VA_ARGS__)
#define SG_INFO(...) ::sugrk::Log::GetLogger()->info(__VA_ARGS__)
#define SG_WARN(...) ::sugrk::Log::GetLogger()->warn(__VA_ARGS__)
#define SG_ERROR(...) ::sugrk::Log::GetLogger()->error(__VA_ARGS__)
#define SG_CRITICAL(...) ::sugrk::Log::GetLogger()->critical(__VA_ARGS__)
