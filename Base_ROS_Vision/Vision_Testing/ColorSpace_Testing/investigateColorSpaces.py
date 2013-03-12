

import cv2
import numpy as np
from random import random
from sys import argv
from os import path,mkdir
from time import time
def main():

	if( argv.__len__() < 2 ):
		print "\nError\nUsage: *.py (filename)"
		return -1
	####
	(workingdir,exec_ext) = path.split(path.realpath(__file__))
	pathlist = argv[1:]

	curtime = int(time())

	##Create a base subfolder for the entire procedure
	base_prefix = workingdir + "/Canny_Testing_"+str(curtime)
	mkdir(base_prefix)
	base_prefix = base_prefix + "/"
	ext    = ".png"
	iter   = 15

	conversion_dict = {"LUV":cv2.COLOR_BGR2LUV,"HSV":cv2.COLOR_BGR2HSV,"YUV":cv2.COLOR_BGR2YUV,"YCR_CB":cv2.COLOR_BGR2YCR_CB,"RGB":cv2.COLOR_BGR2RGB,"HLS":cv2.COLOR_BGR2HLS,"XYZ":cv2.COLOR_BGR2XYZ}

	##Loop over all provided files (images)
	for pathname in pathlist:
		(curdir,filename_ext) = path.split(pathname)
		(filename,ext) = path.splitext(filename_ext)
		
		original = cv2.imread(pathname)

		if( original == None ):
			print "\nError\nFile ",pathname," could not be found"
			continue
		####

		##Create a subfolder for every provided file
		file_prefix = base_prefix+filename
		mkdir(file_prefix)
		file_prefix = file_prefix + "/"

		output = []
		##Loop over all conversions specified
		for (name,conv) in conversion_dict.items():
			##Create a subfolder for every conversion
			prefix = file_prefix + name
			mkdir(prefix)
			prefix = prefix + "/"

			output.append("\n\n"+name)

			########
			##No Blur		
			img = cv2.cvtColor(original,conv)
			(ch1,ch2,ch3) = cv2.split(img)
			cv2.imwrite(prefix+"Ch1_NoBlur"+ext,ch1)
			cv2.imwrite(prefix+"Ch2_NoBlur"+ext,ch2)
			cv2.imwrite(prefix+"Ch3_NoBlur"+ext,ch3)

			output.append("\nNo Blur")
			output.append("\nCh1:")
			output.append(get_stats(ch1))
			output.append("\nCh2:")
			output.append(get_stats(ch2))
			output.append("\nCh3:")
			output.append(get_stats(ch3))
			########

			########
			##HSV Pre-Blur
			for i in xrange(iter):
				ch1 = cv2.medianBlur(ch1,3)
				ch2 = cv2.medianBlur(ch2,3)
				ch3 = cv2.medianBlur(ch3,3)
			####
			cv2.imwrite(prefix+"Ch1_PreBlur"+ext,ch1)
			cv2.imwrite(prefix+"Ch2_PreBlur"+ext,ch2)
			cv2.imwrite(prefix+"Ch3_PreBlur"+ext,ch3)


			output.append("\nPreBlur")
			output.append("\nCh1:")
			output.append(get_stats(ch1))
			output.append("\nCh2:")
			output.append(get_stats(ch2))
			output.append("\nCh3:")
			output.append(get_stats(ch3))
			########

			########
			##HSV Post-Blur
			img = cv2.cvtColor(original,conv)
			for i in xrange(iter):
				img = cv2.medianBlur(img,3)
			####
			(ch1,ch2,ch3) = cv2.split(img)
			cv2.imwrite(prefix+"Ch1_PostBlur"+ext,ch1)
			cv2.imwrite(prefix+"Ch2_PostBlur"+ext,ch2)
			cv2.imwrite(prefix+"Ch3_PostBlur"+ext,ch3)

			output.append("\nPostBlur")
			output.append("\nCh1:")
			output.append(get_stats(ch1))
			output.append("\nCh2:")
			output.append(get_stats(ch2))
			output.append("\nCh3:")
			output.append(get_stats(ch3))
			########

			########
			##HSV BothBlur
			for i in xrange(iter):
				ch1 = cv2.medianBlur(ch1,3)
				ch2 = cv2.medianBlur(ch2,3)
				ch3 = cv2.medianBlur(ch3,3)
			####
			cv2.imwrite(prefix+"Ch1_BothBlur"+ext,ch1)
			cv2.imwrite(prefix+"Ch2_BothBlur"+ext,ch2)
			cv2.imwrite(prefix+"Ch3_BothBlur"+ext,ch3)

			output.append("\nBothBlur")
			output.append("\nCh1:")
			output.append(get_stats(ch1))
			output.append("\nCh2:")
			output.append(get_stats(ch2))
			output.append("\nCh3:")
			output.append(get_stats(ch3))
			########
		####
		output_file = open(file_prefix+"MinMaxAvgSdv.txt",'w')
		output_file.write(''.join(output))
	####

	return 0
####

def get_stats(img):
	min = str(img.min())
	max = str(img.max())
	avg = str(img.mean())
	sdv = str(img.std())
	return '\t'.join([min,max,avg,sdv])
####

if __name__=="__main__":
	main()
####
