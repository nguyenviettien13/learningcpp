#include <fstream>
#include <iostream>
#include <string>
#include "stdio.h"


std::string  getOneLine(char arr[], int startpoint, int endpoint);
void main(void)
{
	std::ifstream		inputfile("c://users//nguyenviettien//desktop//test1.txt", std::ios::in | std::ios::binary);//
	if (inputfile.is_open())
	{
		int					filecount = 1;
		std::streampos		position = 0;
		position = inputfile.tellg();
		std::cout << "Position of File" << position << std::endl;
		int					maxfilesize = 800000;
		char *				buffer = NULL;
		int					buffersize = 5000;
		int					bucketcount = int(maxfilesize) / buffersize;
		int					sizeoffile = 0;
		std::string              sep = "---\r";
		char                threebyte[] = { 239, 187, 191, 0, '\b' };
		while (!inputfile.eof())
		{
			std::ofstream outputfile;
			char subfilename[20];
			_itoa_s(filecount, subfilename, 10);
			strcat_s(subfilename, ".txt");
			outputfile.open(subfilename, std::ios::out);
			if (filecount != 1)
			{
				outputfile << std::string(threebyte);
			}
			std::cout << "opening file " << subfilename << std::endl;
			buffer = new char[buffersize];


			for (int i = 0; i < bucketcount; i++)
			{
				std::cout << "copying block " << i << std::endl;
				if (!inputfile.eof())
				{
					inputfile.read(buffer, buffersize);
					outputfile << buffer;
				}
				else
				{
					outputfile.close();
					break;
				}
			}

			sizeoffile = bucketcount * buffersize;
			std::string line;
			bool createdNewFile = false;
			while (true)
			{
				if (inputfile.eof())
				{
					break;
				}
				else
				{
					inputfile.read(buffer, buffersize);
					int pointStartOfLine = 0;
					int pointFinishOfLine = 0;
					for (int i = 0; i < buffersize; i++)
					{
						if (buffer[i] == '\n')
						{
							pointFinishOfLine = i;

							line = getOneLine(buffer, pointStartOfLine, pointFinishOfLine);
							sizeoffile += (pointFinishOfLine - pointStartOfLine + 1);
							pointStartOfLine = pointFinishOfLine + 1;
							outputfile << std::string(line);
							outputfile << "\n";
							if (line.compare(sep) == 0)
							{
								if (sizeoffile > maxfilesize)
								{
									outputfile.close();
									position = inputfile.tellg();
									std::cout << "Position of File" << position << std::endl;

									inputfile.seekg((pointStartOfLine - buffersize - 1), std::ios_base::cur);
									position = inputfile.tellg();
									std::cout << "After seek file:.................." << std::endl;
									std::cout << "Position of File" << position << std::endl;
									system("pause");
									createdNewFile = true;
									break;
								}
							}
						}
					}
					if (!createdNewFile)
					{
						int i = pointStartOfLine;
						while (i < buffersize)
						{
							outputfile << buffer[i];
							std::cout << buffer[i];
							i++;
						}
					}
				}
				if (createdNewFile)
				{
					break;
				}
			}
			std::cout << "created file : " << subfilename << std::endl;
			std::system("pause");
			filecount += 2;
		}
		delete[] buffer;
	}
	else
	{
		std::cout << "could not open file\n";
	}
}
std::string getOneLine(char arr[], int startpoint, int endpoint) {
	std::cout << "start at: " << startpoint << " && end at: " << endpoint << std::endl;
	char result[5000];
	for (int i = startpoint; i <= endpoint; i++)
	{
		int index = i - startpoint;
		result[index] = arr[i];
	}
	std::cout << "endpoint:" << endpoint << "startpoint: " << startpoint << std::endl;
	result[endpoint - startpoint] = '\0';
	std::string strResult = std::string(result);
	return strResult;
}