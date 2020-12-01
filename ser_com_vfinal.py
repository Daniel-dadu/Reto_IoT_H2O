import time
import serial, os #Importo bibliotecas necesarias no olvidar instalar el serial para python sudo apt-get install python-serial
import mysql.connector
from datetime import date
from datetime import datetime

mydb = mysql.connector.connect( #Conecta con la base de datos
  host = "localhost",
  user = "root",
  password = "",
  database = "wiaH20"
)

puerto = serial.Serial('COM14', baudrate = 9600, timeout = 0.2) #Se abre el puerto serial a un baudrate de 9600, se puede combiar
puerto.isOpen() #Avanza si el puerto está abierto
arduino = serial.Serial('COM3', baudrate = 9600, timeout = 0.2)
arduino.isOpen()

txt = '' #Creamos la variable donde se almacenará lo que llega Geendel puerto
arreglo = '' #Creamos un arreglo que tendrá el resultado de los datos
cuenta = 0 #Es solo para aumentar una cuenta y despliegue datos diferentes, no se necesita para el puerto serial

while(cuenta < 1000): # (cuenta < 10):   #ciclo infinito
    
    time.sleep(3) #Espera 100ms a que se inicialice y limpie el puerto
    #print("dato1:\n")
    
    while puerto.inWaiting() > 0: #Solo que tengamos datos leeemos el puerto
        
        now = datetime.now()
        format = now.strftime('%d-%m-%Y %H:%M:%S')
        
        txt = puerto.readline() #Leemos todo lo del puerto y lo guardamos en la variable txt
        txt = str(txt) #Aunque ya viene como un string, nos aseguramos que sea string
        txt = txt[2:-5] + "*"
        
        
        mycursor = mydb.cursor()
        
        consulta = "INSERT INTO variable (nombre, valor, fecha) VALUES (%s, %s, %s)"
        
        dato = ""
        cont = 0
        for i in txt:
            bole = False
            if (i != ' ' or i != '*'):
                dato += i
            if (i == ' ' or i == '*'):
                bole = True
                cont += 1
            if (bole):
                if(cont == 1):
                    valores = ("Luz 1", float(dato), str(format))
                    mycursor.execute(consulta, valores)
                    mydb.commit()
                if(cont == 2):
                    valores = ("Luz 2", float(dato), str(format))
                    mycursor.execute(consulta, valores)
                    mydb.commit()
                if(cont == 3):
                    valores = ("Piezo eléctrico", float(dato), str(format))
                    mycursor.execute(consulta, valores)
                    mydb.commit()
                if(cont == 4):
                    valores = ("Humedad", float(dato), str(format))
                    mycursor.execute(consulta, valores)
                    mydb.commit()
                if(cont == 5):
                    dato = dato[:-1]
                    valores = ("Temperatura", float(dato), str(format))
                    mycursor.execute(consulta, valores)
                    mydb.commit()
                    cont = 0
                dato = ""
        arduino.write(txt.encode())
        print(txt)
        
    txt = ''
    cuenta += 1

puerto.close()
arduino.close()