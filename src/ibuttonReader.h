/*
 * iButtonReader.h
 *
 *  Created on: 11-Nov-2019 
 *      Author: Guillaume
 */

#ifndef IBUTTONREADER_H_
#define IBUTTONREADER_H_

#include <Arduino.h>
#include <OneWire.h>

#define IBUTTONREADER_DEFAULT_READ_TIMEOUT 200 //200msec
#define ID_LENGTH 8 //8 bytes (64 bits UID)

class ibuttonReader : public OneWire
{
public:
    ibuttonReader(uint8_t oneWirePin)
        :OneWire(oneWirePin), m_readFrequency(IBUTTONREADER_DEFAULT_READ_TIMEOUT) {

        }
     ibuttonReader()
        :OneWire(), m_readFrequency(IBUTTONREADER_DEFAULT_READ_TIMEOUT) {

        }
    void setReadFrequency(int frequency);
    void loop();
    bool available();
    void getHexId(String &id);
    String m_status="";
    

private:
    unsigned long m_lastSearch=0;
    bool m_available=false;
    unsigned long m_readFrequency;
    byte m_addr[ID_LENGTH];
};

#endif /* IBUTTONREADER_H_ */
