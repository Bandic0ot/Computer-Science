/*
 * reader-writer-monitor.h
 *
 * Sean Robson-Kullman
 * 11182480
 * skr519
 *
 * Matthew Muulenga
 * 11144528
 * mam558
 *
 */


/*
 * reader-writer-monitor
 */

/*
 * StartRead()
 * pre: nothing
 * post:
 *
 * will wait if busy,
 * prints number of readers to the consol.
 * signals OKtoRead
 *
 * return: nothing
 */
void StartRead();


/*
 * StopRead()
 * pre: nothing
 * post:
 *
 * prints number of readers to the consol.
 * Signals OKtoWrite when readers == 0
 *
 * return: nothing
 */
void StopRead();


/*
 * StartWrite()
 * pre: nothing
 * post:
 *
 * wait if readers > 0
 * sets states is busy
 * signals OKtoWrite
 *
 * return: nothing
 */
void StartWrite();


/*
 * StopWrite()
 * pre: nothing
 * post:
 *
 * sets is not busy
 * signals OKtoRead
 *
 * return: nothing
 */
void StopWrite();







