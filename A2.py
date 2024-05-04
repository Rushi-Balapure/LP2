import copy
class Puzzle8Square:
    def __init__(self,target,matrix,flag=False):
        self.matrix=[]
        self.target = target
        if(flag):
            self.matrix =matrix
    
    @staticmethod
    def GetDistance(i1,j1,i2,j2):
        return abs(i2-i1)+abs(j2-j1)
    
    def FindElement(self,val):
        for i in range(3):
            if(val in self.matrix[i]):
                return (i,self.matrix[i].index(val))
        return -1,-1
    
    @staticmethod
    def PlayNext(l):
        minR=99
        for i in l:
            minR=min(minR,i.GetHeuristic())
        for i in l:
            if(i.GetHeuristic()==minR):
                return i
            
    def GetHeuristic(self):
        r=0
        for i in range(3):
            for j in range(3):
                if(i==2 and j==2):
                    break
                if(self.matrix[i][j]==self.target[i][j]):
                    continue
                i1,j1=self.FindElement(self.target[i][j])
                r+=self.GetDistance(i1,j1,i,j)
        return r

    def SetPuzzle(self):
        self.matrix=[]
        for i in range(3):
            print("Enter the contents of row "+str(i+1)+":")
            self.matrix.append(list(map(int,input().split())))
    def DisplayPuzzle(self):
        if(self.matrix==[]):
            print("Puzzle not set")
            return
        print("Current Puzzle State")
        for i in range(3):
            for j in range(3):
                if(self.matrix[i][j]==-1):
                    print(" ",end=" ")
                else:
                    print(self.matrix[i][j],end=" ")
            print()
    
    def SetMatrix(self,l):
        self.matrix=l
    
    def CanMoveLeft(self,i,j):
        if(j>0 and self.matrix[i][j]==-1):
            return True
        return False
        
    def CanMoveRight(self,i,j):
        if(j<2 and self.matrix[i][j]==-1):
            return True
        return False

    def CanMoveUp(self,i,j):
        if(i>0 and self.matrix[i][j]==-1):
            return True
        return False
    
    def CanMoveDown(self,i,j):
        if(i<2 and self.matrix[i][j]==-1):
            return True
        return False
    
    def MoveLeft(self,i,j):
        l=copy.deepcopy(self.matrix)
        l[i][j],l[i][j-1]=l[i][j-1],l[i][j]
        puzzle = Puzzle8Square()
        puzzle.SetMatrix(l)
        return puzzle
    
    def MoveRight(self,i,j):
        l=copy.deepcopy(self.matrix)
        l[i][j],l[i][j+1]=l[i][j+1],l[i][j]
        puzzle = Puzzle8Square()
        puzzle.SetMatrix(l)
        return puzzle
    
    def MoveUp(self,i,j):
        tempL=[]
        l=[]
        l=copy.deepcopy(self.matrix)
        l[i][j],l[i-1][j]=l[i-1][j],l[i][j]
        puzzle = Puzzle8Square()
        puzzle.SetMatrix(l)
        return puzzle

    def MoveDown(self,i,j):
        tempL=[]
        l=[]
        l=copy.deepcopy(self.matrix)
        l[i][j],l[i+1][j]=l[i+1][j],l[i][j]
        puzzle = Puzzle8Square()
        puzzle.SetMatrix(l)
        return puzzle
    
    @staticmethod
    def ShowAllPossibleMoves(l):
        for i in l:
            i.DisplayPuzzle()
            print("-----------")
    
    def SolvePuzzle(self):
        cost=0
        while(self.GetHeuristic()!=0):
            cost+=1
            i,j = self.FindElement(-1)
            l=[]
            if(self.CanMoveDown(i,j)):
                l.append(self.MoveDown(i,j))
            if(self.CanMoveUp(i,j)):
                l.append(self.MoveUp(i,j))
            if(self.CanMoveLeft(i,j)):
                l.append(self.MoveLeft(i,j))
            if(self.CanMoveRight(i,j)):
                l.append(self.MoveRight(i,j))
            #self.ShowAllPossibleMoves(l)
            self.matrix = self.PlayNext(l).matrix
            self.DisplayPuzzle()
            print("Current heuristic value:",(self.GetHeuristic()))
        return cost

puzzle = Puzzle8Square(True)
puzzle.DisplayPuzzle()
temp=puzzle.SolvePuzzle()
print("Cost:",temp)