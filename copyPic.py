'''
Program to copy a list of desired files from 
one directory into a new folder
'''

from os import listdir
from os.path import isfile, join
from shutil import copy

def copyPic ( pictures ):
	path = "/Volumes/NO NAME/DCIM/100CANON/Photos"
	files = [f for f in listdir(path) if isfile(join(path, f))]
	for pic in pictures:
		src = path + "/IMG_" + str(pic) + ".JPG"
		dst = "/Volumes/NO NAME/DCIM/100CANON/ToEdit"
		copy(src, dst)

if __name__ == "__main__":
	copyPic([5893, 5893, 5943, 5943, 5949, 5949, 5964, 5964, 5965, 5965, 5970, 5970, 5972, 5972, 5992, 5992, 5998, 5998, 6000, 6000, 6006, 6006, 6019, 6019, 6031, 6031, 6043, 6043, 6055, 6055, 6061, 6061, 6063, 6063, 6075, 6075, 6087, 6087, 6149, 6149, 6168, 6168, 6171, 6171, 6177, 6177, 6215, 6215, 6228, 6228, 6234, 6234, 6239, 6239, 6245, 6245, 6253, 6253, 6265, 6265, 6279, 6279, 6284, 6284, 6289, 6289, 6292, 6292, 6308, 6308, 6311, 6311, 6314, 6314, 6321, 6321, 6329, 6329, 6333, 6333, 6342, 6342, 6360, 6360, 6365, 6365, 6380, 6380, 6383, 6383, 6386, 6386, 6393, 6393, 6397, 6397, 6418, 6418, 6422, 6422, 6423, 6423, 6424, 6424, 6447, 6447, 6450, 6450, 6456, 6456, 6458, 6458, 6472, 6472, 6494, 6494, 6502, 6502, 6514])