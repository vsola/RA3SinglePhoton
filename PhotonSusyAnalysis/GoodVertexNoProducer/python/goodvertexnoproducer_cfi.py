import FWCore.ParameterSet.Config as cms

oneGoodVertexNoProducer = cms.EDProducer('GoodVertexNoProducer',
           vertexCollection = cms.InputTag('offlinePrimaryVertices'),
           minimumNDOF = cms.uint32(4) ,
           maxAbsZ = cms.double(24),   
           maxd0 = cms.double(2)       
)
