import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('127.0.0.1', 8080))
s.listen(10)
while True:
	conn, addr = s.accept()
	data = conn.recv(1024)
	print(data)
	conn.send(data)
	conn.close()

