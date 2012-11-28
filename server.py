from bottle import *
import settings
import util.compile as compile
from app import *

# Home Page
@get('/')
def index():  
    return template("index", {"info": settings.info})

# Simulate Page
@get('/simulate')
def simulate_get(): 
	#sigma.parameters{i}.default = list[i]
    set_file(settings.sigma)
    return template("simulate", {"info": settings.info, 
                                 "sigma": settings.sigma})
#Sensitivity
@post('/analysis')
def sensitivity():
	c_input = read_file()
	return template("analysis", {"info": settings.info})
	

@post('/simulate')
def simulate_post():
    parsedList = []
    c_input = prepare_file(request.forms, settings.sigma)
    for i in range(0,100):
        parsed = run_simulation(request.forms, settings.sigma, c_input)
        throughput = through_put_get(parsed, "PROFIT")
        out = prepare_graphs(parsed, settings.graphs)
        data = prepare_histogram(parsed)
        parsedList.append(throughput) #All my throughput data =D
        

    maxInt = max(parsedList)
    minInt = min(parsedList)
    numberBins = 10
    binSize = int((maxInt - minInt)/10)
    d = {}
    for put in parsedList:
        bin = int((put - minInt)/binSize)
        if (bin * binSize + minInt) in d:
            d[bin * binSize + minInt] += 1
        else:
            d[bin * binSize + minInt] = 1
            
    return template("results", {"info": settings.info,
                                "bind": out,
                                "parameters": request.forms,
                                "histData": data,
                                "put": d,
                                "settings_params": settings.sigma['parameters']})

# Error 404 (when page is not found)
@error(404)
def error404(error):
    return "Sorry, can't find that page!"

# Static Routes
@get('/<filename:re:.*\.js>')
def javascripts(filename):
    return static_file(filename, root='static/js')

@get('/<filename:re:.*\.css>')
def stylesheets(filename):
    return static_file(filename, root='static/css')

@get('/<filename:re:.*\.(jpg|png|gif|ico)>')
def images(filename):
    return static_file(filename, root='static/img')

@get('/<filename:re:.*\.(eot|ttf|woff|svg)>')
def fonts(filename):
    return static_file(filename, root='static/fonts')
  
# Re-Compile Sigma Model and Clean\Create tmp directory
clean_tmp()
compile.build(settings.sigma['model'])

# Custom Template Path and Run Server with Debug on
TEMPLATE_PATH.insert(0, "./templates/")
print "SigmaWeb Running At: http://%s:%s" % (settings.server['hostname'], settings.server['port'])

run(host=settings.server['hostname'], port=settings.server['port'], quiet=True)
