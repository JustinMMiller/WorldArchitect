#include "RWLock.h"

RWLock::RWLock()
	: shared()
	, readerQ()
	, writerQ()
	, active_readers(0)
	, waiting_writers(0)
	, active_writers(0)
{ }

void RWLock::ReadLock()
{
	unique_lock<mutex>lk(shared);
	while( waiting_writers != 0 )
	{
		readerQ.wait(lk);
	}
	++active_readers;
	lk.unlock();
}

void RWLock::ReadUnlock()
{
	unique_lock<mutex> lk(shared);
	--active_readers;
	lk.unlock();
	writerQ.notify_one();
}

void RWLock::WriteLock()
{
	unique_lock<mutex> lk(shared);
	++waiting_writers;
	while(active_readers != 0 || active_writers != 0)
	{
		writerQ.wait(lk);
	}
	++active_writers;
	lk.unlock();
}

void RWLock::WriteUnlock()
{
	unique_lock<mutex> lk(shared);
	--waiting_writers;
	--active_writers;
	if(waiting_writers > 0)
	{
		writerQ.notify_one();
	}
	else
	{
		readerQ.notify_all();
	}
	lk.unlock();
}
