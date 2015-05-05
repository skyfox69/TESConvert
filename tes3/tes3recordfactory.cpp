#include "tes3/tes3recordfactory.h"
#include "tes3/record/tes3recordgeneric.h"
#include "tes3/record/tes3recordignore.h"
#include "tes3/subrecord/tes3subrecordhedr.h"
#include "tes3/subrecord/tes3subrecordsinglestring.h"
#include "tes3/subrecord/tes3subrecordsinglefloat.h"
#include "tes3/subrecord/tes3subrecordsingleulong.h"
#include "tes3/subrecord/tes3subrecordweat.h"
#include "tes3/subrecord/tes3subrecordcolorref.h"
#include "tes3/subrecord/tes3subrecordsnam.h"
#include "tes3/subrecord/tes3subrecorddatacell.h"
#include "tes3/subrecord/tes3subrecordintvland.h"
#include "tes3/subrecord/tes3subrecordvnml.h"
#include "tes3/subrecord/tes3subrecordvhgt.h"
#include "tes3/subrecord/tes3subrecordwnam.h"
#include "tes3/subrecord/tes3subrecordvtex.h"
#include "tes3/record/tes3recordgroup.h"
#include "tes3/subrecord/tes3subrecorddatafrmr.h"
#include "tes3/subrecord/tes3subrecordflags.h"
#include "tes3/subrecord/tes3subrecordambi.h"
#include "tes3/subrecord/tes3subrecordignore.h"
#include "tes3/subrecord/tes3subrecorddatates3.h"

//-----------------------------------------------------------------------------
Tes3RecordFactory::Tes3RecordFactory()
{
	registerClasses();
}

//-----------------------------------------------------------------------------
Tes3RecordFactory::~Tes3RecordFactory()
{}

//-----------------------------------------------------------------------------
void Tes3RecordFactory::registerClasses()
{
	Tes3RecordGeneric::registerClass(_mapKnownRecords);
	Tes3RecordIgnore::registerClass(_mapKnownRecords);
	Tes3RecordGroup::registerClass(_mapKnownRecords);
	
	Tes3SubRecordHEDR::registerClass(_mapKnownRecords);
	Tes3SubRecordWEAT::registerClass(_mapKnownRecords);
	Tes3SubRecordSNAM::registerClass(_mapKnownRecords);
	Tes3SubRecordVNML::registerClass(_mapKnownRecords);
	Tes3SubRecordVHGT::registerClass(_mapKnownRecords);
	Tes3SubRecordWNAM::registerClass(_mapKnownRecords);
	Tes3SubRecordVTEX::registerClass(_mapKnownRecords);
	Tes3SubRecordAMBI::registerClass(_mapKnownRecords);
	Tes3SubRecordSingleString::registerClass(_mapKnownRecords);
	Tes3SubRecordSingleFloat::registerClass(_mapKnownRecords);
	Tes3SubRecordSingleULong::registerClass(_mapKnownRecords);
	Tes3SubRecordColorRef::registerClass(_mapKnownRecords);
	Tes3SubRecordFlags::registerClass(_mapKnownRecords);
	Tes3SubRecordIgnore::registerClass(_mapKnownRecords);
	Tes3SubRecordDATACELL::registerClass(_mapKnownRecords);
	Tes3SubRecordINTVLAND::registerClass(_mapKnownRecords);
	Tes3SubRecordDATAFRMR::registerClass(_mapKnownRecords);
	Tes3SubRecordDATATES3::registerClass(_mapKnownRecords);
}

//-----------------------------------------------------------------------------
TesRecordBase* Tes3RecordFactory::create(string const& token, string const& tokenMain, unsigned char* pBuffer)
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