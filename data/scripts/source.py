import OBS




class MySource():
    def __init__(self):
        super()
        self.create = MySource.create
        self.width = 0
        self.height = 0
    @staticmethod
    def create(settings,source):
        return MySource()    
    def render(self):
        pass
    def tick(self):
        pass
    def get_width(self):
        self.width = self.width + 1
        return self.width
    def get_height(self):
        self.height = self.height + 1
        return self.height



def register():
    src = OBS.Source()
    src.create = MySource.create
    src.video_render = MySource.render
    src.video_tick = MySource.tick
    src.get_height = MySource.get_height
    src.get_width = MySource.get_width
    OBS.obs_register_source(src)
    print ("lol")
