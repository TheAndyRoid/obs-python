
import obspython as libobs
import os,traceback,sys
import json
from importlib.machinery import SourceFileLoader


class OBSPythonManager():
    def __init__(self,settings,source):
        self.source = source
        self.width = 0
        self.height = 0
        self.bpp = 4

        self.SetColour(255,255,255,255)
        self.multi = 1
        self.rand = 0
        self.liveSource = False
        LEVELS =1  

        
        #print(libobs.obs_module_get_config_path(libobs.obs_current_module(), ""))
        #print(libobs.obs_find_module_file(libobs.obs_current_module(), ""))
        #libobs.obs_data_set_string(settings,"SourceFile",__file__)

    @staticmethod
    def create(settings,source):
        
        #myScene = libobs.obs_scene_create("Fancy Pants")
        #mySource = libobs.obs_scene_get_source(myScene)
        #libobs.obs_add_source(mySource)

        #libobs.obs_set_output_source(0,libobs.obs_scene_get_source(myScene))
        #libobs.obs_scene_release(myScene)
        return OBSPythonManager(settings,source)
    def render(self,effect):
        #Manager does not render
        pass
    def tick(self,seconds):
        pass
    def get_width(self):
        return self.width
    def get_height(self):
        return self.height
    def destroy(self):
        pass
    def get_properties(self):
        print("PythonManager get_properties")
        self.liveSource = True

        self.props = libobs.obs_properties_create()

        #need to load from the save file or new python managers will wipe our scripts
        data = open_json_config_file("PythonScripts.json")
        obsdata = libobs.obs_data_create_from_json(json.dumps(data))
        libobs.obs_source_update(self.source,obsdata) 
        libobs.obs_data_release(obsdata)

        scriptFiles = libobs.obs_properties_add_editable_list(self.props,
                                                    "ScriptFiles",
                                                    "PythonScriptFiles",
                                                    True,
                                                    "*.py",
                                                    "../../data/obs-plugins/obs-python/scripts")

        libobs.obs_properties_apply_settings(self.props,obsdata)        

        return self.props

    def update(self,data):
        #Called when a property is changed.
        print("PythonManager Update")
        #should probably check that script can be loaded and remove it if it cant
        #should still work though
        return

    def save(self,data):
        print("PythonManager Save")

        if self.liveSource:
            filename = "PythonScripts.json"
            scriptFiles = 'ScriptFiles'
            parsed = json.loads(libobs.obs_data_get_json(data))

            savedArray = parsed[scriptFiles]
            try:
                currentArray = open_json_config_file(filename)[scriptFiles]
            except:
                currentArray = []
            
            print (currentArray)
            toRemove = []
            toAdd = []
            
            savedDict = set()
            currentDict = set()
            
            for v in currentArray:
                print(v)
                currentDict.add(v['value'])

            for v in savedArray:
                savedDict.add(v['value'])
                        
            for k in savedDict:
                print(k)
                if k not in currentDict:
                    toAdd.append(k)

            for k in currentDict:
                print(k)
                if k not in savedDict:
                    toRemove.append(k)
                    
            print (toRemove)

            for script in toAdd:
                run_register(script)

            save_json_config_file(parsed,filename)        
            self.liveSource = False
            
        return





    @staticmethod
    def get_name():
        return "PythonManager"

    def SetColour(self,r,g,b,a):
        for i in range(0,self.width*self.height*self.bpp,self.bpp):
            self.pixelbuffer[i] = b  #blue
            self.pixelbuffer[i+1] = g #green
            self.pixelbuffer[i+2] = r #red
            self.pixelbuffer[i+3] = a #alpha

def register():

    src = libobs.obs_source_info()
    src.id = "PythonManager"
    src.get_name = OBSPythonManager.get_name
    src.create = OBSPythonManager.create
    src.video_render = OBSPythonManager.render
    src.video_tick = OBSPythonManager.tick
    src.get_height = OBSPythonManager.get_height
    src.get_width = OBSPythonManager.get_width
    src.destroy = OBSPythonManager.destroy
    src.get_properties = OBSPythonManager.get_properties
    src.update = OBSPythonManager.update
    src.save = OBSPythonManager.save
    libobs.obs_register_source(src)

    print ("Registered OBSPythonManager")


def open_json_config_file(filename):
    #get correct config filepath
    filepath = libobs.obs_module_get_config_path(libobs.obs_current_module(),filename)
    print (filepath)

    try:
        fd = open(filepath,'r')
    except FileNotFoundError:
        dirpath = os.path.dirname(filepath)
        if not os.path.exists(dirpath):
            os.makedirs(dirpath)
        emptyDict = {}
        #create the empty file 
        save_json_config_file(emptyDict,filename)
        fd = open(filepath,'r')               
    data = json.load(fd)
    #print(data)
    fd.close()
    return data

def save_json_config_file(data,filename):
    filepath = libobs.obs_module_get_config_path(libobs.obs_current_module(),filename)
    fd = open(filepath,'w+')               
    json.dump(data,fd)
    fd.close()

def run_register(scriptFile):
    scriptName = os.path.basename(scriptFile)
    script = SourceFileLoader(scriptName, scriptFile).load_module()
    try:
        script.register()
        print ("Loaded '%s' from '%s'"%(scriptName,scriptFile))
    except Exception as e:
        print("Failed to load '%s' from '%s'"%(scriptName,scriptFile), file=sys.stderr)
        traceback.print_exc()
        

def register_scripts():
    #Get other scripts from config file
    filename = "PythonScripts.json"
    data = open_json_config_file(filename)
    if not data:
        return
    for i in range(0,len(data["ScriptFiles"])):
        #check that script is not already loaded.
        # TODO currently there is no unregister in libobs will need to find another way
        # wonder what happens when we just register again Kappa
        run_register(data["ScriptFiles"][i]["value"])
    

def obs_module_load():

    #log to a file
    os.environ['PYTHONUNBUFFERED'] = '1'
    sys.stdout = open('./stdOut.txt','w',1)
    sys.stderr = open('./stdErr.txt','w',1)
    print(sys.version)

    #load python manager
    register()
    register_scripts()



