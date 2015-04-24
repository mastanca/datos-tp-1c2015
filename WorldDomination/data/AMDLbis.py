'''
Created on 15/4/2015

@author: mastanca
'''
import re
import os.path
import pandas as pd
import pylzma as lzma
import bz2
import sys
import time
from itertools import groupby
from heapq import *


def clean(s):
    """
        Returns a cleaned, lowercased string
    """
    return " ".join(re.findall(r'\w+', s,flags = re.UNICODE | re.LOCALE)).lower()

def concatenateReviews(trainData,sentiment):
    concatenatedReviews = ""
    num_reviews = len(trainData["review"])
    
    for x in xrange(0, num_reviews/100):
        if (trainData["sentiment"][x] == sentiment ):
            concatenatedReviews = concatenatedReviews + clean(trainData["review"][x])

    return concatenatedReviews

def comprimir(algo):
    return lzma.compress(algo) # posibles: huffman(algo) bz2.compress(algo)

def test():
    myFileDir = os.path.dirname(os.getcwd()) + "/data/testData.tsv"
    preds = []
    i = 0
    for e, line in enumerate(open(myFileDir, "rb")):
        if e > 0:
            i = i + 1
            print (i)
            r = line.strip().split("\t")
            id = r[0]
            testReview = r[1]
            clean(testReview);
            
            testPositiveConcat = positiveConcat + testReview
         
            testNegativeConcat = negativeConcat + testReview
         
            compressedTestPositive = comprimir(testPositiveConcat)
            
            compressedTestNegative = comprimir(testNegativeConcat)
            
            positiveDiff = sys.getsizeof(compressedTestPositive) - sys.getsizeof(compressedPositiveConcat)
        
            negativeDiff = sys.getsizeof(compressedTestNegative) - sys.getsizeof(compressedNegativeConcat)
         
            if (positiveDiff < negativeDiff):
                estimatedSentiment = 1
            else:
                estimatedSentiment = 0
            preds.append([id, estimatedSentiment ])
            
            #if ( i > 500):
            #    break
    with open("popcorn.csv", "wb") as outfile:
        outfile.write('"id","sentiment"' + "\n")
        for p in preds:
            outfile.write("%s,%s\n" % (p[0], p[1]))

if __name__ == '__main__':
    
    start_time = time.time()
    
    myFileDir = os.path.dirname(os.getcwd()) + "/data/labeledTrainData.tsv"
    
    trainData = pd.read_csv(myFileDir, header=0, delimiter="\t", quoting=3)
    
    positiveConcat = concatenateReviews(trainData, sentiment=1)
    
    negativeConcat = concatenateReviews(trainData, sentiment=0)
    
    compressedPositiveConcat = comprimir(positiveConcat)
    
    compressedNegativeConcat = comprimir(negativeConcat)
    print"Processing... \n"    
    test()
    print"--- %s seconds ---" % (time.time() - start_time)
    # LZMA 0.67596 usando los primeros 2500 reviews
    # LZMA 0.67 usando los primeros 250 reviews
    # huffman 0.53 usando 250
    # LZMA  0.70208 con 250 y el archivo limpiado por el coso del perceptron
    # LZMA 0.70360 con los primeros 500 con 25000 y los demas con 250
    
    
    
    
    
''' 
'
' ------------------------------------------ HUFFMAN: sacado de internet---------------------------------------------------
'
'''
class Node(object):
    left = None
    right = None
    item = None
    weight = 0

    def __init__(self, i, w):
        self.item = i
        self.weight = w

    def setChildren(self, ln, rn):
        self.left = ln
        self.right = rn

    def __repr__(self):
        return "%s - %s -- %s _ %s" % (self.item, self.weight, self.left, self.right)

    def __cmp__(self, a):
        return cmp(self.weight, a.weight)



def huffman(input):
    itemqueue =  [Node(a,len(list(b))) for a,b in groupby(sorted(input))]
    heapify(itemqueue)
    while len(itemqueue) > 1:
        l = heappop(itemqueue)
        r = heappop(itemqueue)
        n = Node(None, r.weight+l.weight)
        n.setChildren(l,r)
        heappush(itemqueue, n)
    codes = {}
    def codeIt(s, node):
        if node.item:
            if not s:
                codes[node.item] = "0"
            else:
                codes[node.item] = s
        else:
            codeIt(s+"0", node.left)
            codeIt(s+"1", node.right)
    
    codeIt("",itemqueue[0])
        
    return "".join([codes[a] for a in input]) #return ([codes[a] for a in input])

''' 
'
'-----------------------------------------------FIN DE HUFFMAN---------------------------------------------------
'
''' 
    
