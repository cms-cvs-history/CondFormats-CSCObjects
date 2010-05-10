/*----------------------------------------------------------------------

Toy EDProducers and EDProducts for testing purposes only.

----------------------------------------------------------------------*/

#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CondFormats/CSCObjects/interface/CSCCables.h"
#include "CondFormats/DataRecord/interface/CSCCablesRcd.h"
//#include "CondFormats/CSCObjects/interface/CSCMapItem.h"
//#include "OnlineDB/CSCCondDB/interface/CSCCableRead.h"

using namespace std;

namespace edmtest
{
  class CSCReadCablesValuesAnalyzer : public edm::EDAnalyzer
  {
  public:
    explicit  CSCReadCablesValuesAnalyzer(edm::ParameterSet const& p) 
    { }
    explicit  CSCReadCablesValuesAnalyzer(int i) 
    { }
    virtual ~ CSCReadCablesValuesAnalyzer() { }
    virtual void analyze(const edm::Event& e, const edm::EventSetup& c);
  private:
  };
  
  void
   CSCReadCablesValuesAnalyzer::analyze(const edm::Event& e, const edm::EventSetup& context)
  {
    using namespace edm::eventsetup;
    // Context is not used.
    std::cout <<" I AM IN RUN NUMBER "<<e.id().run() <<std::endl;
    std::cout <<" ---EVENT NUMBER "<<e.id().event() <<std::endl;
    edm::ESHandle<CSCCables> pCables;
    context.get<CSCCablesRcd>().get(pCables);

    const CSCCables* myCables=pCables.product();

    //    std::map<int,CSCMapItem::MapItem>::const_iterator it;
    std::vector<CSCCables::Cables>::const_iterator it;
    
    int count=0;
    for( it=myCables->cables.begin();it!=myCables->cables.end(); ++it ){
      count=count+1;
      //      std::cout<<"Key: ddu_crate*10+ddu_input "<<it->first<<std::endl;

      std::cout<<count<<") ";
      std::cout<<it->chamber_label<<"  ";
      std::cout<<it->cfeb_length<<"  ";
      std::cout<<it->cfeb_rev<<"  ";
      std::cout<<it->alct_length<<"  ";
      std::cout<<it->cfeb_tmb_skew_delay<<"  ";
      std::cout<<it->cfeb_timing_corr<<"  "<<std::endl;
    }
  }
  DEFINE_FWK_MODULE(CSCReadCablesValuesAnalyzer);
}
