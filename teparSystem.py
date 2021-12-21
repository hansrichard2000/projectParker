from pyfirmata import Arduino, util, SERVO, STRING_DATA
import pyfirmata
import time
import pyrebase
import struct
import math

firebaseConfig = {
"apiKey": "AIzaSyDH2rnyq0DCu6eprAdT6eoNKiUqY3TFNqc",
"authDomain": "tepar-af484.firebaseapp.com",
"databaseURL": "https://tepar-af484-default-rtdb.firebaseio.com",
"projectId": "tepar-af484",
"storageBucket": "tepar-af484.appspot.com",
"messagingSenderId": "881141505515",
"appId": "1:881141505515:web:8d5de5f206bfd61ec58dae",
"measurementId": "G-MS4S3B715B"
}

firebase = pyrebase.initialize_app(firebaseConfig)

db = firebase.database()

port = "COM3"
board = Arduino(port)

def msg( text ):
    if text:
        board.send_sysex( STRING_DATA, util.str_to_two_byte_iter( text ) )
# Servo myservo;
# const int in = 7;
# const int out = 6;
# int count = 0;
# int valin = 0;
# int valout = 0;
# int pos =0;
# int cnt;
# int IR = 3;
# int IR2 = 2;
# int IR3 = 4;
# int IR4 = 5;
# int IR5 = 6;
# //int IRgate = 4;
# int LED = 12;
# int LED2 = 11;
# int LED3 = 10;
# int LED4 = 9;
# bool apply = true;
bulb = 13
servo = 8
IR = board.get_pin('d:3:i')
IR2 = board.get_pin('d:2:i')
IR3 = board.get_pin('d:4:i')
IR4 = board.get_pin('d:5:i')
IR5 = board.get_pin('d:6:i')
LED = board.get_pin('d:12:o')
LED2 = board.get_pin('d:11:o')
LED3 = board.get_pin('d:10:o')
LED4 = board.get_pin('d:9:o')
LDR = board.get_pin('a:3:i')

it = pyfirmata.util.Iterator(board)
it.start()

def rotateGate(pin, angle):
    board.digital[pin].mode = SERVO
    board.digital[pin].write(angle)
    time.sleep(0.015)

def parking1(park1):
    if park1 == True:
        db.child("Parking").child("IRA1").child("status").set("off")
    elif park1 == False:
        db.child("Parking").child("IRA1").child("status").set("on")
    else:
        print("Error")

def parking2(park2):
    if park2 == True:
        db.child("Parking").child("IRA2").child("status").set("off")
    elif park2 == False:
        db.child("Parking").child("IRA2").child("status").set("on")
    else:
        print("Error")

def parking3(park3):
    if park3 == True:
        db.child("Parking").child("IRA3").child("status").set("off")
    elif park3 == False:
        db.child("Parking").child("IRA3").child("status").set("on")
    else:
        print("Error")

while True:
    time.sleep(0.5)
    park1 = IR.read()
    park2 = IR3.read()
    park3 = IR4.read()
    gate1 = IR2.read()
    gate2 = IR5.read()
    lightVal = LDR.read()
    if park1 and park2 and park3 and gate1 and gate2 and lightVal == None:
        print("park1:", park1)
        print("park2:", park2)
        print("park3:", park3)
        print("ldr:", lightVal)
        print("gate1:", gate1)
        print("gate2:", gate2)
    else:
        print("park1:", park1)
        print("park2:", park2)
        print("park3:", park3)
        print("ldr:", lightVal)
        print("gate1:", gate1)
        print("gate2:", gate2)

        parking1(park1)

        parking2(park2)
        
        parking3(park3)

        if gate1 == False and gate2 == False:
            rotateGate(servo, 20)
            msg("Open")
        elif gate1 == False and gate2 == True:
            rotateGate(servo, 20)
            msg("Open")
        elif gate2 == False and gate1 == True:
            rotateGate(servo, 20)
            msg("Open")
        else:
            rotateGate(servo, 117)
            msg("Close")
                
        if lightVal > 0.15:
            print("ldr: Wow", lightVal)
            board.digital[bulb].write(0)
            db.child("LDR").child("status").set("off")
        else:
            print("ldr: tinggi", lightVal)
            board.digital[bulb].write(1)
            db.child("LDR").child("status").set("on")