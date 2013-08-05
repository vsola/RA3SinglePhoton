####################################CONFIGURATION##################################
###################################################################################

###SAMPLE###
#Fall 10MC, 7TeV ======9
#Data, 7TeV ======10

sampleConf = 10


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

process.photon2011_HLT_data.HLTPaths=cms.vstring('HLT_Photon75_CaloIdVL_v*')

process.source = cms.Source("PoolSource",
	    	fileNames = cms.untracked.vstring(
	    '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/506/C028594D-9986-E011-B2FD-00304879BAB2.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/506/62E3D6F2-AF86-E011-9860-0030487C2B86.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/487/FC266D33-9786-E011-9C5E-001D09F282F5.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/487/4E6A6963-9986-E011-9697-0030487CD700.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/487/40FA95D8-BB86-E011-B910-001D09F26509.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/486/42ECFE28-8286-E011-A9D7-003048F1C58C.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/484/386FBFC1-3786-E011-A417-003048F118D4.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/423/484EE7EA-C085-E011-9867-0030487CAEAC.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/421/B0980AA3-9785-E011-89DE-000423D94908.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/415/F438EEC5-6B85-E011-9246-001D09F23A34.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/415/E2227BE9-AB85-E011-B832-000423D33970.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/415/CC44F27F-6585-E011-B401-0030487CD13A.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/415/CA588056-7185-E011-8B3F-001D09F28D4A.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/415/ACB6B658-A385-E011-8402-001D09F24399.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/415/960A9DE0-AB85-E011-8BDF-0030487C90EE.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/415/8EA1BE75-AC85-E011-9C77-001D09F24493.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/415/8689D377-9C85-E011-AE6A-003048F024FA.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/415/62FA95B5-A485-E011-9402-001D09F295FB.root',
        '/store/data/Run2011A/PhotonHad/AOD/PromptReco-v4/000/165/415/56D4B46C-9285-E011-929D-0019B9F730D2.root',
	    	
		'/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/F8B586ED-617B-E011-83D6-00215E93C4A8.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/F6FE7879-657B-E011-A54F-00215E221158.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/F0B3284E-4B7B-E011-ACFD-00215E2223EE.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/E6940CAE-447B-E011-A6A9-00215E21D9A8.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/E44F1C7A-557B-E011-A29B-00215E21DCA2.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/E266B7B2-447B-E011-A34F-00215E21D64E.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/E20CB364-557B-E011-B819-E41F1318180C.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/DE616D61-527B-E011-B515-00215E21DD0E.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/D8A9BF1C-447B-E011-844E-00215E21D570.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/D6AD9E7D-527B-E011-917D-00215E21D570.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/D6535E51-4B7B-E011-93F1-E41F131815C0.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/D27F7670-4B7B-E011-B4C7-00215E93EDA4.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/D05132FB-617B-E011-9401-E41F1318099C.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/D03A067B-527B-E011-B236-00215E21DA50.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/CC1DB833-547B-E011-B4C2-00215E222850.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/C6980E5D-4B7B-E011-AE73-00215E21DAC2.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/C0E5146A-4B7B-E011-9573-00215E22237C.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/BE668864-637B-E011-B006-00215E21DD26.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/BE1C66C8-617B-E011-9B9B-00215E93C4A8.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/BC249C39-4B7B-E011-A536-00215E93F080.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/BAD7486E-637B-E011-9756-00215E21D91E.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/BAA63052-4B7B-E011-96A7-00215E21DB88.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/B8305472-527B-E011-84AB-E41F13181A40.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/B4AECA56-4B7B-E011-B903-00215E222244.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/B4464ED7-FE7B-E011-883B-00215E22086A.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/B40F52F8-617B-E011-9F8F-E41F131812AC.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/A8EF6BB9-447B-E011-B000-00215E21DA50.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/A4FDEC77-4B7B-E011-AC65-00215E21D86A.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/A4854368-637B-E011-AA47-E41F131817F8.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/A4747DB9-E87B-E011-86B0-00215E21D8D6.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/A0457C55-637B-E011-9B3C-E41F13181050.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/A02E2DC2-617B-E011-B7BF-00215E21D540.root',
        '/store/data/Run2011A/PhotonHad/AOD/May10ReReco-v1/0000/A01F6AED-1B7C-E011-AB15-00215E21D540.root',
		
	    	
	
	)
		                   
	)


