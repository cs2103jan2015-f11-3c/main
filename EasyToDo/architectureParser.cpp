#include "architectureParser.h"
#include "architectureLogic.h"
#include "architectureStorage.h"
#include "architectureInputFeedback.h"

std::string architectureParser::_startHour;
std::string architectureParser::_startMin;
std::string architectureParser::_endHour;
std::string architectureParser::_endMin;
std::string architectureParser::_dateDay;
std::string architectureParser::_dateMonth;
std::string architectureParser::_taskDesc;
std::string architectureParser::_taskType;
std::string architectureParser::_newContent;
std::string architectureParser::_taskID;
std::string architectureParser::_command;
std::string architectureParser::_userInput;
std::vector<std:: string> architectureParser::addTaskDetails;

void architectureParser::pushUserInput(std:: string userInput) {
	_userInput = userInput; // recieve command and content input from gui
	tokenizeCommand();

	architectureInputFeedback::addToMasterInputList(userInput);
}

void architectureParser::tokenizeCommand() {

	std::string tokenizeContent = _userInput;
	size_t commandFirst = 0;
	size_t commandEnd = tokenizeContent.find_first_of(" ");
	addTaskDetails.clear(); // always clear the vector before pushing anything into it

	if(commandEnd != std:: string::npos) {
		_command = tokenizeContent.substr(commandFirst,commandEnd);
		commandFirst = commandEnd + 1;
		std::string restOfContent = tokenizeContent.substr(commandFirst);
		addTaskDetails.push_back(_command);
		//push the command into vector and send the rest of the content for tokenizing
		checkCommand(_command,restOfContent);
	} else {
		addTaskDetails.push_back(_userInput);
		tokenizeUndo(_userInput);
	}
}

void architectureParser::tokenizeInvalid() {

	addTaskDetails.push_back("invalid");

	addEmptyString(9); // this functions pushes back empty string into vector
}

void architectureParser::checkCommand(std::string _command,std::string restOfContent) {
		
	if(_command == "add") { 
		tokenizeAddEmptyStringFirst(restOfContent);
	} else if(_command == "delete") {
		tokenizeDeleteOrDone(restOfContent);
	} else if(_command == "update") {
		tokenizeUpdate(restOfContent);
	} else if(_command == "clear") {
		tokenizeClear(restOfContent);
	} else if(_command == "done") {
		tokenizeDeleteOrDone(restOfContent);
	} else if(_command == "save") {
		tokenizeSave(restOfContent);
	} else {
		tokenizeInvalid();
	}

}

void architectureParser::tokenizeAddEmptyStringFirst(std::string tokenizeContent) {

	_taskType = "";
	addTaskDetails.push_back(_taskType);
	_taskID = "";
	addTaskDetails.push_back(_taskID);

	tokenizeAdd(tokenizeContent);
}

void architectureParser::tokenizeAdd(std:: string tokenizeContent) {
	_newContent = tokenizeContent;

	size_t taskFirst = 0;
	size_t taskLast = _newContent.find(" on ");
	// this function will differentiate what type of task it is adding; dealine,timed etc.
	if(taskLast!=std::string::npos){
		tokenizeDeadlineTask(tokenizeContent,taskLast); //tokenizes the task description
	} else {
		taskLast = _newContent.find(" by ");

		if(taskLast!=std::string::npos){
			tokenizeDeadlineTask(tokenizeContent,taskLast);	
		} else {
			taskLast = _newContent.find(" from ");

			if(taskLast!=std::string::npos){
				tokenizeTimedTask(tokenizeContent,taskLast);	
			} else {
				taskLast = _newContent.npos;
				_taskDesc = _newContent.substr(taskFirst,taskLast);
				addTaskDetails.push_back(_taskDesc);

				addEmptyString(6);

				return;
			}
		}
	}
}
void architectureParser::tokenizeDeadlineTask(std::string toknizeContent, size_t taskLast) {
	
		size_t taskFirst = 0;

		_taskDesc = toknizeContent.substr(taskFirst,taskLast);
		addTaskDetails.push_back(_taskDesc);

		taskFirst = taskLast+4;
		taskLast = toknizeContent.npos;
		std::string dateContent = toknizeContent.substr(taskFirst,taskLast);
		tokenizeDateDay(dateContent);

}

void architectureParser::tokenizeTimedTask(std::string toknizeContent, size_t taskLast) {

		size_t taskFirst = 0;

		_taskDesc = toknizeContent.substr(taskFirst,taskLast);
		addTaskDetails.push_back(_taskDesc);

		taskFirst = taskLast+6;
		taskLast = toknizeContent.npos;
		std::string dateContent = toknizeContent.substr(taskFirst,taskLast);
		tokenizeDateDay(dateContent);
}

void architectureParser::tokenizeUpdate(std::string tokenizeContent) {

	std::string _newContent = tokenizeContent; 
	size_t taskFirst = _newContent.find_first_not_of(" ");
	size_t taskLast = _newContent.find_first_of(" ",taskFirst);
	_taskType = _newContent.substr(taskFirst,taskLast); // tokenize tasktype which is either today upcoming or misc

	addTaskDetails.push_back(_taskType);

	taskFirst = taskLast + 1;
	std::string taskIDContent =_newContent.substr(taskFirst);
	taskFirst = taskIDContent.find_first_not_of(" ");
	taskLast = taskIDContent.find_first_of(" ");
	_taskID = taskIDContent.substr(taskFirst,taskLast);

	addTaskDetails.push_back(_taskID);

	taskFirst = taskLast+1;
	taskLast = taskIDContent.npos;
	std::string updateContent = taskIDContent.substr(taskFirst,taskLast);

	tokenizeAdd(updateContent); //sends the rest of the content to be tokenize by the adding function again
}

