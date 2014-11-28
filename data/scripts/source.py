import OBS




class MySource():
    def __init__(self):
        super()
        self.width = 100
        self.height = 100
        self.bpp = 4
        self.pixelbuffer = bytearray(self.width*self.height*self.bpp)
        self.SetColour(255,255,255,255)
        GS_BGRA = 5
        LEVELS =1  
        FLAGS = 0
        OBS.obs_enter_graphics()
        self.tex = OBS.gs_texture_create(self.width,
                                    self.height,
                                    GS_BGRA,LEVELS,
                                    self.pixelbuffer,
                                    FLAGS)
        OBS.obs_leave_graphics()
        print (self.tex)
    @staticmethod
    def create(settings,source):
        return MySource()    
    def render(self):
        pass
    def tick(self):
        pass
    def get_width(self):
        return self.width
    def get_height(self):
        return self.height
    def destroy(self):
        print(self.tex)
        OBS.obs_enter_graphics()
        OBS.gs_texture_destroy(self.tex)
        OBS.obs_leave_graphics()
    def SetColour(self,r,g,b,a):
        for i in range(0,self.width*self.height*self.bpp,self.bpp):
            self.pixelbuffer[i] = b  #blue
            self.pixelbuffer[i+1] = g #green
            self.pixelbuffer[i+2] = r #red
            self.pixelbuffer[i+3] = a #alpha


def register():
    src = OBS.Source()
    src.create = MySource.create
    src.video_render = MySource.render
    src.video_tick = MySource.tick
    src.get_height = MySource.get_height
    src.get_width = MySource.get_width
    src.destroy = MySource.destroy
    OBS.obs_register_source(src)
    print ("lol")

"""     OBS.obs_enter_graphics()
        self.tex = OBS.gs_texture_create(self.width,
                                    self.height,
                                    GS_BGRA,LEVELS,
                                    self.pixelbuffer,
                                    FLAGS)
        OBS.obs_leave_graphics()
        print (self.tex)"""
"""     print(self.tex)
        OBS.obs_enter_graphics()
        OBS.gs_texture_destroy(self.tex)
        OBS.obs_leave_graphics()"""
