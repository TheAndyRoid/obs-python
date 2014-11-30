import OBS
import os
from random import randint




class MySource():
    def __init__(self):
        super()
        self.width = 500
        self.height = 500
        self.bpp = 4
        self.pixelbuffer = bytearray(self.width*self.height*self.bpp)
        self.SetColour(255,255,255,255)
        GS_BGRA = 5
        LEVELS =1  
        FLAGS = 1<<1
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
    def render(self,effect):
        rand = randint(0,255)
        self.SetColour(rand,
                       rand,
                       rand,
                       255)
                       
        OBS.obs_enter_graphics()
        OBS.gs_texture_set_image(self.tex,self.pixelbuffer,self.width*self.bpp,False)
        OBS.gs_reset_blend_state()
        param = OBS.gs_effect_get_param_by_name(effect,"image")        
        OBS.gs_effect_set_texture(param,self.tex)
        OBS.gs_draw_sprite(self.tex,0,self.width,self.height)
        OBS.obs_leave_graphics()
        print(param)
        print("render")
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
    print(os.getcwd())
    src = OBS.Source()
    src.create = MySource.create
    src.video_render = MySource.render
    src.video_tick = MySource.tick
    src.get_height = MySource.get_height
    src.get_width = MySource.get_width
    src.destroy = MySource.destroy
    OBS.obs_register_source(src)
    print ("Registered MySource")

