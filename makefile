#program name
prog	=Complex_Transform

#directories
srcDir	=src
binDir	=bin
bldDir	=bld
incDir	=inc
resDir	=res

#flags
cc		=g++
incl	=-I$(incDir)
lib		=-lGL -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -ldl -lXinerama -lXcursor
flag	=-pthread

#classes and objects
classes	=$(shell find $(srcDir) -name "*.cpp")
objects	=$(patsubst $(srcDir)/%,$(bldDir)/%,$(classes:.cpp=.o))

#rules
all:	resources $(prog)

resources: directories
	@mkdir -p $(binDir)/$(resDir)
	@cp -rf $(resDir)/* $(binDir)/$(resDir)

directories:
	@mkdir -p $(binDir)
	@mkdir -p $(bldDir)

$(prog):	$(objects)
	@echo "<<<<< BUILDING >>>>>"
	$(cc) -o $(binDir)/$@ $^ $(lib)

$(bldDir)/%.o:	$(srcDir)/%.cpp
	@echo "<<<< COMPILING >>>>>"
	$(cc) -o $@ -c $< $(flag) $(incl)

clean:
	@rm -rf $(bldDir)
	@echo "cleaning complete"

purge: clean
	@rm -rf $(binDir)
	@echo "Entire village is purged !"
