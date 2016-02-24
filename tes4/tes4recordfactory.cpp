#include "tes4/tes4recordfactory.h"
#include "tes4/record/tes4recordgeneric.h"
#include "tes4/record/tes4recordgroup.h"
#include "tes4/record/tes4recordignore.h"
#include "tes4/subrecord/tes4subrecordhedr.h"
#include "tes4/subrecord/tes4subrecordsinglestring.h"
#include "tes4/subrecord/tes4subrecordsingleulong.h"
#include "tes4/subrecord/tes4subrecordsingleushort.h"
#include "tes4/subrecord/tes4subrecordsinglefloat.h"
#include "tes4/subrecord/tes4subrecordmnam.h"
#include "tes4/subrecord/tes4subrecordsingleuchar.h"
#include "tes4/subrecord/tes4subrecorddoublelong.h"
#include "tes4/subrecord/tes4subrecorddoubleshort.h"
#include "tes4/subrecord/tes4subrecordxclccell.h"
#include "tes4/subrecord/tes4subrecordflags.h"
#include "tes4/subrecord/tes4subrecordvnml.h"
#include "tes4/subrecord/tes4subrecordvhgt.h"
#include "tes4/subrecord/tes4subrecordatxt.h"
#include "tes4/subrecord/tes4subrecordbtxt.h"
#include "tes4/subrecord/tes4subrecordvtxt.h"
#include "tes4/subrecord/tes4subrecordobnd.h"
#include "tes4/subrecord/tes4subrecorddodt.h"
#include "tes4/subrecord/tes4subrecordonam.h"
#include "tes4/subrecord/tes4subrecorddoubleuchar.h"
#include "tes4/subrecord/tes4subrecorddoublefloat.h"
#include "tes4/subrecord/tes4subrecordignore.h"
#include "tes4/subrecord/tes4subrecordxxxx.h"
#include "tes4/subrecord/tes4subrecordtriplefloat.h"

//-----------------------------------------------------------------------------
Tes4RecordFactory::Tes4RecordFactory()
{
	registerClasses();
}

//-----------------------------------------------------------------------------
Tes4RecordFactory::~Tes4RecordFactory()
{}

//-----------------------------------------------------------------------------
void Tes4RecordFactory::registerClasses()
{
	Tes4RecordGeneric::registerClass(_mapKnownRecords);
	Tes4RecordGroup::registerClass(_mapKnownRecords);
	Tes4RecordIgnore::registerClass(_mapKnownRecords);
	
	Tes4SubRecordHEDR::registerClass(_mapKnownRecords);
	Tes4SubRecordMNAM::registerClass(_mapKnownRecords);
	Tes4SubRecordVNML::registerClass(_mapKnownRecords);
	Tes4SubRecordVHGT::registerClass(_mapKnownRecords);
	Tes4SubRecordATXT::registerClass(_mapKnownRecords);
	Tes4SubRecordBTXT::registerClass(_mapKnownRecords);
	Tes4SubRecordVTXT::registerClass(_mapKnownRecords);
	Tes4SubRecordOBND::registerClass(_mapKnownRecords);
	Tes4SubRecordDODT::registerClass(_mapKnownRecords);
	Tes4SubRecordONAM::registerClass(_mapKnownRecords);
	Tes4SubRecordXXXX::registerClass(_mapKnownRecords);
	Tes4SubRecordXCLCCELL::registerClass(_mapKnownRecords);
	Tes4SubRecordSingleFloat::registerClass(_mapKnownRecords);
	Tes4SubRecordSingleString::registerClass(_mapKnownRecords);
	Tes4SubRecordSingleULong::registerClass(_mapKnownRecords);
	Tes4SubRecordSingleUShort::registerClass(_mapKnownRecords);
	Tes4SubRecordSingleUChar::registerClass(_mapKnownRecords);
	Tes4SubRecordDoubleLong::registerClass(_mapKnownRecords);
	Tes4SubRecordDoubleUChar::registerClass(_mapKnownRecords);
	Tes4SubRecordDoubleFloat::registerClass(_mapKnownRecords);
	Tes4SubRecordDoubleShort::registerClass(_mapKnownRecords);
	Tes4SubRecordTripleFloat::registerClass(_mapKnownRecords);
	Tes4SubRecordFlags::registerClass(_mapKnownRecords);
	Tes4SubRecordIgnore::registerClass(_mapKnownRecords);

}

//-----------------------------------------------------------------------------
TesRecordBase* Tes4RecordFactory::create(string const& token, string const& tokenMain, unsigned char* pBuffer)
{
	//  check for Record
	if (_mapKnownRecords.count(token) > 0) {
		return _mapKnownRecords[token](pBuffer);
	}

	//  check for SubRecord
	if (_mapKnownRecords.count(tokenMain+token) > 0) {
		return _mapKnownRecords[tokenMain+token](pBuffer);
	}

	return nullptr;
}
