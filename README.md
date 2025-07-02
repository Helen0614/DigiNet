# Digit Classification Neural Network (MNIST) in C

This project implements a multi-layer neural network in pure C for handwritten digit classification using the MNIST dataset. The implementation uses optimized matrix operations and C programming techniques for efficient data processing.

## 🔍 Project Description

This program implements a fully connected, feed-forward neural network with 4 layers:
- Processes 28x28 pixel images (784 features) of handwritten digits
- Uses the ReLU activation function in hidden layers
- Classifies digits from 0 to 9
- Evaluates model performance with accuracy metrics
- Allows ASCII visualization of images and predictions

## 🏗️ Neural Network Architecture

The neural network has the following architecture:

```
Input: 784 neurons (28x28 image)
    ↓
Layer 1: 784 → 200 neurons + ReLU
    ↓
Layer 2: 200 → 100 neurons + ReLU
    ↓
Layer 3: 100 → 50 neurons + ReLU
    ↓
Layer 4: 50 → 10 neurons (output)
    ↓
Argmax: Final classification (0-9)
```

## 📁 Project Structure

```
DigiNet/
├── digiNet.c           # Main source code
├── digiNet.h           # Application header
├── func.c              # Neural network and utility functions
├── README.md           
├── csvs/
│   ├── data.csv        # MNIST dataset
│   └── digits.csv      # Digit labels (60,000 samples)
└── parameters/
    ├── weights0_1.csv  # Layer 1 weights (784x200)
    ├── weights1_1.csv  # Layer 2 weights (200x100)
    ├── weights2_1.csv  # Layer 3 weights (100x50)
    ├── weights3_1.csv  # Layer 4 weights (50x10)
    ├── biases0_1.csv   # Layer 1 biases (200 values)
    ├── biases1_1.csv   # Layer 2 biases (100 values)
    ├── biases2_1.csv   # Layer 3 biases (50 values)
    └── biases3_1.csv   # Layer 4 biases (10 values)
```



## 🚀 Compilation and Execution

### Requirements
- GCC compiler
- POSIX-compatible OS (Linux, macOS, WSL, or Windows with GCC)
- At least 500MB of free RAM to load the dataset

### Compilation
```bash
gcc -o digiNet digiNet.c func.c
```

### Execution
```bash
./digiNet 1
```

The numeric argument indicates the number of processes (currently only 1 is supported).


## 📊 Features

### Data Loading
- **Dataset**: 60,000 MNIST training images
- **Format**: CSV files with normalized pixel values
- **Labels**: Digits from 0 to 9

### Implemented Operations
1. **Matrix multiplication** (`mat_mul`): Matrix product A × B
2. **Vector addition** (`sum_vect`): Adds bias vector to each matrix row
3. **ReLU function** (`relu`): max(0, x) element-wise
4. **Argmax** (`argmax`): Finds the class with the highest probability

### Model Evaluation
- Calculates total model accuracy
- Shows execution time statistics for each operation
- Allows inspection of individual images and predictions

### Visualization
The program includes a function to display images in ASCII format:
- `#` for very dark pixels (>191)
- `$` for dark pixels (127-191)
- `O` for gray pixels (63-127)
- `.` for light pixels (<63)


## 🔧 Technical Details

### Memory Management
- Dynamic allocation with `malloc` for all matrices
- Proper memory release with `free`
- Error handling in all file operations

### Performance Measurement
The program measures the execution time of each operation using `clock()`:
- Data loading
- Matrix multiplications
- Activation function application
- Prediction calculation

### Error Handling
- File opening verification
- Data type conversion control
- Input range validation

## 📈 Expected Performance

With the included pretrained parameters, the model should achieve approximately 85-95% accuracy on the test dataset.


## 🛠️ Possible Improvements

- [ ] Separate folders for functions and main code
- [ ] Add functions to improve data visualization
- [ ] Implement real parallelization for multiple processes

## 📝 Notes

- The project is designed for educational and demonstration purposes
- The weights are pretrained and do not require a training phase
- The implementation prioritizes code clarity over computational efficiency

## 🤝 Contributions

This project is part of an academic assignment. Contributions are welcome to improve the implementation or add new features.

---

**Course**: Introduction to Computer Networks and Operating Systems
**University**: University of the Basque Country (UPV/EHU)

---

# Red Neuronal para Clasificación de Dígitos (MNIST) en C

Este proyecto implementa una red neuronal multicapa en C puro para la clasificación de dígitos manuscritos del dataset MNIST. La implementación utiliza operaciones matriciales optimizadas y técnicas de programación en C para el procesamiento eficiente de datos.

## 🔍 Descripción del Proyecto

