#ifndef RS232_WRAP_H
#define RS232_WRAP_H

#include <string>
#include <vector>


class RS232_Wrap{
private:
    int comport_Number;
    int ser_Ret;

public:
    RS232_Wrap();
    RS232_Wrap(std::string comport_Name, int comport_Baud=9600, std::string comport_Config="8n1");
    ~RS232_Wrap();

    int Connect(std::string comport_Name, int comport_Baud=9600, std::string comport_Config="8n1");
    int Send_Message(std::vector<uint8_t> message);
    std::vector<uint8_t> Receive_Message(unsigned int num_Bytes_To_Read, unsigned int polling_Period_ms = 100, unsigned int timeout_ms = 100);
    std::vector<uint8_t> Send_Message_Get_Reply(std::vector<uint8_t> message, unsigned int num_Bytes_To_Read, unsigned int polling_Period_ms = 100, unsigned int timeout_ms = 100);

};

#endif // RS232_WRAP_H
