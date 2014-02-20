// GTest & unit test Headers
#include <gtest/gtest.h>
#include "MainUnitTestC.h"

// STL Headers`
#include <map>
#include <string>

// MAMA Headers
#include "mama/middleware.h"
#include "mama/msg.h"

class MamaEnumTestsC : public ::testing::Test
{
protected:
   MamaEnumTestsC();
   virtual ~MamaEnumTestsC();

   virtual void SetUp(void);

   virtual void TearDown(void);

   typedef std::pair <std::string,     std::string>    PayloadNameLib;
   typedef std::map  <mamaPayloadType, PayloadNameLib> MamaPayloadMapType;
   typedef std::map  <mamaMiddleware,  std::string>    MamaMiddlewareMapType;

private:   
   void CreateTestData();

};

MamaEnumTestsC::MamaEnumTestsC() : testing::Test() 
{
   CreateTestData();
}


MamaEnumTestsC::~MamaEnumTestsC() {}

void
MamaEnumTestsC::SetUp()
{
}

void
MamaEnumTestsC::TearDown()
{
}

void
MamaEnumTestsC::CreateTestData()
{
}

TEST_F (MamaEnumTestsC, testPayloadStringConversions)
{
    MamaPayloadMapType testData;
    testData[MAMA_PAYLOAD_ACTIV]      = PayloadNameLib ("activ",      "activmsg");
    testData[MAMA_PAYLOAD_AVIS]       = PayloadNameLib ("AVIS",       "avismsg");
    testData[MAMA_PAYLOAD_EXEGY]      = PayloadNameLib ("EXEGY",      "exegymsg");
    testData[MAMA_PAYLOAD_FAST]       = PayloadNameLib ("FAST",       "fastmsg");
    testData[MAMA_PAYLOAD_IBMWFO]     = PayloadNameLib ("ibmwfo",     "ibmwfomsg");
    testData[MAMA_PAYLOAD_QPID]       = PayloadNameLib ("QPID",       "qpidmsg");
    testData[MAMA_PAYLOAD_RAI]        = PayloadNameLib ("rai",        "raimsg");
    testData[MAMA_PAYLOAD_SOLACE]     = PayloadNameLib ("solacemsg",  "solacemsg");
    testData[MAMA_PAYLOAD_TIBRV]      = PayloadNameLib ("TIBRV",      "tibrvmsg");
    testData[MAMA_PAYLOAD_TICK42BLP]  = PayloadNameLib ("TICK42BLP",  "tick42blpmsg");
    testData[MAMA_PAYLOAD_TICK42RMDS] = PayloadNameLib ("TICK42RMDS", "tick42rmdsmsg");
    testData[MAMA_PAYLOAD_UMS]        = PayloadNameLib ("UMS",        "umsmsg");
    testData[MAMA_PAYLOAD_VULCAN]     = PayloadNameLib ("Vulcan",     "vulcanmsg");
    testData[MAMA_PAYLOAD_WOMBAT_MSG] = PayloadNameLib ("WombatMsg",  "wmsg");
    testData[MAMA_PAYLOAD_V5]         = PayloadNameLib ("V5",         "wcachemsg");
    testData[MAMA_PAYLOAD_UNKNOWN]    = PayloadNameLib ("unknown",    "");

    MamaPayloadMapType::iterator itr;

    for(itr = testData.begin(); itr != testData.end(); ++itr) {
    
       mamaPayloadType payload = itr->first;
       PayloadNameLib& namelib = itr->second;
       const char*     name    = namelib.first.c_str();
       const char*     library = namelib.second.c_str();

       // Override for unknown, mama returns NULL for unknown library (so that
       // it prevents libraries from trying to load libmamaunknownmsg).
       if (MAMA_PAYLOAD_UNKNOWN == payload)
       {
           library = NULL;
       }

       // Check name/payload conversion
       EXPECT_STREQ(name, mamaPayload_convertToString (payload));
       EXPECT_EQ((char)payload, (char)mamaPayload_convertFromString (name));

       // Check library/payload conversion
       EXPECT_STREQ(library, mamaPayload_convertToLibString (payload));
       EXPECT_EQ((char)payload, (char)mamaPayload_convertFromLibString (library));
    }
}

TEST_F (MamaEnumTestsC, testMiddlewareStringConversions)
{
    MamaMiddlewareMapType testData;
    testData[MAMA_MIDDLEWARE_WMW]        = "wmw";
    testData[MAMA_MIDDLEWARE_LBM]        = "lbm";
    testData[MAMA_MIDDLEWARE_TIBRV]      = "tibrv";
    testData[MAMA_MIDDLEWARE_AVIS]       = "AVIS";
    testData[MAMA_MIDDLEWARE_TICK42BLP]  = "tick42blp";
    testData[MAMA_MIDDLEWARE_SOLACE]     = "SOLACE";
    testData[MAMA_MIDDLEWARE_RAI]        = "rai";
    testData[MAMA_MIDDLEWARE_QPID]       = "QPID";
    testData[MAMA_MIDDLEWARE_EXEGY]      = "exegy";
    testData[MAMA_MIDDLEWARE_IBMWFO]     = "ibmwfo";
    testData[MAMA_MIDDLEWARE_ACTIV]      = "activ";
    testData[MAMA_MIDDLEWARE_TICK42RMDS] = "tick42rmds";
    testData[MAMA_MIDDLEWARE_UMS]        = "ums";
    testData[MAMA_MIDDLEWARE_VULCAN]     = "vulcan";
    testData[MAMA_MIDDLEWARE_UNKNOWN]    = "unknown";
    MamaMiddlewareMapType::iterator itr;

    for(itr = testData.begin(); itr != testData.end(); ++itr) {
    
       mamaMiddleware middleware = itr->first;
       const char*    name       = itr->second.c_str();

       EXPECT_STREQ(name, mamaMiddleware_convertToString (middleware));
       EXPECT_EQ((char)middleware, (char)mamaMiddleware_convertFromString (name));
    }
}

