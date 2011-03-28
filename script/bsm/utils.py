#!/usr/bin/env python

import config
import os
import tempfile
import shutil
import urllib
import signal
import thread
import time
import glob


def write_file(name, data):
	fd, tmp_name = tempfile.mkstemp()
	os.write(fd, data)
	os.close(fd)
	shutil.move(tmp_name, name)

def http_get(url, data=None):
	if data:
		data = urllib.urlencode(data)

	signal.alarm(config.net_timeout)
	f = urllib.urlopen(url, data)
	reply = f.read()
	signal.alarm(0)

	return reply

def update_index(directory):
	msg_index = []
	for msg in glob.glob(directory + "/" + "[0-9]" * 6):
		msg_index.append(os.path.basename(msg))
	msg_index.sort()
	msg_index = '\n'.join(msg_index)
	write_file(directory + "/" + config.msg_index, msg_index)
