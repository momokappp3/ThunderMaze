#include "Timer.h"
#include "Dxlib.h"

Timer::Timer() {
	_startTime = 0;
	_startNum = 0;
	_nowNum = 0;

	_isStart = false;
	_isStop = false;
	_isEnd = false;
}

Timer::~Timer() {
}

void Timer::Process() {

	int nowTime = GetNowCount() - _startTime;
	int nowSecond = nowTime / 1000;
	int nowNum = _startNum - nowSecond;

	if (_nowNum != nowNum) {
		_nowNum = nowNum;

		if (_nowNum < 0) {
			_nowNum = 0;
		}

		if (_nowNum == 0) {
			_isEnd = true;
		}
	}
}

bool Timer::GetIsEnd() {
	return _isEnd;
}

void Timer::SetStartSeconds(int startNum) {

	_isStart = true;
	_isEnd = false;
	_isStop = false;

	_startNum = startNum;
	_nowNum = startNum;

	_startTime = GetNowCount();  //‹N“®‚µ‚Ä‚©‚ç‚Ç‚ê‚­‚ç‚¢‚½‚Á‚½‚©
}

void Timer::SetStartMinutes(int minutes, int seconds){

	_isStart = true;
	_isEnd = false;
	_isStop = false;

	_startNum = minutes * 60 + seconds;
	_nowNum = _startNum;

	_startTime = GetNowCount();  //‹N“®‚µ‚Ä‚©‚ç‚Ç‚ê‚­‚ç‚¢‚½‚Á‚½‚©
}

int Timer::GetNowTimeSeconds() {
	return _nowNum;
}

Point Timer:: GetNowTimeMinutes(){

	Point minutes;

	minutes.x = _nowNum / 60;
	minutes.y = _nowNum % 60 ;

	return minutes;
}