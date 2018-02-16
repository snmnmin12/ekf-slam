from websocket_server import WebsocketServer
import numpy as np
import matplotlib.pyplot as plt
import json

plt.ion()
plt.show()
# Called for every client connecting (after handshake)
def new_client(client, server):
	print('connected!')
	# print("New client connected and was given id %d" % client['id'])
	server.send_message_to_all("Hey all, a new client has joined us")


# Called for every client disconnecting
def client_left(client, server):
	print("disconnected!")
	# print("Client(%d) disconnected" % client['id'])


# Called when a client sends a message
def message_received(client, server, message):
	# print(message)
	plt.clf()
	jData = json.loads(message)
	for i in range(len(jData)):
		data = jData[str(i+1)]
		X = np.array(data['x'])
		Y = np.array(data['y'])
		settings = data['settings']

		if 'marker' in settings:
			plt.plot(X, Y, color=settings['color'], marker=settings['marker'],markersize=int(settings['markersize']), \
				linestyle=settings['linestyle'], linewidth=int(settings['linewidth']))
		else:
			plt.plot(X, Y, color=settings['color'])
	plt.pause(0.001)


PORT=9001
server = WebsocketServer(PORT)
server.set_fn_new_client(new_client)
server.set_fn_client_left(client_left)
server.set_fn_message_received(message_received)
server.run_forever()
