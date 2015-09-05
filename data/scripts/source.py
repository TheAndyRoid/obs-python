import os
import obspython as libobs
#import pygame
from random import randint



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
        FLAGS = 1<<1
        libobs.obs_enter_graphics()
        self.tex = libobs.gs_texture_create(self.width,
                                         self.height,
                                         libobs.GS_BGRA,
                                         LEVELS,
                                         self.pixelbuffer,
                                         libobs.GS_DYNAMIC)
        libobs.obs_leave_graphics()
        print (self.tex)
    @staticmethod
    def create(settings,source):
        print(settings)
        print(source)
        return MySource()    
    def render(self,effect):
        libobs.blog("render")
        rand = randint(0,255)
        self.SetColour(rand,
                       rand,
                       rand,
                       255)
        try:
            libobs.obs_enter_graphics()
            libobs.gs_texture_set_image(self.tex,self.pixelbuffer,self.width*self.bpp,False)
            libobs.gs_reset_blend_state()
            param = libobs.gs_effect_get_param_by_name(effect,"image")        
            libobs.gs_effect_set_texture(param,self.tex)
            libobs.gs_draw_sprite(self.tex,0,self.width,self.height)
        except:
            pass
        finally:
            libobs.obs_leave_graphics()
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
        libobs.obs_enter_graphics()
        libobs.gs_texture_destroy(self.tex)
        libobs.obs_leave_graphics()
    def get_properties(self):
        a = libobs.obs_properties_create()
        print (a) 
        return a


    def SetColour(self,r,g,b,a):
        for i in range(0,self.width*self.height*self.bpp,self.bpp):
            self.pixelbuffer[i] = b  #blue
            self.pixelbuffer[i+1] = g #green
            self.pixelbuffer[i+2] = r #red
            self.pixelbuffer[i+3] = a #alpha


def register():
    #print(os.getcwd())
    #print(src)
    src = libobs.obs_source_info()
    print(src)
    print (src.id)
    src.create = MySource.create
    src.video_render = MySource.render
    src.video_tick = MySource.tick
    src.get_height = MySource.get_height
    src.get_width = MySource.get_width
    src.destroy = MySource.destroy
#    src.get_properties = MySource.get_properties
    
    libobs.obs_register_source(src)
    libobs.blog("###################################################################")
    print ("Registered MySource")

