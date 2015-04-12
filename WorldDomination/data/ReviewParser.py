import re

import pandas as pd

from bs4 import BeautifulSoup
from nltk.corpus import stopwords

def review_to_words( raw_review ):
    # Function to convert a raw review to a string of words
    # The input is a single string (a raw movie review), and 
    # the output is a single string (a preprocessed movie review)
    #
    # 1. Remove HTML
    review_text = BeautifulSoup(raw_review).get_text() 
    #
    # 2. Remove non-letters        
    letters_only = re.sub("[^a-zA-Z]", " ", review_text) 
    #
    # 3. Convert to lower case, split into individual words
    words = letters_only.lower().split()                             
    #
    # 4. In Python, searching a set is much faster than searching
    #   a list, so convert the stop words to a set
    stops = set(stopwords.words("english"))                  
    # 
    # 5. Remove stop words
    meaningful_words = [w for w in words if not w in stops]   
    #
    # 6. Join the words back into one string separated by space, 
    # and return the result.
    return( " ".join( meaningful_words ))   

if __name__ == '__main__':
    
    # Clean train reviews
    train = pd.read_csv( 'labeledTrainData.tsv', header=0, delimiter="\t", quoting=3)

    clean_train_reviews = []
    
    print "Cleaning and parsing the training set movie reviews...\n"
    for i in xrange( 0, len(train["review"])):
        clean_train_reviews.append(review_to_words(train["review"][i]))
    
    
    output = pd.DataFrame( data={"id":train["id"], "sentiment":train["sentiment"], "review":clean_train_reviews} )
        
    output.to_csv('clean_labeled_train_data.csv', index=False,columns=["id","sentiment","review"], quoting=3)
    print "Wrote clean reviews to clean_labeled_train_data.csv \n"
    
    # Same procedure with test data
    test = pd.read_csv( 'testData.tsv', header=0, delimiter="\t", quoting=3)
    
    clean_test_reviews = []
    
    print "Cleaning and parsing the test set movie reviews...\n"
    for i in xrange( 0, len(test["review"])):
        clean_test_reviews.append(review_to_words(test["review"][i]))
        
    output = pd.DataFrame( data={"id":test["id"],"review":clean_test_reviews} )
        
    output.to_csv('clean_test_data.csv', index=False,columns=["id","review"], quoting=3)
    print "Wrote clean reviews to clean_test_data.csv \n"
