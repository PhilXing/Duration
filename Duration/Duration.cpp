#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

int ShowUsage()
{
	printf("This tool calculate duration between times in 24h format.\n\n"
		"\tUsage: duration [startTime] endTime\n"
	);
	return 1;
}

int main(int argc, char* argv[])
{
	struct tm tmStart, tmEnd, tmDuration;
	char* strStartTime, * strEndTime;


	switch (argc) {
	case 2:
		strEndTime = argv[1];
		sscanf_s(strEndTime, "%2u:%02u:%02u", &(tmStart.tm_hour), &(tmStart.tm_min), &(tmStart.tm_sec));

		time_t rawtime;
		time(&rawtime);
#pragma warning(suppress : 4996)
		tmEnd = *(localtime(&rawtime));
		break;
	case 3:
		strStartTime = argv[1];
		sscanf_s(strStartTime, "%2u:%02u:%02u", &(tmStart.tm_hour), &(tmStart.tm_min), &(tmStart.tm_sec));
		strEndTime = argv[2];
		sscanf_s(strEndTime, "%2u:%02u:%02u", &(tmEnd.tm_hour), &(tmEnd.tm_min), &(tmEnd.tm_sec));
		break;
	default:
		ShowUsage();
		return -1;
	}
	tmDuration.tm_sec = tmEnd.tm_sec - tmStart.tm_sec;
	tmDuration.tm_min = tmEnd.tm_min - tmStart.tm_min;
	tmDuration.tm_hour = tmEnd.tm_hour - tmStart.tm_hour;

	if (tmDuration.tm_sec < 0)
	{
		tmDuration.tm_sec += 60;
		tmDuration.tm_min--;
	}
	if (tmDuration.tm_min < 0)
	{
		tmDuration.tm_min += 60;
		tmDuration.tm_hour--;
	}
	if (tmDuration.tm_hour < 0)
	{
		tmDuration.tm_hour += 24;
	}
	printf("%2u:%02u:%02u", tmDuration.tm_hour, tmDuration.tm_min, tmDuration.tm_sec);
	return 1;
}