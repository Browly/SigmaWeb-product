from util.stats import *
from util.parser import parse
from util.decorators import run_in_env
from random import randint
from time import time
from subprocess import Popen, PIPE, STDOUT
import os, sys
from glob import glob

PROJECT_PATH = os.getcwd()

def clean_tmp():
    """
    Removes any files leftover in the tmp directory. 
    Also creates the tmp directory if it does not exist.
    """
    if not os.path.exists("tmp"):
        os.mkdir("tmp")
    else:
        for f in glob('tmp/*.exp'):
            os.unlink(f)
        for f in glob('tmp/*.out'):
            os.unlink(f)
        
@run_in_env("tmp")  

def run_analysis(forms):
	if forms['choice'] is 'R':
		blah
	else :
		blah
	return
	
def run_simulation(forms, sigma_settings, array):
    """
    Takes in the variables to be written from the client forms
    and the params from the settings file which determines the
    order of the parameters. 
    Returns a parsed SigmaOutput instance of output file.
    """

    f_name = int(time())
    outfile_name = "%s.out" % f_name
    expfile_name = "%s.exp" % f_name
    randomseed = randint(0, 65534)
    exp = [outfile_name, "n", str(randomseed), forms['RUNTIME'], "1"]
    
    for j in range(0, len(array) - 1):
    	exp.append(array[j])
	
    #for param in sigma_settings['parameters']:
    #    exp.append(forms[param['name']]) #If I want to split it up going to have to make a bunch of these. 
        
    expstr = " ".join(exp)
	# This is where I should create the data file? 
    expfile = open(expfile_name, 'w')
	#This is where it appends to a file that it will give to the c when it asks for it. 
    expfile.write(expstr)
    expfile.flush()
    expfile.close()
    p = Popen(["%s\\sigma\\bin\\%s.exe" % (PROJECT_PATH, sigma_settings['model']), 
               expfile_name], stdout=PIPE, stderr=STDOUT)
			   #Opens the sigma MOdel specified in the settings. and the file to give to the c. 
    p.wait()
    
    out_inst = parse(outfile_name)
    os.remove(expfile_name)
    os.remove(outfile_name)
    
    return out_inst
 
def prepare_file(forms, sigma_settings): #Prepare files takes a form 
	f_name = "INPUT"
	inputfile_name = "%s.dat" %f_name #This will be the input file data
	
	input = []
	for param in sigma_settings['parameters']:
		input.append(forms[param['name']])
		input.append(" ")
	
	inputfile = open(os.path.join("%s/tmp" %(PROJECT_PATH),inputfile_name), 'w') #Create the file
	inputstr = "".join(input)
	inputfile.write(inputstr)
	inputfile.flush()
	inputfile.close()
	
	return input

def set_file(sigma_settings):
	previous = read_file()
	
	for i in range(0,len(previous) - 1):
		sigma_settings['parameters'][i]['default'] = previous[i]
	return 

def read_file():
	previous = []
	
	f_name = "INPUT"
	previousfile_name = "%s.dat" %f_name
	
	previousfile = open(os.path.join("%s/tmp" %(PROJECT_PATH),previousfile_name), 'r')
	line = previousfile.readline()
	previous = line.split(" ")
	
	return previous


def prepare_graphs(parsed_data, graph_settings):
    """
    Takes in parsed SigmaOutput type data from run_simulation,
    returns a dictionary ready to be sent to the client.
    """
    data = {}

    for graph in graph_settings:
        if graph['x-axis'] not in data:
            data[graph['x-axis']] = parsed_data.getColumn(graph['x-axis'])
        if graph['y-axis'] not in data:
            data[graph['y-axis']] = parsed_data.getColumn(graph['y-axis'])
    
    out = {"data": data, "graphs": graph_settings}
    return out

def prepare_tables(parsed_data, table_settings):
    """
    Takes in parsed SigmaOutput type data from run_simulation,
    returns a dictionary ready to be sent to the client.
    """
    data = {}

    for table in table_settings:
        if table['x-axis'] not in data:
            data[table['x-axis']] = parsed_data.getColumn(table['x-axis'])
        if table['y-axis'] not in data:
            data[table['y-axis']] = parsed_data.getColumn(table['y-axis'])
    
    out = {"data": data, "graphs": table_settings}
    return out
    
def prepare_histogram(parsed_data):
    datax = parsed_data.getColumn("Time")
    datay0 = datax.count(0)
    datay1 = datax.count(1)
    data = []
    data.append(datay0)
    data.append(datay1)
    return data

def through_put_get(parsed_data, string):
    data  = parsed_data.getColumn(string)
    data1 = data[len(data) - 1]
    return data1

def through_put_count(parsed_data, string):
	return data
