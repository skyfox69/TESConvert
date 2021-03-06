#ifndef	TESPROCESSOR_H
#define	TESPROCESSOR_H

#include "common/tesparser.h"
#include "common/util/verbosity.h"
#include <map>

class ITesProcessor;

//-----------------------------------------------------------------------------
class TesProcessor : protected Verbosity
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
		virtual	void						dumpTokensByName(string const token);
		virtual	void						dumpTokensBySequence();
		virtual	void						dumpTokensBySequenceAsXml();
		virtual	void						dumpUsedTokens();
		
		//  convert to TES files
		virtual	bool						convert(string const fileName, unsigned char const targetType, string const worldspace, ITesProcessor* pSubProcessor);
		
	protected:
											TesProcessor();

	public:
		virtual								~TesProcessor();
		
		static	TesProcessor*				getInstance();

		virtual	bool						process(int argc, char** argv, int offset);
};
#endif  /* TESPROCESSOR_H */
