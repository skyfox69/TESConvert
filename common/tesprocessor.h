#ifndef	TESPROCESSOR_H
#define	TESPROCESSOR_H

#include "common/tesparser.h"
#include <map>

//-----------------------------------------------------------------------------
class TesProcessor
{
	private:
		static	TesProcessor*				_pInstance;
		TesParser							_parser;
		map<string, vector<TesRecordBase*>>	_mapRecords;

		//  prepare token structures
		virtual	bool						parse(string const fileName);
		virtual	bool						prepareRecordMap();
		virtual	bool						prepareRecordMapRecursive(vector<TesRecordBase*>& collection);

		//  dump parsed data
		virtual	void						dumpTokensByName();
		virtual	void						dumpTokensBySequence();
		virtual	bool						dumpVclrMap(string const fileName);
		virtual	bool						dumpVhgtMap(string const fileName);
		virtual	bool						dumpVtexMap(string const fileName);
		
		//  convert to TES files
		virtual	bool						convertToTES4(string const fileName);
		
	protected:
											TesProcessor();

	public:
		virtual								~TesProcessor();
		
		static	TesProcessor*				getInstance();

		virtual	bool						process(int argc, char** argv, int offset);
};
#endif  /* TESPROCESSOR_H */
