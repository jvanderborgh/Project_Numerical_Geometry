#
#  Makefile for MAC OS (cocoa) 
#
#     make all   (construction de l'executable)
#     make clean (effacement des fichiers objets et de l'executable)
#
#  A adapter en fonction des ordinateurs/environnements 
#  Compilateur, edition de liens, 
#
GLFWINCLUDE  = /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/include
GLFWLIBRARY  = /Users/julienvdb/Documents/UCL_Master2/Q9/Numerical_Geometry_LMECA2170/Projet/glfw-3.2.1/build/src/libglfw3.a
DEVLIB = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer
#
CC       = gcc  
LD       = gcc
CFLAGS   = -isysroot $(DEVLIB)/SDKs/MacOSX10.12.sdk -mmacosx-version-min=10.11 -I$(GLFWINCLUDE) -O3 -Dgraphic -Wall -g
LFLAGS   = -isysroot $(DEVLIB)/SDKs/MacOSX10.12.sdk -mmacosx-version-min=10.11 -Wl,-search_paths_first -Wl,-headerpad_max_install_names -g -Wall -O3 -framework AGL -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo
LIBS     = $(GLFWLIBRARY) -lm
#
PROG     = myFem
LISTEOBJ = \
  homework.o   fem.o   glfem.o  main.o
# ATTENTION... aucun caractere apres le caractere de continuation "\"
#
# compilation
#
.c.o :
	$(CC) -c  $(CFLAGS) -o $@ $<
# ATTENTION... la ligne precedente doit commencer par une tabulation
#
# dependances
#
all        : $(PROG)
homework.o : homework.c fem.h
fem.o      : fem.c fem.h
glfem.o    : glfem.c fem.h glfem.h
main.o     : main.c fem.h glfem.h
#
# edition de lien
#
$(PROG) : $(LISTEOBJ)
	$(LD) -o $(PROG) $(LFLAGS) $(LISTEOBJ) $(LIBS)
# ATTENTION... la ligne precedente doit commencer par une tabulation
#
# effacement des fichiers intermediaires
#
clean :
	rm -vf $(PROG) $(LISTEOBJ) core a.out
# ATTENTION... la ligne precedente doit commencer par une tabulation
#
# ATTENTION... il faut une ligne vide a la fin du fichier.


