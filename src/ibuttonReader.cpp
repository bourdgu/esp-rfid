#include "ibuttonReader.h"
#include <OneWire.h>

void ibuttonReader::setReadFrequency(int frequency)
{
    m_readFrequency = frequency;
}

bool ibuttonReader::available()
{
        return m_available;
}

void ibuttonReader::loop()
{
    unsigned long _now = millis();
    if (_now > (m_lastSearch + m_readFrequency))
    {
        m_lastSearch = _now;
        if (!search(m_addr))
        {
            reset_search();
            return;
        }
        if (OneWire::crc8(m_addr, 7) != m_addr[7]) //check CRC on 8th byte
        {
            m_status = F("CRC invalid");
            return;
        }

        if (m_addr[0] != 0x01)
        {
            m_status = F("not DS1990A");
            return;
        }
        m_available=true;
        m_status = F("ok");
        reset();
    }
}

void ibuttonReader::getHexId(String &uid)
{
    if (m_available)
    {
        uid="";
        for (uint8_t i = 0; i < ID_LENGTH; i++)
        {
            uid+=String(m_addr[i], HEX);
        }
        m_available = false;
    }
}
