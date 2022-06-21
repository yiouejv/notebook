# encoding: utf-8
from threading import Thread
from time import ctime, sleep

class Thread_(Thread):
    def __init__(self, target, name=None, args=(), kwargs=None):
        super(Thread_, self).__init__(name=name, args=args, kwargs=kwargs, target=target)

    def run(self):
        super(Thread_, self).run()


def player(song, sec):
    for i in range(2):
        print('Playing %s: %s' % (song, ctime()))
        sleep(sec)


t = Thread_(target=player, args=('热热', 2))
t.start()
t.join()