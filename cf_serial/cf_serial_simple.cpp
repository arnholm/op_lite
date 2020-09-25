#include "cf_serial_simple.h"
#include "cf_reader.h"
#include <iostream>
using namespace std;



cf_serial_simple::cf_serial_simple(const std::string& port, size_t baud_rate)
{
   m_sp = std::make_shared<boost_serial_port>(m_ios,port);
   m_sp->set_option(boost_serial_port::baud_rate((unsigned int)baud_rate));
}

cf_serial_simple::~cf_serial_simple()
{
   m_sp->close();
}


void cf_serial_simple::write_string(const std::string& text)
{
   m_sp->write_some(boost::asio::buffer(text));
}

std::string cf_serial_simple::read_some()
{
  // code example
  // https://stackoverflow.com/questions/23519309/serial-port-communication-c-linux

   std::string retval;

   const size_t bufsiz=1024;
   char tmpbuf[bufsiz];
   size_t len = m_sp->read_some(boost::asio::buffer(tmpbuf,bufsiz));
   if(len > 0) {
      retval = std::string(tmpbuf,len);
   }

   return retval;
}


bool cf_serial_simple::read(std::string& text, size_t timeout_ms)
{
   // read with timeout
   cf_reader reader(m_ios,*m_sp,timeout_ms);
   return reader.read_string(text);
}

