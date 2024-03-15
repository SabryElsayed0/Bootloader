import serial, time
# hex = open("FLASHER.hex", "r")
hex = open("D:\ITI\ARM2\TTL_PythonCode_OTA\Record2.txt", "r")
end = "END\n\n"
ttl = serial.Serial('COM4', 9600, 8, 'N', 1)
#ttl.write(':'.encode())

for line in hex :
   for char in line:
      ttl.write(char.encode())
      print(char)
      ttl.read_until('k',1)
   ttl.read_until('k',1)
time.sleep(.5)
for char in end:
   ttl.write(char.encode())
   ttl.read_until('k',1)
   print(char)
