CPP = g++
OPTS =  -lglut -lGLU -lGL
FILES = OpenGL2DTemplate.cpp BaseTypes.cpp Border.cpp DrawTools.cpp Ball.cpp Player.cpp
APPNAME = firstOpenGlApp

all:
	$(CPP) $(FILES) -o $(APPNAME) $(OPTS)

clean:
	rm $(APPNAME)