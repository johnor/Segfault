import socket
import struct


class Network():
    def __init__(self, ip, port, gyro_input_model_callback, bias_model_callback):
        print("Connecting to ip: {0}, port: {1}".format(ip, port))
        self.ip = ip
        self.port = port

        self.socket = None

        self.reply = bytes()
        self.gyro_input_model_callback = gyro_input_model_callback
        self.bias_model_callback = bias_model_callback

        self.header_format = "II"
        self.header_size = struct.calcsize(self.header_format)

        self.connect()

    def tick(self):
        try:
            if self.socket:
                self.reply = self.reply + self.socket.recv(100)

            while len(self.reply) > self.header_size:
                header_data = self.reply[0:self.header_size]
                (body_length_from_header, command) = struct.unpack(self.header_format, header_data)
                # print("-------Reply:")
                # print("Length: %i" % (body_length_from_header))
                # print("Cmd: %i" % (command))

                struct_type, body_length = self.get_msg_type_and_length(command)

                if len(self.reply) > body_length_from_header + self.header_size:
                    body_data = self.reply[self.header_size:self.header_size + body_length_from_header]

                    if command == 2:
                        (f1, f2, f3) = struct.unpack(struct_type, body_data)
                        body_length = struct.calcsize(struct_type)
                        print("F1: %.2f" % f1)
                        print("F2: %.2f" % f2)
                        print("F3: %.2f" % f3)
                    elif command == 3:
                        (w, x, y, z) = struct.unpack(struct_type, body_data)
                        self.gyro_input_model_callback(w, x, y, z)
                    elif command == 4:
                        (w, x, y, z) = struct.unpack(struct_type, body_data)
                        self.bias_model_callback(w, x, y, z)
                    else:
                        raise SystemExit("Command not supported")

                    self.reply = self.reply[self.header_size + body_length:]
                else:
                    break
        except BlockingIOError:
            pass
        except socket.error as e:
            # print("Unknown socket error: {0}".format(str(e).encode('UTF-8')))
            self.connect()

    def connect(self):
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.setblocking(False)
            self.socket.connect((self.ip, self.port))
        except ConnectionRefusedError:
            print("Connection to server refused")
            self.socket = None
        except BlockingIOError:
            pass

    @staticmethod
    def get_msg_type_and_length(command):
        if command == 2:
            struct_type = "fff"
        elif command == 3 or command == 4:
            struct_type = "ffff"
        else:
            struct_type = None

        if struct_type is None:
            return struct_type, 0

        msg_size = struct.calcsize(struct_type)
        return struct_type, msg_size
