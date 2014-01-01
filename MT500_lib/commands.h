#ifndef COMMANDS_H
#define COMMANDS_H

#define SEND_IMAGE              0x00 // Command from server to client requesting an image
#define IMAGE_RESPONSE          0X01 // Response from client to server with image in the data field
#define SYNC_TIME               0x02 // Command from client to server requesting server time
#define TIME_RESPONSE           0x03 // Response from server to client with time in the data field
#define RESEND			0x04 // Bidirectional response asking for the sender to resend the previous message
#define REBOOT                  0x05 // Command from server to client initiating a reboot
#define SEND_CFG	        0x06 // Command from server to client requesting the current configuration
#define CFG_RESPONSE            0x07 // Command from client to server with configuration in the data field
#define CRC_MISMATCH            0xFF // Mismatch in CRC...returned from data protocol decode function

#endif // COMMANDS_H
