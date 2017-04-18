
You must call InitSystem first
You must call ShutdownSystem Last
You must call updatesystem once

You can only load compressed or uncompressed .tga file that are 24 bit or 32 bit.

You can allocate and initilize in the Init function for your state, This will happen once.  If you are restart you dont need to deallocate resources.  If you are pausing, you probably don't want to reinitilze.