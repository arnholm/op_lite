#include "cf_reader.h"
#include <boost/bind.hpp>

#include <iostream>
using namespace std;

// this code is modified based on
// https://www.ridgesolutions.ie/index.php/2012/12/13/boost-c-read-from-serial-port-with-timeout-example/

cf_reader::cf_reader(boost::asio::io_service& ios, boost::asio::serial_port& port, size_t timeout_ms)
: m_ios(ios)
, m_port(port)
, m_timeout_ms(timeout_ms)
, m_timer(m_ios)
{
   m_ios.reset();
}

cf_reader::~cf_reader()
{
   // reset port after reading
   m_ios.reset();
}

bool cf_reader::read_buffer(size_t max_len)
{
      m_bytes_transferred = 0;

   // prepare the receive buffer
   m_buffer.clear();
   m_buffer.resize(max_len);

   // start async io
   boost::asio::async_read(m_port, boost::asio::buffer(&m_buffer[0],max_len),
   boost::bind(&cf_reader::read_complete,this,boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

   // Setup a deadline time to implement timeout.
   m_timer.expires_from_now(boost::posix_time::milliseconds(m_timeout_ms));
   m_timer.async_wait(boost::bind(&cf_reader::time_out,this, boost::asio::placeholders::error));

   // perform IO, this will return when read completed or timed out
   m_ios.run();

   // resize receive buffer and convert reply to string
   m_buffer.resize(m_bytes_transferred);

   return (m_buffer.size()>0);
}

bool cf_reader::read_string(std::string& text, size_t max_len)
{
   bool retval = read_buffer(max_len);
   text = std::string(m_buffer.begin(), m_buffer.end());
   return retval;
}

bool cf_reader::read(int& value)
{
   if(read_buffer(sizeof(value))) {

      // check this: is the byte order correct?
      memcpy(&value,&m_buffer[0],sizeof(value));
      return true;
   }
   return false;
}

bool cf_reader::read(float& value)
{
   if(read_buffer(sizeof(value))) {

      // check this: is the byte order correct?
      memcpy(&value,&m_buffer[0],sizeof(value));
      return true;
   }
   return false;
}

// Called when an async read completes or has been cancelled
void cf_reader::read_complete(const boost::system::error_code& error, size_t bytes_transferred)
{
   // set number of bytes transferred
   m_bytes_transferred = bytes_transferred;

   // Read has finished, so cancel the timer.
   m_timer.cancel();
}

// Called when the timer's deadline expires.
void cf_reader::time_out(const boost::system::error_code& error)
{

   // Was the timeout cancelled?
   if (error) {
      // yes
      return;
   }

   // no, we have timed out, so kill
   // the read operation
   // The read callback will be called
   // with an error
   m_bytes_transferred = 0;
   m_port.cancel();
}
