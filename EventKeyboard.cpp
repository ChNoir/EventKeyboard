#include "EventKeyboard.h"

EventKeyboard::EventKeyboard(){
	run();
}

EventKeyboard::~EventKeyboard(){
	stop();
}

void EventKeyboard::run(){
	mt.lock();
	getRun = true;
	th = new std::thread(&EventKeyboard::RunFun, this);
	mt.unlock();
}

void EventKeyboard::stop(){
	mt.lock();
	getRun = false;
	th->join();
	delete th;
	mt.unlock();
}

int EventKeyboard::getKey(){
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	mt.lock();
	if (keyChange) {

		mt.unlock();
		keyChange = false;
		return key; 
		
	}
	mt.unlock();
	return -1;
	
}

int EventKeyboard::getKey(std::string WhiteList, bool inverseur){
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	if (inverseur) {
		/// WhiteList

		mt.lock();
		if (keyChange) {
			
			for (int i = 0; i < WhiteList.size(); i++) {
				if ((char)key == WhiteList[i]) {

					mt.unlock();
					keyChange = false;
					return key;

				}
			}
			mt.unlock();
			return -1;
		}
		mt.unlock();
		return -1;
	}
	else
	{
		/// BlackList

		mt.lock();
		if (keyChange) {
			bool tamp = false;
			for (int i = 0; i < WhiteList.size(); i++) {
				if ((char)key == WhiteList[i]) {

					tamp = true;

				}
			}
			if (tamp) {
				mt.unlock();
				keyChange = false;
				return key;
			}
			else
			{
				mt.unlock();
				return -1;
			}	
		}
		mt.unlock();
		return -1;
	}
}

bool EventKeyboard::Eventkey(int conditions){
	if (getKey() == conditions) {
		return true;
	}
	return false ;
}




void EventKeyboard::RunFun(){
	while (getRun)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if (_kbhit()) {

			key = _getch();
			if (key == 224 || key == 0) {
				key = _getch();
			}

			mt.lock();
			keyChange = true;
			mt.unlock();
		}
	}
}


bool EventKeyboard::keyChange = false;
bool EventKeyboard::getRun = false;
int EventKeyboard::key = 0;

std::thread* EventKeyboard::th;
std::mutex EventKeyboard::mt;

