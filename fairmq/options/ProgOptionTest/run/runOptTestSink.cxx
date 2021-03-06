/* 
 * File:   runOptTestSink.cxx
 * Author: winckler
 *
 * Created on June 10, 2015, 3:34 PM
 */

#include <cstdlib>
/// std
#include <iostream>
#include <string>

/// boost
#include "boost/program_options.hpp"

/// FairRoot/FairMQ
#include "FairMQLogger.h"
#include "FairMQParser.h"
#include "FairMQProgOptions.h"


//////////////////////////////////////////////////////////////
/// main
//////////////////////////////////////////////////////////////
using namespace std;
using namespace FairMQParser;
using namespace boost::program_options;
int main(int argc, char** argv)
{
    FairMQProgOptions config;
    try
    {
        // //////////////////////////////////////////////////////////////
        // define key specific to the BenchmarkSampler in options_description
        
        int eventSize;
        int eventRate;
        int ioThreads;
        options_description Sink_options("Sink options");
        Sink_options.add_options()
            ("io-threads", value<int>(&ioThreads)->default_value(1),    "Number of I/O threads");
        
        // and add it to cmdline option of FairMQProgOptions
        config.AddToCmdLineOptions(Sink_options);

        // //////////////////////////////////////////////////////////////
        // Parse command line options and store in variable map
        if(config.ParseAll(argc,argv,true))
            return 0;
        
        // keys defined in FairMQProgOptions
        string filename=config.GetValue<string>("config-json-file");
        string deviceID=config.GetValue<string>("id");

        // //////////////////////////////////////////////////////////////
        // User defined parsing method. 
        
        config.UserParser<JSON>(filename,deviceID);
        FairMQMap channels=config.GetFairMQMap();
        //set device here
        
    }
    catch (exception& e)
    {
        LOG(error) << e.what();
        LOG(info) << "Command line options are the following : ";
        config.PrintHelp();
        return 1;
    }
    return 0;
}






