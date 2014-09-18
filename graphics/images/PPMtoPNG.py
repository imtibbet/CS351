import sys
import os

if __name__ == "__main__":
	if len(sys.argv) != 2 or not os.path.isfile(sys.argv[1]):
		print("pass in file containing .ppm filenames to convert to png");
		exit()

	with open(sys.argv[1]) as ppmListFile:
		ppmFilenames = [filename.strip() for filename in ppmListFile.readlines()]

	for ppmFilename in ppmFilenames:
		pngFilename = ".".join(ppmFilename.split(".")[:-1]) + ".png"
		os.system(" ".join(["convert", ppmFilename, pngFilename]))
		os.system(" ".join(["rm", ppmFilename]))