Este programa implementa una red neuronal feed-forward de 4 capas completamente conectadas que:
- Procesa imágenes de 28x28 píxeles (784 características) de dígitos manuscritos
- Utiliza la función de activación ReLU en capas ocultas
- Clasifica dígitos del 0 al 9
- Evalúa el rendimiento del modelo con métricas de precisión
- Permite visualización ASCII de las imágenes y predicciones

## 🏗️ Arquitectura de la Red Neuronal

La red neuronal tiene la siguiente arquitectura:

```
Entrada: 784 neuronas (imagen 28x28)
    ↓
Capa 1: 784 → 200 neuronas + ReLU
    ↓
Capa 2: 200 → 100 neuronas + ReLU
    ↓
Capa 3: 100 → 50 neuronas + ReLU
    ↓
Capa 4: 50 → 10 neuronas (salida)
    ↓
Argmax: Clasificación final (0-9)
```


## 📁 Estructura del Proyecto

```
DigiNet/
├── digiNet.c           # Código fuente principal
├── digiNet.h           # Librería de la aplicación
├── func.c              # Funciones de red neuronal y utilidades
├── README.md           
├── csvs/
│   ├── data.csv        # Dataset MNIST
│   └── digits.csv      # Etiquetas de los dígitos (60,000 muestras)
└── parameters/
    ├── weights0_1.csv  # Pesos de la capa 1 (784x200)
    ├── weights1_1.csv  # Pesos de la capa 2 (200x100)
    ├── weights2_1.csv  # Pesos de la capa 3 (100x50)
    ├── weights3_1.csv  # Pesos de la capa 4 (50x10)
    ├── biases0_1.csv   # Sesgos de la capa 1 (200 valores)
    ├── biases1_1.csv   # Sesgos de la capa 2 (100 valores)
    ├── biases2_1.csv   # Sesgos de la capa 3 (50 valores)
    └── biases3_1.csv   # Sesgos de la capa 4 (10 valores)
```

## 🚀 Compilación y Ejecución

### Requisitos
- Compilador GCC
- Sistema operativo compatible con POSIX (Linux, macOS, WSL)
- Al menos 500MB de RAM libre para cargar el dataset

### Compilación
```bash
gcc -o digiNet digiNet.c func.c
```

### Ejecución
```bash
./digiNet 1
```

El argumento numérico indica el número de procesos (actualmente solo soporta 1).

## 📊 Funcionalidades

### Carga de Datos
- **Dataset**: 60,000 imágenes de entrenamiento del MNIST
- **Formato**: Archivos CSV con valores de píxeles normalizados
- **Etiquetas**: Dígitos del 0 al 9

### Operaciones Implementadas
1. **Multiplicación de matrices** (`mat_mul`): Producto matricial A × B
2. **Suma vectorial** (`sum_vect`): Suma de vector bias a cada fila de la matriz
3. **Función ReLU** (`relu`): max(0, x) elemento a elemento
4. **Argmax** (`argmax`): Encuentra la clase con mayor probabilidad

### Evaluación del Modelo
- Calcula la precisión total del modelo
- Muestra estadísticas de tiempo de ejecución por operación
- Permite inspección individual de imágenes y predicciones

### Visualización
El programa incluye una función para mostrar las imágenes en formato ASCII:
- `#` para píxeles muy oscuros (>191)
- `$` para píxeles oscuros (127-191)
- `O` para píxeles grises (63-127)
- `.` para píxeles claros (<63)

## 🔧 Detalles Técnicos

### Gestión de Memoria
- Allocación dinámica con `malloc` para todas las matrices
- Liberación apropiada de memoria con `free`
- Control de errores en todas las operaciones de archivo

### Medición de Rendimiento
El programa mide el tiempo de ejecución de cada operación usando `clock()`:
- Carga de datos
- Multiplicaciones matriciales
- Aplicación de funciones de activación
- Cálculo de predicciones

### Manejo de Errores
- Verificación de apertura de archivos
- Control de conversión de tipos de datos
- Validación de rangos de entrada

## 📈 Rendimiento Esperado

Con los parámetros preentrenados incluidos, el modelo debería alcanzar una precisión aproximada del 85-95% en el dataset de prueba.

## 🛠️ Posibles Mejoras

- [ ] Separación de carpetas en funciones y codigo principal
- [ ] Añadir funciones para mejorar la visibilidad de los datos
- [ ] Implementación de paralelización real para múltiples procesos

## 📝 Notas

- El proyecto está diseñado para fines educativos y de demostración
- Los pesos están preentrenados y no requieren fase de entrenamiento
- La implementación prioriza la claridad del código sobre la eficiencia computacional

## 🤝 Contribuciones

Este proyecto es parte de un trabajo académico. Las contribuciones son bienvenidas para mejorar la implementación o añadir nuevas funcionalidades.

---

**Curso**: Introducción a las Redes de Computadores y Sistemas Operativos
**Universidad**: Universidad del País Vasco (UPV/EHU)