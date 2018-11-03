#ifndef RWLOCK_H
#define RWLOCK_H
#include<mutex>
#include<condition_variable>
using namespace std;
class RWLock
{
	private:
		mutex shared;
		condition_variable readerQ;
		condition_variable writerQ;
		int active_readers, waiting_writers, active_writers;
	public:
		RWLock();
		void ReadLock();
		void ReadUnlock();
		void WriteLock();
		void WriteUnlock();
};
#endif
