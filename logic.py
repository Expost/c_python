import time
import importlib

replaysvr = importlib.import_module("replaysvr")


def init():
    replaysvr.replay_log(0, "logic init")
    return 0


def on_recv(data):
    replaysvr.replay_log(1, "recv replay at %s, data is %s" % (time.time(), data))
    return 100


def exception():
    value = 1 / 0
