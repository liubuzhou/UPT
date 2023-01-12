#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include <time.h>
#include <stdexcept>
#include <direct.h>
#include <io.h>


namespace UPT
{
	namespace utility
	{
		const std::string Logger::s_level[LEVEL_COUNT] = {
			"DEBUG",
			"INFO",
			"WARN",
			"ERROR",
			"FATAL"
		};
		Logger* Logger::m_instance = nullptr;

		Logger::Logger():m_level(Level::DEBUG),m_len(0),m_max(1048576),m_filename("../log/logger.log")
		{
			this->m_dirname = m_filename.substr(0, m_filename.rfind('/'));
		}
		Logger::~Logger()
		{
		}
		Logger* Logger::instance()
		{
			if (m_instance == nullptr)
			{
				m_instance = new Logger();
			}
			return m_instance;
		}

		void Logger::open(const std::string & filename)
		{
			m_filename = filename;
			m_fout.open(filename, std::ios::app);
			if (m_fout.fail())
			{
				throw std::logic_error("open file failed" + filename);
			}
		}
		void Logger::open()
		{
			removelog(m_dirname);
			m_fout.open(m_filename, std::ios::app);
			if (m_fout.fail())
			{
				throw std::logic_error("open file failed" + m_filename);
			}
		}
		void Logger::close()
		{
			m_fout.close();
		}

		void Logger::log(Level level, const std::string file, int line, const std::string format, ...)
		{
			m_len = 0;
			if (m_level > level)
			{
				return;
			}

			if (m_fout.fail())
			{
				throw std::logic_error("open file failed" + m_filename);
			}

			time_t ticks = time(nullptr);
			struct tm * ptm = localtime(&ticks);
			char timestamp[32];
			memset(timestamp, 0, sizeof(timestamp));
			strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", ptm);

			const std::string ftm = std::string(timestamp) + ' '
				+ '[' + s_level[level] + ']' + "\t-> "
				+ file.substr(file.rfind('\\') + 1, file.length()) + ':'
				+ std::to_string(line) + "\t-> " 
				+ format + ' '
				+ '\n';

			m_fout << ftm;

			m_fout.seekp(0, m_fout.end);
			size_t dstFileSize = m_fout.tellp();

			m_len = (int)dstFileSize + sizeof(ftm);
			m_fout.flush();

			if (m_len >= m_max && m_max > 0)
			{
				rotate();
			}
			
		}

		void Logger::rotate()
		{
			close();
			time_t ticks = time(nullptr);
			struct tm * ptm = localtime(&ticks);
			char timestamp[32];
			memset(timestamp, 0, sizeof(timestamp));
			strftime(timestamp, sizeof(timestamp), "%H_%M_%S", ptm);

			std::string filename = m_filename.substr(0, m_filename.rfind('/')+1) + std::string(timestamp) + ".log";
			m_filename = filename;
			open(m_filename);
		}

		void Logger::getAllFiles(std::string path, std::vector<std::string>& files)
		{
			//文件句柄
			long long hFile = 0;
			//文件信息
			struct _finddata_t fileinfo;
			std::string p;
			if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1) 
			{
				do 
				{
					if ((fileinfo.attrib & _A_SUBDIR)) 
					{  //比较文件类型是否是文件夹
						if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) 
						{
							files.push_back(p.assign(path).append("/").append(fileinfo.name));
							//递归搜索
							getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);
						}
					}
					else 
					{
						files.push_back(p.assign(path).append("/").append(fileinfo.name));
					}
				} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
				_findclose(hFile);
			}
		}

		void Logger::removelog(std::string dirname)
		{
			std::vector<std::string> files;
			getAllFiles(dirname, files);
			for (auto it = files.begin();it!=files.end();it++)
			{
				char source[256];
				strcpy(source, (*it).c_str());
				remove(source);
			}
		}
	}
}

