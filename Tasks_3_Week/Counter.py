from collections import Counter
import os
#encoding="utf-8-sig"
def main():
 file = open(r"input.txt", "r")
 wordcount = Counter(file.read().split())
 for item in wordcount.items(): 
     print("{}\t{}".format(*item))

 with open('answer.txt', 'a') as answer:
  for word in wordcount.items(): 
    answer.write("{}\t{}".format(*word)+os.linesep)
    
if __name__ == "__main__":
    main()