#include "CondCore/DBCommon/interface/DBWriter.h"
#include "CondCore/DBCommon/interface/DBSession.h"
#include "CondCore/DBCommon/interface/Exception.h"
#include "CondCore/DBCommon/interface/ServiceLoader.h"
#include "CondCore/DBCommon/interface/ConnectMode.h"
#include "CondCore/DBCommon/interface/MessageLevel.h"
#include "CondFormats/CSCObjects/interface/CSCPedestals.h"
#include "CondCore/IOVService/interface/IOV.h"
#include "CondCore/MetaDataService/interface/MetaData.h"
#include "FWCore/Framework/interface/IOVSyncValue.h"
#include <string>
#include <map>
#include <iostream>
int main(){
  cond::ServiceLoader* loader=new cond::ServiceLoader;
  ::putenv("CORAL_AUTH_USER=me");
  ::putenv("CORAL_AUTH_PASSWORD=mypass");
  loader->loadAuthenticationService( cond::Env );
  loader->loadMessageService( cond::Error );
  try{
    cond::DBSession* session1=new cond::DBSession(std::string("sqlite_file:csctest.db"));
    session1->setCatalog("file:mycsccatalog.xml");
    session1->connect(cond::ReadWriteCreate);
    cond::DBWriter pwriter(*session1, "CSCPedestals");
    cond::DBWriter iovwriter(*session1, "IOV");
    session1->startUpdateTransaction();
    cond::IOV* pediov=new cond::IOV;
    int nObj=3;
    for( int i=0; i<nObj; ++i){
      CSCPedestals* myped=new CSCPedestals;
      for( int iLayer=0; iLayer<5; ++iLayer){  //writing 5 layers
	std::vector<CSCPedestals::Item> mypedValue;
	for(int ichannel=0; ichannel<=80; ++ichannel){//80 channels
	  CSCPedestals::Item item;
	  item.ped=1.11*ichannel;//dummy algorithm
	  item.rms=1.12*ichannel;
	  mypedValue.push_back(item);
	}
	myped->pedestals.insert(std::make_pair(iLayer,mypedValue));
      }
      std::string mytok=pwriter.markWrite<CSCPedestals>(myped);
      pediov->iov.insert(std::make_pair(i+1,mytok)); 
    }
    std::string pediovToken=iovwriter.markWrite<cond::IOV>(pediov);  
    session1->commit();//commit all in one
    session1->disconnect();
    delete session1;
    cond::MetaData metadata_svc("sqlite_file:csctest.db",*loader);
    metadata_svc.connect();
    metadata_svc.addMapping("mycsctest", pediovToken);
    metadata_svc.disconnect();
  }catch(const cond::Exception& er){
    std::cout<<er.what()<<std::endl;
    delete loader;
    exit(-1);
  }catch(...){
    std::cout<<"Funny error"<<std::endl;
    delete loader;
    exit(-1);
  }
}
