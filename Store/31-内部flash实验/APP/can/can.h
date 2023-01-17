#ifndef __CAN_H__
#define __CAN_H__

#include "system.h"

#define CAN_RX0_INT_EANBLE  0

void CAN_Mode_Init(u8 t_sjw, u8 t_bs2, u8 t_bs1, u16 brp, u8 mode);
u8 CAN_Send_Msg(u8 *message, u8 len);
u8 CAN_REceive_Msg(u8 *buf);


#endif
