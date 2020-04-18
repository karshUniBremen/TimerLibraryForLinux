/*
 * bTimer.h
 *
 *  Created on: Apr 17, 2020
 *      Author: karsh
 */

#ifndef BTIMER_H_
#define BTIMER_H_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <pthread.h>
#include <mutex>

class btimer{
public:
	typedef std::function<void(void* arg)> cb_t;
	typedef enum{
		ONE_SHOT=0,
		PERIODIC=1
	}mode_e;

public:
	btimer(const btimer& ref) = delete;
	btimer& operator=(const btimer& ref) = delete;

	btimer(mode_e mode,cb_t callback=NULL,void* callback_arg=NULL);
	~btimer();
	bool start(uint64_t msInterval);
	bool stop();
	bool isExpired();
	bool registerCB(cb_t callback,void* callback_arg);


private:
	mode_e mode;
	boost::asio::deadline_timer* handle;
	boost::asio::io_service* service;
	uint64_t duration;//changing
	cb_t notifyCB;
	void* notifyCBarg;
	pthread_t threadID;
	std::mutex resProtect;
	bool timerExpiry;

private:
	void setExpired(bool ind);
	bool restart();

	friend void* serviceTaskLoop(void* arg);
	friend void timeoutCB(btimer* arg);

};



#endif /* BTIMER_H_ */
