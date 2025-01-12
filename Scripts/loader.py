import os
import GCT
import utils.Graphics.graphicspp as Graphics

directory = GCT.GetGCTFolder()+"\\"+"Scripts\\features"

Graphics.Notification("Starting GCT2 ...")

for filename in os.listdir(directory):
    if filename.endswith(".py"):
        GCT.RunScript(os.path.join(directory, filename))