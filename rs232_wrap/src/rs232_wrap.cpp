#include "rs232.h"
#include "rs232_wrap.h"
#include "DaveUtil.h"

RS232_Wrap::RS232_Wrap(){};

RS232_Wrap::RS232_Wrap(std::string comport_Name, int comport_Baud, std::string comport_Config){
    Connect(comport_Name, comport_Baud, comport_Config);
}

int RS232_Wrap::Connect(std::string comport_Name, int comport_Baud, std::string comport_Config){
    comport_Number = RS232_GetPortnr(comport_Name.c_str());
    return RS232_OpenComport(comport_Number, comport_Baud, comport_Config.c_str());
}

RS232_Wrap::~RS232_Wrap(){
    RS232_CloseComport(comport_Number);
}

int RS232_Wrap::Send_Message(std::vector<uint8_t> message){
    return RS232_SendBuf(comport_Number, message.data(), message.size());
}

std::vector<uint8_t> RS232_Wrap::Receive_Message(unsigned int num_Bytes_To_Read, unsigned int polling_Period_ms, unsigned int timeout_ms){
    int bytes_Recvd = 0;
    std::vector<unsigned char> ser_Buf(num_Bytes_To_Read);
    std::vector<uint8_t> message;
    unsigned int millisecond_Timer = 0;
    message.reserve(num_Bytes_To_Read);
    do{
        bytes_Recvd = RS232_PollComport(comport_Number, ser_Buf.data(), num_Bytes_To_Read);
        // Keep track of bytes remaining to be read.
        num_Bytes_To_Read -= bytes_Recvd;
        for(int i=0; i < bytes_Recvd; i++){
            message.push_back(ser_Buf[i]);
        }

        MySleep(polling_Period_ms);
        millisecond_Timer += polling_Period_ms;

    } while ((millisecond_Timer > timeout_ms) |
            (num_Bytes_To_Read == message.size()));

    return message;
}

std::vector<uint8_t> RS232_Wrap::Send_Message_Get_Reply(std::vector<uint8_t> message, unsigned int num_Bytes_To_Read, unsigned int polling_Period_ms, unsigned int timeout_ms){
    Send_Message(message);
    return Receive_Message(num_Bytes_To_Read, polling_Period_ms, timeout_ms);
}
