#ifndef CF_READER_H
#define CF_READER_H

#include <boost/asio.hpp>
#include <string>
#include <vector>

// A simple serial port blocking reader with timeout
class cf_reader {
public:

	// Constructs a blocking reader, pass in an open serial_port and a timeout in milliseconds.
   cf_reader(boost::asio::io_service& ios, boost::asio::serial_port& port, size_t timeout_ms);
   virtual ~cf_reader();

   // read a string of max length
   bool read_string(std::string& text, size_t max_len=1024);

   // read integer (untested)
   bool read(int& value);

   // read float (untested)
   bool read(float& value);

protected:
   // read from port into buffer
   bool read_buffer(size_t max_len);

   // Called when an async read completes or has been cancelled
   void read_complete(const boost::system::error_code& error, size_t bytes_transferred);

   // Called when the timer's deadline expires.
   void time_out(const boost::system::error_code& error);

private:
   boost::asio::io_service&    m_ios;                // reference to io_service used by serial port
   boost::asio::serial_port&   m_port;               // reference to serial port
   size_t                      m_timeout_ms;         // timeout in milliseconds
   boost::asio::deadline_timer m_timer;              // timer handling timouts
   std::vector<char>           m_buffer;             // data receive buffer
   size_t                      m_bytes_transferred;  // number of bytes transferred
};

#endif // CF_READER_H
