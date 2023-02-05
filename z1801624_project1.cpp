/********************************************************************
CSCI 480 - Assignment 1 - Spring 2023 
Programmer: Blane Gorospe
Section: 1
Date Due: 2/4/2023
Purpose: 
This program checks different /proc files in a /procfile system. 
Then answers questions based on the file. 
it will open and read different files despite being virtual. 
This program does as follows: sort through and read file data, store necessary data to answer questions,
then use the sorted data to answer.
*********************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int main()
{
std::cout << "A: Questions about turing's OS:" << std::endl;
std::string ostype; //string to hold text
std::ifstream OSTypeFile("/proc/sys/kernel/ostype"); //open file that has ostype
  
if (OSTypeFile.is_open())//if statement for if the file is opened
{
	//Get the lines in a file and put into a string
    	while (getline(OSTypeFile, ostype))
    	{
      	//Output the ostype 
      	std::cout << "1. The type of turing's OS is " << ostype << "." << std::endl;
    	}
}
else
{
//unable to open file error
std::cerr << "ERROR: unable to open file /proc/sys/kernel/ostype" << std::endl;
  	}
OSTypeFile.close();

std::string hostname; //string to hold text in hostname file
std::ifstream HostNameFile("/proc/sys/kernel/hostname"); //open the file that contains the hostname of turing
 
//if statement for open file
if (HostNameFile.is_open())
{
	//Get the lines in a file and put into a string
    	while (getline(HostNameFile, hostname))
    	{
    		//Output the hostname 
      		std::cout << "2. The turing hostname is " << hostname << "." << std::endl;
    	}
}
else
{
    //unable to open error
    std::cerr << "ERROR: unable to open open file /proc/sys/kernel/hostname" << std::endl;
}

HostNameFile.close();
std::string osrelease; //string to hold the text in osrelease file
std::ifstream OSReleaseFile("/proc/sys/kernel/osrelease"); //open the file that contains the osrelease of turing

if (OSReleaseFile.is_open())
{
	//Get the lines in a file and put into a string
    	while (getline(OSReleaseFile, osrelease))
    	{
      		//Output the osrelease of turing
      		std::cout << "3. OS release of turing is " << osrelease << "." << std::endl;
    	}
}
else
{
	//unable to open error
  	std::cerr << "ERROR: unable to open file /proc/sys/kernel/osrelease" << std::endl;
}

OSReleaseFile.close();
std::string version; //string to hold the text in version file
std::ifstream VersionFile("/proc/sys/kernel/version"); //open the file that contains the version of turing

if (VersionFile.is_open())
{
	//Get the lines in a file and put into a string
   	while (getline(VersionFile, version))
    	{
      		//Output the version
      		std::cout << "4. turing version is " << version << "." << std::endl << std::endl;
    	}
}
else
{
	//unable to open fileerror
    	std::cerr << "ERROR: unable open file /proc/sys/kernel/version" << std::endl;
}

VersionFile.close();
std::cout << "B. Questions about turing's processor:" << std::endl;
std::string cpuinfo1; //string to hold the text in cpuinfo file
//open file with cpuinfo
std::ifstream CPUInfoFile1("/proc/cpuinfo");

int processorCount = 0; //variable used to count processors
int idCount = 0;
int hold = -1;

if (CPUInfoFile1.is_open())
{
	//Get the lines in a file and put into a string
   	while (getline(CPUInfoFile1, cpuinfo1))
    	{
     	//If the line is empty add to it
      	if (cpuinfo1.empty())
        {
        	processorCount++;
        }
        //If line contains physical id
        if (cpuinfo1.find("physical id") != std::string::npos)
      	{
		//remove everyhting until only the physical id shows
		cpuinfo1 = cpuinfo1.substr(cpuinfo1.find(":") + 2);
	
		//Convert the string to int so its easier to compare
       		int id = std::stoi(cpuinfo1);

	//if the placeholder id doesn't match actual id
	if (hold != id)
	{
		//Add one to the count
          	idCount++;
	}
	//set the placeholder the the number of the id
	hold = id;
        }
}

	//Output the number of processors that turing has
    	std::cout << "1. Turing has " << processorCount << " processors." << std::endl;

    	//Output the number of physical multi-core chips turing has
    	std::cout << "2. Turing has " << idCount << " physical multi-core chips." << std::endl;
}
else
{
	//unable to open file error
   	std::cerr << "ERROR: unable to open file /proc/cpuinfo" << std::endl;
}

CPUInfoFile1.close();

std::string uptime; //string to hold the text in uptime file
std::ifstream UptimeFile("/proc/uptime"); //open the file that contains the uptime info

if (UptimeFile.is_open())
{
	//Get the lines in a file and put into a string
    	while (getline(UptimeFile, uptime))
    	{
      		//remove everything after space
     		 std::string strTime = uptime.substr(0, uptime.find(" ", 0));

      		//Output the time turing has been up in seconds
      		std::cout << "3. Turing has been open for " << strTime << " seconds." << std::endl;

      		//convert string to int
      		int uptimeTime =  std::stoi(strTime);

     	 	int uptimeDays = uptimeTime / (24 * 3600); 
      		uptimeTime = uptimeTime % (24 * 3600);
     		int uptimeHours = uptimeTime / 3600;
      		uptimeTime %= 3600;
      		int uptimeMinutes = uptimeTime / 60; 
      		uptimeTime %= 60;
      		int uptimeSeconds = uptimeTime; 

      		//Output in days, hours, minutes, and seconds how long turing has been up
      		std::cout << "4. That time is equivalent to " << uptimeDays << " days, " << uptimeHours << " hours, " << 
	      	uptimeMinutes << " minutes, " << uptimeSeconds << " seconds." << std::endl << std::endl;
    	}
}
else
{
	//unable to open file error
    	std::cerr << "ERROR: unable to open file /proc/uptime" << std::endl;
}

UptimeFile.close();

std::cout << "C. Questions about processor 0:" << std::endl;
std::string cpuinfo2; //string to hold the the text in the cpuinfo file
std::ifstream CPUInfoFile2("/proc/cpuinfo"); 

bool trigger = false; //set to true when we hit processor 0
std::string processor = "-1"; //the number of the current processor

if (CPUInfoFile2.is_open())
{
	//Get the lines in a file and put into a string
    	while (getline(CPUInfoFile2, cpuinfo2))
   	{
      		if (cpuinfo2.find("processor") != std::string::npos)
      		{
			//set the processor to 0
        		processor = cpuinfo2.substr(cpuinfo2.find(":") + 2);
      		}

      		//set tru if processor is 0
      		if (processor == "0")
      		{
       			trigger = true;
      		}

     		 //enter if loop if true
      		if (trigger == true)
      		{
       			//If a line is empty, exit loop
        		if (cpuinfo2.empty())
        		{
          			break;
        		}

        		//If a line has vendor_id
        		if (cpuinfo2.find("vendor_id") != std::string::npos)
        		{
          			std::cout << "1. The vendor of processor 0 is" << cpuinfo2.substr(cpuinfo2.find(":") + 1) << "." << std::endl;
        		}

        		//If a line has model name
        		if (cpuinfo2.find("model name") != std::string::npos)
        		{
          			std::cout << "2. The model name of processor 0 is" << cpuinfo2.substr(cpuinfo2.find(":") + 1) << "." << std::endl;
        		}

        		//If a line has address sizes
        		if (cpuinfo2.find("address sizes") != std::string::npos)
        		{
          			std::string physical = cpuinfo2.substr(cpuinfo2.find(":") + 1);
	  			physical = physical.substr(0, physical.find(",", 0)); //Cuts out everything after the "," in the string (the virtual address)

	  			//Output phsycial address size of processor 0
          			std::cout << "3. The physical address size of processor 0 is" << physical << "." << std::endl;

		  		std::cout << "4. The virtual address size of processor 0 is" << cpuinfo2.substr(cpuinfo2.find(",") + 1) << "." << std::endl << std::endl;;
        		}
      		}
    	}
}
else
{
	//unable to open file error
	std::cerr << "ERROR: unable to open file /proc/cpuinfo" << std::endl;
}

CPUInfoFile2.close();

std::cout << "D. Questions about processor 5:" << std::endl;
std::string stat; //string to hold the text in the stat file
std::ifstream StatFile("/proc/stat"); //open the file that contains the stat info
std::string strUser, strSystem, strIdle; //strings to hold the values from the file
int intUser, intSystem, intIdle; //integers to hold the converted strings

if (StatFile.is_open())
{
	//Get the lines in a file and put into a string
    	while (getline(StatFile, stat))
    	{
      		//If line has cpu5
      		if (stat.find("cpu5") != std::string::npos)
      		{
			std::string arr[10]; //create an array for each value
			int i = 0; //counter to store each word 
			std::stringstream ssin(stat); //split each value in the line

		//While there are values in the line
		while (ssin.good() && i < 10)
		{
         		//Put each value in defferent spots
          		ssin >> arr[i];
	  		i++;
		}

		strUser = arr[1]; 
        	intUser = std::stoi(strUser); 
		intUser *= .01; 

		strSystem = arr[3]; 
		intSystem = std::stoi(strSystem); 
		intSystem *= .01; 

		strIdle = arr[4]; 
		intIdle = std::stoi(strIdle); 
		intIdle *= .01; 

        	std::cout << "1. Processor 5 has been in user mode for " << intUser << " seconds." << std::endl;
        	std::cout << "2. Processor 5 has been in system mode for " << intSystem << " seconds." << std::endl;

		//Output idle time processor 5
        	std::cout << "3. Processor 5 has been idle for " << intIdle << " seconds." << std::endl;

        	int idleDays = intIdle / (24 * 3600); 
        	intIdle = intIdle % (24 * 3600);
        	int idleHours = intIdle / 3600; 
        	intIdle %= 3600;
        	int idleMinutes = intIdle / 60; 
        	intIdle %= 60;
        	int idleSeconds = intIdle; 

		//Output idle time for processor 5 in days, hours, minutes, and seconds
        	std::cout << "4. That time is equivalent to " << idleDays << " days, " << idleHours << " hours, " << 
	      	idleMinutes << " minutes, " << idleSeconds << " seconds." << std::endl << std::endl;
      		}
    	}
}
else
{
	//The unable to open error
	std::cerr << "ERROR: Unable to open file /proc/stat" << std::endl;
}
  
StatFile.close();

std::string swaps; 
std::ifstream SwapsFile("/proc/swaps"); //open the file with swaps info

if (SwapsFile.is_open())
{
	//Get the lines in a file and put into a string
    	while (getline(SwapsFile, swaps))
   	{
        	//if the line does not have filename
     		if (swaps.find("/dev/md2") != std::string::npos)
      		{
       			std::string strSize = swaps.substr(swaps.find("partition") + 10); 
			strSize = strSize.substr(0, strSize.find("\t", 0)); 
			double size = std::stoi(strSize);
			size *= 0.000976562; //Convert it from kb to mb

			//Output the size of turing
        		std::cout << "E. The size of turing's swap device in MB is " << size << "." << std::endl;
      		}
	}
}
else
{
	//The unable to open error
    	std::cerr << "ERROR: unable to open file /proc/swaps" << std::endl;
}
SwapsFile.close();
return 0;
}
