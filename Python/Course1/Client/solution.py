import socket
import time


class ClientError(Exception):
    pass


class Client:
    def __init__(self, host, port, timeout=None):
        self.sock = socket.create_connection((host, port), timeout)

    def put(self, metric, value, timestamp=None):
        if timestamp is None:
            timestamp = int(time.time())
        self.sock.sendall("put {0} {1} {2}\n".format(metric, value, timestamp).encode())

        response = str(self.sock.recv(1024).decode()).strip().split('\n')
        if response[0] == 'error':
            raise ClientError

    def get(self, metric):
        self.sock.sendall("get {0}\n".format(metric).encode())
        response = str(self.sock.recv(1024).decode()).strip().split('\n')

        if response[0] != 'ok':
            raise ClientError

        result = dict()

        del response[0]

        for rsp in response:
            try:
                line = rsp.split(' ')
                if line[0] in result:
                    result[line[0]].append((int(line[2]), float(line[1])))
                    result[line[0]].sort(key=lambda x: (x[0]))
                else:
                    result[line[0]] = [(int(line[2]), float(line[1]))]
            except Exception:
                raise ClientError

        return result
