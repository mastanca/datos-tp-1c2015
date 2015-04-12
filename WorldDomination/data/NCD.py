'''
Created on 12/4/2015

@author: mastanca
'''

import pylzma
import os
import pandas as pd
import backports.lzma as lzma

def NCDpylzma(review1,review2):
    concatenatedReviews = review1 + review2
    cConcatenadosCompressed = len(pylzma.compress(concatenatedReviews))
    cReview1Compressed = len(pylzma.compress(review1))
    cReview2Compressed = len(pylzma.compress(review2))
      
    if cReview1Compressed<cReview2Compressed:
        minC = cReview1Compressed
        maxC = cReview2Compressed
    else:
        minC = cReview2Compressed
        maxC = cReview1Compressed
    
    return ((float(cConcatenadosCompressed)-float(minC))/float(maxC))

def NCDbackportlzma(review1,review2):
    concatenatedReviews = review1 + review2
    cConcatenadosCompressed = len(lzma.compress(concatenatedReviews))
    cReview1Compressed = len(lzma.compress(review1))
    cReview2Compressed = len(lzma.compress(review2))
      
    if cReview1Compressed<cReview2Compressed:
        minC = cReview1Compressed
        maxC = cReview2Compressed
    else:
        minC = cReview2Compressed
        maxC = cReview1Compressed
    
    return ((float(cConcatenadosCompressed)-float(minC))/float(maxC))

if __name__ == '__main__':
    myFileDir = os.path.dirname(os.getcwd()) + "/data/clean_labeled_train_data.csv"
    
    trainData = pd.read_csv(myFileDir, header=0, delimiter=",", quoting=3)
    
    num_reviews = len(trainData["review"])
    
    # Testing
    sentiment1 = trainData["sentiment"][0]
    sentiment2 = trainData["sentiment"][9001]
    
    print "Sentimient review 1: " + str(sentiment1) 
    print "Sentimient review 2: " + str(sentiment2) + "\n"
    
    review1 = trainData["review"][0]
    review2 = trainData["review"][9001]
    
    ncdpylzma = NCDpylzma(review1, review2)
    
    ncdbplzma = NCDbackportlzma(review1, review2)
    
    # Using backportlzma obtains better results
    # print ("NCD using pylzma: " + str(ncdpylzma))
    
    print ("NCD using backport.lzma: " + str(ncdbplzma))
    