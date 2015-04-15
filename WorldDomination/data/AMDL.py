'''
Created on 15/4/2015

@author: mastanca
'''
import os.path
import pandas as pd
import backports.lzma as lzma
import sys
import time


def concatenateReviews(trainData,sentiment):
    concatenatedReviews = ""
    num_reviews = len(trainData["review"])
        
    # Takes half the total reviews for example, change to try diff results
    
    for x in xrange(0, num_reviews/2):  
        if (trainData["sentiment"][x] == sentiment ):
            concatenatedReviews = concatenatedReviews + trainData["review"][x]

    return concatenatedReviews


if __name__ == '__main__':
    
    start_time = time.time()
    
    myFileDir = os.path.dirname(os.getcwd()) + "/data/clean_labeled_train_data.csv"
    
    trainData = pd.read_csv(myFileDir, header=0, delimiter=",", quoting=3)
    
    # Concatenate all reviews according to their sentiment and compress each file
    
    print "Processing... \n"
    positiveConcat = concatenateReviews(trainData, sentiment=1)
    
    negativeConcat = concatenateReviews(trainData, sentiment=0)
    
    compressedPositiveConcat = lzma.compress(positiveConcat)
    
    compressedNegativeConcat = lzma.compress(negativeConcat)
    
    #######################################################
    #         USE THIS TO TEST A SINGLE REVIEW            #
    #######################################################
    
#     # Given a test review, append to each concatenation and compress
#     
#     reviewNumber = 1002 # CHANGE THIS TO CHANGE THE TEST REVIEW
#     
#     testReview = trainData["review"][reviewNumber]
#     print "Real sentiment of test review is: ", trainData["sentiment"][reviewNumber], "\n"
#     
#     # Concatenate test review with training reviews and compressing
#     testPositiveConcat = positiveConcat + testReview
#     
#     testNegativeConcat = negativeConcat + testReview
#     
#     compressedTestPositive = lzma.compress(testPositiveConcat)
#     
#     compressedTestNegative = lzma.compress(testNegativeConcat)
#     
#     # Calculate minimum compression distance
#     
#     positiveDiff = sys.getsizeof(compressedTestPositive) - sys.getsizeof(compressedPositiveConcat)
#     
#     negativeDiff = sys.getsizeof(compressedTestNegative) - sys.getsizeof(compressedNegativeConcat)
#     
#     if (positiveDiff<negativeDiff):
#         print "Estimated sentiment of test review is 1 (positive) \n"
#     else:
#         print "Estimated sentiment of test review is 0 (negative) \n"
    
    ###############################################################
    #  USE THIS TO PREDICT MULTIPLE REVIEWS AND GET A % OF HITS   #
    ###############################################################
    num_reviews = len(trainData["review"])
    hits = 0
    counter = 0
    
    # Define range
    begin = (num_reviews/2)+1
    end = (num_reviews/2)+11
    
    # Define variables to estimate time
    checkTime = True
    initialTime = time.time()
    
    
    # print "This may take a while... ETA:", 16*(end-begin), "seconds\n"
    for i in xrange(begin, end):
     
        testReview = trainData["review"][i]
        
#         if( (i+1)%10 == 0 ):
#             print "Processed %d of %d\n" % ( i+1-begin, end-begin ) 
                 
        # Concatenate test review with training reviews and compressing
        testPositiveConcat = positiveConcat + testReview
         
        testNegativeConcat = negativeConcat + testReview
         
        compressedTestPositive = lzma.compress(testPositiveConcat)
         
        compressedTestNegative = lzma.compress(testNegativeConcat)
         
        # Calculate minimum compression distance
         
        positiveDiff = sys.getsizeof(compressedTestPositive) - sys.getsizeof(compressedPositiveConcat)
         
        negativeDiff = sys.getsizeof(compressedTestNegative) - sys.getsizeof(compressedNegativeConcat)
         
        if (positiveDiff<negativeDiff):
            estimatedSentiment = 1
        else:
            estimatedSentiment = 0
        
        if estimatedSentiment == trainData["sentiment"][i]:
            hits += 1
        
        if checkTime:
            print "ETA:", int((time.time()-initialTime)*(end-begin+1)), "seconds \n"
            checkTime = False
            
        counter += 1
    
    # Get % of hits 
    print "Percentage of hits:", (float(hits)/counter)*100, "% \n"
    
    # Print execution time    
    print("--- %s seconds ---" % (time.time() - start_time))
    