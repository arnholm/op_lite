#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
using namespace std;

// wxWidgets
#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>
#include <wx/string.h>   // wxString
#include <wx/cmdline.h>  // command line parser
typedef map<wxString,wxString> CmdLineMap;    // CmdLineMap

#include "op_demo.h"

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
//   kind              shortName         longName           description                           parameterType          flag(s)
  { wxCMD_LINE_SWITCH, wxT_2("h"),       wxT_2("help"),     wxT_2("command line parameter help"), wxCMD_LINE_VAL_NONE,   wxCMD_LINE_OPTION_HELP },
  { wxCMD_LINE_PARAM,  wxT_2("db_path"), wxT_2("db_path"),  wxT_2("<db_path>"),                   wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },
  { wxCMD_LINE_SWITCH, wxT_2("c"),       wxT_2("c"),        wxT_2("create new database"),         wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("d"),       wxT_2("d"),        wxT_2("delete Triangle in database"), wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_NONE,   wxT_2(""),        wxT_2(""),         wxT_2(""),                            wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  }
};

// helper function for command line parameters
void ParserToMap(wxCmdLineParser& parser, CmdLineMap& cmdMap)
{
   size_t pcount = sizeof(cmdLineDesc)/sizeof(wxCmdLineEntryDesc) - 1;
   for(size_t i=0; i<pcount; i++) {
      wxString pname = cmdLineDesc[i].longName;
      if(cmdLineDesc[i].kind == wxCMD_LINE_PARAM) {
         cmdMap.insert(make_pair(pname,parser.GetParam(0)));
      }
      else {
         // switch or option, mush check if present
         if(parser.Found(pname)) {
            wxString pvalue;
            cmdMap.insert(make_pair(pname,pvalue));
         }
      }
   }
}

int main(int argc, char **argv)
{
   // initialise wxWidgets library
   wxInitializer initializer(argc,argv);

   // parse command line
   wxCmdLineParser parser(cmdLineDesc);
   parser.SetSwitchChars(wxT("-"));
   parser.SetCmdLine(argc,argv);
   if(parser.Parse() != 0) {
      // command line parameter error
      return 1;
   }
   CmdLineMap cmdMap;
   ParserToMap(parser,cmdMap);

   // get the command line parameters
   string db_path    = cmdMap["db_path"].ToStdString();
   bool   db_create  = cmdMap.find("c") != cmdMap.end();
   bool   del_tri    = cmdMap.find("d") != cmdMap.end();

   try {
      op_demo::init();

      if(db_create) {
         // create a new database
         op_demo::create_database(db_path);
      }
      else {

         // read an existing database
         op_demo::read_database(db_path,del_tri);
      }
   }
   catch( exception& e) {

      // something unexpected happened
      cout << "op_demo::Exception: " << e.what() << endl;
   }

   return 0;
}



