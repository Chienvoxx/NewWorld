#include <utils.h>


/*	get_file_contents()
This was the fastest of all methods tested at
http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
*/
std::string readTextFile(const char *filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

int checkErrorBits(const std::ifstream &f) {
	int stop = 0;
	if (f.eof()) {
		perror("stream eofbit. error state");
		// EOF after std::getline() is not the criterion to stop processing data:
		// In case there is data between the last delimiter and EOF,
		// getline() extracts it and sets the eofbit.
		stop = 0;
	}
	if (f.fail()) {
		perror("stream failbit (or badbit). error state");
		stop = 1;
	}
	if (f.bad()) {
		perror("stream badbit. error state");
		stop = 1;
	}
	return stop;
}

std::vector<std::string> readTextFileLines(const char *filename)
{	// vector of strings, each containing one line of a given file.
	// https://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing-correctly-with-badbit-failbit-eofbit-and-perror/
	std::vector<std::string> lines;

	std::string line;
	int getlinecount = 1;

	std::ifstream f(filename);
	perror("error state after ifstream constructor");
	if (!f.is_open())
		perror("is_open() returned false. error state");
	else
	{
		// check error bits once before first getline
		checkErrorBits(f);

		while (1) {
			getline(f, line);
			if (checkErrorBits(f)) {
				std::cout << "checkErrorBits(ifstream) failed!!* skip operation on data, break loop" << std::endl;
				break;
			}
			// This is the actual operation on the data obtained and we want to
			// protect it from errors during the last IO operation on the stream
			std::cout << "data line " << getlinecount << ": " << line << std::endl;
			getlinecount++;
		}
	}
	f.close();

	return lines;
}



std::string findFileOrThrow(const std::string &strBasename)
{
	return std::string();
}