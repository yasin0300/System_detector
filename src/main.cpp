#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/utsname.h>
#include <sys/statvfs.h>
int main()
{
	struct utsname systemInfo;

	std::cout << "\n"
			  << "Operating System\n";
	if (uname(&systemInfo) == 0)
	{
		std::cout << systemInfo.sysname << '\n'
				  << systemInfo.version << '\n'
				  << systemInfo.nodename << '\n'
				  << systemInfo.release << '\n'
				  << systemInfo.machine << '\n'
				  << '\n';
	}
	else
	{
		perror("uname");
	}

	std::cout << "Cpu\n";
	std::ifstream cpuFile("/proc/cpuinfo");
	std::string cpuLine;
	std::string cpuCore_line;

	
	while (std::getline(cpuFile, cpuLine))
	{
		if (cpuLine.find("model name") != std::string::npos)
		{
			std::cout << cpuLine << '\n';
			break;
		}
	}
	
	while (std::getline(cpuFile, cpuCore_line))
	{
		if (cpuCore_line.find("cpu cores") != std::string::npos)
		{
			std::cout << cpuCore_line << '\n'
					  << '\n';
			break;
		}
	}

	std::cout << "Ram\n";
	std::ifstream ramFile("/proc/meminfo");
	std::string ramTotalLine;
	long long ramTotalKb = 0;
	
	while (std::getline(ramFile, ramTotalLine))
	{
		if (ramTotalLine.find("MemTotal") != std::string::npos)
		{
			std::stringstream ss(ramTotalLine);
			std::string label;
			ss >> label >> ramTotalKb;
			std::cout << "Gesamt: " << ramTotalKb / (1024.0 * 1024.0) << " GiB\n";
			break;
		}
	}
	std::string ramFreeLine;
	long long ramFreeKb = 0;

	while (std::getline(ramFile, ramFreeLine))
	{
		if (ramFreeLine.find("MemFree") != std::string::npos)
		{
			std::stringstream ss(ramFreeLine);
			std::string label;
			ss >> label >> ramFreeKb;
			std::cout << "Frei: " << ramFreeKb / (1024.0 * 1024.0) << " GiB\n\n";
			break;
		}
	}
	std::cout << "Disk\n";
	struct statvfs diskInfo;

	if (statvfs("/", &diskInfo) == 0)
	{
		unsigned long long total =
			static_cast<unsigned long long>(diskInfo.f_blocks) * diskInfo.f_frsize;

		unsigned long long free =
			static_cast<unsigned long long>(diskInfo.f_bfree) * diskInfo.f_frsize;

		unsigned long long available =
			static_cast<unsigned long long>(diskInfo.f_bavail) * diskInfo.f_frsize;

		std::cout << "Gesamt: " << total / (1024.0 * 1024 * 1024) << " GiB\n";
		std::cout << "Frei: " << free / (1024.0 * 1024 * 1024) << " GiB\n";
		std::cout << "Verfügbar: " << available / (1024.0 * 1024 * 1024) << " GiB\n";
	}
	else
	{
		perror("statvfs");
		return 1;
	}

	return 0;
}
