/*
Owner: Uri Naor
Date: Feb 29, 2024
*/

#include <stddef.h> /* size_t */
#include <unistd.h> /* getpid() */

#include "uid.h"

const ilrd_uid_t bad_uid = {0, (pid_t)-1, (time_t)-1};

/******************** FUNCTIONS ********************/
ilrd_uid_t UIDGenerate(void)
{
	ilrd_uid_t uid;
	static size_t count = 1;
	
	uid.time = time(NULL);
	if ((time_t)-1 == uid.time)
	{
		return bad_uid;
	}
	
	/* used atomic built-in to make uid generation thread-safe */
	uid.counter = __sync_fetch_and_add(&count, 1);
	uid.pid = getpid();
	
	return uid;
}

int UIDIsEqual(ilrd_uid_t one, ilrd_uid_t other)
{

	return ((one.counter == other.counter) && (one.pid == other.pid) && 
		   (one.time == other.time));
}
