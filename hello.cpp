#include <boost/date_time/posix_time/posix_time.hpp>
#include <fstream>
#include <fastcgi++/request.hpp>
#include <fastcgi++/manager.hpp>

void error_log(const char* msg)
{
   using namespace std;
   using namespace boost;
   static ofstream error;
   if(!error.is_open())
   {
      error.open("/tmp/errlog", ios_base::out | ios_base::app);
      error.imbue(locale(error.getloc(), new posix_time::time_facet()));
   }
   error << '[' << posix_time::second_clock::local_time() << "] " << msg << endl;
}
class HelloWorld: public Fastcgipp::Request<char>
{
   bool response()
   {
    
      out << "Content-Type: text/html; charset=utf-8\r\n\r\n";
      out << "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8' />";
      out << "<title>fastcgi++: Hello World in UTF-8</title></head><body>";
      out << "Hello World<br />";
      out << "</body></html>";
      err << "Hello nginx error log";
      return true;
   }
};

int main()
{
   try
   {
      Fastcgipp::Manager<HelloWorld> fcgi;
      fcgi.handler();
   }
   catch(std::exception& e)
   {
      error_log(e.what());
   }
}
