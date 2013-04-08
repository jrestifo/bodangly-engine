/*
 * Log.h
 *
 *  Created on: Apr 7, 2013
 *      Author: demian
 */

#ifndef LOG_H_
#define LOG_H_
#include <fstream>
#include <String>
class Log {
public:
	virtual ~Log();

	static Log* instance();

	bool initLog(const std::string& sPath);
	bool changeFile(const std::string& sNewPath);

	void stopStderr();
	void startStderr();

	void stopStdout();
	void startStdout();

	void postError(const std::string& sError);
	void postMsg(const std::string& sMsg);

private:
	Log();
	Log(Log const&){};
	Log& operator=(Log const&){};
	static Log* _pInstance;

	//Determines whether to print to stderr or not
	bool _bStderr;
	bool _bStdout;

	std::ofstream _fLog;
};

#endif /* LOG_H_ */
