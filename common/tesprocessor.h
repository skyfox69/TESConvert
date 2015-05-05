#ifndef	TESPROCESSOR_H
#define	TESPROCESSOR_H

#include "common/tesparser.h"
#include <map>

//-----------------------------------------------------------------------------
class TesProcessor
{
	private:
		TesParser							_parser;
		map<string, vector<TesRecordBase*>>	_mapRecords;
		
		virtual	bool						prepareRecordMap();

	public:
											TesProcessor();
		virtual								~TesProcessor();
		
		virtual	bool						parse(string const fileName);
		virtual	void						dumpTokensByName();
		virtual	void						dumpTokensBySequence();
		virtual	bool						dumpVclrMap(string const fileName);
		virtual	bool						dumpVhgtMap(string const fileName);
};
#endif  /* TESPROCESSOR_H */
