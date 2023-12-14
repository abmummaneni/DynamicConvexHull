
LEDALib = /usr/cots/leda-6.1
LFLAG = -L$(LEDALib) -lleda -lX11 -lm
INC = -I$(LEDALib)/incl
CXX = g++ -g3 
Angle.o: Angle.cpp Angle.h Point.h
	$(CXX) -c Angle.cpp $(INC)
	
Point.o: Point.cpp Point.h
	$(CXX) -c Point.cpp $(INC)

ConcatenableQueue.o: ConcatenableQueue.cpp ConcatenableQueue.h Angle.h Point.h
	$(CXX) -std=c++20 -c ConcatenableQueue.cpp $(INC)
	
TTree.o: TTree.cpp TTree.h Angle.h ConcatenableQueue.h Point.h
	$(CXX) -c TTree.cpp $(INC)
	
timer.o: timer.cpp timer.h TTree.h
	$(CXX) -c timer.cpp $(INC)
	
timer: timer.o TTree.o ConcatenableQueue.o Angle.o Point.o
	$(CXX) -o timer timer.o TTree.o ConcatenableQueue.o Angle.o Point.o

VisTTree.o: VisTTree.cpp TTree.h Angle.h ConcatenableQueue.h Point.h
	$(CXX) -c VisTTree.cpp $(INC)

VisUtils.o: VisUtils.cpp VisUtils.h
	$(CXX) -c VisUtils.cpp $(INC)

minimalLeda.o: minimalLeda.cpp TTree.h Angle.h ConcatenableQueue.h Point.h
	$(CXX) -c minimalLeda.cpp $(INC)
	
minimalLeda: minimalLeda.o TTree.o ConcatenableQueue.o Angle.o Point.o VisUtils.o
	$(CXX) -o minimalLeda minimalLeda.o TTree.o ConcatenableQueue.o Angle.o Point.o VisUtils.o $(LFLAG)

mediumLeda.o: mediumLeda.cpp VisTTree.h TTree.h Angle.h ConcatenableQueue.h Point.h
	$(CXX) -c mediumLeda.cpp $(INC)
	
mediumLeda: mediumLeda.o VisTTree.o TTree.o ConcatenableQueue.o Angle.o Point.o VisUtils.o
	$(CXX) -o mediumLeda mediumLeda.o VisTTree.o TTree.o ConcatenableQueue.o Angle.o Point.o VisUtils.o $(LFLAG)

clean:
	rm -f *.o minimalLeda mediumLeda timer