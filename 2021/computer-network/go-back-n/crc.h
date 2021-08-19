#ifndef GO_BACK_N_CRC_H
#define GO_BACK_N_CRC_H

#include "frame.h"

int GetCRC(struct Frame *s, int flag);

int CheckCRC(struct Frame *s);

#endif //GO_BACK_N_CRC_H
