import nltk
nltk.download('words')
from nltk.corpus import words

class node:
    def __init__(self, val = None):
        self.val = val
        self.end = False
        self.left = None
        self.right = None
        self.equal = None


class TST:
    def __init__(self):
        self.root = None
        self.vol = 0
    
    def insert(self, word):
        if self.root == None:
            self.root = node(word[0])
        curr, index = self.root, 0
        while index < len(word):
            l = word[index]
            if l < curr.val:
                if curr.left == None:
                    curr.left = node(l)
                curr = curr.left
            elif l > curr.val:
                if curr.right == None:
                    curr.right = node(l)
                curr = curr.right
            elif l == curr.val:
                if index + 1 == len(word):
                    if not curr.end:
                        self.vol += 1
                    curr.end = True
                if curr.equal == None:
                    if index + 1 < len(word):
                        curr.equal = node(word[index + 1])
                curr = curr.equal
                index += 1
                
    def search(self, word):
        curr, index = self.root, 0
        while index < len(word):
            if curr == None:
                return False
            l = word[index]
            if l < curr.val:
                curr = curr.left
            elif l > curr.val:
                curr = curr.right
            elif l == curr.val:
                if index + 1 == len(word) and curr.end:
                     return True
                curr = curr.equal
                index += 1
        return False
    
    def traverseRecursive(self, curr, l, word):
        if curr == None:
            return
        if curr.end:
            l.append(word + curr.val)
        self.traverseRecursive(curr.left, l, word)
        self.traverseRecursive(curr.right, l, word)
        self.traverseRecursive(curr.equal, l, word + curr.val)
        
    
    def traverse(self, node):
        l = []
        word = ""
        self.traverseRecursive(node, l, word)
        return l
    
    def partialSearch(self, prefix):
        curr, index = self.root, 0
        end = None
        while index < len(prefix):
            if curr == None:
                break
            l = prefix[index]
            if l < curr.val:
                curr = curr.left
            elif l > curr.val:
                curr = curr.right
            elif l == curr.val:
                if index + 1 == len(prefix):
                     end = curr
                     break
                curr = curr.equal
                index += 1
              
        if end == None:
            return []
        suffixes = self.traverse(end.equal)
        matches = [prefix + suffix for suffix in suffixes]
        return matches
    
    def delete(self, word):
        curr, index = self.root, 0
        while index < len(word):
            if curr == None:
                return
            l = word[index]
            if l < curr.val:
                curr = curr.left
            elif l > curr.val:
                curr = curr.right
            elif l == curr.val:
                if index + 1 == len(word) and curr.end:
                    self.vol -= 1
                    curr.end = False
                curr = curr.equal
                index += 1
        return
    
    def searchNode(self, node, suffix):
        curr, index = node, 0
        while index < len(suffix):
            if curr == None:
                return False
            l = suffix[index]
            if l < curr.val:
                curr = curr.left
            elif l > curr.val:
                curr = curr.right
            elif l == curr.val:
                if index + 1 == len(suffix) and curr.end:
                     return True
                curr = curr.equal
                index += 1
        return False
        
    def recurLeftRightNodes(self, node, suffix, l):
        if node == None:
            return 
        if self.searchNode(node.equal, suffix):
            l.append(node.val)
        self.recurLeftRightNodes(node.left, suffix, l)
        self.recurLeftRightNodes(node.right, suffix, l)
        
    
    def omissionSearch(self, word, i):
        prefix = word[:i]
        suffix = word[i:]
        curr, index = self.root, 0
        end = None
        while index < len(prefix):
            if curr == None:
                break
            l = prefix[index]
            if l < curr.val:
                curr = curr.left
            elif l > curr.val:
                curr = curr.right
            elif l == curr.val:
                if index + 1 == len(prefix):
                     end = curr
                     break
                curr = curr.equal
                index += 1
                
        if end == None:
            return None
        
        curr = end.equal
        l = []
        self.recurLeftRightNodes(curr, suffix, l)
        matches = [prefix + c + suffix for c in l]
        return matches
        
    def nearestNeighborSearch(self, word):
        matches = []
        # OMISSION SEARCH ORDER 1
        for i in range(1, len(word)):
            matches += self.omissionSearch(word, i)
        # INSERTION SEARCH ORDER 1
        for i in range(0, len(word)):
            s = word[:i] + word[i+1:]
            if self.search(s):
                matches.append(s)
        return matches
                
    def insertWords(self, vocabulary):
        for word in vocabulary:
            self.insert(word)
            
            
tst = TST()
tst.insertWords(words.words())
#tst.insertWords(['abcd', 'adcb', 'aedf', 'abce', 'afgs', 'aabc', 'abed', 'abtd', 'ad'])
#print(tst.nearestNeighborSearch('abd'))
