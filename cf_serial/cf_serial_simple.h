#ifndef CF_SERIAL_SIMPLE_H
#define CF_SERIAL_SIMPLE_H

#include <boost/asio.hpp>
#include <memory>
#include <string>

// An extremely simplified serial communication class with timeout support
// Typical use is string communication with Arduino
class cf_serial_simple {
public:
   typedef boost::asio::io_service    boost_io_service;
   typedef boost::asio::serial_port   boost_serial_port;

   // open serial port, keep it open for as long as object lives
   cf_serial_simple(const std::string& port, size_t baud_rate = 9600);
   virtual ~cf_serial_simple();

   // read string onto 'text' from serial port with timeout in milliseconds
   // return false if timeout exceeded. Suggest timeout 1200ms
   bool read(std::string& text, size_t timeout_ms);

   // write string to serial port
   void write_string(const std::string& text);

   // read string from serial port
   // this is a blocking read and will hang forever if no data received
   std::string read_some();

private:
   boost_io_service                   m_ios;   // io service must exist during communication
   std::shared_ptr<boost_serial_port> m_sp;    // the serial port
};

#endif // CF_SERIAL_SIMPLE_H
