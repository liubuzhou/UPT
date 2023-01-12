#pragma once
#include <string>
#include <fstream>
#include <vector>

namespace UPT{
namespace utility{

#define LOG_DEBUG(info)\
	Logger::instance()->log(Logger::DEBUG,__FILE__,__LINE__,info)

#define LOG_INFO(info)\
	Logger::instance()->log(Logger::INFO,__FILE__,__LINE__,info)

#define LOG_WARN(info)\
	Logger::instance()->log(Logger::WARN,__FILE__,__LINE__,info)

#define LOG_ERROR(info)\
	Logger::instance()->log(Logger::ERROR,__FILE__,__LINE__,info)

#define LOG_FATAL(info)\
	Logger::instance()->log(Logger::FATAL,__FILE__,__LINE__,info)

class _declspec (dllexport) Logger
{
public:

	enum Level
	{
		DEBUG = 0,
		INFO,
		WARN,
		ERROR,
		FATAL,
		LEVEL_COUNT
	};
	static Logger * instance();
	void open(const std::string & filename);
	void open();
	void close();
	void log(Level level, const std::string file, int line, const std::string format, ...);
	void level(Level level)
	{
		m_level = level;
	}
	void max(int max)
	{
		m_max = max;
	}
private:
	Logger();
	~Logger();
	void rotate();
	void getAllFiles(std::string path, std::vector<std::string>& files);
	void removelog(std::string dir);

private:
	std::string m_filename;
	std::string m_dirname;
	std::ofstream m_fout;
	Level m_level;
	int m_len;
	int m_max;
	static const std::string s_level[LEVEL_COUNT];
	static Logger * m_instance;
};



}
}


