# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall

# Nome do executável
TARGET = graph

# Lista de arquivos-fonte
SOURCES = graph.c

# Lista de arquivos objeto gerados
OBJECTS = $(SOURCES:.c=.o)

# Regra principal
all: $(TARGET)

# Compilação do executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regra para compilar os arquivos-fonte
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Executar os casos de teste
test: $(TARGET)
	@echo "Executando teste de DFS com matriz de adjacência..."
	@./$(TARGET) matrix

	@echo "\nExecutando teste de DFS com lista de adjacência..."
	@./$(TARGET) list

# Limpar arquivos objeto e executável
clean:
	rm -f $(TARGET) *.o
