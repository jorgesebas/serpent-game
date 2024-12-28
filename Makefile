# Nombre del compilador
CXX = g++

# Directorio de los archivos de encabezado
INCLUDEDIR = include

# Banderas del compilador
CXXFLAGS = -Wall -Wextra -I$(INCLUDEDIR)

# Librerías adicionales
LDFLAGS = -lncurses

# Nombre del ejecutable
TARGET = serpent

# Directorio de los archivos fuente
SRCDIR = src

# Directorio de los archivos objeto
OBJDIR = obj

# Directorio para el ejecutable
BINDIR = bin

# Archivos fuente
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Archivos objeto
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

# Ruta completa del ejecutable
EXECUTABLE = $(BINDIR)/$(TARGET)

# Regla para compilar el programa
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)
	
# Regla para compilar archivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Regla para ejecurar el programa
run: $(EXECUTABLE)
	./$(EXECUTABLE)
# Regla para limpiar los archivos generados

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
	rm -rf $(OBJDIR) $(BINDIR)

# Regla para imprimir los archivos fuente y objeto
fuente:
	@echo "Archivos Fuente: $(SOURCES)"
	@echo "Archivos Objeto: $(OBJECTS)"
	@echo "Ejecutable: $(EXECUTABLE)"
