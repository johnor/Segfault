#ifndef SLAVE_CONNECTION_H_
#define SLAVE_CONNECTION_H_

typedef enum
{
  CONNECTION_SUCCESS,
  CONNECTION_FAILURE,
  CONNECTION_TIMEOUT
} ConnectionResult;


ConnectionResult connectToSlave(void);



#endif
