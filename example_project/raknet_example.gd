
extends Node

var peer

func _ready():
	# Create a peer object using the custom RakNetExample C++ class.
	peer = RakNetExample.new()
	# Enable the _process function to be called every frame, so we can listen
	# to incoming packets.
	set_process(true)
	pass
	
func _process(delta):
	# receive_packets function returns us an Array of Strings. Both Array and
	# String are core classes of the Godot engine.
	var packets = peer.receive_packets()
	if !packets.empty():
		for m in packets:
			_show_message("Received a packet:\n" + "    " + m)

func _on_btn_startup_pressed():
	get_node("btn_startup").set_disabled(true)
	var port = get_node("in_local_port").get_text()
	peer.startup(port.to_int())
	_show_message("Started peer on port " + port)
	pass

func _on_btn_listen_pressed():
	get_node("btn_listen").set_disabled(true)
	get_node("btn_connect").set_disabled(true)
	peer.listen()
	_show_message("Listening for a connection...")
	pass

func _on_btn_connect_pressed():
	get_node("btn_listen").set_disabled(true)
	get_node("btn_connect").set_disabled(true)
	var remote_ip = get_node("in_remote_ip").get_text()
	var remote_port = get_node("in_remote_port").get_text()
	peer.connect(remote_ip, remote_port.to_int())
	_show_message("Connection request sent to " + remote_ip + ":" + remote_port)
	pass

func _on_btn_disconnect_pressed():
	peer.shutdown()
	_show_message("Shutdown function called")
	get_node("btn_startup").set_disabled(false)
	get_node("btn_listen").set_disabled(false)
	get_node("btn_connect").set_disabled(false)
	pass

# A simple function to print the messages on the rich text box in the scene.
func _show_message(var msg):
	get_node("lbl_text").newline()
	get_node("lbl_text").add_text(msg)
	pass
	
