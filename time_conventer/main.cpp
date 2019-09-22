#include <iostream>
#include <string>
#include <map>
#include <vector>

std::string format_duration(int seconds)
{
    if(seconds == 0) return "now";

    std::vector<int> time_units{31536000, 86400, 3600, 60, 1};
    std::vector<int> results(5,0);
    std::vector<std::string> time_names{"year", "day", "hour", "minute", "second"};
    std::vector<std::string> marks;
    int zero = 5;
    for(int i=0; i<5; i++)
    {
        results[i] = seconds/time_units[i];
        seconds = seconds%time_units[i];
        if(results[i] != 0) zero--;

    }

    for(int i=0; i< (5-zero-2); i++)
    {
        marks.push_back(", ");
    }
    if(zero < 4) marks.push_back(" and ");
    marks.push_back("");


    int marks_counter = 0;
    std::string result;
    for(int i=0; i<5; i++)
    {
        if(results[i] == 0) continue;
        result += std::to_string(results[i]) + " ";
        if(results[i] > 1) result += time_names[i] + "s";
        else result += time_names[i];
        result += marks[marks_counter];
        marks_counter++;
    }
  return result;
}


int main()
{
    std::cout<<format_duration(121);

    return 0;
}
