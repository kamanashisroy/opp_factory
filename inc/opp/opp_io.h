/*
 * io_signal.h
 *
 *  Created on: Jul 1, 2011
 *      Author: ayaskanti
 */

#ifndef IO_SIGNAL_H_
#define IO_SIGNAL_H_

enum {
	IO_ACTION_READ = 128,
	IO_ACTION_WRITE,
	IO_ACTION_CLOSE,
	IO_ACTION_SET,
	IO_ACTION_GET,
	IO_ACTION_DATA_AVAILABLE,
	IO_ACTION_TRAFFIC_TX,
	IO_ACTION_TRAFFIC_RX,
};

#endif /* IO_SIGNAL_H_ */
