#!/usr/bin/env python

import socket
import struct
import time
import binascii
import sys
import traceback

tcpip = '127.0.0.1'
#tcpip = '192.168.137.2'
tcpport = 5001


try:
   s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
   s.connect((tcpip, tcpport))

   data = struct.pack('II50s',  50, 0, b"Testing message")
   print(data)
   print("Sending")
   s.sendall(data)
   print("Send finished")
   
   reply = bytes()
   while 1:
      reply = reply + s.recv(4096)
      if reply:
         headersize = struct.calcsize("II")
         (length, cmd) = struct.unpack("II", reply[0:headersize])
         print("-------Reply:")
         print("Length: %i" % (length))
         print("Cmd: %i" % (cmd))
         
         if cmd == 1:
            msg = struct.unpack(str(length) + "s", reply[headersize:headersize+length])[0]
            msgsize = struct.calcsize(str(length) + "s")
            print("Msg: " + str(msg))
         elif cmd == 2:
            (f1, f2, f3) = struct.unpack("fff", reply[headersize:headersize+length])
            msgsize = struct.calcsize("fff")
            print("F1: %.2f" % (f1))
            print("F2: %.2f" % (f2))
            print("F3: %.2f" % (f3))
         
         reply = reply[headersize+msgsize:]

   s.close()

except socket.timeout:
   print("Connection timed out")
except Exception as err:
   print("Unknown exception")
   print(traceback.format_exc())



