####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#Fall 10MC, 7TeV ======9
#Data, 7TeV ======10

sampleConf = 9


#####################################################################################
#################################################
import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonJetSelection")
process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

test=False
import PhotonSusyAnalysis.SelectionAnalyzer.selectionanalyzer_multi_cfg as baseConfig
doSkimming=True
doAnalysis=True
noKinematicPresel=False
PUDistributionMC=cms.vdouble(0)
baseConfig.getProcessFor(sampleConf,process,test,doSkimming,doAnalysis,"",noKinematicPresel,PUDistributionMC,0)



process.weightProducer.Method=cms.string("Constant")
process.weightProducer.XS = cms.double(123.9)
process.weightProducer.NumberEvts = cms.double(6321549)
process.weightProducer.Lumi = cms.double(100.)

process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	      '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/FEA6599D-7F9D-E011-87D1-00A0D1EC3950.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/FCDDF4DE-779D-E011-81EC-0015178C4A68.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/FCA37C9E-749D-E011-B637-001D0967CF1D.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/FC032DC1-739D-E011-9162-001D0967CEF0.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/F0D50E82-799D-E011-88A9-00A0D1EE2990.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/ECB223ED-709D-E011-9938-0015178C4C18.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/EA0C7110-769D-E011-ABCB-00A0D1EC3950.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/E4A1AEC4-779D-E011-A329-001D0967CEF0.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/E2C741FE-6D9D-E011-B1BB-001D0967D6C0.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/DA1C53AC-7A9D-E011-A174-00A0D1EC3950.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/D2CD3DFA-6B9D-E011-816E-001D0967DA71.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/D23D46B8-9E9D-E011-94FE-0026B94E288C.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/CC39A806-769D-E011-85CD-00A0D1EE2990.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/C8360FF3-749D-E011-A0DE-00151796D5AC.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/C251D4A8-719D-E011-A8DE-00151796C1A8.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/B63B5930-829D-E011-941C-00A0D1EC3950.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/B092D680-779D-E011-BADB-00A0D1EE8EB4.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/A6ED5D77-809D-E011-A895-00A0D1EC3950.root',
        '/store/mc/Summer11/GVJets_7TeV-madgraph/AODSIM/PU_S4_START42_V11-v1/0000/A65B20DA-799D-E011-ACC1-00151796D860.root',
	    
	)
		                   
	)

			