void architectureParser::tokenizeDeleteOrDone(std::string tokenizeContent) {

	std::string _newContent = tokenizeContent;
	size_t taskFirst = _newContent.find_first_not_of(" ");
	size_t taskLast = _newContent.find_first_of(" ",taskFirst);
	_taskType = _newContent.substr(taskFirst,taskLast);
	addTaskDetails.push_back(_taskType);

	taskFirst = taskLast + 1;
	std::string taskIDContent =_newContent.substr(taskFirst);
	taskFirst = taskIDContent.find_first_not_of(" ");
	_taskID = taskIDContent.substr(taskFirst);
	addTaskDetails.push_back(_taskID);

	addEmptyString(7);
}

void architectureParser::tokenizeClear(std::string tokenizeContent) {

	std::string _newContent = tokenizeContent;
	
	size_t taskFirst = _newContent.find_first_not_of(" ");
	_taskType = _newContent.substr(taskFirst);
	
	addTaskDetails.push_back(_taskType);

	addEmptyString(8);
}

void architectureParser::tokenizeUndo(std::string tokenizeContent) {

	addEmptyString(9);

}


void architectureParser::tokenizeDateDay(std::string tokenizeContent){

	std::string remainingContent = tokenizeContent;
	size_t taskFirst = 0;
	size_t taskLast = remainingContent.find_first_of(" ");
	_dateDay = remainingContent.substr(taskFirst,taskLast);	//tokenizing the day
	addTaskDetails.push_back(_dateDay);

	taskFirst = taskLast+1;
	_newContent = remainingContent.substr(taskFirst);

	tokenizeDateMonth(_newContent);
}

void architectureParser::tokenizeDateMonth(std::string tokenizeContent){

	std::string remainingContent = tokenizeContent;
	size_t taskFirst = 0;
	size_t taskLast = remainingContent.find_first_of(" ");
	_dateMonth = remainingContent.substr(taskFirst,taskLast);//tokenizing the month
	
	taskFirst = taskLast+1;
	addTaskDetails.push_back(_dateMonth);
	_newContent = remainingContent.substr(taskFirst);

	checkTimedOrDeadline(_newContent);
}



void architectureParser::checkTimedOrDeadline(std::string tokenizeContent){

	size_t taskLast = tokenizeContent.find("to");
	if(taskLast!=std::string::npos)	//differentiate between timed and deadline task
		tokenizeTimedTime(tokenizeContent);
	else
	{
		size_t taskLast = tokenizeContent.find("-");
		if(taskLast!=std::string::npos)
			tokenizeTimedTime(tokenizeContent);
		else
			tokenizeDeadlineTime(tokenizeContent);
	}
}


void architectureParser::tokenizeDeadlineTime(std::string tokenizeContent){

	std::string remainingContent = tokenizeContent;
	size_t taskFirst = 0;
	size_t taskLast = remainingContent.find_first_of(":");
	
	_startHour = remainingContent.substr(taskFirst,taskLast);	//tokenizing the time part of deadline tasks
	addTaskDetails.push_back(_startHour);

	taskFirst = taskLast+1;
	_startMin = remainingContent.substr(taskFirst);
	addTaskDetails.push_back(_startMin);
	
	_endHour = "";
	addTaskDetails.push_back(_endHour);
	_endMin = "";
	addTaskDetails.push_back(_endHour);

	architectureLogic::pushParserVector(addTaskDetails);
}

void architectureParser::tokenizeTimedTime(std::string tokenizeContent){
	//tokenizing the time part of timed tasks
	std::string remainingContent = tokenizeContent;
	size_t taskFirst = 0;
	size_t taskLast = remainingContent.find_first_of(":");
	_startHour = remainingContent.substr(taskFirst,taskLast);
	addTaskDetails.push_back(_startHour);

	taskFirst = taskLast+1;
	taskLast = remainingContent.find_first_of(" ");
	taskLast = taskLast-3;
	_startMin = remainingContent.substr(taskFirst,taskLast);

	addTaskDetails.push_back(_startMin);

	taskFirst = remainingContent.find_last_of(" ");
	taskFirst = taskFirst+1;
	std::string endTime = remainingContent.substr(taskFirst);
	taskFirst = 0;
	taskLast = endTime.find_first_of(":");
	_endHour = endTime.substr(taskFirst,taskLast);
	
	addTaskDetails.push_back(_endHour);

	taskFirst = taskLast+1;
	_endMin = endTime.substr(taskFirst);
	
	addTaskDetails.push_back(_endMin);

	architectureLogic::pushParserVector(addTaskDetails);
}

void architectureParser::addEmptyString(int count) {
	//this functions pushes empty string into the vector
	for( int i = count; i!=0; i--) {

		addTaskDetails.push_back("");

	}
	architectureLogic::pushParserVector(addTaskDetails);
}

void architectureParser::tokenizeSave(std::string tokenizeContent) {

	std::string _newContent = tokenizeContent;

	size_t taskFirst = _newContent.find_last_of(" ") - 1;
	size_t taskLast = _newContent.find_last_not_of(" ");
	_taskID = _newContent.substr(taskFirst,taskLast); // filename
	_newContent.erase(taskFirst, taskLast);

	taskFirst = _newContent.find_first_not_of(" ");
	taskLast = _newContent.find_last_not_of(" ") + 1;
	_taskType = _newContent.substr(taskFirst, taskLast); // file Directory
	addTaskDetails.push_back(_taskType); 
	addTaskDetails.push_back(_taskID);

	addEmptyString(7);
}
