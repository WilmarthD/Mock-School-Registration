COURSE = cs240
SEMESTER = spring2023
CP_NUMBER = 1
LASTNAME = Wilmarth
GITUSERID = WilmarthD
EXE = scheduler_cp1

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/scheduler.o $(OBJ)/StudentList.o $(OBJ)/CourseList.o $(OBJ)/Student.o $(OBJ)/Course.o
	$(CC) $(FLAGS) $(OBJ)/scheduler.o $(OBJ)/StudentList.o $(OBJ)/CourseList.o $(OBJ)/Student.o $(OBJ)/Course.o -o $@

$(OBJ)/scheduler.o: scheduler.cpp CourseList.h StudentList.h
	$(CC) $(FLAGS) -c scheduler.cpp -o $@

$(OBJ)/StudentList.o: StudentList.cpp Student.h
	$(CC) $(FLAGS) -c StudentList.cpp -o $@

$(OBJ)/CourseList.o: CourseList.cpp Course.h
	$(CC) $(FLAGS) -c CourseList.cpp -o $@

$(OBJ)/Student.o: Student.cpp Course.h
	$(CC) $(FLAGS) -c Student.cpp -o $@
	
$(OBJ)/Course.o: Course.cpp Student.h
	$(CC) $(FLAGS) -c Course.cpp -o $@

#all: scheduler_cp1 (Added lines above after the first scheduler.cpp -o $@)

#scheduler_cp1: scheduler.o
#	g++ scheduler.o -o scheduler_cp1

#scheduler.o: scheduler.cpp
#	g++ -c scheduler.cpp

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz
