# alias for sample, see file sample.conf for possible settings
sample = "local"

# reading the configuration file
from ConfigParser import RawConfigParser
conf = RawConfigParser()
conf.read( "sample.conf" )
isData = conf.getboolean( sample, "isData")


# define process
import FWCore.ParameterSet.Config as cms
process = cms.Process("PhotonJetSelection")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring( conf.get( sample, "filename" ) ) )


import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cff as baseConfig
baseConfig.getProcessFor( process, isData )

# set global tag
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = cms.string( conf.get( sample, "tag") )

lumi = 100.

#Set weight method:
if not isData:
	process.weightProducer.Method = cms.string( conf.get( sample, "wMethod" ) )
	process.weightProducer.XS = cms.double( conf.getfloat( sample, "xs" ) )
	process.weightProducer.NumberEvts = cms.double( conf.getint( sample, "nEvents" ) )
	process.weightProducer.Lumi = cms.double( lumi )



def writeConfigToFile( process, filename = "combination_cfg.py" ):
	"""Combines all python configuration files to one single file

	@type process: cms process
	@param process: the actual running cmssw process
	@type filename: string
	@param filename: filename of the output file, which will be created ( default combination_cfg.py )
	"""
	process.schedule = cms.Schedule( process.selectionSequence, process.p, process.eAll )
	open( filename, "w" ).write( process.dumpPython() )

#writeConfigToFile( process )
