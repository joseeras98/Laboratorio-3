#!/usr/bin/python3
# Importar las bibliotecas necesarias
import serial  # Para la comunicación serie
import time    # Para gestionar el tiempo
import csv     # Para trabajar con archivos CSV

# Nombre del archivo CSV en el que se almacenarán los datos
fileName = "output.csv"

# Encabezado para el archivo CSV
encabezado = "Tension1; Tension2; Tension3; Tension4\n"

# Crear una instancia de la clase Serial para la comunicación serie
ser = serial.Serial(
    port='COM3',                # Puerto COM3
    baudrate=9600,              # Velocidad de baudios
    parity=serial.PARITY_NONE,  # Paridad: Ninguna
    stopbits=serial.STOPBITS_ONE,  # Bits de parada: 1
    bytesize=serial.EIGHTBITS,  # Tamaño de bytes: 8 bits
    timeout=20                  # Tiempo de espera (en segundos)
)

# Imprimir un mensaje indicando el puerto al que se ha conectado
print("connected to: " + ser.portstr)

# Imprimir un mensaje indicando que se ha creado el archivo CSV
print("Created file")

# Inicialización de variables
contador = 0     # Contador utilizado más adelante
valores = []     # Lista para almacenar los valores recibidos
file = open(fileName, mode='w', newline='')  # Abrir el archivo CSV en modo escritura ('w')
file.write(encabezado)  # Escribir el encabezado en el archivo CSV

# Número de datos que se esperan recibir antes de cerrar el puerto
num_datos = 100

# Contador de datos recibidos
contador_datos = 0

# Bucle principal
while True:
    # Leer una línea de datos desde el puerto serie, decodificarla y eliminar espacios en blanco
    linea_serie = ser.readline().decode().strip()
    
    # Dividir la línea en valores separados por comas y agregarlos a la lista "valores"
    valores.extend(linea_serie.split(','))
    print(valores)

    # Si hay al menos 4 valores en la lista "valores", procesarlos y escribirlos en el archivo CSV
    if len(valores) >= 4:
        while len(valores) >= 4:
            # Crear una línea con los primeros 4 valores separados por punto y coma
            linea = ";".join([str(valor) for valor in valores[:4]])
            # Escribir la línea en el archivo CSV
            file.write(linea)
            file.write("\n")
            # Eliminar los 4 valores procesados de la lista "valores"
            valores = valores[4:]
            contador += 4

    # Incrementar el contador de datos recibidos
    contador_datos += 1

    # Si se han recibido suficientes datos, salir del bucle principal
    if contador_datos >= num_datos:
        break

# Cerrar el puerto serie y el archivo CSV
ser.close()
file.close()